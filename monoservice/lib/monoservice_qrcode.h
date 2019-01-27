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

#ifndef __MONOSERVICE_QRCODE_H__
#define __MONOSERVICE_QRCODE_H__

#include <glib.h>
#include <glib-object.h>

#include <qrencode.h>

#define MONOSERVICE_TYPE_QRCODE                (monoservice_qrcode_get_type())
#define MONOSERVICE_QRCODE(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), MONOSERVICE_TYPE_QRCODE, MonoserviceQrcode))
#define MONOSERVICE_QRCODE_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST(class, MONOSERVICE_TYPE_QRCODE, MonoserviceQrcodeClass))
#define MONOSERVICE_IS_QRCODE(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MONOSERVICE_TYPE_QRCODE))
#define MONOSERVICE_IS_QRCODE_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE ((class), MONOSERVICE_TYPE_QRCODE))
#define MONOSERVICE_QRCODE_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS(obj, MONOSERVICE_TYPE_QRCODE, MonoserviceQrcodeClass))

#define MONOSERVICE_QRCODE_DEFAULT_URL "http://monothek.ch"
#define MONOSERVICE_QRCODE_DEFAULT_FILENAME SRCDIR "/monoservice.share/monoservice/qrcode/qrcode.xpm"

#define MONOSERVICE_QRCODE_DEFAULT_SVG_WIDTH (480)
#define MONOSERVICE_QRCODE_DEFAULT_SVG_HEIGHT (480)

#define MONOSERVICE_QRCODE_DEFAULT_PNG_WIDTH (480)
#define MONOSERVICE_QRCODE_DEFAULT_PNG_HEIGHT (480)

typedef struct _MonoserviceQrcode MonoserviceQrcode;
typedef struct _MonoserviceQrcodeClass MonoserviceQrcodeClass;

struct _MonoserviceQrcode
{
  GObject gobject;
  
  guint flags;
  
  gchar *url;
  gchar *filename;
  
  QRcode *qrcode;
};

struct _MonoserviceQrcodeClass
{
  GObjectClass gobject;

  void (*encode)(MonoserviceQrcode *qrcode);
  
  void (*write)(MonoserviceQrcode *qrcode);
};

GType monoservice_qrcode_get_type();

void monoservice_qrcode_encode(MonoserviceQrcode *qrcode);

void monoservice_qrcode_write(MonoserviceQrcode *qrcode);

void monoservice_qrcode_export_svg(MonoserviceQrcode *qrcode,
				   gchar *svg_filename);
void monoservice_qrcode_export_png(MonoserviceQrcode *qrcode,
				   gchar *png_filename);

MonoserviceQrcode* monoservice_qrcode_new();

#endif /*__MONOSERVICE_QRCODE_H__*/
