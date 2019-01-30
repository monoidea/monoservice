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

#include <monoservice/lib/monoservice_qrcode.h>

#include <cairo.h>
#include <cairo-svg.h>

#include <stdio.h>

#include <i18n.h>

void monoservice_qrcode_class_init(MonoserviceQrcodeClass *qrcode);
void monoservice_qrcode_init(MonoserviceQrcode *qrcode);
void monoservice_qrcode_set_property(GObject *gobject,
				     guint prop_id,
				     const GValue *value,
				     GParamSpec *param_spec);
void monoservice_qrcode_get_property(GObject *gobject,
				     guint prop_id,
				     GValue *value,
				     GParamSpec *param_spec);
void monoservice_qrcode_finalize(GObject *gobject);

void monoservice_qrcode_real_encode(MonoserviceQrcode *qrcode);
void monoservice_qrcode_real_write(MonoserviceQrcode *qrcode);

/**
 * SECTION:monoservice_qrcode
 * @short_description: The qrcode object
 * @title: MonoserviceQrcode
 * @section_id:
 * @include: monoservice/lib/monoservice_qrcode.h
 *
 * #MonoserviceQrcode creates QRCodes.
 */

enum{
  PROP_0,
  PROP_URL,
  PROP_FILENAME,
  PROP_QRCODE,
};

enum{
  ENCODE,
  WRITE,
  LAST_SIGNAL,
};

static gpointer monoservice_qrcode_parent_class = NULL;

static guint qrcode_signals[LAST_SIGNAL];

GType
monoservice_qrcode_get_type()
{
  static volatile gsize g_define_type_id__volatile = 0;

  if(g_once_init_enter (&g_define_type_id__volatile)){
    GType monoservice_type_qrcode = 0;

    static const GTypeInfo monoservice_qrcode_info = {
      sizeof (MonoserviceQrcodeClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) monoservice_qrcode_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (MonoserviceQrcode),
      0,    /* n_preallocs */
      (GInstanceInitFunc) monoservice_qrcode_init,
    };

    monoservice_type_qrcode = g_type_register_static(G_TYPE_OBJECT,
						     "MonoserviceQrcode", &monoservice_qrcode_info,
						     0);

    g_once_init_leave(&g_define_type_id__volatile, monoservice_type_qrcode);
  }

  return g_define_type_id__volatile;
}

void
monoservice_qrcode_class_init(MonoserviceQrcodeClass *qrcode)
{
  GObjectClass *gobject;

  GParamSpec *param_spec;

  monoservice_qrcode_parent_class = g_type_class_peek_parent(qrcode);

  /* GObjectClass */
  gobject = (GObjectClass *) qrcode;

  gobject->set_property = monoservice_qrcode_set_property;
  gobject->get_property = monoservice_qrcode_get_property;

  gobject->finalize = monoservice_qrcode_finalize;

  /* properties */
  /**
   * MonoserviceQrcode:url:
   *
   * The assigned url.
   * 
   * Since: 1.0.0
   */
  param_spec = g_param_spec_string("url",
				   i18n_pspec("url"),
				   i18n_pspec("The assigned url"),
				   NULL,
				   G_PARAM_READABLE | G_PARAM_WRITABLE);
  g_object_class_install_property(gobject,
				  PROP_URL,
				  param_spec);

  /**
   * MonoserviceQrcode:filename:
   *
   * The assigned filename.
   * 
   * Since: 1.0.0
   */
  param_spec = g_param_spec_string("filename",
				   i18n_pspec("filename"),
				   i18n_pspec("The assigned filename"),
				   NULL,
				   G_PARAM_READABLE | G_PARAM_WRITABLE);
  g_object_class_install_property(gobject,
				  PROP_FILENAME,
				  param_spec);

  /**
   * MonoserviceQrcode:qrcode:
   *
   * The assigned qrcode.
   * 
   * Since: 1.0.0
   */
  param_spec = g_param_spec_pointer("qrcode",
				    i18n_pspec("qrcode"),
				    i18n_pspec("The assigned qrcode"),
				    G_PARAM_READABLE);
  g_object_class_install_property(gobject,
				  PROP_QRCODE,
				  param_spec);
  
  /* MonoserviceQrcode */
  qrcode->encode = monoservice_qrcode_real_encode;
  qrcode->write = monoservice_qrcode_real_write;
  
  /* signals */
  /**
   * MonoserviceQrcode::encode:
   * @qrcode: the #MonoserviceQrcode
   *
   * The ::encode signal notifies about encode event.
   *
   * Since: 1.0.0
   */
  qrcode_signals[ENCODE] =
    g_signal_new("encode",
		 G_TYPE_FROM_CLASS(qrcode),
		 G_SIGNAL_RUN_LAST,
		 G_STRUCT_OFFSET(MonoserviceQrcodeClass, encode),
		 NULL, NULL,
		 g_cclosure_marshal_VOID__VOID,
		 G_TYPE_NONE, 0);

  /**
   * MonoserviceQrcode::write:
   * @qrcode: the #MonoserviceQrcode
   *
   * The ::write signal notifies about write event.
   *
   * Since: 1.0.0
   */
  qrcode_signals[WRITE] =
    g_signal_new("write",
		 G_TYPE_FROM_CLASS(qrcode),
		 G_SIGNAL_RUN_LAST,
		 G_STRUCT_OFFSET(MonoserviceQrcodeClass, write),
		 NULL, NULL,
		 g_cclosure_marshal_VOID__VOID,
		 G_TYPE_NONE, 0);
}

void
monoservice_qrcode_init(MonoserviceQrcode *qrcode)
{
  qrcode->flags = 0;

  qrcode->url = g_strdup(MONOSERVICE_QRCODE_DEFAULT_URL);
  qrcode->filename = g_strdup(MONOSERVICE_QRCODE_DEFAULT_FILENAME);
  
  qrcode->qrcode = NULL;
}

void
monoservice_qrcode_set_property(GObject *gobject,
				guint prop_id,
				const GValue *value,
				GParamSpec *param_spec)
{
  MonoserviceQrcode *qrcode;

  qrcode = MONOSERVICE_QRCODE(gobject);

  switch(prop_id){
  case PROP_URL:
  {
    gchar *url;

    url = (gchar *) g_value_get_string(value);

    if(url == qrcode->url){
      return;
    }

    if(qrcode->url != NULL){
      g_free(qrcode->url);
    }
      
    qrcode->url = g_strdup(url);
  }
  break; 
  case PROP_FILENAME:
  {
    gchar *filename;

    filename = (gchar *) g_value_get_string(value);

    if(filename == qrcode->filename){
      return;
    }

    if(qrcode->filename != NULL){
      g_free(qrcode->filename);
    }
      
    qrcode->filename = g_strdup(filename);
  }
  break; 
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
monoservice_qrcode_get_property(GObject *gobject,
				guint prop_id,
				GValue *value,
				GParamSpec *param_spec)
{
  MonoserviceQrcode *qrcode;

  qrcode = MONOSERVICE_QRCODE(gobject);

  switch(prop_id){
  case PROP_URL:
  {
    g_value_set_string(value, qrcode->url);
  }
  break;
  case PROP_FILENAME:
  {
    g_value_set_string(value, qrcode->filename);
  }
  break;
  case PROP_QRCODE:
  {
    g_value_set_pointer(value, qrcode->qrcode);
  }
  break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
monoservice_qrcode_finalize(GObject *gobject)
{
  MonoserviceQrcode *qrcode;

  qrcode = (MonoserviceQrcode *) gobject;

  g_free(qrcode->url);
  g_free(qrcode->filename);

  if(qrcode->qrcode != NULL){
    QRcode_free(qrcode->qrcode);
  }
  
  /* call parent */
  G_OBJECT_CLASS(monoservice_qrcode_parent_class)->finalize(gobject);
}

void
monoservice_qrcode_real_encode(MonoserviceQrcode *qrcode)
{
  qrcode->qrcode = QRcode_encodeString8bit(qrcode->url,
					   0,
					   QR_ECLEVEL_L);
}

void
monoservice_qrcode_encode(MonoserviceQrcode *qrcode)
{
  g_return_if_fail(MONOSERVICE_IS_QRCODE(qrcode));
  
  g_object_ref((GObject *) qrcode);
  g_signal_emit(G_OBJECT(qrcode),
		qrcode_signals[ENCODE], 0);
  g_object_unref((GObject *) qrcode);
}

void
monoservice_qrcode_real_write(MonoserviceQrcode *qrcode)
{
  FILE *f;

  guint width, height;
  guint i, j;
  
  static const guint color_count = 3;
  static const guint char_per_pixel = 1;
  static const guint border_width = 1;

  width = qrcode->qrcode->width;
  height = qrcode->qrcode->width;
  
  f = fopen(qrcode->filename,
	    "w");

  fprintf(f, "/* XPM */\n");

  fprintf(f, "static char *XPM_qrcode[] = {\n");

  fprintf(f, "\"%d %d %d %d XPMEXT\",\n", width, height, color_count, char_per_pixel);
  fprintf(f, "\"  c NONE\",\n");
  fprintf(f, "\". c #FFFFFF\",\n");
  fprintf(f, "\"# c #000000\",\n");

  /* border top */
  for(i = 0; i < border_width; i++){
    fprintf(f, "\"");
    
    for(j = 0; j < width + (2 * border_width); j++){
      fputc(' ', f);
    }

    fprintf(f, "\",\n");
  }

  /* qrcode */
  for(i = 0; i < height; i++){
    fprintf(f, "\"");

    /* border left */
    for(j = 0; j < border_width; j++){
      fputc(' ', f);
    }

    /* content */
    for(j = 0; j < width; j++){
      if(qrcode->qrcode->data[i * qrcode->qrcode->width + j] % 2 == 1){
	fputc('#', f);
      }else{
	fputc('.', f);
      }
    }
    
    /* border right */
    for(j = 0; j < border_width; j++){
      fputc(' ', f);
    }

    fprintf(f, "\",\n");
  }
    
  /* border bottom */
  for(i = 0; i < border_width; i++){
    fprintf(f, "\"");
    
    for(j = 0; j < width + (2 * border_width); j++){
      fputc(' ', f);
    }

    fprintf(f, "\",\n");
  }

  /* complete */
  fprintf(f, "\"XPMEXT author monothek.ch\",\n");
  fprintf(f, "\"XPMENDEXT\",\n");

  fprintf(f, "}\n");

  fclose(f);
}

void
monoservice_qrcode_write(MonoserviceQrcode *qrcode)
{
  g_return_if_fail(MONOSERVICE_IS_QRCODE(qrcode));
  
  g_object_ref((GObject *) qrcode);
  g_signal_emit(G_OBJECT(qrcode),
		qrcode_signals[WRITE], 0);
  g_object_unref((GObject *) qrcode);
}

void
monoservice_qrcode_export_svg(MonoserviceQrcode *qrcode,
			      gchar *svg_filename)
{
  cairo_surface_t *svg_surface;
  cairo_t *cr;
  
  guint svg_width, svg_height;
  gdouble svg_square_size;
  guint width, height;
  guint i, j;
  
  svg_width = MONOSERVICE_QRCODE_DEFAULT_SVG_WIDTH;
  svg_height = MONOSERVICE_QRCODE_DEFAULT_SVG_HEIGHT;
  
  svg_surface = cairo_svg_surface_create(svg_filename,
					 svg_width,
					 svg_height);
  cairo_svg_surface_restrict_to_version(svg_surface,
					CAIRO_SVG_VERSION_1_2);
  
  cr = cairo_create(svg_surface);

  /* background */
  cairo_set_source_rgba(cr,
			1.0,
			1.0,
			1.0,
			1.0);
  
  cairo_rectangle(cr,
		  0.0,
		  0.0,
		  svg_width,
		  svg_height);
  cairo_fill(cr);

  /* qrcode */
  width = qrcode->qrcode->width;
  height = qrcode->qrcode->width;

  svg_square_size = (gdouble) svg_width / (gdouble) width;
  
  cairo_set_source_rgb(cr,
		       0.0,
		       0.0,
		       0.0);

  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      if(qrcode->qrcode->data[i * qrcode->qrcode->width + j] % 2 == 1){
	cairo_rectangle(cr,
			j * svg_square_size,
			i * svg_square_size,
			svg_square_size,
			svg_square_size);
	cairo_fill(cr);
      }
    }
  }

  cairo_surface_flush(svg_surface);
  cairo_surface_finish(svg_surface);

  cairo_surface_destroy(svg_surface);
  
  cairo_destroy(cr);
}

void
monoservice_qrcode_export_png(MonoserviceQrcode *qrcode,
			      gchar *png_filename)
{
  cairo_surface_t *png_surface;
  cairo_t *cr;
  
  guint png_width, png_height;
  gdouble png_square_size;
  guint width, height;
  guint i, j;
  
  png_width = MONOSERVICE_QRCODE_DEFAULT_PNG_WIDTH;
  png_height = MONOSERVICE_QRCODE_DEFAULT_PNG_HEIGHT;
  
  png_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
					   png_width,
					   png_height);
  
  cr = cairo_create(png_surface);

  /* background */
  cairo_set_source_rgba(cr,
			1.0,
			1.0,
			1.0,
			1.0);
  
  cairo_rectangle(cr,
		  0.0,
		  0.0,
		  png_width,
		  png_height);
  cairo_fill(cr);

  /* qrcode */
  width = qrcode->qrcode->width;
  height = qrcode->qrcode->width;

  png_square_size = (gdouble) png_width / (gdouble) width;
  
  cairo_set_source_rgb(cr,
		       0.0,
		       0.0,
		       0.0);

  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      if(qrcode->qrcode->data[i * qrcode->qrcode->width + j] % 2 == 1){
	cairo_rectangle(cr,
			j * png_square_size,
			i * png_square_size,
			png_square_size,
			png_square_size);
	cairo_fill(cr);
      }
    }
  }

  cairo_surface_flush(png_surface);
  cairo_surface_write_to_png(png_surface,
			     png_filename);

  cairo_surface_finish(png_surface);
  cairo_surface_destroy(png_surface);
  
  cairo_destroy(cr);
}

/**
 * monoservice_qrcode_new:
 *
 * Creates an #MonoserviceQrcode
 *
 * Returns: a new #MonoserviceQrcode
 *
 * Since: 1.0.0
 */
MonoserviceQrcode*
monoservice_qrcode_new()
{
  MonoserviceQrcode *qrcode;

  qrcode = (MonoserviceQrcode *) g_object_new(MONOSERVICE_TYPE_QRCODE,
					      NULL);
  
  return(qrcode);
}
