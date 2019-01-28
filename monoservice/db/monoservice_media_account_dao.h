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

#ifndef __MONOSERVICE_MEDIA_ACCOUNT_DAO_H__
#define __MONOSERVICE_MEDIA_ACCOUNT_DAO_H__

#include <glib.h>
#include <glib-object.h>

#include <mysql.h>

int monoservice_media_account_dao_create();
void monoservice_media_account_dao_delete(int media_account_id);

void monoservice_media_account_dao_set_billing_address(int media_account_id,
						       int billing_address);

void monoservice_media_account_dao_set_video_file(int media_account_id,
						  int video_file);

void monoservice_media_account_dao_set_session_store(int media_account_id,
						     int session_store);
						      
#endif /*__MONOSERVICE_MEDIA_ACCOUNT_DAO_H__*/
