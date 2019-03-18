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

#include <monoservice/db/monoservice_vproc_queue_screen_upload_file_dao.h>

void
monoservice_vproc_queue_screen_upload_file_dao_create(MonoserviceMysqlConnector *mysql_connector,
						      guint64 vproc_queue,
						      guint64 screen_upload_file)
{
  gchar *query;

  GError *error;
  
  query = g_strdup_printf("INSERT INTO VPROC_QUEUE_SCREEN_UPLOAD_FILE (VPROC_QUEUE, SCREEN_UPLOAD_FILE) VALUES (%lu, %lu)",
			  vproc_queue,
			  screen_upload_file);

  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     NULL,
					     NULL,
					     NULL,
					     NULL, NULL,
					     &error);

  g_free(query);
}

void
monoservice_vproc_queue_screen_upload_file_dao_delete(MonoserviceMysqlConnector *mysql_connector,
						      guint64 vproc_queue,
						      guint64 screen_upload_file)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("DELETE FROM VPROC_QUEUE_SCREEN_UPLOAD_FILE WHERE VPROC_QUEUE = '%lu' AND SCREEN_UPLOAD_FILE = '%lu'",
			  vproc_queue,
			  screen_upload_file);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}
