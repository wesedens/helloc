// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source is governed by a BSD-style license that can be
// found in the LICENSE file.

// config.h is generated from version.h.in.  Edit the source!

#define PACKAGE           "libconfig-test"
#define PACKAGE_NAME      "libconfig-wedens"
#define PACKAGE_URL       "wes.k.edens@gmail.com"
#define PACKAGE_BUGREPORT "wes.k.edens@gmail.com"
#define PACKAGE_STRING    (PACKAGE "-" VERSION)
#define PACKAGE_VERSION   VERSION

// Branding Information
#define COMPANY_FULLNAME_STRING  "Johns Hopkins University Applied Physics Lab"
#define COMPANY_SHORTNAME_STRING "JHUAPL"
#define PRODUCT_FULLNAME_STRING  "libconfig-wedens"
#define PRODUCT_SHORTNAME_STRING "hw"
#define COPYRIGHT_STRING         "bob lob law"
#define OFFICIAL_BUILD_STRING    "build"


#if ((__GNUC__ \
      ? defined __GNUC_STDC_INLINE__ && __GNUC_STDC_INLINE__ \
      : 199901L <= __STDC_VERSION__) \
     && !defined __APPLE__)
# define _INLINE inline
# define _EXTERN_INLINE extern inline
#elif 2 < __GNUC__ + (7 <= __GNUC_MINOR__) && !defined __APPLE__
# if __GNUC_GNU_INLINE__
   /* __gnu_inline__ suppresses a GCC 4.2 diagnostic.  */
#  define _INLINE extern inline __attribute__ ((__gnu_inline__))
# else
#  define _INLINE extern inline
# endif
# define _EXTERN_INLINE extern
#else
# define _INLINE static _UNUSED
# define _EXTERN_INLINE static _UNUSED
#endif



/* The __const__ attribute was added in gcc 2.95.  */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
# define _ATTRIBUTE_CONST __attribute__ ((__const__))
#else
# define _ATTRIBUTE_CONST /* empty */
#endif

