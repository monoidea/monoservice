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

#ifndef __MONOSERVICE_PAYMENT_TRANSACTION_DAO_H__
#define __MONOSERVICE_PAYMENT_TRANSACTION_DAO_H__

#include <glib.h>
#include <glib-object.h>

#include <time.h>

#include <monoservice/db/monoservice_mysql_connector.h>

guint64 monoservice_payment_transaction_dao_create(MonoserviceMysqlConnector *mysql_connector);
void monoservice_payment_transaction_dao_delete(MonoserviceMysqlConnector *mysql_connector,
						guint64 payment_transaction_id);

gchar** monoservice_payment_transaction_dao_select(MonoserviceMysqlConnector *mysql_connector,
						   guint64 payment_transaction_id);

void monoservice_payment_transaction_dao_set_billing_address(MonoserviceMysqlConnector *mysql_connector,
							     guint64 payment_transaction_id,
							     guint64 billing_address);

void monoservice_payment_transaction_dao_set_invoice_amount(MonoserviceMysqlConnector *mysql_connector,
							    guint64 payment_transaction_id,
							    gdouble invoice_amount);

void monoservice_payment_transaction_dao_set_due_date(MonoserviceMysqlConnector *mysql_connector,
						      guint64 payment_transaction_id,
						      time_t due_date);

void monoservice_payment_transaction_dao_set_completed(MonoserviceMysqlConnector *mysql_connector,
						       guint64 payment_transaction_id,
						       gboolean completed);

guint64* monoservice_payment_transaction_find_by_billing_address(MonoserviceMysqlConnector *mysql_connector,
								 guint64 billing_address,
								 guint *payment_transaction_count);

#endif /*__MONOSERVICE_PAYMENT_TRANSACTION_DAO_H__*/
