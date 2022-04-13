/* BEGIN LICENSE
 * Copyright (C) 2008-2014 Stewart Smith <stewart@flamingspork.com>
 * This program is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License version 3, as published 
 * by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranties of 
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR 
 * PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 * END LICENSE */

#include "config.h"
#include "libeatmyxattr/visibility.h"

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <stdio.h>
#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

typedef ssize_t (*libc_listxattr_t)(const char *path, char *list, size_t size);
typedef ssize_t (*libc_llistxattr_t)(const char *path, char *list, size_t size);
typedef ssize_t (*libc_flistxattr_t)(int fd, char *list, size_t size);
typedef ssize_t (*libc_getxattr_t)(const char *path, const char *name, void *value, size_t size);
typedef ssize_t (*libc_lgetxattr_t)(const char *path, const char *name, void *value, size_t size);
typedef ssize_t (*libc_fgetxattr_t)(int fd, const char *name, void *value, size_t size);

/* All the following are thread-local, to avoid initialization races between
 * threads. */
static TLS int init_running = 0;
static TLS int init_complete = 0;
static TLS libc_listxattr_t libc_listxattr= NULL;
static TLS libc_llistxattr_t libc_llistxattr= NULL;
static TLS libc_flistxattr_t libc_flistxattr= NULL;
static TLS libc_getxattr_t libc_getxattr= NULL;
static TLS libc_lgetxattr_t libc_lgetxattr= NULL;
static TLS libc_fgetxattr_t libc_fgetxattr= NULL;

#define ASSIGN_DLSYM_OR_DIE(name)			\
        libc_##name = (libc_##name##_##t)(intptr_t)dlsym(RTLD_NEXT, #name);			\
        if (!libc_##name)                       \
        {                                       \
                const char *dlerror_str = dlerror();                          \
                fprintf(stderr, "libeatmyxattr init error for %s: %s\n", #name,\
                        dlerror_str ? dlerror_str : "(null)");                \
                _exit(1);                       \
        }

#define ASSIGN_DLSYM_IF_EXIST(name)			\
        libc_##name = (libc_##name##_##t)(intptr_t)dlsym(RTLD_NEXT, #name);			\
						   dlerror();

#pragma weak pthread_testcancel

void __attribute__ ((constructor)) eatmyxattr_init(void);

void __attribute__ ((constructor)) eatmyxattr_init(void)
{
	init_running++;
	ASSIGN_DLSYM_OR_DIE(listxattr);
	ASSIGN_DLSYM_OR_DIE(llistxattr);
	ASSIGN_DLSYM_OR_DIE(flistxattr);
	ASSIGN_DLSYM_OR_DIE(getxattr);
	ASSIGN_DLSYM_OR_DIE(lgetxattr);
	ASSIGN_DLSYM_OR_DIE(fgetxattr);
	init_running--;
	init_complete++;
}

ssize_t LIBEATMYXATTR_API listxattr(const char *path, char *list, size_t size)
{
	return 0;
}

ssize_t LIBEATMYXATTR_API getxattr(const char *path, const char *name, void *value, size_t size)
{
	errno = ENODATA;
	return -1;
}

ssize_t LIBEATMYXATTR_API llistxattr(const char *path, char *list, size_t size)
{
	return 0;
}

ssize_t LIBEATMYXATTR_API lgetxattr(const char *path, const char *name, void *value, size_t size)
{
	errno = ENODATA;
	return -1;
}

ssize_t LIBEATMYXATTR_API flistxattr(int fd, char *list, size_t size)
{
	return 0;
}

ssize_t LIBEATMYXATTR_API fgetxattr(int fd, const char *name, void *value, size_t size)
{
	errno = ENODATA;
	return -1;
}
