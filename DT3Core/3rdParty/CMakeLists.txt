cmake_minimum_required(VERSION 2.8)
#==============================================================================
#
#	File: CMakeLists.txt	(for 3rdParty)
#
#	Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
#
#	This file is subject to the terms and conditions defined in
#	file 'LICENSE.txt', which is part of this source code package.
#
#==============================================================================

#
#	With the asumption that this is called from the DT3Core/CMakeLists.txt

#### Specified if the libs are going to be in DT3Core/bin/unix
#set(CORE_LIBS 1)

if(EXISTS ${THIRD_PARTY_OUTPUT_LIBRARY_PATH})
    SET(LIBRARY_OUTPUT_PATH "${THIRD_PARTY_OUTPUT_LIBRARY_PATH}")
elseif(EXISTS ${CORE_LIBS})
    SET(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../bin/unix/")
else()
    SET(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/unix/")
endif(EXISTS ${THIRD_PARTY_OUTPUT_LIBRARY_PATH})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIBRARY_OUTPUT_PATH}")


#
# jenkins
#

set(PROJECT_SRCS
    JenkinsHash/lookup3.c
)

set(PROJECT_INCLUDES
    JenkinsHash
)

include_directories("${PROJECT_INCLUDES}")
add_library(jenkins STATIC ${PROJECT_SRCS})







