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

#include <mysql.h>

int monoservice_billing_address_dao_create();
void monoservice_billing_address_dao_delete(int billing_address_id);

void monoservice_billing_address_dao_set_payment_transaction(int billing_address_id,
							     int payment_transaction);

void monoservice_billing_address_dao_set_firstname(int billing_address_id,
						   char *firstname);
void monoservice_billing_address_dao_set_surname(int billing_address_id,
						 char *surname);

void monoservice_billing_address_dao_set_email(int billing_address_id,
					       char *email);

void monoservice_billing_address_dao_set_street(int billing_address_id,
						char *street);

void monoservice_billing_address_dao_set_zip(int billing_address_id,
					     char *zip);

void monoservice_billing_address_dao_set_city(int billing_address_id,
					      char *city);

void monoservice_billing_address_dao_set_country(int billing_address_id,
						 char *country);

int* monoservice_billing_address_dao_get_by_media_account(int media_account_id,
							  guint *billing_address_count);

#endif /*__MONOSERVICE_BILLING_ADDRESS_DAO_H__*/
