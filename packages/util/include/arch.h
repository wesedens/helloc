/**
 *  @file
 *  @author Wes Edens
 *  @date 10/05/2011
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

#ifndef arch_H_
#define arch_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined _WIN32
#  if defined _MATLAB32
#     define _ARCH_PC_MATLAB32
#  else
#     define _ARCH_PC
#  endif
#elif defined __vxworks
#  if defined _ARCH_PPC
#    define _ARCH_MCP750
#  elif defined __sparc
#    define _ARCH_LEON
#  elif defined __embedded__
#    define _ARCH_ML510
#  else
#    error No valid architecture found
#  endif
#elif defined __linux__
#  define _ARCH_NIX
#else
#  error No valid architecture found
#endif


#ifdef __cplusplus
}
#endif

#endif /* arch_H_ */
