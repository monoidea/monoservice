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

#include <monoservice/db/monoservice_billing_address_dao.h>

guint64
monoservice_billing_address_dao_create(MonoserviceMysqlConnector *mysql_connector,
				       gchar *firstname,
				       gchar *surname,
				       gchar *phone,
				       gchar *email,
				       gchar *street,
				       gchar *zip,
				       gchar *city,
				       gchar *country)
{
  gchar *query;
  guint64 billing_address_id;

  GError *error;

  query = g_strdup_printf("INSERT INTO BILLING_ADDRESS (FIRSTNAME,SURNAME,PHONE,EMAIL,STREET,ZIP,CITY,COUNTRY) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s')",
			  firstname,
			  surname,
			  phone,
			  email,
			  street,
			  zip,
			  city,
			  country);
  billing_address_id = 0;

  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     &billing_address_id,
					     NULL,
					     NULL,
					     NULL, NULL,
					     &error);

  g_free(query);
  
  return(billing_address_id);
}

void
monoservice_billing_address_dao_delete(MonoserviceMysqlConnector *mysql_connector,
				       guint64 billing_address_id)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("DELETE FROM BILLING_ADDRESS WHERE BILLING_ADDRESS_ID = '%lu'", billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

gchar**
monoservice_billing_address_dao_select(MonoserviceMysqlConnector *mysql_connector,
				       guint64 billing_address_id)
{
  gchar ***table;
  gchar **strv;
  gchar *query;

  GError *error;

  query = g_strdup_printf("SELECT * FROM BILLING_ADDRESS WHERE BILLING_ADDRESS_ID = '%lu'", billing_address_id);

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
monoservice_billing_address_dao_set_payment_transaction(MonoserviceMysqlConnector *mysql_connector,
							guint64 billing_address_id,
							guint64 payment_transaction)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET PAYMENT_TRANSACTION = '%lu' WHERE BILLING_ADDRESS_ID = '%lu'", payment_transaction, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_billing_address_dao_set_firstname(MonoserviceMysqlConnector *mysql_connector,
					      guint64 billing_address_id,
					      gchar *firstname)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET FIRSTNAME = '%s' WHERE BILLING_ADDRESS_ID = '%lu'", firstname, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_billing_address_dao_set_surname(MonoserviceMysqlConnector *mysql_connector,
					    guint64 billing_address_id,
					    gchar *surname)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET SURNAME = '%s' WHERE BILLING_ADDRESS_ID = '%lu'", surname, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_billing_address_dao_set_phone(MonoserviceMysqlConnector *mysql_connector,
					  guint64 billing_address_id,
					  gchar *phone)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET PHONE = '%s' WHERE BILLING_ADDRESS_ID = '%lu'", phone, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_billing_address_dao_set_email(MonoserviceMysqlConnector *mysql_connector,
					  guint64 billing_address_id,
					  gchar *email)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET EMAIL = '%s' WHERE BILLING_ADDRESS_ID = '%lu'", email, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_billing_address_dao_set_street(MonoserviceMysqlConnector *mysql_connector,
					   guint64 billing_address_id,
					   gchar *street)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET STREET = '%s' WHERE BILLING_ADDRESS_ID = '%lu'", street, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_billing_address_dao_set_zip(MonoserviceMysqlConnector *mysql_connector,
					guint64 billing_address_id,
					gchar *zip)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET ZIP = '%s' WHERE BILLING_ADDRESS_ID = '%lu'", zip, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_billing_address_dao_set_city(MonoserviceMysqlConnector *mysql_connector,
					 guint64 billing_address_id,
					 gchar *city)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET CITY = '%s' WHERE BILLING_ADDRESS_ID = '%lu'", city, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_billing_address_dao_set_country(MonoserviceMysqlConnector *mysql_connector,
					    guint64 billing_address_id,
					    gchar *country)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE BILLING_ADDRESS SET COUNTRY = '%s' WHERE BILLING_ADDRESS_ID = '%lu'", country, billing_address_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

guint64*
monoservice_billing_address_dao_find_by_media_account(MonoserviceMysqlConnector *mysql_connector,
						      guint64 media_account_id,
						      guint64 *billing_address_count)
{
  gchar ***table;
  gchar *query;

  guint64 *billing_address;
  
  guint64 row_count;
  guint i;

  GError *error;

  query = g_strdup_printf("SELECT BILLING_ADDRESS.BILLING_ADDRESS_ID,MEDIA_ACCOUNT.MEDIA_ACCOUNT_ID,MEDIA_ACCOUNT.BILLING_ADDRESS FROM BILLING_ADDRESS INNER JOIN MEDIA_ACCOUNT ON (MEDIA_ACCOUNT.MEDIA_ACCOUNT_ID = '%lu' AND MEDIA_ACCOUNT.BILLING_ADDRESS = BILLING_ADDRESS.BILLING_ADDRESS_ID)", media_account_id);
  
  table = NULL;
  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     NULL,
					     NULL,
					     &table,
					     &row_count, NULL,
					     &error);

  g_free(query);

  billing_address = NULL;

  if(row_count > 0){
    billing_address = (guint64 *) malloc(row_count * sizeof(guint64));

    for(i = 0; i < row_count; i++){
      billing_address[i] = g_ascii_strtoull(table[i][0],
					    NULL,
					    10);

      g_strfreev(table[i]);
    }

    g_free(table);
  }

  if(billing_address_count != NULL){
    billing_address_count[0] = row_count;
  }
  
  return(billing_address);
}
