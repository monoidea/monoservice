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

#include <monoservice/db/monoservice_mysql_connector.h>

#include <i18n.h>

void monoservice_mysql_connector_class_init(MonoserviceMysqlConnectorClass *mysql_connector);
void monoservice_mysql_connector_init(MonoserviceMysqlConnector *mysql_connector);
void monoservice_mysql_connector_set_property(GObject *gobject,
					      guint prop_id,
					      const GValue *value,
					      GParamSpec *param_spec);
void monoservice_mysql_connector_get_property(GObject *gobject,
					      guint prop_id,
					      GValue *value,
					      GParamSpec *param_spec);
void monoservice_mysql_connector_finalize(GObject *gobject);

/**
 * SECTION:monoservice_mysql_connector
 * @short_description: The MySQL connector object
 * @title: MonoserviceMysqlConnector
 * @section_id:
 * @include: monoservice/db/monoservice_mysql_connector.h
 *
 * #MonoserviceMysqlConnector connect to MySQL DB instance.
 */

enum{
  PROP_0,
};

static gpointer monoservice_mysql_connector_parent_class = NULL;

static pthread_mutex_t monoservice_mysql_connector_class_mutex = PTHREAD_MUTEX_INITIALIZER;

GType
monoservice_mysql_connector_get_type()
{
  static volatile gsize g_define_type_id__volatile = 0;

  if(g_once_init_enter (&g_define_type_id__volatile)){
    GType monoservice_type_mysql_connector = 0;

    static const GTypeInfo monoservice_mysql_connector_info = {
      sizeof (MonoserviceMysqlConnectorClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) monoservice_mysql_connector_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (MonoserviceMysqlConnector),
      0,    /* n_preallocs */
      (GInstanceInitFunc) monoservice_mysql_connector_init,
    };

    monoservice_type_mysql_connector = g_type_register_static(G_TYPE_OBJECT,
							      "MonoserviceMysqlConnector", &monoservice_mysql_connector_info,
							      0);

    g_once_init_leave(&g_define_type_id__volatile, monoservice_type_mysql_connector);
  }

  return g_define_type_id__volatile;
}

void
monoservice_mysql_connector_class_init(MonoserviceMysqlConnectorClass *mysql_connector)
{
  GObjectClass *gobject;

  GParamSpec *param_spec;

  monoservice_mysql_connector_parent_class = g_type_class_peek_parent(mysql_connector);

  /* GObjectClass */
  gobject = (GObjectClass *) mysql_connector;

  gobject->set_property = monoservice_mysql_connector_set_property;
  gobject->get_property = monoservice_mysql_connector_get_property;

  gobject->finalize = monoservice_mysql_connector_finalize;

  /* properties */
}

void
monoservice_mysql_connector_init(MonoserviceMysqlConnector *mysql_connector)
{
  mysql_connector->flags = 0;

  /* object mutex */
  mysql_connector->obj_mutexattr = (pthread_mutexattr_t *) malloc(sizeof(pthread_mutexattr_t));
  pthread_mutexattr_init(mysql_connector->obj_mutexattr);
  
  mysql_connector->obj_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(mysql_connector->obj_mutex,
		     mysql_connector->obj_mutexattr);

  /* common fields */
  mysql_connector->hostname = g_strdup(MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_HOSTNAME);

  mysql_connector->user = g_strdup(MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_USER);
  mysql_connector->password = g_strdup(MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_PASSWORD);

  mysql_connector->db_name = g_strdup(MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_DB_NAME);

  mysql_connector->port = MONOSERVICE_MYSQL_CONNECTOR_DEFAULT_PORT;

  mysql_connector->socket = NULL;

  mysql_connector->my = mysql_init(NULL);

  if(mysql_connector->my == NULL){
    g_critical("unable to init MySQL");
  }
}

void
monoservice_mysql_connector_set_property(GObject *gobject,
					 guint prop_id,
					 const GValue *value,
					 GParamSpec *param_spec)
{
  MonoserviceMysqlConnector *mysql_connector;

  mysql_connector = MONOSERVICE_MYSQL_CONNECTOR(gobject);

  switch(prop_id){
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
monoservice_mysql_connector_get_property(GObject *gobject,
					 guint prop_id,
					 GValue *value,
					 GParamSpec *param_spec)
{
  MonoserviceMysqlConnector *mysql_connector;

  mysql_connector = MONOSERVICE_MYSQL_CONNECTOR(gobject);

  switch(prop_id){
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
monoservice_mysql_connector_finalize(GObject *gobject)
{
  MonoserviceMysqlConnector *mysql_connector;

  mysql_connector = (MonoserviceMysqlConnector *) gobject;
  
  /* call parent */
  G_OBJECT_CLASS(monoservice_mysql_connector_parent_class)->finalize(gobject);
}

/**
 * monoservice_mysql_connector_get_class_mutex:
 *
 * Get class mutex.
 *  
 * Returns: the MySQL connector's class mutex
 *
 * Since: 1.0.0
 */
pthread_mutex_t*
monoservice_mysql_connector_get_class_mutex()
{
  return(&monoservice_mysql_connector_class_mutex);
}

/**
 * monoservice_mysql_connector_set_flags:
 * @mysql_connector: the #MonoserviceMysqlConnector
 * @flags: the flags
 * 
 * Set @flags of @mysql_connector.
 *
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_set_flags(MonoserviceMysqlConnector *mysql_connector,
				      guint flags)
{
  pthread_mutex_t *obj_mutex;

  if(!MONOSERVICE_IS_MYSQL_CONNECTOR(mysql_connector)){
    return;
  }
  
  /* get object mutex */
  pthread_mutex_lock(monoservice_mysql_connector_get_class_mutex());
  
  obj_mutex = mysql_connector->obj_mutex;

  pthread_mutex_unlock(monoservice_mysql_connector_get_class_mutex());
  
  /* set flags */
  pthread_mutex_lock(obj_mutex);

  mysql_connector->flags |= flags;
  
  pthread_mutex_unlock(obj_mutex);
}

/**
 * monoservice_mysql_connector_unset_flags:
 * @mysql_connector: the #MonoserviceMysqlConnector
 * @flags: the flags
 * 
 * Unset @flags of @mysql_connector.
 *
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_unset_flags(MonoserviceMysqlConnector *mysql_connector,
					guint flags)
{
  pthread_mutex_t *obj_mutex;

  if(!MONOSERVICE_IS_MYSQL_CONNECTOR(mysql_connector)){
    return;
  }
  
  /* get object mutex */
  pthread_mutex_lock(monoservice_mysql_connector_get_class_mutex());
  
  obj_mutex = mysql_connector->obj_mutex;

  pthread_mutex_unlock(monoservice_mysql_connector_get_class_mutex());
  
  /* set flags */
  pthread_mutex_lock(obj_mutex);

  mysql_connector->flags &= (~flags);
  
  pthread_mutex_unlock(obj_mutex);
}

/**
 * monoservice_mysql_connector_test_flags:
 * @mysql_connector: the #MonoserviceMysqlConnector
 * @flags: the flags
 * 
 * Test @flags of @mysql_connector.
 * 
 * Returns: %TRUE if flags set, otherwise %FALSE
 *
 * Since: 1.0.0
 */
gboolean
monoservice_mysql_connector_test_flags(MonoserviceMysqlConnector *mysql_connector,
				       guint flags)
{
  gboolean success;
  
  pthread_mutex_t *obj_mutex;

  if(!MONOSERVICE_IS_MYSQL_CONNECTOR(mysql_connector)){
    return(FALSE);
  }

  /* get object mutex */
  pthread_mutex_lock(monoservice_mysql_connector_get_class_mutex());
  
  obj_mutex = mysql_connector->obj_mutex;

  pthread_mutex_unlock(monoservice_mysql_connector_get_class_mutex());
  
  /* set flags */
  pthread_mutex_lock(obj_mutex);

  success = ((flags & (mysql_connector->flags)) != 0) ? TRUE: FALSE;
  
  pthread_mutex_unlock(obj_mutex);

  return(success);
}

/**
 * monoservice_mysql_connector_connect:
 * @mysql_connector: the #MonoserviceMysqlConnector
 * @error: return location for #GError-struct
 *
 * Connect @mysql_connector to MySQL server.
 * 
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_connect(MonoserviceMysqlConnector *mysql_connector,
				    GError **error)
{
  MYSQL *retval;

  if(!MONOSERVICE_IS_MYSQL_CONNECTOR(mysql_connector)){
    return;
  }

  if(monoservice_mysql_connector_test_flags(mysql_connector, MONOSERVICE_MYSQL_CONNECTOR_CONNECTED)){
    g_warning("already connected to %s", mysql_connector->hostname);
    
    return;
  }
  
  retval = mysql_real_connect(mysql_connector->my,
			      mysql_connector->hostname,
			      mysql_connector->user,
			      mysql_connector->password,
			      mysql_connector->db_name,
			      mysql_connector->port,
			      mysql_connector->socket,
			      0);
  
  if(retval != NULL){
    monoservice_mysql_connector_set_flags(mysql_connector,
					  MONOSERVICE_MYSQL_CONNECTOR_CONNECTED);
  }else{
    g_critical("unable to connect to %s", mysql_connector->hostname);
  }
}

/**
 * monoservice_mysql_connector_connect:
 * @mysql_connector: the #MonoserviceMysqlConnector
 * @db_name: the database's name
 * @error: return location for #GError-struct
 *
 * Select database with @db_name.
 * 
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_select_db(MonoserviceMysqlConnector *mysql_connector,
				      gchar *db_name,
				      GError **error)
{
  if(!MONOSERVICE_IS_MYSQL_CONNECTOR(mysql_connector)){
    return;
  }

  g_free(mysql_connector->db_name);
  
  mysql_connector->db_name = g_strdup(db_name);

  if(monoservice_mysql_connector_test_flags(mysql_connector, MONOSERVICE_MYSQL_CONNECTOR_CONNECTED)){
    mysql_select_db(mysql_connector->my,
		    mysql_connector->db_name);
  }
}

/**
 * monoservice_mysql_connector_query:
 * @mysql_connector: the #MonoserviceMysqlConnector
 * @query: the query string
 * 
 * Query @mysql_connector for @query.
 *
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_query(MonoserviceMysqlConnector *mysql_connector,
				  gchar *query,
				  GError **error)
{
  monoservice_mysql_connector_query_extended(mysql_connector,
					     query,
					     NULL,
					     NULL,
					     NULL,
					     NULL, NULL,
					     error);
}

/**
 * monoservice_mysql_connector_query_extended:
 * @mysql_connector: the #MonoserviceMysqlConnector
 * @query: the query string
 * @insert_id: return location of autoincrement value
 * @fields_strv: return location of fields
 * @value_strv_arr: return location of table
 * @row_count: return location of queried row count
 * @col_count: return location of queried column count
 * @error: return location for #GError-struct
 * 
 * Query @mysql_connector for @query.
 *
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_query_extended(MonoserviceMysqlConnector *mysql_connector,
					   gchar *query,
					   guint64 *insert_id,
					   gchar ***field_strv,
					   gchar ****value_strv_arr,
					   guint64 *row_count, guint64 *col_count,
					   GError **error)
{
  MYSQL_RES *res;
  MYSQL_ROW row;  

  gchar **header;
  gchar ***table;

  guint64 id;
  guint64 rows, cols;
  guint i, j;
  
  if(!MONOSERVICE_IS_MYSQL_CONNECTOR(mysql_connector)){
    return(NULL);
  }

  /* query */
  mysql_query(mysql_connector->my,
	      query);

  id = mysql_insert_id(mysql_connector->my);

  if(id != 0){
    if(insert_id != NULL){
      insert_id[0] = id;
    }

    if(field_strv != NULL){
      field_strv[0] = NULL;
    }

    if(value_strv_arr != NULL){
      value_strv_arr[0] = NULL;
    }

    if(row_count != NULL){
      row_count[0] = 0;
    }

    if(col_count != NULL){
      col_count[0] = 0;
    }
    
    return;
  }

  if(insert_id != NULL){
    insert_id[0] = 0;
  }
  
  res = mysql_store_result(mysql_connector->my);

  if(res == NULL){
    if(field_strv != NULL){
      field_strv[0] = NULL;
    }

    if(value_strv_arr != NULL){
      value_strv_arr[0] = NULL;
    }

    if(row_count != NULL){
      row_count[0] = 0;
    }

    if(col_count != NULL){
      col_count[0] = 0;
    }

    return;
  }
  
  rows = (guint64) mysql_num_rows(res);
  cols = (guint64) mysql_num_fields(res);

  /* fields */
  if(field_strv != NULL){
    MYSQL_FIELD *field;

    mysql_fetch_fields(res);
    
    header =
      field_strv[0] = (gchar **) malloc((cols + 1) * sizeof(gchar *));

    for(i = 0; i < cols; i++){
      header[cols] = g_strdup(field[i].name);
    }
  
    header[cols] = NULL;  
  }

  /* values */
  if(value_strv_arr != NULL){
    table =
      value_strv_arr[0] = (gchar ***) malloc((rows + 1) * sizeof(gchar **));

    for(i = 0; i < rows; i++){
      row = mysql_fetch_row(res);
      
      table[i] = (gchar **) malloc((cols + 1) * sizeof(gchar *));
      
      for(j = 0; j < cols; j++){
	table[i][j] = g_strdup(row[j]);
      }
      
      table[i][cols] = NULL;
    }
    
    table[rows] = NULL;
  }

  /* dimension */
  if(row_count != NULL){
    row_count[0] = rows;
  }
  
  if(col_count != NULL){
    col_count[0] = cols;
  }

  /* free result */
  mysql_free_result(res);
}

/**
 * monoservice_mysql_connector_close:
 * @mysql_connector: the #MonoserviceMysqlConnector
 *
 * Close connection of @mysql_connector.
 * 
 * Since: 1.0.0
 */
void
monoservice_mysql_connector_close(MonoserviceMysqlConnector *mysql_connector)
{
  if(!MONOSERVICE_IS_MYSQL_CONNECTOR(mysql_connector)){
    return;
  }

  if(!monoservice_mysql_connector_test_flags(mysql_connector, MONOSERVICE_MYSQL_CONNECTOR_CONNECTED)){
    g_warning("not connected");
    
    return;
  }
  
  mysql_close(mysql_connector->my);
}

/**
 * monoservice_mysql_connector_new:
 *
 * Creates an #MonoserviceMysqlConnector
 *
 * Returns: a new #MonoserviceMysqlConnector
 *
 * Since: 1.0.0
 */
MonoserviceMysqlConnector*
monoservice_mysql_connector_new()
{
  MonoserviceMysqlConnector *mysql_connector;

  mysql_connector = (MonoserviceMysqlConnector *) g_object_new(MONOSERVICE_TYPE_MYSQL_CONNECTOR,
							       NULL);
  
  return(mysql_connector);
}
