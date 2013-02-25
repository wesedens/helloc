// This file adds defines about the platform we're currently building on.
//  Operating System:
//    OS_WIN / OS_MACOSX / OS_LINUX / OS_POSIX (MACOSX or LINUX)
//  Compiler:
//    COMPILER_MSVC / COMPILER_GCC
//  Processor:
//    ARCH_CPU_X86 / ARCH_CPU_X86_64 / ARCH_CPU_X86_FAMILY (X86 or X86_64)
//    ARCH_CPU_32_BITS / ARCH_CPU_64_BITS

#ifndef BUILD_BUILD_CONFIG_H_
#define BUILD_BUILD_CONFIG_H_

// A set of macros to use for platform detection.
#if defined(__APPLE__)
#   define OS_MACOSX 1
#      if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#         define OS_IOS 1
#      endif  // defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#elif defined(ANDROID)
#   define OS_ANDROID 1
#elif defined(__native_client__)
#   define OS_NACL 1
#elif defined(__linux__)
#   define OS_LINUX 1
// Use TOOLKIT_GTK on linux if TOOLKIT_VIEWS isn't defined.
#   if !defined(TOOLKIT_VIEWS)
#      define TOOLKIT_GTK
#   endif
#elif defined(_WIN32)
#   define OS_WIN 1
#   define TOOLKIT_VIEWS 1
#elif defined(__FreeBSD__)
#   define OS_FREEBSD 1
#   define TOOLKIT_GTK
#elif defined(__OpenBSD__)
#   define OS_OPENBSD 1
#   define TOOLKIT_GTK
#elif defined(__sun)
#   define OS_SOLARIS 1
#   define TOOLKIT_GTK
#else
#   error Please add support for your platform in build/build_config.h
#endif

#if defined(USE_OPENSSL) && defined(USE_NSS)
#error Cannot use both OpenSSL and NSS
#endif

// For access to standard BSD features, use OS_BSD instead of a
// more specific macro.
#if defined(OS_FREEBSD) || defined(OS_OPENBSD)
#define OS_BSD 1
#endif

// For access to standard POSIXish features, use OS_POSIX instead of a
// more specific macro.
#if defined(OS_MACOSX) || defined(OS_LINUX) || defined(OS_FREEBSD) ||     \
    defined(OS_OPENBSD) || defined(OS_SOLARIS) || defined(OS_ANDROID) ||  \
    defined(OS_NACL)
#define OS_POSIX 1
#endif

#if defined(OS_POSIX) && !defined(OS_MACOSX) && !defined(OS_ANDROID) && \
    !defined(OS_NACL)
#define USE_X11 1  // Use X for graphics.
#endif

// Use tcmalloc
#if (defined(OS_WIN) || defined(OS_LINUX)) && !defined(NO_TCMALLOC)
#define USE_TCMALLOC 1
#endif

// Compiler detection.
#if defined(__GNUC__)
#define COMPILER_GCC 1
#elif defined(_MSC_VER)
#define COMPILER_MSVC 1
#else
#error Please add support for your compiler in build/build_config.h
#endif

// Processor architecture detection.  For more info on what's defined, see:
//   http://msdn.microsoft.com/en-us/library/b0084kay.aspx
//   http://www.agner.org/optimize/calling_conventions.pdf
//   or with gcc, run: "echo | gcc -E -dM -"
#if defined(_M_X64) || defined(__x86_64__)
#   define ARCH_CPU_X86_FAMILY    1
#   define ARCH_CPU_X86_64        1
#   define ARCH_CPU_64_BITS       1
#   define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(_M_IX86) || defined(__i386__)
#   define ARCH_CPU_X86_FAMILY    1
#   define ARCH_CPU_X86           1
#   define ARCH_CPU_32_BITS       1
#   define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(__ARMEL__)
#   define ARCH_CPU_ARM_FAMILY    1
#   define ARCH_CPU_ARMEL         1
#   define ARCH_CPU_32_BITS       1
#   define ARCH_CPU_LITTLE_ENDIAN 1
#else
#   error Please add support for your architecture in build/build_config.h
#endif


#endif  // BUILD_BUILD_CONFIG_H_
