#!/bin/bash

PROJECT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"/../..

source ${PROJECT_ROOT}/build/unix/setenv_Defaults.sh

CMAKE_GENERATOR="Eclipse CDT4 - Unix Makefiles"

source ${PROJECT_ROOT}/build/unix/setenv_Debug.sh
source ${PROJECT_ROOT}/build/unix/setenv_Release.sh
source ${PROJECT_ROOT}/build/unix/setenv_RelWithBInfo.sh

