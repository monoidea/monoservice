/* Monoservice - monoidea's monoservice
 * Copyright (C) 2019 Joël Krähemann
 *
 * This file is part of Monoservice.
 *
 * Monoservice is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Monoservice is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Monoservice.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <glib-object.h>

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#define _GNU_SOURCE
#include <locale.h>
#include <pthread.h>

#include <sys/types.h>
#include <regex.h>

#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/DOCBparser.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

void monoservice_download_write_status(gchar *status_message, guint status_code);
void monoservice_download_write_content_header(gsize content_length);

gboolean monoservice_download_parse_query_string(gchar **session_id, gchar **token);

gboolean monoservice_download_lookup_resource(gchar *session_id, gchar *token,
					      gchar **resource_id);

#define MONOSERVICE_DOWNLOAD_TEMPLATE_FILENAME SRCDIR "/monoservice.share/xml/monoservice/template/download.xml"
#define MONOSERVICE_DOWNLOAD_XSL_FILENAME SRCDIR "/monoservice.share/xml/monoservice/stylesheet/download.xsl"

#define HTTP_STATUS_MESSAGE_OK "OK"
#define HTTP_STATUS_CODE_OK (200)

#define HTTP_STATUS_MESSAGE_MALFORMED "Bad Request"
#define HTTP_STATUS_CODE_MALFORMED (400)

#define HTTP_STATUS_MESSAGE_FORBIDDEN "Forbidden"
#define HTTP_STATUS_CODE_FORBIDDEN (403)

static locale_t c_locale;
static pthread_mutex_t regex_mutex = PTHREAD_MUTEX_INITIALIZER;

extern int xmlLoadExtDtdDefaultValue;

void
monoservice_download_write_status(gchar *status_message, guint status_code)
{
  printf("HTTP/1.1 %d %s\r\n", status_code, status_message);
}

void
monoservice_download_write_content_header(gsize content_length)
{
  printf("Cache-Control: no-store, no-cache\r\n");
  printf("Content-Type: text/html\r\n");

  if(content_length > 0){
    printf("Content-length: %lu\r\n", content_length);
  }

  printf("\r\n");
}

gboolean
monoservice_download_parse_query_string(gchar **session_id, gchar **token)
{
  regmatch_t match_arr[3];

  char *str;

  int retval;
  gboolean success;
  
  static regex_t parameter_regex;

  static gboolean regex_compiled = FALSE;

  static const gchar *parameter_pattern = "^\\?session-id=([a-z0-9\\-]+)&token=([a-z0-9\\-]+)";

  static const size_t max_matches = 3;

  str = getenv("QUERY_STRING");

  pthread_mutex_lock(&regex_mutex);
  
  if(!regex_compiled){
    regex_compiled = TRUE;
    
    regcomp(&parameter_regex, parameter_pattern, REG_EXTENDED);
  }

  pthread_mutex_unlock(&regex_mutex);  

  regcomp(&parameter_regex, parameter_pattern, REG_EXTENDED);

  retval = regexec(&parameter_regex, str, max_matches, match_arr, 0);
  success = FALSE;
  
  if(retval == 0){
    if(match_arr[1].rm_eo - match_arr[1].rm_so == 36 &&
       match_arr[2].rm_eo - match_arr[2].rm_so == 36){
      success = TRUE;

      if(session_id != NULL){
	session_id[0] = g_strndup(str + match_arr[1].rm_so,
				  36);
      }

      if(token != NULL){
	token[0] = g_strndup(str + match_arr[2].rm_so,
			     36);
      }
    }
  }

  return(success);
}

gboolean
monoservice_download_lookup_resource(gchar *session_id, gchar *token,
				     gchar **resource_id)
{
  gboolean success;
  
  success = FALSE;

  //TODO:JK: implement me

  return(success);
}

int
main(int argc, char **argv)
{
  xmlDoc *template, *html_output;
  xsltStylesheet *stylesheet;

  gchar **param_strv;
  
  xmlChar *template_filename;
  xmlChar *xsl_filename;
  xmlChar *data;
  gchar *session_id, *token;
  gchar *resource_id;

  guint param_count;
  int data_length;
  gboolean success;
  
  c_locale = newlocale(LC_ALL_MASK, "C", (locale_t) 0);
  uselocale(c_locale);

  /* check parameter */
  session_id = NULL;
  token = NULL;
  
  success = monoservice_download_parse_query_string(&session_id, &token);

  if(!success){
    monoservice_download_write_status(HTTP_STATUS_MESSAGE_MALFORMED,
				      HTTP_STATUS_CODE_MALFORMED);

    goto download_MALFORMED;
  }

  /* lookup resource */
  resource_id = NULL;
  
  success = monoservice_download_lookup_resource(session_id, token,
						 &resource_id);

  if(!success){
    monoservice_download_write_status(HTTP_STATUS_MESSAGE_FORBIDDEN,
				      HTTP_STATUS_CODE_FORBIDDEN);

    goto download_FORBIDDEN;
  }
  
  /* XSL params */
  param_count = 1;
  param_strv = (gchar **) malloc(((2 * param_count) + 1) * sizeof(gchar *));
  
  param_strv[0] = g_strdup("mediaURL");
  param_strv[1] = g_strdup_printf("http://monothek.ch/media/monothek-video.mp4?session_id=%s,token=%s",
				  session_id,
				  token);

  param_strv[2] = NULL;
  
  xmlSubstituteEntitiesDefault(1);
  xmlLoadExtDtdDefaultValue = 1;
  
  /* parse XSL */
  xsl_filename = g_strdup(MONOSERVICE_DOWNLOAD_XSL_FILENAME);
  template_filename = g_strdup(MONOSERVICE_DOWNLOAD_TEMPLATE_FILENAME);
  
  stylesheet = xsltParseStylesheetFile(xsl_filename);

  template = xmlParseFile(template_filename);
  
  html_output = xsltApplyStylesheet(stylesheet, template, param_strv);

  data = NULL;
  data_length = -1;
  xsltSaveResultToString(&data, &data_length, html_output, stylesheet);

  /* response */
  if(data != NULL){
    monoservice_download_write_status(HTTP_STATUS_MESSAGE_OK,
				      HTTP_STATUS_CODE_OK);
    monoservice_download_write_content_header(data_length);

    fwrite(data, data_length, sizeof(xmlChar), stdout);

    free(data);
  }else{
    monoservice_download_write_status(HTTP_STATUS_MESSAGE_OK,
				      HTTP_STATUS_CODE_OK);
    monoservice_download_write_content_header(0);
  }
  
  /*  */
  xsltFreeStylesheet(stylesheet);
  xmlFreeDoc(html_output);
  xmlFreeDoc(template);

  xsltCleanupGlobals();
  xmlCleanupParser();
  
  /*  */
  g_strfreev(param_strv);
  
  g_free(xsl_filename);
  
download_FORBIDDEN:
  g_free(resource_id);
  
download_MALFORMED:
  g_free(session_id);
  g_free(token);  
  
  return(0);
}
