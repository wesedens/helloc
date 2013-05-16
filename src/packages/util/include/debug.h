/**
 *  @file
 *  @author Wes Edens
 *  @date 05/16/2012
 *
 *  @brief this file declares macros for use in debugging
 */

#ifndef debug_H_
#define debug_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#ifdef DEBUG
#   define DEBUGP  1
#else
#   define DEBUGP  0
#endif

#ifdef _WIN32
#   define __func__ 0
#endif

#ifdef MATLAB_MEX_FILE
/**
 * prints out a message to matlab terminal with __FILE__, __LINE__, and
 * __func__
 * @param[in]  fmt character array (same as printf)
 * @param[in]  ... var args for format replacement
 */
#define dbg_printf(fmt, ...)                                                 \
                      do { if (DEBUGP) mexPrintf("%s:%d:%s(): " fmt,   \
						    __FILE__, __LINE__, __func__, __VA_ARGS__); } while(0)

#else

/**
 * prints out a message to stderr with __FILE__, __LINE__, and __func__
 * @param[in]  fmt character array (same as printf)
 * @param[in]  ... var args for format replacement
 */
#define dbg_printf(fmt, ...)                                                 \
                      do { if (DEBUGP) fprintf(stderr, "%s:%d:%s(): " fmt,   \
						    __FILE__, __LINE__, __func__, __VA_ARGS__); } while(0)

#endif

#ifdef __cplusplus
}
#endif

#endif /* debug_H_ */

