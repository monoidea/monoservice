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

#include <monoservice/db/monoservice_soundcard_upload_file_dao.h>

#define USECS_PER_SEC (1000000)

guint64
monoservice_soundcard_upload_file_dao_create(MonoserviceMysqlConnector *mysql_connector,
					     gchar *filename,
					     time_t creation_time,
					     useconds_t duration,
					     gboolean available)
{
  gchar *query;

  guint64 soundcard_upload_file_id;
  gdouble duration_value;

  GError *error;
  
  if(filename == NULL){
    filename = g_strdup("NULL");
  }else{
    filename = g_strdup_printf("'%s'", filename);
  }
  
  duration_value = (gdouble) duration / (gdouble) USECS_PER_SEC;

  query = g_strdup_printf("INSERT INTO SOUNDCARD_UPLOAD_FILE (FILENAME, CREATION_TIME, DURATION, AVAILABLE) VALUES (%s, %ld, %f, %s)",
			  filename,
			  creation_time,
			  duration_value,
			  (available ? "true": "false"));
  soundcard_upload_file_id = 0;

  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     &soundcard_upload_file_id,
					     NULL,
					     NULL,
					     NULL, NULL,
					     &error);

  g_free(filename);

  g_free(query);
  
  return(soundcard_upload_file_id);
}

void
monoservice_soundcard_upload_file_dao_delete(MonoserviceMysqlConnector *mysql_connector,
					     guint64 soundcard_upload_file_id)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("DELETE FROM SOUNDCARD_UPLOAD_FILE WHERE SOUNDCARD_UPLOAD_FILE_ID = '%lu'", soundcard_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

gchar**
monoservice_soundcard_upload_file_dao_select(MonoserviceMysqlConnector *mysql_connector,
					     guint64 soundcard_upload_file_id)
{
  gchar ***table;
  gchar **strv;
  gchar *query;

  GError *error;

  query = g_strdup_printf("SELECT * FROM SOUNDCARD_UPLOAD_FILE WHERE SOUNDCARD_UPLOAD_FILE_ID = '%lu'", soundcard_upload_file_id);

  table = NULL;
  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     NULL,
					     NULL,
					     &table,
					     NULL, NULL,
					     &error);

  g_free(query);

  if(table != NULL){
    strv = table[0];

    g_free(table);
  }

  return(strv);
}

void
monoservice_soundcard_upload_file_dao_set_filename(MonoserviceMysqlConnector *mysql_connector,
						   guint64 soundcard_upload_file_id,
						   gchar *filename)
{
  gchar *query;

  GError *error;

  if(filename == NULL){
    filename = g_strdup("NULL");
  }else{
    filename = g_strdup_printf("'%s'", filename);
  }

  query = g_strdup_printf("UPDATE SOUNDCARD_UPLOAD_FILE SET FILENAME = %s WHERE SOUNDCARD_UPLOAD_FILE_ID = '%lu'", filename, soundcard_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(filename);
  
  g_free(query);
}

void
monoservice_soundcard_upload_file_dao_set_creation_time(MonoserviceMysqlConnector *mysql_connector,
							guint64 soundcard_upload_file_id,
							time_t creation_time)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE SOUNDCARD_UPLOAD_FILE SET CREATION_TIME = %ld WHERE SOUNDCARD_UPLOAD_FILE_ID = '%lu'", creation_time, soundcard_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);
  
  g_free(query);
}

void
monoservice_soundcard_upload_file_dao_set_duration(MonoserviceMysqlConnector *mysql_connector,
						   guint64 soundcard_upload_file_id,
						   useconds_t duration)
{
  gchar *query;

  gdouble duration_value;

  GError *error;

  duration_value = (gdouble) duration / (gdouble) USECS_PER_SEC;

  query = g_strdup_printf("UPDATE SOUNDCARD_UPLOAD_FILE SET DURATION = %f WHERE SOUNDCARD_UPLOAD_FILE_ID = '%lu'", duration_value, soundcard_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);
  
  g_free(query);
}

void
monoservice_soundcard_upload_file_dao_set_available(MonoserviceMysqlConnector *mysql_connector,
						    guint64 soundcard_upload_file_id,
						    gboolean available)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE SOUNDCARD_UPLOAD_FILE SET AVAILABLE = %s WHERE SOUNDCARD_UPLOAD_FILE_ID = '%lu'", (available ? "true": "false"), soundcard_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);
  
  g_free(query);
}
