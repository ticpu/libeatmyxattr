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
  fsynctest.result \
  test_run.sh \
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

check_PROGRAMS += \
  libeatmyxattr/test/fsynctest \
  libeatmyxattr/test/tst-key4 \
  libeatmyxattr/test/tst-invalidfd \
  libeatmyxattr/test/eatmyxattrtest \
  libeatmyxattr/test/eatmyxattrtest_largefile \
  libeatmyxattr/test/syncfstest \
  libeatmyxattr/test/fcntltest

if HAVE_PTHREAD_BARRIERS
  check_PROGRAMS += libeatmyxattr/test/tst-cancel4
endif

libeatmyxattr_test_tst_cancel4_LDADD= -lpthread

libeatmyxattr_test_tst_key4_LDADD= -lpthread

#
# Simple libeatmyxattr application
#

TESTS = $(check_PROGRAMS)

LOG_COMPILER = ${top_srcdir}/test_run.sh

test: distcheck

check-verbose:
	@LIBEATMYXATTR_TEST_ARGS="v" make check

check-debug:
	@LIBEATMYXATTR_TEST_ARGS="vvv" make check

check-valgrind:
	@LIBEATMYXATTR_TEST_PREFIX="valgrind -q --leak-check=full --show-reachable=yes --suppressions=valgrind.suppressions" make check

check-valgrind-debug:
	@LIBEATMYXATTR_TEST_PREFIX="valgrind -q --leak-check=full --show-reachable=yes --suppressions=valgrind.suppressions" LIBEATMYXATTR_TEST_ARGS="vvv" make check

check-gdb:
	@LIBEATMYXATTR_TEST_PREFIX="gdb -q" make check

check-time:
	@LIBEATMYXATTR_TEST_PREFIX="/usr/bin/time" make check

check-strace:
	@LIBEATMYXATTR_TEST_PREFIX="strace -c" make check

check-truss:
	@LIBEATMYXATTR_TEST_PREFIX="truss -c" make check

lcov: lcov-clean check
	@echo
	@echo "------------------------------------------------------"
	@echo "Make sure ./configure was run with '--enable-coverage'"
	@echo "------------------------------------------------------"
	@echo
	cd libeatmyxattr && lcov --directory . --base-directory .. --capture --output-file lcov.out
	cd libeatmyxattr && lcov --directory . --base-directory .. --extract lcov.out `pwd`/\* --output-file lcov_extract.out
	genhtml -o lcov -t libeatmyxattr libeatmyxattr/lcov_extract.out

lcov-clean: clean
	find . -name '*.gcno' -exec rm {} \;
	find . -name '*.gcda' -exec rm {} \;
	find . -name 'lcov*.out' -exec rm {} \;
