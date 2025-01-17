#!/bin/sh
#
# Copyright ©: 2010, Modestas Vainius <modax@debian.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

libeatmyxattr="/usr/local/lib/libeatmyxattr"
name="eatmyxattr"

if [ "x`uname`" = "xDarwin" ]; then
	libeatmyxattr="$libeatmyxattr.dylib"
else
	libeatmyxattr="$libeatmyxattr.so"
fi

eatmyxattr_error()
{
    echo "$name error: $1" >&2
    exit 1
}

eatmyxattr_exec()
{
    local cmd
    cmd="$1"
    if [ "${cmd#*/*}" = "${cmd}" ]; then
        # $cmd does not contain '/'. Look in $PATH avoiding loops with self.
        local self save_ifs path exe ok

        self="`readlink -f "$0"`"
        save_ifs="$IFS"
        IFS=":"
        ok=""
        for path in $PATH; do
            exe="${path}/$cmd"
            # Avoid loops with self
            if [ -x "$exe" ] && [ "`readlink -f "$exe"`" != "$self" ]; then
                ok="yes"
                break
            fi
        done
        IFS="$save_ifs"
        if [ -n "$ok" ]; then
            cmd="$exe"
        else
            eatmyxattr_error "unable to find '$cmd' in PATH"
        fi
    fi

    # Preload libeatmyxattr
    if [ `uname` = "Darwin" ]; then
	export DYLD_FORCE_FLAT_NAMESPACE=1
	export DYLD_INSERT_LIBRARIES="$libeatmyxattr"
    else
        if [ -n "$LD_PRELOAD" ]; then
            export LD_PRELOAD="$libeatmyxattr $LD_PRELOAD"
        else
            export LD_PRELOAD="$libeatmyxattr"
        fi
    fi

    # Execute requested command
    shift
    exec "$cmd" "$@"
}

# Verify environment
if [ ! -f "$libeatmyxattr" ]; then
    eatmyxattr_error "could not find $name library $libeatmyxattr"
fi
