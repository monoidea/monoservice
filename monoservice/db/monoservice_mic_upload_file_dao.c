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

#include <monoservice/db/monoservice_mic_upload_file_dao.h>

#define USECS_PER_SEC (1000000)

guint64
monoservice_mic_upload_file_dao_create(MonoserviceMysqlConnector *mysql_connector,
				       gchar *filename,
				       time_t timestamp,
				       useconds_t duration,
				       gboolean available)
{
  gchar *query;

  guint64 mic_upload_file_id;
  gdouble duration_value;

  GError *error;
  
  if(filename == NULL){
    filename = g_strdup("NULL");
  }else{
    filename = g_strdup_printf("'%s'", filename);
  }
  
  duration_value = (gdouble) duration / (gdouble) USECS_PER_SEC;

  query = g_strdup_printf("INSERT INTO MIC_UPLOAD_FILE (FILENAME, TIMESTAMP, DURATION, AVAILABLE) VALUES (%s, %ld, %f, %s)",
			  filename,
			  timestamp,
			  duration_value,
			  (available ? "true": "false"));
  mic_upload_file_id = 0;

  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     &mic_upload_file_id,
					     NULL,
					     NULL,
					     NULL, NULL,
					     &error);

  g_free(filename);

  g_free(query);
  
  return(mic_upload_file_id);
}

void
monoservice_mic_upload_file_dao_delete(MonoserviceMysqlConnector *mysql_connector,
				       guint64 mic_upload_file_id)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("DELETE FROM MIC_UPLOAD_FILE WHERE MIC_UPLOAD_FILE_ID = '%lu'", mic_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

gchar**
monoservice_mic_upload_file_dao_select(MonoserviceMysqlConnector *mysql_connector,
				       guint64 mic_upload_file_id)
{
  gchar ***table;
  gchar **strv;
  gchar *query;

  GError *error;

  query = g_strdup_printf("SELECT * FROM MIC_UPLOAD_FILE WHERE MIC_UPLOAD_FILE_ID = '%lu'", mic_upload_file_id);

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
monoservice_mic_upload_file_dao_set_filename(MonoserviceMysqlConnector *mysql_connector,
					     guint64 mic_upload_file_id,
					     gchar *filename)
{
  gchar *query;

  GError *error;

  if(filename == NULL){
    filename = g_strdup("NULL");
  }else{
    filename = g_strdup_printf("'%s'", filename);
  }

  query = g_strdup_printf("UPDATE MIC_UPLOAD_FILE SET FILENAME = %s WHERE MIC_UPLOAD_FILE_ID = '%lu'", filename, mic_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(filename);
  
  g_free(query);
}

void
monoservice_mic_upload_file_dao_set_timestamp(MonoserviceMysqlConnector *mysql_connector,
					      guint64 mic_upload_file_id,
					      time_t timestamp)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE MIC_UPLOAD_FILE SET TIMESTAMP = %ld WHERE MIC_UPLOAD_FILE_ID = '%lu'", timestamp, mic_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);
  
  g_free(query);
}

void
monoservice_mic_upload_file_dao_set_duration(MonoserviceMysqlConnector *mysql_connector,
					     guint64 mic_upload_file_id,
					     useconds_t duration)
{
  gchar *query;

  gdouble duration_value;

  GError *error;

  duration_value = (gdouble) duration / (gdouble) USECS_PER_SEC;

  query = g_strdup_printf("UPDATE MIC_UPLOAD_FILE SET DURATION = %f WHERE MIC_UPLOAD_FILE_ID = '%lu'", duration_value, mic_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);
  
  g_free(query);
}

void
monoservice_mic_upload_file_dao_set_available(MonoserviceMysqlConnector *mysql_connector,
					      guint64 mic_upload_file_id,
					      gboolean available)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE MIC_UPLOAD_FILE SET AVAILABLE = %s WHERE MIC_UPLOAD_FILE_ID = '%lu'", (available ? "true": "false"), mic_upload_file_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);
  
  g_free(query);
}
