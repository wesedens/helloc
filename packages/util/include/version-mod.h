/**
 *  @file
 *  @author Wes Edens
 *  @date 01/17/2013
 *
 *  @brief this file declares macros for module versioning
 */

#ifndef version_H_
#define version_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ___module_cat(a,b) __mod_ ## a ## b
#define __module_cat(a,b) ___module_cat(a,b)

#define __stringify_1(x...)     #x
#define __stringify(x...)       __stringify_1(x)

#define __used                 __attribute__((__used__))

#if !defined(BUILD_MODNAME)
#define BUILD_MODNAME "default module"
#endif

#define __MODULE_INFO(tag, name, info)                                    \
static const char __module_cat(name,__LINE__)[]                           \
  __used __attribute__((section(".modinfo"), unused, aligned(1)))         \
  = __stringify(tag) "=" info

#define MODULE_INFO(tag, info) __MODULE_INFO(tag, tag, info)

#define MODULE_VERSION(_version) MODULE_INFO(version, _version)
#define MODULE_AUTHOR(_author) MODULE_INFO(author, _author)

struct module_version_attribute {
        const char *module_name;
        const char *version;
} __attribute__ ((__aligned__(sizeof(void *))));

#ifdef __cplusplus
}
#endif

#endif /* debug_H_ */

