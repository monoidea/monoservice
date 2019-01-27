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

localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

bin_PROGRAMS=monoservice-www

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

libmonoservice_la_HEADERS_0 = $(libmonoservice_lib_h_sources)
libmonoservice_la_SOURCES = $(libmonoservice_la_HEADERS_0) $(libmonoservice_lib_c_sources)

# library libmonoservice
libmonoservice_la_CFLAGS = $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
libmonoservice_la_LDFLAGS = $(LDFLAGS) -version-info 1:0:0 -shared -fPIC -Wl,-soname,libmonoservice.so -pthread
libmonoservice_la_LIBADD = -ldl -lm $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# monoservice
monoservice_www_SOURCES = $(monoservice_www_c_sources) $(monoservice_wwwheaders)

monoservice_www_CFLAGS += $(LIBXML2_CFLAGS) $(GOBJECT_CFLAGS) $(LIBQRENCODE_CFLAGS) $(CAIRO_CFLAGS)
monoservice_www_LDFLAGS += -pthread
monoservice_www_LDADD = libmonoservice.la -ldl -lm $(LIBXML2_LIBS) $(GOBJECT_LIBS) $(LIBQRENCODE_LIBS) $(CAIRO_LIBS)

# libmonoservice all files
deprecated_libmonoservice_lib_h_sources =

libmonoservice_lib_h_sources = \
	$(deprecated_libmonoservice_lib_h_sources) \
	monoservice/lib/monoservice_qrcode.h

deprecated_libmonoservice_lib_c_sources =

libmonoservice_lib_c_sources = \
	$(deprecated_libmonoservice_lib_c_sources) \
	monoservice/lib/monoservice_qrcode.c

# monoservice_www all files
monoservice_wwwheaders = \
	monoservice/monoservice_main.h

monoservice_www_c_sources = \
	monoservice/monoservice_main.c

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
