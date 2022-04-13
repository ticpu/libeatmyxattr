/*
 * Libeatmyxattr
 *
 * Copyright (C) 2010 Eric Day (eday@oddments.org)
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See the
 * COPYING file in the root project directory for full text.
 */

/**
 * @file
 * @brief Common Macro Definitions
 */

#ifndef LIBEATMYXATTR_VISIBILITY_H
#define LIBEATMYXATTR_VISIBILITY_H

/**
 * Be sure to put LIBEATMYXATTR_API in front of all public API symbols, or one of
 * the other macros as appropriate. The default visibility without a macro is
 * to be hidden (LIBEATMYXATTR_LOCAL).
 */

#if defined(BUILDING_LIBEATMYXATTR) && defined(HAVE_VISIBILITY)
# if defined(__GNUC__)
#  define LIBEATMYXATTR_API __attribute__ ((visibility("default")))
#  define LIBEATMYXATTR_INTERNAL_API __attribute__ ((visibility("hidden")))
#  define LIBEATMYXATTR_API_DEPRECATED __attribute__ ((deprecated,visibility("default")))
#  define LIBEATMYXATTR_LOCAL  __attribute__ ((visibility("hidden")))
# elif (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)) || (defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x550))
#  define LIBEATMYXATTR_API __global
#  define LIBEATMYXATTR_INTERNAL_API __hidden
#  define LIBEATMYXATTR_API_DEPRECATED __global
#  define LIBEATMYXATTR_LOCAL __hidden
# elif defined(_MSC_VER)
#  define LIBEATMYXATTR_API extern __declspec(dllexport)
#  define LIBEATMYXATTR_INTERNAL_API extern __declspec(dllexport)
#  define LIBEATMYXATTR_DEPRECATED_API extern __declspec(dllexport)
#  define LIBEATMYXATTR_LOCAL
# endif
#else  /* defined(BUILDING_LIBEATMYXATTR) && defined(HAVE_VISIBILITY) */
# if defined(_MSC_VER)
#  define SCALESTACK_API extern __declspec(dllimport)
#  define LIBEATMYXATTR_INTERNAL_API extern __declspec(dllimport)
#  define LIBEATMYXATTR_API_DEPRECATED extern __declspec(dllimport)
#  define LIBEATMYXATTR_LOCAL
# else
#  define LIBEATMYXATTR_API
#  define LIBEATMYXATTR_INTERNAL_API
#  define LIBEATMYXATTR_API_DEPRECATED
#  define LIBEATMYXATTR_LOCAL
# endif /* defined(_MSC_VER) */
#endif  /* defined(BUILDING_LIBEATMYXATTR) && defined(HAVE_VISIBILITY) */


#endif /* LIBEATMYXATTR_VISIBILITY_H */
