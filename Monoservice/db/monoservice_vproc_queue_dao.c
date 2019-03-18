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

#include <monoservice/db/monoservice_vproc_queue_dao.h>

guint64
monoservice_vproc_queue_dao_create(MonoserviceMysqlConnector *mysql_connector)
{
  gchar *query;
  guint64 vproc_queue_id;

  GError *error;

  query = g_strdup("INSERT INTO VPROC_QUEUE DEFAULT VALUES");
  vproc_queue_id = 0;

  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     &vproc_queue_id,
					     NULL,
					     NULL,
					     NULL, NULL,
					     &error);

  g_free(query);
  
  return(vproc_queue_id);
}

void
monoservice_vproc_queue_dao_delete(MonoserviceMysqlConnector *mysql_connector,
				   guint64 vproc_queue_id)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("DELETE FROM VPROC_QUEUE WHERE VPROC_QUEUE_ID = '%lu'", vproc_queue_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

gchar**
monoservice_vproc_queue_dao_select(MonoserviceMysqlConnector *mysql_connector,
				   guint64 vproc_queue_id)
{
  gchar ***table;
  gchar **strv;
  gchar *query;

  GError *error;

  query = g_strdup_printf("SELECT * FROM VPROC_QUEUE WHERE VPROC_QUEUE_ID = '%lu'", vproc_queue_id);

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
monoservice_vproc_queue_dao_set_video_file(MonoserviceMysqlConnector *mysql_connector,
					   guint64 vproc_queue_id,
					   guint64 video_file)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE VPROC_QUEUE SET VIDEO_FILE = '%lu' WHERE VPROC_QUEUE_ID = '%lu'", video_file, vproc_queue_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_vproc_queue_dao_set_raw_video_file(MonoserviceMysqlConnector *mysql_connector,
					       guint64 vproc_queue_id,
					       guint64 raw_video_file)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE VPROC_QUEUE SET RAW_VIDEO_FILE = '%lu' WHERE VPROC_QUEUE_ID = '%lu'", raw_video_file, vproc_queue_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_vproc_queue_dao_set_title_strip_video_file(MonoserviceMysqlConnector *mysql_connector,
						       guint64 vproc_queue_id,
						       guint64 title_strip_video_file)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE VPROC_QUEUE SET TITLE_STRIP_VIDEO_FILE = '%lu' WHERE VPROC_QUEUE_ID = '%lu'", title_strip_video_file, vproc_queue_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_vproc_queue_dao_set_end_credits_video_file(MonoserviceMysqlConnector *mysql_connector,
						       guint64 vproc_queue_id,
						       guint64 end_credits_video_file)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE VPROC_QUEUE SET END_CREDITS_VIDEO_FILE = '%lu' WHERE VPROC_QUEUE_ID = '%lu'", end_credits_video_file, vproc_queue_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_vproc_queue_dao_set_started(MonoserviceMysqlConnector *mysql_connector,
					guint64 vproc_queue_id,
					gboolean started)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE VPROC_QUEUE SET STARTED = %s WHERE VPROC_QUEUE_ID = '%lu'", (started ? "true": "false"), vproc_queue_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_vproc_queue_dao_set_completed(MonoserviceMysqlConnector *mysql_connector,
					  guint64 vproc_queue_id,
					  gboolean completed)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE VPROC_QUEUE SET COMPLETED = %s WHERE VPROC_QUEUE_ID = '%lu'", (completed ? "true": "false"), vproc_queue_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}
