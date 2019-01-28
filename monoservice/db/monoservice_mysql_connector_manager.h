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

#ifndef __MONOSERVICE_MYSQL_CONNECTOR_MANAGER_H__
#define __MONOSERVICE_MYSQL_CONNECTOR_MANAGER_H__

#include <glib.h>
#include <glib-object.h>

#include <pthread.h>

#define MONOSERVICE_TYPE_MYSQL_CONNECTOR_MANAGER                (monoservice_mysql_connector_manager_get_type())
#define MONOSERVICE_MYSQL_CONNECTOR_MANAGER(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), MONOSERVICE_TYPE_MYSQL_CONNECTOR_MANAGER, MonoserviceMysqlConnectorManager))
#define MONOSERVICE_MYSQL_CONNECTOR_MANAGER_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST(class, MONOSERVICE_TYPE_MYSQL_CONNECTOR_MANAGER, MonoserviceMysqlConnectorManagerClass))
#define MONOSERVICE_IS_MYSQL_CONNECTOR_MANAGER(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MONOSERVICE_TYPE_MYSQL_CONNECTOR_MANAGER))
#define MONOSERVICE_IS_MYSQL_CONNECTOR_MANAGER_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE ((class), MONOSERVICE_TYPE_MYSQL_CONNECTOR_MANAGER))
#define MONOSERVICE_MYSQL_CONNECTOR_MANAGER_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS(obj, MONOSERVICE_TYPE_MYSQL_CONNECTOR_MANAGER, MonoserviceMysqlConnectorManagerClass))

typedef struct _MonoserviceMysqlConnectorManager MonoserviceMysqlConnectorManager;
typedef struct _MonoserviceMysqlConnectorManagerClass MonoserviceMysqlConnectorManagerClass;

struct _MonoserviceMysqlConnectorManager
{
  GObject gobject;
  
  pthread_mutexattr_t *obj_mutexattr;
  pthread_mutex_t *obj_mutex;
  
  GList *connector;
};

struct _MonoserviceMysqlConnectorManagerClass
{
  GObjectClass gobject;
};

GType monoservice_mysql_connector_manager_get_type();

pthread_mutex_t* monoservice_mysql_connector_manager_get_class_mutex();

void monoservice_mysql_connector_manager_add_connector(MonoserviceMysqlConnectorManager *mysql_connector_manager,
						       GObject *connector);
void monoservice_mysql_connector_manager_remove_connector(MonoserviceMysqlConnectorManager *mysql_connector_manager,
							  GObject *connector);

GList* monoservice_mysql_connector_manager_get_connector_by_hostname(MonoserviceMysqlConnectorManager *mysql_connector_manager,
								     gchar *hostname);

MonoserviceMysqlConnectorManager* monoservice_mysql_connector_manager_get_instance();

MonoserviceMysqlConnectorManager* monoservice_mysql_connector_manager_new();

#endif /*__MONOSERVICE_MYSQL_CONNECTOR_MANAGER_H__*/
