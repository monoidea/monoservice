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

#ifndef __MONOSERVICE_BILLING_ADDRESS_DAO_H__
#define __MONOSERVICE_BILLING_ADDRESS_DAO_H__

#include <glib.h>
#include <glib-object.h>

#include <monoservice/db/monoservice_mysql_connector.h>

guint64 monoservice_billing_address_dao_create(MonoserviceMysqlConnector *mysql_connector,
					       gchar *firstname,
					       gchar *surname,
					       gchar *phone,
					       gchar *email,
					       gchar *street,
					       gchar *zip,
					       gchar *city,
					       gchar *country);
void monoservice_billing_address_dao_delete(MonoserviceMysqlConnector *mysql_connector,
					    guint64 billing_address_id);

gchar** monoservice_billing_address_dao_select(MonoserviceMysqlConnector *mysql_connector,
					       guint64 billing_address_id);

void monoservice_billing_address_dao_set_payment_transaction(MonoserviceMysqlConnector *mysql_connector,
							     guint64 billing_address_id,
							     guint64 payment_transaction);

void monoservice_billing_address_dao_set_firstname(MonoserviceMysqlConnector *mysql_connector,
						   guint64 billing_address_id,
						   gchar *firstname);
void monoservice_billing_address_dao_set_surname(MonoserviceMysqlConnector *mysql_connector,
						 guint64 billing_address_id,
						 gchar *surname);

void monoservice_billing_address_dao_set_phone(MonoserviceMysqlConnector *mysql_connector,
					       guint64 billing_address_id,
					       gchar *phone);

void monoservice_billing_address_dao_set_email(MonoserviceMysqlConnector *mysql_connector,
					       guint64 billing_address_id,
					       gchar *email);

void monoservice_billing_address_dao_set_street(MonoserviceMysqlConnector *mysql_connector,
						guint64 billing_address_id,
						gchar *street);

void monoservice_billing_address_dao_set_zip(MonoserviceMysqlConnector *mysql_connector,
					     guint64 billing_address_id,
					     gchar *zip);

void monoservice_billing_address_dao_set_city(MonoserviceMysqlConnector *mysql_connector,
					      guint64 billing_address_id,
					      gchar *city);

void monoservice_billing_address_dao_set_country(MonoserviceMysqlConnector *mysql_connector,
						 guint64 billing_address_id,
						 gchar *country);

guint64* monoservice_billing_address_dao_find_by_media_account(MonoserviceMysqlConnector *mysql_connector,
							       guint64 media_account_id,
							       guint64 *billing_address_count);

#endif /*__MONOSERVICE_BILLING_ADDRESS_DAO_H__*/
