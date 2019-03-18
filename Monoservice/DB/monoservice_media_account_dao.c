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

#include <monoservice/db/monoservice_media_account_dao.h>

guint64
monoservice_media_account_dao_create(MonoserviceMysqlConnector *mysql_connector)
{
  gchar *query;
  guint64 media_account_id;

  GError *error;

  query = g_strdup("INSERT INTO MEDIA_ACCOUNT DEFAULT VALUES");
  media_account_id = 0;

  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     &media_account_id,
					     NULL,
					     NULL,
					     NULL, NULL,
					     &error);

  g_free(query);
  
  return(media_account_id);
}

void
monoservice_media_account_dao_delete(MonoserviceMysqlConnector *mysql_connector,
				     guint64 media_account_id)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("DELETE FROM MEDIA_ACCOUNT WHERE MEDIA_ACCOUNT_ID = '%lu'", media_account_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

gchar**
monoservice_media_account_dao_select(MonoserviceMysqlConnector *mysql_connector,
				     guint64 media_account_id)

{
  gchar ***table;
  gchar **strv;
  gchar *query;

  GError *error;

  query = g_strdup_printf("SELECT * FROM MEDIA_ACCOUNT WHERE MEDIA_ACCOUNT_ID = '%lu'", media_account_id);

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
monoservice_media_account_dao_set_billing_address(MonoserviceMysqlConnector *mysql_connector,
						  guint64 media_account_id,
						  guint64 billing_address)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE MEDIA_ACCOUNT SET BILLING_ADDRESS = '%lu' WHERE MEDIA_ACCOUNT_ID = '%lu'", billing_address, media_account_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}
