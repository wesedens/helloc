/**
 *  @file
 *  @author Wes Edens
 *  @date 10/05/2011
 *
 *  @brief defines common types for all archs
 *
 *  this file determines which processor we are compiling on so we can use the
 *  correct types between architectures
 *
 *  Preprocessor check to see if we are on\n
 *    1. regular x86 pc : _ARCH_PC\n
 *    2. ML510 PowerPC  : _ARCH_ML510\n
 *    3. MCP750         : _ARCH_MCP750\n
 *  we are looking to use the standard definitions (we will have to do some
 *    remapping for xilinx)
 */

#ifndef types_H_
#define types_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "build_config.h"

#if defined(OS_WIN) && !defined(OS_MATLAB)
   #include <stdint.h>
   
   #define INLINE 
   #define __PACKED
   #define __CONST
   #define __NORETURN
#elif defined(OS_VXWORKS)
   #include <types/vxTypes.h>
   
   #define INLINE     inline
   #define __PACKED   __attribute__ ((packed))
   #define __CONST    __attribute__ ((const))
   #define __NORETURN __attribute__ ((noreturn))
#elif defined(ARCH_CPU_ML510)
   #include <xil_types.h>
   // We want standart type definitions
   #define uint8_t     u8
   #define uint16_t    u16
   #define uint32_t    u32

   #define int8_t      s8
   #define int16_t     s16
   #define int32_t     s32
   
   #define INLINE     inline
   #define __PACKED   __attribute__ ((packed))
   #define __CONST    __attribute__ ((const))
   #define __NORETURN __attribute__ ((noreturn))
#elif defined(OS_MATLAB)
   #define uint8_t     unsigned char
   #define uint16_t    unsigned short
   #define uint32_t    unsigned

   #define int8_t      char
   #define int16_t     short
   #define int32_t     int
   
   #define __PACKED
   #define INLINE
   #define __CONST
   #define __NORETURN
#elif defined(OS_LINUX)
   #include <stdint.h>
   
   #define INLINE     inline
   #define __PACKED   __attribute__ ((packed))
   #define __CONST    __attribute__ ((const))
   #define __NORETURN __attribute__ ((noreturn))
   #define __USED     __attribute__((__used__))
   #define __UNUSED   __attribute__((__unused__))
#else
  #error No valid type found
#endif

#ifdef __cplusplus
}
#endif

#endif /* types_H_ */
