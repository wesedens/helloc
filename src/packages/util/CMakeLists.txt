cmake_minimum_required (VERSION 2.6)
project(util)

###################
# ADD DEFINITIONS #
###################

#add_definitions( -DDEBUG=1 )

################
# DEPENDENCIES #
################

####################
# Component Source #
####################

include_directories ( include )

set (util-sources  src/version.c )

add_library      ( util-shared SHARED ${util-sources} )
set_target_properties (util-shared PROPERTIES OUTPUT_NAME "util")
install (TARGETS util-shared RUNTIME DESTINATION lib/shared LIBRARY DESTINATION lib/shared ARCHIVE DESTINATION lib/shared)

add_library      ( util-static STATIC ${util-sources} )
set_target_properties (util-static PROPERTIES OUTPUT_NAME "util")
set_target_properties (util-static PROPERTIES PREFIX "lib")
install (TARGETS util-static DESTINATION lib/static )


##############
# UNIT Tests #
##############



