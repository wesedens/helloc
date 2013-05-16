cmake_minimum_required (VERSION 2.6)
project(libconfig-test-main)

###################
# ADD DEFINITIONS #
###################

#add_definitions( -DDEBUG=1 )

################
# DEPENDENCIES #
################

include_directories ( ${util_SOURCE_DIR}/include )

####################
# Component Source #
####################

include_directories ( include )

set (libconfig-test-main-sources  src/hello-main.c)

add_executable ( libconfig-test ${libconfig-test-main-sources} )

target_link_libraries ( libconfig-test util-static )

install (TARGETS libconfig-test DESTINATION bin/ )
