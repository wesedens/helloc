/**
 *  @file
 *  @author Wes Edens
 *  @date 02/08/2013
 *
 *  @brief finds processor being compiled for
 *
 *  find which processor we are compiling on so we can use the correct headers,
 *  types, endianness...
 *
 *  Preprocessor check to see if we are on:\n
 *    1. regular x86 pc : _X86\n
 *    2. ML510 PowerPC  : __embedded__\n
 *    3. MCP750         : __vxworks\n
 *  I just looked at the defines of each compiler and picked unique ones. We
 *  May want to put something else here. my check was
 *  gcc/powerpc-eabi-gcc/g++powerpc\n
 *  this command lists all the preprocessor definitions
 *  @code
 *  gcc -E -dM foo.h > dump
 *  @endcode
 */

#ifndef build_config_H_
#define build_config_H_

#ifdef __cplusplus
extern "C" {
#endif

// A set of macros to use for platform detection.
#if defined(__APPLE__)
#   define OS_MACOSX      1
#elif defined(__linux__)
#   define OS_LINUX       1
#elif defined(_WIN32)
#   define OS_WIN         1
#elif defined(__vxworks)
#   define OS_VXWORKS     1
#else
#   error Please add support for your platform in build_config.h
#endif


#if defined(_MATLAB32)
#   define OS_MATLAB
#endif

// For access to standard POSIXish features, use OS_POSIX instead of a
// more specific macro.
#if defined(OS_MACOSX) || defined(OS_LINUX)
#   define OS_POSIX 1
#endif

// Compiler detection.
#if defined(__GNUC__)
#   define COMPILER_GCC 1
#elif defined(_MSC_VER)
#   define COMPILER_MSVC 1
#else
#   error Please add support for your compiler in build_config.h
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
#elif defined(_ARCH_PPC)
#   define ARCH_CPU_PPC_FAMILY    1
#   define ARCH_CPU_PPC           1
#   define ARCH_CPU_32_BITS       1
#   define ARCH_CPU_BIG_ENDIAN    1
#   define ARCH_CPU_MCP750        1
#elif defined(__sparc)
#   define ARCH_CPU_LEON_FAMILY   1
#   define ARCH_CPU_LEON          1
#   define ARCH_CPU_32_BITS       1
#   define ARCH_CPU_BIG_ENDIAN    1
#   define ARCH_CPU_LEON          1
#elif defined(__embedded__)
#   define ARCH_CPU_PPC_FAMILY    1
#   define ARCH_CPU_PPC440        1
#   define ARCH_CPU_32_BITS       1
#   define ARCH_CPU_BIG_ENDIAN    1
#   define ARCH_CPU_ML510         1
#else
#   error Please add support for your architecture in build_config.h
#endif

#ifdef __cplusplus
}
#endif

#endif /* build_config_H_ */
