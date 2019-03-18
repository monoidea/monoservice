/* Monoservice - monoidea's monothek service
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

#ifndef __MONOSERVICE_MYSQL_CONNECTOR_H__
#define __MONOSERVICE_MYSQL_CONNECTOR_H__

#include <glib.h>
#include <glib-object.h>

#include <mysql.h>

#define MONOSERVICE_TYPE_MYSQL_CONNECTOR                (monoservice_mysql_connector_get_type())
#define MONOSERVICE_MYSQL_CONNECTOR(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), MONOSERVICE_TYPE_MYSQL_CONNECTOR, MonoserviceMysqlConnector))
#define MONOSERVICE_MYSQL_CONNECTOR_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST(class, MONOSERVICE_TYPE_MYSQL_CONNECTOR, MonoserviceMysqlConnectorClass))
#define MONOSERVICE_IS_MYSQL_CONNECTOR(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MONOSERVICE_TYPE_MYSQL_CONNECTOR))
#define MONOSERVICE_IS_MYSQL_CONNECTOR_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE ((class), MONOSERVICE_TYPE_MYSQL_CONNECTOR))
#define MONOSERVICE_MYSQL_CONNECTOR_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS(obj, MONOSERVICE_TYPE_MYSQL_CONNECTOR, MonoserviceMysqlConnectorClass))

#define MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_HOSTNAME "localhost"

#define MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_USER "monothek"
#define MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_PASSWORD "monothek"

#define MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_DB_NAME "MONOSERVICE"

#define MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_PORT (3306)

typedef struct _MonoserviceMysqlConnector MonoserviceMysqlConnector;
typedef struct _MonoserviceMysqlConnectorClass MonoserviceMysqlConnectorClass;

typedef enum{
  MONOSERVICE_MYSQL_CONNECTOR_CONNECTED    = 1,
}MonoserviceMysqlConnectorFlags;

struct _MonoserviceMysqlConnector
{
  GObject gobject;
  
  guint flags;

  pthread_mutexattr_t *obj_mutexattr;
  pthread_mutex_t *obj_mutex;

  gchar *hostname;

  gchar *user;
  gchar *password;

  gchar *db_name;

  guint port;

  gpointer socket;
  
  MYSQL *my;
};

struct _MonoserviceMysqlConnectorClass
{
  GObjectClass gobject;
};

GType monoservice_mysql_connector_get_type();

pthread_mutex_t* monoservice_mysql_connector_get_class_mutex();

void monoservice_mysql_connector_set_flags(MonoserviceMysqlConnector *mysql_connector,
					   guint flags);
void monoservice_mysql_connector_unset_flags(MonoserviceMysqlConnector *mysql_connector,
					     guint flags);
gboolean monoservice_mysql_connector_test_flags(MonoserviceMysqlConnector *mysql_connector,
						guint flags);

void monoservice_mysql_connector_connect(MonoserviceMysqlConnector *mysql_connector,
					 GError **error);

void monoservice_mysql_connector_select_db(MonoserviceMysqlConnector *mysql_connector,
					   gchar *db_name,
					   GError **error);

void monoservice_mysql_connector_query(MonoserviceMysqlConnector *mysql_connector,
				       gchar *query,
				       GError **error);
void monoservice_mysql_connector_query_extended(MonoserviceMysqlConnector *mysql_connector,
						gchar *query,
						guint64 *insert_id,
						gchar ***field_strv,
						gchar ****value_strv_arr,
						guint64 *row_count, guint64 *col_count,
						GError **error);

void monoservice_mysql_connector_close(MonoserviceMysqlConnector *mysql_connector);

MonoserviceMysqlConnector* monoservice_mysql_connector_new();

#endif /*__MONOSERVICE_MYSQL_CONNECTOR_H__*/
