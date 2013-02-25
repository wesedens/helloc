/**
 *  @file
 *  @author Wes Edens
 *  @date 10/05/2011
 *
 *  @brief defines all the macros for byte swapping for endianness
 *
 *  We assume that we are on a big endian machine since it will be eventually be
 *  run on a PPC. So if we are compiling on a LE machine we need to swap every
 *  read because the data structures are defined absolutely and need to be in
 *  big endian.
 *
 *  casts are necessary for constants, because we never know how for sure
 *  how U/UL/ULL map to __u16, __u32, __u64. At least not in a portable way.
 */

#ifndef swab_H_
#define swab_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "byteorder.h"

#define ___constant_swab16(x) ((uint16_t)(                     \
       (((uint16_t)(x) & (uint16_t)0x00ffU) << 8) |         \
       (((uint16_t)(x) & (uint16_t)0xff00U) >> 8)))

#define ___constant_swab32(x) ((uint32_t)(                     \
       (((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) |   \
       (((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) |   \
       (((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) |   \
       (((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24)))

#define ___constant_swahw32(x) ((uint32_t)(                    \
       (((uint32_t)(x) & (uint32_t)0x0000ffffUL) << 16) |   \
       (((uint32_t)(x) & (uint32_t)0xffff0000UL) >> 16)))

#define ___constant_swahb32(x) ((uint32_t)(                    \
       (((uint32_t)(x) & (uint32_t)0x00ff00ffUL) << 8) |    \
       (((uint32_t)(x) & (uint32_t)0xff00ff00UL) >> 8)))

#if _LITTLE_ENDIAN_ == 1
#  define correct_swab16  ___constant_swab16
#  define correct_swab32  ___constant_swab32
#elif _BIG_ENDIAN_ == 1
#  define correct_swab16
#  define correct_swab32
#else
#  error No endianness found!
#endif

#ifdef __cplusplus
}
#endif

#endif /* swab_H_ */
