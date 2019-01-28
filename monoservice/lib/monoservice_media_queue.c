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

#include <monoservice/lib/monoservice_media_queue.h>

#include <i18n.h>

void monoservice_media_queue_class_init(MonoserviceMediaQueueClass *media_queue);
void monoservice_media_queue_init(MonoserviceMediaQueue *media_queue);
void monoservice_media_queue_set_property(GObject *gobject,
					  guint prop_id,
					  const GValue *value,
					  GParamSpec *param_spec);
void monoservice_media_queue_get_property(GObject *gobject,
					  guint prop_id,
					  GValue *value,
					  GParamSpec *param_spec);
void monoservice_media_queue_finalize(GObject *gobject);

/**
 * SECTION:monoservice_media_queue
 * @short_description: The media queue object
 * @title: MonoserviceMediaQueue
 * @section_id:
 * @include: monoservice/lib/monoservice_media_queue.h
 *
 * #MonoserviceMediaQueue enqueues media files to be processed.
 */

enum{
  PROP_0,
};

static gpointer monoservice_media_queue_parent_class = NULL;
GType
monoservice_media_queue_get_type()
{
  static volatile gsize g_define_type_id__volatile = 0;

  if(g_once_init_enter (&g_define_type_id__volatile)){
    GType monoservice_type_media_queue = 0;

    static const GTypeInfo monoservice_media_queue_info = {
      sizeof (MonoserviceMediaQueueClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) monoservice_media_queue_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (MonoserviceMediaQueue),
      0,    /* n_preallocs */
      (GInstanceInitFunc) monoservice_media_queue_init,
    };

    monoservice_type_media_queue = g_type_register_static(G_TYPE_OBJECT,
							  "MonoserviceMediaQueue", &monoservice_media_queue_info,
							  0);

    g_once_init_leave(&g_define_type_id__volatile, monoservice_type_media_queue);
  }

  return g_define_type_id__volatile;
}

void
monoservice_media_queue_class_init(MonoserviceMediaQueueClass *media_queue)
{
  GObjectClass *gobject;

  GParamSpec *param_spec;

  monoservice_media_queue_parent_class = g_type_class_peek_parent(media_queue);

  /* GObjectClass */
  gobject = (GObjectClass *) media_queue;

  gobject->set_property = monoservice_media_queue_set_property;
  gobject->get_property = monoservice_media_queue_get_property;

  gobject->finalize = monoservice_media_queue_finalize;

  /* properties */
}

void
monoservice_media_queue_init(MonoserviceMediaQueue *media_queue)
{
  media_queue->flags = 0;
}

void
monoservice_media_queue_set_property(GObject *gobject,
				     guint prop_id,
				     const GValue *value,
				     GParamSpec *param_spec)
{
  MonoserviceMediaQueue *media_queue;

  media_queue = MONOSERVICE_MEDIA_QUEUE(gobject);

  switch(prop_id){
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
monoservice_media_queue_get_property(GObject *gobject,
				     guint prop_id,
				     GValue *value,
				     GParamSpec *param_spec)
{
  MonoserviceMediaQueue *media_queue;

  media_queue = MONOSERVICE_MEDIA_QUEUE(gobject);

  switch(prop_id){
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
monoservice_media_queue_finalize(GObject *gobject)
{
  MonoserviceMediaQueue *media_queue;

  media_queue = (MonoserviceMediaQueue *) gobject;
  
  /* call parent */
  G_OBJECT_CLASS(monoservice_media_queue_parent_class)->finalize(gobject);
}

/**
 * monoservice_media_queue_new:
 *
 * Creates an #MonoserviceMediaQueue
 *
 * Returns: a new #MonoserviceMediaQueue
 *
 * Since: 1.0.0
 */
MonoserviceMediaQueue*
monoservice_media_queue_new()
{
  MonoserviceMediaQueue *media_queue;

  media_queue = (MonoserviceMediaQueue *) g_object_new(MONOSERVICE_TYPE_MEDIA_QUEUE,
						       NULL);
  
  return(media_queue);
}
