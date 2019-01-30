# Copyright (C) 2019 Jo\u00EBl Kr\u00E4hemann
# 
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.

AUTOMAKE_OPTIONS = foreign
SUBDIRS = po

ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -std=gnu99 -include errno.h -I$(top_srcdir) -DMONOSERVICE_DEVEL_MODE=1 -DSRCDIR=\"$(srcdir)\" -DDESTDIR=\"$(DESTDIR)$(datadir)\" -DPACKAGE_VERSION=\"$(PACKAGE_VERSION)\" -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security

# what flags you want to pass to the C compiler & linker
CFLAGS =  @CFLAGS@
LDFLAGS = @LDFLAGS@ $(LTLIBINTL)
LIBTOOL_DEPS = @LIBTOOL_DEPS@

monoservice_www_CFLAGS = @MONOSERVICE_CFLAGS@
monoservice_www_LDFLAGS = @MONOSERVICE_LDFLAGS@

monoservice_status_cgi_CFLAGS = @MONOSERVICE_CFLAGS@
monoservice_status_cgi_LDFLAGS = @MONOSERVICE_LDFLAGS@

monoservice_config_cgi_CFLAGS = @MONOSERVICE_CFLAGS@
monoservice_config_cgi_LDFLAGS = @MONOSERVICE_LDFLAGS@

monoservice_control_cgi_CFLAGS = @MONOSERVICE_CFLAGS@
monoservice_control_cgi_LDFLAGS = @MONOSERVICE_LDFLAGS@

monoservice_upload_cgi_CFLAGS = @MONOSERVICE_CFLAGS@
monoservice_upload_cgi_LDFLAGS = @MONOSERVICE_LDFLAGS@

monoservice_download_cgi_CFLAGS = @MONOSERVICE_CFLAGS@
monoservice_download_cgi_LDFLAGS = @MONOSERVICE_LDFLAGS@

monoservice_video_cgi_CFLAGS = @MONOSERVICE_CFLAGS@
monoservice_video_cgi_LDFLAGS = @MONOSERVICE_LDFLAGS@

localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

bin_PROGRAMS = monoservice-www \
	monoservice-status.cgi \
	monoservice-config.cgi \
	monoservice-control.cgi \
	monoservice-upload.cgi \
	monoservice-download.cgi \
	monoservice-video.cgi

libmonoservicedir = $(libdir)/monoservice
libmonoservice_LTLIBRARIES = libmonoservice.la

EXTRA_DIST = config.rpath m4/ChangeLog  config.rpath \
	monoservice/config.h.in \
	gtk-doc.make \
	aclocal.m4 \
	README \
	m4/Makefile.am \
	m4/Makefile.in \
	monoservice/i18n.h \
	monoservice/gettext.h \
	m4/README \
	po/README

CLEANFILES = \
	m4/Makefile

libmonoservice_la_HEADERS_0 = $(libmonoservice_lib_h_sources) $(libmonoservice_db_h_sources)
libmonoservice_la_SOURCES = $(libmonoservice_la_HEADERS_0) $(libmonoservice_lib_c_sources) $(libmonoservice_db_c_sources)

# library libmonoservice
libmonoservice_la_CFLAGS = $(MYSQLCLIENT_CFLAGS) $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
libmonoservice_la_LDFLAGS = $(LDFLAGS) -version-info 1:0:0 -shared -fPIC -Wl,-soname,libmonoservice.so -pthread
libmonoservice_la_LIBADD = -ldl -lm $(MYSQLCLIENT_LIBS) $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# monoservice WWW
monoservice_www_SOURCES = $(monoservice_www_c_sources) $(monoservice_wwwheaders)

monoservice_www_CFLAGS += $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
monoservice_www_LDFLAGS += -pthread
monoservice_www_LDADD = libmonoservice.la -ldl -lm $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# monoservice-status.cgi
monoservice_status_cgi_SOURCES = $(monoservice_status_cgi_c_sources) $(monoservice_status_cgiheaders)

monoservice_status_cgi_CFLAGS += $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
monoservice_status_cgi_LDFLAGS += -pthread
monoservice_status_cgi_LDADD = -ldl -lm $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# monoservice-config.cgi
monoservice_config_cgi_SOURCES = $(monoservice_config_cgi_c_sources) $(monoservice_config_cgiheaders)

monoservice_config_cgi_CFLAGS += $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
monoservice_config_cgi_LDFLAGS += -pthread
monoservice_config_cgi_LDADD = -ldl -lm $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# monoservice-control.cgi
monoservice_control_cgi_SOURCES = $(monoservice_control_cgi_c_sources) $(monoservice_control_cgiheaders)

monoservice_control_cgi_CFLAGS += $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
monoservice_control_cgi_LDFLAGS += -pthread
monoservice_control_cgi_LDADD = -ldl -lm $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# monoservice-upload.cgi
monoservice_upload_cgi_SOURCES = $(monoservice_upload_cgi_c_sources) $(monoservice_upload_cgiheaders)

monoservice_upload_cgi_CFLAGS += $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
monoservice_upload_cgi_LDFLAGS += -pthread
monoservice_upload_cgi_LDADD = -ldl -lm $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# monoservice-download.cgi
monoservice_download_cgi_SOURCES = $(monoservice_download_cgi_c_sources) $(monoservice_download_cgiheaders)

monoservice_download_cgi_CFLAGS += $(LIBXSLT_CFLAGS) $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
monoservice_download_cgi_LDFLAGS += -pthread
monoservice_download_cgi_LDADD = -ldl -lm $(LIBXSLT_LIBS) $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# monoservice-video.cgi
monoservice_video_cgi_SOURCES = $(monoservice_video_cgi_c_sources) $(monoservice_video_cgiheaders)

monoservice_video_cgi_CFLAGS += $(LIBXSLT_CFLAGS) $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
monoservice_video_cgi_LDFLAGS += -pthread
monoservice_video_cgi_LDADD = -ldl -lm $(LIBXSLT_LIBS) $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# libmonoservice lib files
deprecated_libmonoservice_lib_h_sources =

libmonoservice_lib_h_sources = \
	$(deprecated_libmonoservice_lib_h_sources) \
	monoservice/lib/monoservice_media_queue.h \
	monoservice/lib/monoservice_qrcode.h

deprecated_libmonoservice_lib_c_sources =

libmonoservice_lib_c_sources = \
	$(deprecated_libmonoservice_lib_c_sources) \
	monoservice/lib/monoservice_media_queue.c \
	monoservice/lib/monoservice_qrcode.c

# libmonoservice db files
deprecated_libmonoservice_db_h_sources =

libmonoservice_db_h_sources = \
	$(deprecated_libmonoservice_db_h_sources) \
	monoservice/db/monoservice_mysql_connector.h \
	monoservice/db/monoservice_mysql_connector_manager.h \
	monoservice/db/monoservice_media_account_dao.h \
	monoservice/db/monoservice_billing_address_dao.h \
	monoservice/db/monoservice_payment_transaction_dao.h

deprecated_libmonoservice_db_c_sources =

libmonoservice_db_c_sources = \
	$(deprecated_libmonoservice_db_c_sources) \
	monoservice/db/monoservice_mysql_connector.c \
	monoservice/db/monoservice_mysql_connector_manager.c \
	monoservice/db/monoservice_media_account_dao.c \
	monoservice/db/monoservice_billing_address_dao.c \
	monoservice/db/monoservice_payment_transaction_dao.c

# monoservice_www all files
monoservice_wwwheaders = \
	monoservice/monoservice_main.h

monoservice_www_c_sources = \
	monoservice/monoservice_main.c

# monoservice_status_cgi all files
monoservice_status_cgiheaders =

monoservice_status_cgi_c_sources = \
	monoservice/cgi-bin/monoservice_status.c

# monoservice_config_cgi all files
monoservice_config_cgiheaders =

monoservice_config_cgi_c_sources = \
	monoservice/cgi-bin/monoservice_config.c

# monoservice_control_cgi all files
monoservice_control_cgiheaders =

monoservice_control_cgi_c_sources = \
	monoservice/cgi-bin/monoservice_control.c

# monoservice_upload_cgi all files
monoservice_upload_cgiheaders =

monoservice_upload_cgi_c_sources = \
	monoservice/cgi-bin/monoservice_upload.c

# monoservice_download_cgi all files
monoservice_download_cgiheaders =

monoservice_download_cgi_c_sources = \
	monoservice/cgi-bin/monoservice_download.c

# monoservice_video_cgi all files
monoservice_video_cgiheaders =

monoservice_video_cgi_c_sources = \
	monoservice/cgi-bin/monoservice_video.c

check-gettext:
	@if test x$(USE_NLS) != "xyes" ; then echo "Missing gettext. Rerun configure and check for" \
	"'checking whether to use NLS... yes'!" ; exit 1 ; fi

update-po: check-gettext
	@find $(srcdir)/monoservice/{lib}/ -name "*.c" -print | sort > $(srcdir)/po/POTFILES.in.2 ; \
	if diff $(srcdir)/po/POTFILES.in $(srcdir)/po/POTFILES.in.2 >/dev/null 2>&1 ; then \
		rm -f $(srcdir)/po/POTFILES.in.2 ; \
	else \
		mv $(srcdir)/po/POTFILES.in.2 $(srcdir)/po/POTFILES.in ; \
	fi
	cd po && $(MAKE) $(AM_MAKEFLAGS) update-po

update-gmo: check-gettext
	cd po && $(MAKE) $(AM_MAKEFLAGS) update-gmo

force-update-gmo: check-gettext
	touch po/*.po
	cd po && $(MAKE) $(AM_MAKEFLAGS) update-gmo

force-update-gmo-%: check-gettext
	@language=`echo $@ | sed s/force-update-gmo-//` ; \
	if test ! -f po/$$language.po ; then echo "file po/$$language.po does not exist" ; exit 1 ; fi ; \
	touch po/$$language.po ; \
	cd po && $(MAKE) $(AM_MAKEFLAGS) update-gmo

.PHONY: check-gettext update-po update-gmo force-update-gmo
