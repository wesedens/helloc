cmake_minimum_required (VERSION 2.6)
project(hello-main)

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

set (hello-main-sources  src/hello-main.c)

add_executable ( helloc ${hello-main-sources} )

target_link_libraries ( helloc util-static )

install (TARGETS helloc DESTINATION bin/ )
