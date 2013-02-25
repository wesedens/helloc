cmake_minimum_required (VERSION 2.6)
project(hello C)

##########################
# ADD GLOBAL DEFINITIONS #
##########################

#add_definitions( -DDEBUG=1 )

##################
# Compiler Flags #
##################

message ("Compile Flags Before Customization (Defaults)")
message ("CMAKE_C_FLAGS=${CMAKE_C_FLAGS}")
message ("CMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}")
message ("CMAKE_C_FLAGS_RELWITHDEBINFO=${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message ("CMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}")

if (UNIX)
	# -Wno-long-long needed for Eigen
	# -Wno-unused-parameter since we are using abstractions where all parameters
	# might not always be used in implementations
	# don't want -ansi
	set (COMMON_C_FLAGS_UNIX "-Wall -Wextra -Wno-unused-parameter -Wno-missing-braces -Wno-sign-compare -Wno-missing-field-initializers -fPIC -Wno-long-long -pthread")
	set(CMAKE_C_FLAGS ${COMMON_C_FLAGS_UNIX})
endif (UNIX)

message ("Compile Flags After Customization")
message ("CMAKE_C_FLAGS=${COMMON_C_FLAGS_UNIX}")
message ("CMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}")
message ("CMAKE_C_FLAGS_RELWITHDEBINFO=${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message ("CMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}")

######################
# External Libraries #
######################

enable_testing()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../build/unix/CMakeModules/")
find_package(Check REQUIRED)

####################
# Version creation #
####################

file(WRITE ${CMAKE_BINARY_DIR}/version.cmake
"
set ( MAJOR 1 )
set ( MINOR 0 )
set ( BUILD 0 )
set ( PATCH 0 )

set ( PACKAGE            "hello" )
set ( PACKAGE_NAME       "hello-wedens" )
set ( PACKAGE_URL        "wes.k.edens@gmail.com" )
set ( PACKAGE_BUGREPORT  "wes.k.edens@gmail.com" )

# Branding Information

set ( COMPANY_FULLNAME  "Johns Hopkins University Applied Physics Lab" )
set ( COMPANY_SHORTNAME "JHUAPL" )
set ( PRODUCT_FULLNAME  "hello-wedens")
set ( PRODUCT_SHORTNAME "hw")
set ( COPYRIGHT         "bob lob law")
set ( OFFICIAL_BUILD    "build")

configure_file( \${SRC} \${DST} @ONLY )
")

file(WRITE ${PROJECT_ROOT}/packages/util/src/version.c
"#include \"version.h\"
char const *Version = VERSION;
")

###################
# ADD SUBPROJECTS #
###################

add_subdirectory (util)
add_subdirectory (hello-main)


## Debug see all cmake variables
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
