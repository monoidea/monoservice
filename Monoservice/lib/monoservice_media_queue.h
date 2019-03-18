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

#ifndef __MONOSERVICE_MEDIA_QUEUE_H__
#define __MONOSERVICE_MEDIA_QUEUE_H__

#include <glib.h>
#include <glib-object.h>

#include <qrencode.h>

#define MONOSERVICE_TYPE_MEDIA_QUEUE                (monoservice_media_queue_get_type())
#define MONOSERVICE_MEDIA_QUEUE(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), MONOSERVICE_TYPE_MEDIA_QUEUE, MonoserviceMediaQueue))
#define MONOSERVICE_MEDIA_QUEUE_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST(class, MONOSERVICE_TYPE_MEDIA_QUEUE, MonoserviceMediaQueueClass))
#define MONOSERVICE_IS_MEDIA_QUEUE(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MONOSERVICE_TYPE_MEDIA_QUEUE))
#define MONOSERVICE_IS_MEDIA_QUEUE_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE ((class), MONOSERVICE_TYPE_MEDIA_QUEUE))
#define MONOSERVICE_MEDIA_QUEUE_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS(obj, MONOSERVICE_TYPE_MEDIA_QUEUE, MonoserviceMediaQueueClass))

typedef struct _MonoserviceMediaQueue MonoserviceMediaQueue;
typedef struct _MonoserviceMediaQueueClass MonoserviceMediaQueueClass;

struct _MonoserviceMediaQueue
{
  GObject gobject;
  
  guint flags;
};

struct _MonoserviceMediaQueueClass
{
  GObjectClass gobject;
};

GType monoservice_media_queue_get_type();

MonoserviceMediaQueue* monoservice_media_queue_new();

#endif /*__MONOSERVICE_MEDIA_QUEUE_H__*/
