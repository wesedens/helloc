cmake_minimum_required (VERSION 2.6)
project(libconfig-test C)

##########################
# ADD GLOBAL DEFINITIONS #
##########################

#add_definitions( -DDEBUG=1 )

###################
# ADD SUBPROJECTS #
###################

add_subdirectory (util)
add_subdirectory (hello-main)
