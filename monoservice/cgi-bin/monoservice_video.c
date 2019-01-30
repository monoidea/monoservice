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
#include <sys/stat.h>
#include <unistd.h>

#include <regex.h>

void monoservice_video_write_status(gchar *status_message, guint status_code);
void monoservice_video_write_content_header(gsize content_length);

gboolean monoservice_video_parse_query_string(gchar **session_id, gchar **token);

gboolean monoservice_video_lookup_resource(gchar *session_id, gchar *token,
					   gchar **resource_id);

gchar* monoservice_video_find_media(gchar *resource_id);

#define MONOSERVICE_VIDEO_BUFFER_SIZE (8192)

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
monoservice_video_write_status(gchar *status_message, guint status_code)
{
  printf("HTTP/1.1 %d %s\r\n", status_code, status_message);
}

void
monoservice_video_write_content_header(gsize content_length)
{
  printf("Cache-Control: no-store, no-cache\r\n");
  printf("Content-Type: video/mp4\r\n");

  if(content_length > 0){
    printf("Content-length: %d\r\n", content_length);
  }
  
  printf("Content-Disposition: attachment; filename=monothek-video.mp4\r\n");

  printf("\r\n");
}

gboolean
monoservice_video_parse_query_string(gchar **session_id, gchar **token)
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
monoservice_video_lookup_resource(gchar *session_id, gchar *token,
				  gchar **resource_id)
{
  gboolean success;
  
  success = FALSE;

  //TODO:JK: implement me

  return(success);
}

gchar*
monoservice_video_find_media(gchar *resource_id)
{
  gchar *filename;

  filename = NULL;

  //TODO:JK: implement me

  return(filename);
}

int
main(int argc, char **argv)
{
  FILE *f;

  struct stat statbuf;    
  
  gchar *video_filename;
  gchar *session_id, *token;
  gchar *resource_id;

  unsigned char data[MONOSERVICE_VIDEO_BUFFER_SIZE];

  size_t num_read;
  gboolean success;
  
  c_locale = newlocale(LC_ALL_MASK, "C", (locale_t) 0);
  uselocale(c_locale);

  /* check parameter */
  session_id = NULL;
  token = NULL;
  
  success = monoservice_video_parse_query_string(&session_id, &token);

  if(!success){
    monoservice_video_write_status(HTTP_STATUS_MESSAGE_MALFORMED,
				   HTTP_STATUS_CODE_MALFORMED);

    goto video_MALFORMED;
  }

  /* lookup resource */
  resource_id = NULL;
  
  success = monoservice_video_lookup_resource(session_id, token,
					      &resource_id);

  if(!success){
    monoservice_video_write_status(HTTP_STATUS_MESSAGE_FORBIDDEN,
				   HTTP_STATUS_CODE_FORBIDDEN);

    goto video_FORBIDDEN;
  }

  video_filename = monoservice_video_find_media(resource_id);
  
  if(video_filename != NULL){
    stat(video_filename, &statbuf);
    
    monoservice_video_write_status(HTTP_STATUS_MESSAGE_OK,
				   HTTP_STATUS_CODE_OK);
    monoservice_video_write_content_header(statbuf.st_size);
    
    f = fopen(video_filename, "r");

    num_read = MONOSERVICE_VIDEO_BUFFER_SIZE;

    while(num_read == MONOSERVICE_VIDEO_BUFFER_SIZE){
      num_read = fread(data, num_read, sizeof(unsigned char), f);

      fwrite(data, num_read, sizeof(unsigned char), stdout);
    }

    fclose(f);
  }else{
    monoservice_video_write_status(HTTP_STATUS_MESSAGE_OK,
				   HTTP_STATUS_CODE_OK);
    monoservice_video_write_content_header(0);
  }
  
video_FORBIDDEN:
  g_free(resource_id);
  
video_MALFORMED:
  g_free(session_id);
  g_free(token);  
  
  return(0);
}
