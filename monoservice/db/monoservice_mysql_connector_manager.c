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

#include <monoservice/db/monoservice_mysql_connector_manager.h>

#include <monoservice/db/monoservice_mysql_connector.h>

#include <i18n.h>

void monoservice_mysql_connector_manager_class_init(MonoserviceMysqlConnectorManagerClass *mysql_connector_manager);
void monoservice_mysql_connector_manager_init(MonoserviceMysqlConnectorManager *mysql_connector_manager);
void monoservice_mysql_connector_manager_finalize(GObject *gobject);

/**
 * SECTION:monoservice_mysql_connector_manager
 * @short_description: The mysql connector manager
 * @title: MonoserviceMysqlConnectorManager
 * @section_id:
 * @include: monoservice/db/monoservice_mysql_connector_manager.h
 *
 * #MonoserviceMysqlConnectorManager manages MySQL connectors.
 */

static gpointer monoservice_mysql_connector_manager_parent_class = NULL;

static pthread_mutex_t monoservice_mysql_connector_manager_class_mutex = PTHREAD_MUTEX_INITIALIZER;

GType
monoservice_mysql_connector_manager_get_type()
{
  static volatile gsize g_define_type_id__volatile = 0;

  if(g_once_init_enter (&g_define_type_id__volatile)){
    GType monoservice_type_mysql_connector_manager = 0;

    static const GTypeInfo monoservice_mysql_connector_manager_info = {
      sizeof (MonoserviceMysqlConnectorManagerClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) monoservice_mysql_connector_manager_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (MonoserviceMysqlConnectorManager),
      0,    /* n_preallocs */
      (GInstanceInitFunc) monoservice_mysql_connector_manager_init,
    };

    monoservice_type_mysql_connector_manager = g_type_register_static(G_TYPE_OBJECT,
								      "MonoserviceMysqlConnectorManager", &monoservice_mysql_connector_manager_info,
								      0);

    g_once_init_leave(&g_define_type_id__volatile, monoservice_type_mysql_connector_manager);
  }

  return g_define_type_id__volatile;
}

void
monoservice_mysql_connector_manager_class_init(MonoserviceMysqlConnectorManagerClass *mysql_connector_manager)
{
  GObjectClass *gobject;

  monoservice_mysql_connector_manager_parent_class = g_type_class_peek_parent(mysql_connector_manager);

  /* GObjectClass */
  gobject = (GObjectClass *) mysql_connector_manager;

  gobject->finalize = monoservice_mysql_connector_manager_finalize;
}

void
monoservice_mysql_connector_manager_init(MonoserviceMysqlConnectorManager *mysql_connector_manager)
{
  /* object mutex */
  mysql_connector_manager->obj_mutexattr = (pthread_mutexattr_t *) malloc(sizeof(pthread_mutexattr_t));
  pthread_mutexattr_init(mysql_connector_manager->obj_mutexattr);
  
  mysql_connector_manager->obj_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(mysql_connector_manager->obj_mutex,
		     mysql_connector_manager->obj_mutexattr);

  /* common fields */
  mysql_connector_manager->connector = NULL;
}

void
monoservice_mysql_connector_manager_finalize(GObject *gobject)
{
  MonoserviceMysqlConnectorManager *mysql_connector_manager;

  mysql_connector_manager = (MonoserviceMysqlConnectorManager *) gobject;

  pthread_mutex_destroy(mysql_connector_manager->obj_mutex);
  pthread_mutexattr_destroy(mysql_connector_manager->obj_mutexattr);
  
  free(mysql_connector_manager->obj_mutex);
  free(mysql_connector_manager->obj_mutexattr);

  /* call parent */
  G_OBJECT_CLASS(monoservice_mysql_connector_manager_parent_class)->finalize(gobject);
}

/**
 * monoservice_mysql_connector_manager_get_class_mutex:
 *
 * Get class mutex.
 *  
 * Returns: the MySQL connector manager's class mutex
 *
 * Since: 1.0.0
 */
pthread_mutex_t*
monoservice_mysql_connector_manager_get_class_mutex()
{
  return(&monoservice_mysql_connector_manager_class_mutex);
}

/**
 * monoservice_mysql_connector_manager_add_connector:
 * @mysql_connector_manager: the #MonoserviceMysqlConnectorManager
 * @connector: the #MonoserviceMysqlConnector to add
 * 
 * Add @connector to @mysql_connector_manager.
 * 
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_manager_add_connector(MonoserviceMysqlConnectorManager *mysql_connector_manager,
						  GObject *connector)
{
  pthread_mutex_t *obj_mutex;

  if(!MONOSERVICE_IS_MYSQL_CONNECTOR_MANAGER(mysql_connector_manager) ||
     !MONOSERVICE_IS_MYSQL_CONNECTOR(connector)){
    return;
  }
  
  /* get object mutex */
  pthread_mutex_lock(monoservice_mysql_connector_manager_get_class_mutex());
  
  obj_mutex = mysql_connector_manager->obj_mutex;

  pthread_mutex_unlock(monoservice_mysql_connector_manager_get_class_mutex());

  /*  */
  pthread_mutex_lock(obj_mutex);

  if(g_list_find(mysql_connector_manager->connector, connector) == NULL){
    g_object_ref(connector);
    mysql_connector_manager->connector = g_list_prepend(mysql_connector_manager->connector,
							connector);
  }

  pthread_mutex_unlock(obj_mutex);
}

/**
 * monoservice_mysql_connector_manager_add_connector:
 * @mysql_connector_manager: the #MonoserviceMysqlConnectorManager
 * @connector: the #MonoserviceMysqlConnector to remove
 * 
 * Remove @connector from @mysql_connector_manager.
 * 
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_manager_remove_connector(MonoserviceMysqlConnectorManager *mysql_connector_manager,
						     GObject *connector)
{
  pthread_mutex_t *obj_mutex;

  if(!MONOSERVICE_IS_MYSQL_CONNECTOR_MANAGER(mysql_connector_manager) ||
     !MONOSERVICE_IS_MYSQL_CONNECTOR(connector)){
    return;
  }
  
  /* get object mutex */
  pthread_mutex_lock(monoservice_mysql_connector_manager_get_class_mutex());
  
  obj_mutex = mysql_connector_manager->obj_mutex;

  pthread_mutex_unlock(monoservice_mysql_connector_manager_get_class_mutex());

  /*  */
  pthread_mutex_lock(obj_mutex);

  if(g_list_find(mysql_connector_manager->connector, connector) != NULL){
    mysql_connector_manager->connector = g_list_remove(mysql_connector_manager->connector,
						       connector);
    g_object_unref(connector);
  }

  pthread_mutex_unlock(obj_mutex);
}

/**
 * monoservice_mysql_connector_manager_add_connector:
 * @mysql_connector_manager: the #MonoserviceMysqlConnectorManager
 * @hostname: the hostname
 * 
 * Get connectors by @hostname.
 * 
 * Returns: the #GList-struct containing #MonoserviceMysqlConnector
 * 
 * Since: 1.0.0
 */
GList*
monoservice_mysql_connector_manager_get_connector_by_hostname(MonoserviceMysqlConnectorManager *mysql_connector_manager,
							      gchar *hostname)
{
  GList *start_list, *list;
  GList *match;

  pthread_mutex_t *obj_mutex;

  if(!MONOSERVICE_IS_MYSQL_CONNECTOR_MANAGER(mysql_connector_manager) ||
     hostname == NULL){
    return(NULL);
  }
  
  /* get object mutex */
  pthread_mutex_lock(monoservice_mysql_connector_manager_get_class_mutex());
  
  obj_mutex = mysql_connector_manager->obj_mutex;

  pthread_mutex_unlock(monoservice_mysql_connector_manager_get_class_mutex());

  /* copy list */
  pthread_mutex_lock(obj_mutex);

  start_list = g_list_copy(mysql_connector_manager->connector);
  
  pthread_mutex_unlock(obj_mutex);

  match = NULL;
  list = start_list;

  while(list != NULL){
    pthread_mutex_t *connector_mutex;

    pthread_mutex_lock(monoservice_mysql_connector_get_class_mutex());
      
    connector_mutex = MONOSERVICE_MYSQL_CONNECTOR(list->data)->obj_mutex;
    
    pthread_mutex_unlock(monoservice_mysql_connector_get_class_mutex());

    /* check match */
    pthread_mutex_lock(connector_mutex);
    
    if(MONOSERVICE_MYSQL_CONNECTOR(list->data)->hostname != NULL &&
       !g_strcmp0(MONOSERVICE_MYSQL_CONNECTOR(list->data)->hostname,
		  hostname)){
      match = g_list_prepend(match,
			     list->data);
    }
    
    pthread_mutex_unlock(connector_mutex);

    /* iterate */
    list = list->next;
  }

  /* reverse match and free list */
  match = g_list_reverse(match);

  g_list_free(start_list);
  
  return(match);
}

MonoserviceMysqlConnectorManager*
monoservice_mysql_connector_manager_get_instance()
{
  static MonoserviceMysqlConnectorManager *manager = NULL;
  
  static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&mutex);

  if(manager == NULL){
    manager = monoservice_mysql_connector_manager_new();    
  }
  
  pthread_mutex_unlock(&mutex);

  return(manager);
}

/**
 * monoservice_mysql_connector_manager_new:
 *
 * Creates an #MonoserviceMysqlConnectorManager
 *
 * Returns: a new #MonoserviceMysqlConnectorManager
 *
 * Since: 1.0.0
 */
MonoserviceMysqlConnectorManager*
monoservice_mysql_connector_manager_new()
{
  MonoserviceMysqlConnectorManager *mysql_connector_manager;

  mysql_connector_manager = (MonoserviceMysqlConnectorManager *) g_object_new(MONOSERVICE_TYPE_MYSQL_CONNECTOR_MANAGER,
									      NULL);
  
  return(mysql_connector_manager);
}
