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
monoservice_payment_transaction_dao_create(MonoserviceMysqlConnector *mysql_connector)
{
  gchar *query;
  guint64 payment_transaction_id;

  GError *error;

  query = g_strdup_printf("INSERT INTO PAYMENT_TRANSACTION DEFAULT VALUES");
  payment_transaction_id = 0;

  error = NULL;
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     &payment_transaction_id,
					     NULL,
					     NULL,
					     NULL, NULL,
					     &error);

  g_free(query);
  
  return(payment_transaction_id);
}

void
monoservice_payment_transaction_dao_delete(MonoserviceMysqlConnector *mysql_connector,
					   guint64 payment_transaction_id)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("DELETE FROM PAYMENT_TRANSACTION WHERE PAYMENT_TRANSACTION_ID = '%lu'", payment_transaction_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

gchar**
monoservice_payment_transaction_dao_select(MonoserviceMysqlConnector *mysql_connector,
					   guint64 payment_transaction_id)
{
  gchar ***table;
  gchar **strv;
  gchar *query;

  GError *error;

  query = g_strdup_printf("SELECT * FROM PAYMENT_TRANSACTION WHERE PAYMENT_TRANSACTION_ID = '%lu'", payment_transaction_id);

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
monoservice_payment_transaction_dao_set_billing_address(MonoserviceMysqlConnector *mysql_connector,
							guint64 payment_transaction_id,
							guint64 billing_address)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE PAYMENT_TRANSACTION SET BILLING_ADDRESS = '%lu' WHERE PAYMENT_TRANSACTION_ID = '%lu'", billing_address, payment_transaction_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_payment_transaction_dao_set_invoice_amount(MonoserviceMysqlConnector *mysql_connector,
						       guint64 payment_transaction_id,
						       gdouble invoice_amount)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE PAYMENT_TRANSACTION SET INVOICE_AMOUNT = '%f' WHERE PAYMENT_TRANSACTION_ID = '%lu'", invoice_amount, payment_transaction_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_payment_transaction_dao_set_due_date(MonoserviceMysqlConnector *mysql_connector,
						 guint64 payment_transaction_id,
						 time_t due_date)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE PAYMENT_TRANSACTION SET DUE_DATE = '%ld' WHERE PAYMENT_TRANSACTION_ID = '%lu'", due_date, payment_transaction_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

void
monoservice_payment_transaction_dao_set_completed(MonoserviceMysqlConnector *mysql_connector,
						  guint64 payment_transaction_id,
						  gboolean completed)
{
  gchar *query;

  GError *error;

  query = g_strdup_printf("UPDATE PAYMENT_TRANSACTION SET COMPLETED = '%s' WHERE PAYMENT_TRANSACTION_ID = '%lu'", (completed ? "true": "false"), payment_transaction_id);

  error = NULL;
  monoservice_mysql_connector_query(mysql_connector,
				    query,
				    &error);

  g_free(query);
}

guint64*
monoservice_payment_transaction_find_by_billing_address(MonoserviceMysqlConnector *mysql_connector,
							guint64 billing_address,
							guint *payment_transaction_count)
{
  gchar ***table;
  gchar *query;

  guint64 *payment_transaction;
  
  guint64 row_count;
  guint i;

  GError *error;

  query = g_strdup_printf("SELECT * FROM PAYMENT_TRANSACTION PAYMENT_TRANSACTION.BILLING_ADDRESS = '%lu'", billing_address);

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

  payment_transaction = NULL;

  if(row_count > 0){
    payment_transaction = (guint64 *) malloc(row_count * sizeof(guint64));

    for(i = 0; i < row_count; i++){
      payment_transaction[i] = g_ascii_strtoull(table[i][0],
						NULL,
						10);

      g_strfreev(table[i]);
    }

    g_free(table);
  }

  if(payment_transaction_count != NULL){
    payment_transaction_count[0] = row_count;
  }
  
  return(payment_transaction);
}
