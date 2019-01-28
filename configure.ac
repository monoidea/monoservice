#                                               -*- Autoconf -*-
# Copyright (C) 2019 Jo\u00EBl Kr\u00E4hemann
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([monoservice],[1.0.0-PRERELEASE],[jkraehemann@gmail.com])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([monoservice/config.h.in])
AC_CONFIG_HEADERS([monoservice/config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19.8])

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL

# libtool
LT_PREREQ([2.4.2])
LT_INIT
AC_SUBST([LIBTOOL_DEPS])
AC_ENABLE_SHARED

AC_SUBST([MONOSERVICE_CFLAGS])
AC_SUBST([MONOSERVICE_LDFLAGS])

# FIXME: Replace `main' with a function in `-ldl':
AC_CHECK_LIB([dl], [main], , AC_MSG_ERROR("No dl library present"))

# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main], , AC_MSG_ERROR("No math library present"))

PKG_CHECK_MODULES([LIBXML2], [libxml-2.0 >= 2.8.0])
AC_SUBST(LIBXML2_CFLAGS)
AC_SUBST(LIBXML2_LIBS)

PKG_CHECK_MODULES([LIBXSLT], [libxslt >= 1.1.32])
AC_SUBST(LIBXSLT_CFLAGS)
AC_SUBST(LIBXSLT_LIBS)

PKG_CHECK_MODULES([GOBJECT], [gobject-2.0 >= 2.32.3 glib-2.0 >= 2.32.3 gmodule-2.0 >= 2.32.3 gthread-2.0 >= 2.32.3])
AC_SUBST(GOBJECT_CFLAGS)
AC_SUBST(GOBJECT_LIBS)

PKG_CHECK_MODULES([LIBQRENCODE], [libqrencode >= 4.0.0])
AC_SUBST(LIBQRENCODE_CFLAGS)
AC_SUBST(LIBQRENCODE_LIBS)

PKG_CHECK_MODULES([MYSQLCLIENT], [mysqlclient >= 20.3.11])
AC_SUBST(MYSQLCLIENT_CFLAGS)
AC_SUBST(MYSQLCLIENT_LIBS)

PKG_CHECK_MODULES([CAIRO], [cairo >= 1.16.0])
AC_SUBST(CAIRO_CFLAGS)
AC_SUBST(CAIRO_LIBS)

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

# check for gtk-doc
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])

AM_EXTRA_RECURSIVE_TARGETS([monoservice-docs])
AC_CONFIG_FILES([
Makefile
po/Makefile.in])

AC_OUTPUT
