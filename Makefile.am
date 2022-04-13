#
# Libeatmyxattr
#
### BEGIN LICENSE
# Copyright (C) 2008-2021 Stewart Smith <stewart@flamingspork.com>
# This program is free software: you can redistribute it and/or modify it 
# under the terms of the GNU General Public License version 3, as published 
# by the Free Software Foundation.
# 
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranties of 
# MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR 
# PURPOSE.  See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along 
# with this program.  If not, see <http://www.gnu.org/licenses/>.
### END LICENSE

ACLOCAL_AMFLAGS = -I m4
#LDADD = libeatmyxattr.la

AUTOMAKE_OPTIONS = parallel-tests

bin_PROGRAMS =
check_PROGRAMS =
noinst_PROGRAMS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =
nobase_include_HEADERS =
noinst_HEADERS =
CLEANFILES = $(bin_SCRIPTS) $(libexec_SCRIPTS)
DISTCLEANFILES = config/top.h
EXTRA_DIST = \
  README.md \
  AUTHORS \
  eatmyxattr.in \
  eatmyxattr.sh.in \
  debian/changelog \
  debian/compat \
  debian/control \
  debian/copyright \
  debian/docs \
  debian/README.Debian \
  debian/rules \
  debian/source \
  libeatmyxattr.spec


bin_SCRIPTS = eatmyxattr
libexec_SCRIPTS = eatmyxattr.sh

do_subst = @SED@ \
	-e 's!@''libdir''@!$(libdir)!g' \
	-e 's!@''libexecdir''@!$(libexecdir)!g'

eatmyxattr: eatmyxattr.in Makefile
	$(do_subst) $(srcdir)/eatmyxattr.in > $@
	chmod +x eatmyxattr

eatmyxattr.sh: eatmyxattr.sh.in Makefile
	$(do_subst) $(srcdir)/eatmyxattr.sh.in > $@

#
# libeatmyxattr
#

lib_LTLIBRARIES += libeatmyxattr.la

libeatmyxattr_la_SOURCES = \
  libeatmyxattr/libeatmyxattr.c

noinst_HEADERS += \
  libeatmyxattr/visibility.h

libeatmyxattr_la_CFLAGS = \
	$(AM_CFLAGS) \
  $(NO_WERROR) \
	-DBUILDING_LIBEATMYXATTR

libeatmyxattr_la_LIBADD = $(LIBDL_LIBS) -ldl
libeatmyxattr_la_LDFLAGS = $(AM_LDFLAGS) -avoid-version

#install-exec-hook:
#	find $(DESTDIR)$(libdir) -type f -name \*.la |xargs rm -f
