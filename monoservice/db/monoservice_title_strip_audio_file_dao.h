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

#ifndef __MONOSERVICE_TITLE_STRIP_AUDIO_FILE_DAO_H__
#define __MONOSERVICE_TITLE_STRIP_AUDIO_FILE_DAO_H__

#include <glib.h>
#include <glib-object.h>

#include <monoservice/db/monoservice_mysql_connector.h>

guint64 monoservice_title_strip_audio_file_dao_create(MonoserviceMysqlConnector *mysql_connector);
void monoservice_title_strip_audio_file_dao_delete(MonoserviceMysqlConnector *mysql_connector,
						   guint64 title_strip_audio_file_id);

gchar** monoservice_title_strip_audio_file_dao_select(MonoserviceMysqlConnector *mysql_connector,
						      guint64 title_strip_audio_file_id);
 
#endif /*__MONOSERVICE_TITLE_STRIP_AUDIO_FILE_DAO_H__*/
