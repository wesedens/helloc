cmake_minimum_required (VERSION 2.6)
project(util)

###################
# ADD DEFINITIONS #
###################

#add_definitions( -DDEBUG=1 )

################
# DEPENDENCIES #
################

add_custom_target(
    version
    ${CMAKE_COMMAND} -D SRC=${PROJECT_ROOT}/packages/util/include/version.h.in
                     -D DST=${PROJECT_ROOT}/packages/util/include/version.h
                     -P ${CMAKE_BINARY_DIR}/version.cmake
)

add_custom_target(
    config
    ${CMAKE_COMMAND} -D SRC=${PROJECT_ROOT}/packages/util/include/config.h.in
                     -D DST=${PROJECT_ROOT}/packages/util/include/config.h
                     -P ${CMAKE_BINARY_DIR}/version.cmake
)

####################
# Component Source #
####################

include_directories ( include )

set (util-sources  src/c-ctype.c
                   src/closein.c
                   src/closeout.c
                   src/close-stream.c
                   src/c-strcasecmp.c
                   src/c-strncasecmp.c
                   src/error.c
                   src/exitfail.c
                   src/fpending.c
                   src/freadahead.c
                   src/inttostr.c
                   src/localcharset.c
                   src/progname.c
                   src/quotearg.c
                   src/version.c
                   src/version-etc.c
                   src/xalloc-die.c
                   src/xmalloc.c )

add_library      ( util-shared SHARED ${util-sources} )
add_dependencies ( util-shared version)
add_dependencies ( util-shared config)
set_target_properties (util-shared PROPERTIES OUTPUT_NAME "util")
install (TARGETS util-shared RUNTIME DESTINATION lib/shared LIBRARY DESTINATION lib/shared ARCHIVE DESTINATION lib/shared)

add_library      ( util-static STATIC ${util-sources} )
add_dependencies ( util-static version)
add_dependencies ( util-static config)
set_target_properties (util-static PROPERTIES OUTPUT_NAME "util")
set_target_properties (util-static PROPERTIES PREFIX "lib")
install (TARGETS util-static DESTINATION lib/static )


##############
# UNIT Tests #
##############

include_directories ( include )
include_directories (${CHECK_INCLUDE_DIRS})

add_executable        ( util-test test/util-test.c )
target_link_libraries ( util-test util-static )
target_link_libraries ( util-test ${CHECK_LIBRARIES})
add_test              ( util-tests util-test)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS util-test)

