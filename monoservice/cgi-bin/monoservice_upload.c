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

#include <libsoup/soup.h>

#include <stdlib.h>
#include <stdio.h>
#define _GNU_SOURCE
#include <string.h>

#include <strings.h>

#include <time.h>

void monoservice_upload_write_status(gchar *status_message, guint status_code);
gboolean monoservice_upload_authenticate(gchar *username, gchar *token);

#define MONOSERVICE_UPLOAD_DEFAULT_BUFFER_SIZE (131072)

#define MONOSERVICE_UPLOAD_FORM_DATA_USERNAME "Content-Disposition: form-data; name=\"username\"\r\n\r\n"
#define MONOSERVICE_UPLOAD_FORM_DATA_TOKEN "Content-Disposition: form-data; name=\"token\"\r\n\r\n"

#define MONOSERVICE_UPLOAD_DEFAULT_USERNAME "monothek"
#define MONOSERVICE_UPLOAD_DEFAULT_TOKEN "monothek"

#define MONOSERVICE_UPLOAD_MAX_USERNAME_LENGTH (255)
#define MONOSERVICE_UPLOAD_MAX_TOKEN_LENGTH (8192)

#define MONOSERVICE_UPLOAD_DEFAULT_METHOD "PUT"
#define MONOSERVICE_UPLOAD_DEFAULT_URI "http://monothek.ch/upload/media"

#define MONOSERVICE_UPLOAD_DEFAULT_CONTENT_TYPE "multipart/form-data"

#define MONOSERVICE_UPLOAD_VIDEO_DIRECTORY "/home/joelkraehemann/monoservice/upload/media/video"
#define MONOSERVICE_UPLOAD_AUDIO_DIRECTORY "/home/joelkraehemann/monoservice/upload/media/audio"

#define HTTP_STATUS_MESSAGE_OK "OK"
#define HTTP_STATUS_CODE_OK (200)

#define HTTP_STATUS_MESSAGE_MALFORMED "Bad Request"
#define HTTP_STATUS_CODE_MALFORMED (400)

#define HTTP_STATUS_MESSAGE_FORBIDDEN "Forbidden"
#define HTTP_STATUS_CODE_FORBIDDEN (403)

void
monoservice_upload_write_status(gchar *status_message, guint status_code)
{
  printf("HTTP/1.1 %d %s\r\n", status_code, status_message);
}

gboolean
monoservice_upload_authenticate(gchar *username, gchar *token)
{
  gchar *auth_username, *auth_token;
  gboolean success;

  if(username == NULL ||
     token == NULL ||
     strlen(username) > MONOSERVICE_UPLOAD_MAX_USERNAME_LENGTH ||
     strlen(token) > MONOSERVICE_UPLOAD_MAX_TOKEN_LENGTH){
    return(FALSE);
  }
  
  //FIXME:JK: make more secure
  auth_username = MONOSERVICE_UPLOAD_DEFAULT_USERNAME;
  auth_token = MONOSERVICE_UPLOAD_DEFAULT_TOKEN;  

  success = FALSE;

  if(!g_strcmp0(auth_username,
		username) &&
     !g_strcmp0(auth_token,
		token)){
    success = TRUE;
  }
  
  return(success);
}

int
main(int argc, char **argv)
{
  SoupMessage *media_message;

  SoupBuffer *file;

  GHashTable *form_data_table;

  struct tm *upload_date;
  
  char *str;
  char *buffer;
  char pre_buffer[MONOSERVICE_UPLOAD_DEFAULT_BUFFER_SIZE + 1];
  gchar *content_type;
  gchar *form_data;
  gchar *boundary;
  gchar *username, *token;
  gchar *filename;
  gchar *file_content_type;
  gchar *upload_dir;
  gchar *upload_filename;

  gsize pre_buffer_length;
  gsize content_length;
  gsize num_read;
  time_t upload_timestamp;
  gboolean success;

  /* content type */
  content_type = getenv("CONTENT_TYPE");
  
  /* content length */
  content_length = 0;

  str = getenv("CONTENT_LENGTH");
  
  if(str != NULL){
    content_length = g_ascii_strtoull(str,
				      NULL,
				      10);
  }

  /* check content type and boundary */
  form_data = NULL;
  boundary = NULL;

  if(content_type == NULL ||
     !g_str_has_prefix(content_type,
		       "Content-Type: multipart/form-data;")){
    monoservice_upload_write_status(HTTP_STATUS_MESSAGE_MALFORMED,
				    HTTP_STATUS_CODE_MALFORMED);

    goto upload_MALFORMED;
  }

  content_type = g_strdup("multipart/form-data");
  
  if((str = strstr(content_type, "boundary=")) == NULL){
    monoservice_upload_write_status(HTTP_STATUS_MESSAGE_MALFORMED,
				    HTTP_STATUS_CODE_MALFORMED);

    goto upload_MALFORMED;
  }

  boundary = g_strdup_printf("%s\r\n", str + strlen("boundary="));

  /* username and token has to be located in the first 128KB */
  username = NULL;
  token = NULL;
  
  num_read = fread(pre_buffer, MONOSERVICE_UPLOAD_DEFAULT_BUFFER_SIZE, sizeof(char), stdin);

  pre_buffer_length = num_read;
  pre_buffer[pre_buffer_length] = '\0';

  /* find username */
  str = pre_buffer;

  while((str = strstr(str, boundary)) != NULL){
    str += strlen(boundary);

    if(str[0] == '\0'){
      break;
    }
    
    if(!strncmp(str,
		MONOSERVICE_UPLOAD_FORM_DATA_USERNAME,
		strlen(MONOSERVICE_UPLOAD_FORM_DATA_USERNAME))){
      char *tmp;
      
      str += strlen(MONOSERVICE_UPLOAD_FORM_DATA_USERNAME);
      
      tmp = strstr(str, "\r\n");

      if(tmp != NULL &&
	tmp - str < MONOSERVICE_UPLOAD_MAX_USERNAME_LENGTH){
	username = g_strndup(str,
			     tmp - str);
      }

      break;
    }
  }
  
  /* find token */
  str = pre_buffer;

  while((str = strstr(str, boundary)) != NULL){
    str += strlen(boundary);

    if(str[0] == '\0'){
      break;
    }
    
    if(!strncmp(str,
		MONOSERVICE_UPLOAD_FORM_DATA_TOKEN,
		strlen(MONOSERVICE_UPLOAD_FORM_DATA_TOKEN))){
      char *tmp;
      
      str += strlen(MONOSERVICE_UPLOAD_FORM_DATA_TOKEN);
      
      tmp = strstr(str, "\r\n");

      if(tmp != NULL &&
	tmp - str < MONOSERVICE_UPLOAD_MAX_TOKEN_LENGTH){
	token = g_strndup(str,
			  tmp - str);
      }

      break;
    }
  }
    
  if(!monoservice_upload_authenticate(username, token)){
    monoservice_upload_write_status(HTTP_STATUS_MESSAGE_FORBIDDEN,
				    HTTP_STATUS_CODE_FORBIDDEN);
    
    goto upload_FORBIDDEN;
  }
  
  buffer = (char *) malloc(content_length * sizeof(char));

  memcpy(buffer, pre_buffer, num_read * sizeof(char));

  if(pre_buffer_length < content_length){
    num_read = fread(buffer + pre_buffer_length, (content_length - pre_buffer_length), sizeof(char), stdin);
    buffer[pre_buffer_length + num_read] = '\0';
  }

  /* media message */
  media_message = soup_message_new(MONOSERVICE_UPLOAD_DEFAULT_METHOD,
				   MONOSERVICE_UPLOAD_DEFAULT_URI);
  g_object_ref(media_message);
  
  soup_message_set_request(media_message,
			   MONOSERVICE_UPLOAD_DEFAULT_CONTENT_TYPE,
			   SOUP_MEMORY_STATIC,
			   buffer,
			   content_length);

  /* decode form data */
  filename = NULL;
  file_content_type = NULL;
  file = NULL;

  form_data_table = soup_form_decode_multipart(media_message,
					       NULL,
					       &filename,
					       &file_content_type,
					       &file);

  /* date */
  upload_timestamp = 0;
    
  str = g_hash_table_lookup(form_data_table,
			    "media-timestamp");

  if(str != NULL){
    upload_timestamp = (time_t) g_ascii_strtoull(str,
						 NULL,
						 10);
  }
    
  upload_date = localtime(upload_timestamp);

  /* create directory */
  upload_dir = g_strdup_printf("%s/%d/%d/%d/%d",
			       MONOSERVICE_UPLOAD_AUDIO_DIRECTORY,
			       upload_date->tm_year,
			       upload_date->tm_mon,
			       upload_date->tm_mday,
			       upload_date->tm_hour);

  g_mkdir_with_parents(upload_dir,
		       0755);

  /* upload filename */
  str = rindex(filename, '/');

  if(str == NULL){
    str = filename;
  }else{
    str++;
  }
  
  upload_filename = g_strdup_printf("%s/%s",
				    upload_dir,
				    str);
  
  if(g_str_has_suffix(filename,
		      ".wav")){
    FILE *f;

    guint8 *data;
    
    gsize length;

    /* audio file */
    soup_buffer_get_data(file,
			 &data,
			 &length);
    
    f = fopen(upload_filename,
	      "w");
    fwrite(data, length, sizeof(guint8), f);

    //TODO:JK: implement me
  }else if(g_str_has_suffix(filename,
			    ".mp4")){
    FILE *f;

    guint8 *data;

    gsize length;

    /* video file */
    soup_buffer_get_data(file,
			 &data,
			 &length);

    f = fopen(upload_filename,
	      "w");
    fwrite(data, length, sizeof(guint8), f);

    //TODO:JK: implement me
  }

  g_object_run_dispose(media_message);
  g_object_unref(media_message);

  soup_buffer_free(file);
  
  g_hash_table_destroy(form_data_table);

  g_free(upload_dir);
  g_free(upload_filename);
  
  g_free(filename);
  g_free(file_content_type);
  
  free(buffer);
  
upload_FORBIDDEN:
  g_free(username);
  g_free(token);
  
upload_MALFORMED:
  g_free(form_data);
  g_free(boundary);
  
  return(0);
}
