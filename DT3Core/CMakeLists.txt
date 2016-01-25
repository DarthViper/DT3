cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)


#==============================================================================
#
#	File: CMakeLists.txt	(for Android)
#
#	Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
#
#	This file is subject to the terms and conditions defined in
#	file 'LICENSE.txt', which is part of this source code package.
#
#==============================================================================

#cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER_INIT g++)
enable_language(ASM)

#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic -nostartfiles -fno-short-enums -fno-strict-aliasing -Wall  -std=c++11 " )
#set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   -fpic -pthread  -Wall " )
#set( CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" )

set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_C_FLAGS}" )
set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_C_FLAGS}" )
set( CMAKE_MODULE_LINKER_FLAGS "${CMAKE_C_FLAGS}" )

set (ENGINE_ROOT "${PROJECT_SOURCE_DIR}/DT3Core")

#External Variable for
if(EXISTS "${DT3_CORE_OUTPUT_PATH}")
    SET(LIBRARY_OUTPUT_PATH ${THIRD_PARTY_OUTPUT_LIBRARY_PATH})
else()
    SET(LIBRARY_OUTPUT_PATH "${ENGINE_ROOT}/bin/unix")
endif(EXISTS "${DT3_CORE_OUTPUT_PATH}")

#
# Useful variables and macros
#

MACRO(HEADER_DIRECTORIES new_list return_list)
    SET(dir_list "")

    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})

#
# build dependencies
#



# DT3Core/3rdParty
set (PROJECT_SUBDIR "${ENGINE_ROOT}/3rdParty")
add_subdirectory("${ENGINE_ROOT}/3rdParty/" )
set (PROJECT_SOURCE ${PROJECT_SUBDIR} ${PROJECT_SOURCE})


#
# Build DT3Linux
#

include_directories("${ENGINE_ROOT}/../")

set (PROJECT_MODULE "${ENGINE_ROOT}/../DT3Linux/")
if (EXISTS "${PROJECT_MODULE}")

    # Compile files
    file(GLOB_RECURSE PROJECT_SRCS
            "${ENGINE_ROOT}/../DT3Linux/HAL.hpp"
            "${ENGINE_ROOT}/../DT3Linux/HAL.cpp"
    )
    SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})

    # Build include directories
    HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
    include_directories(${HEADER_INCLUDES})

else (EXISTS "${PROJECT_MODULE}")
        MESSAGE(FATAL_ERROR "DT3Android is required for building")
endif (EXISTS "${PROJECT_MODULE}")

#
# Build DT3Core
#
set (PROJECT_MODULE "${ENGINE_ROOT}/")
if (EXISTS "${PROJECT_MODULE}")
        #Add libraries
        set(MODULE_LIBS ${MODULE_LIBS} "freetype" "zlib" "lpng" "jenkins" "libjpeg.a" )
        #set(MODULE_LIBS_DIRS ${MODULE_LIBS_DIRS} "${ENGINE_ROOT}/3rdParty/libjpeg-turbo-1.3.0/libjpeg-turbo-android/lib/${ANDROID_NDK_ABI_NAME}" )

        # Library includes
        include_directories("${ENGINE_ROOT}/3rdParty/zlib-1.2.5")
        include_directories("${ENGINE_ROOT}/3rdParty/")
        include_directories("${ENGINE_ROOT}/3rdParty/freetype-2.4.7/include")
        include_directories("${ENGINE_ROOT}/3rdParty/lpng151")
        #include_directories("${ENGINE_ROOT}/3rdParty/md5-cc")
        #include_directories("${ENGINE_ROOT}/3rdParty/libjpeg-turbo-1.3.0/libjpeg-turbo-android/include")

        # Compile files
        file(GLOB_RECURSE PROJECT_SRCS
                "${ENGINE_ROOT}/Components/*"
                "${ENGINE_ROOT}/Devices/*"
                "${ENGINE_ROOT}/Entry/*"
                "${ENGINE_ROOT}/Objects/*"
                "${ENGINE_ROOT}/Resources/*"
                "${ENGINE_ROOT}/Scripting/*"
                "${ENGINE_ROOT}/System/*"
                "${ENGINE_ROOT}/Tools/*"
                "${ENGINE_ROOT}/Transitions/*"
                "${ENGINE_ROOT}/Types/*.hpp"
                "${ENGINE_ROOT}/Types/*.cpp"
                "${ENGINE_ROOT}/Types/Utility/ContextSwitcher_asm.S"
                "${ENGINE_ROOT}/World/*"
        )
        SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})

        # Build include directories
        include_directories("${ENGINE_ROOT}")

else (EXISTS "${PROJECT_MODULE}")
        MESSAGE(FATAL_ERROR "DT3Core is required for building")
endif (EXISTS "${PROJECT_MODULE}")



#### SDL2 Optionals
if(USE_SDL2)
    message(DEBUG "USE SDLDT3CORE")
    set(MODULE_LIBS  ${MODULE_LIBS}  "SDL2" )
    add_definitions( "-lSDL2" )
    include_directories("${ENGINE_ROOT}/3rdParty/SDL2/include")
##needs tweaking, cause not all platform code belongs to SDL2....
    file(GLOB_RECURSE PROJECT_SRCS
                "${ENGINE_ROOT}/Platform/*.cpp"
                "${ENGINE_ROOT}/Platform/*.h"
          )
        SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})
endif(USE_SDL2)



#
# Build DTPortalSDK
#
#set (PROJECT_MODULE "${ENGINE_ROOT}/../DTPortalSDK/")
if (EXISTS "${PROJECT_MODULE_PORTAL}")

        # DTPortalSDK/DTPortalLib/3rdParty
        set (PROJECT_SUBDIR "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/3rdParty")
        add_subdirectory(${PROJECT_SUBDIR} "${CMAKE_CURRENT_BINARY_DIR}/DTPortalSDK/DTPortalLib/3rdParty")
        set (PROJECT_SOURCE ${PROJECT_SUBDIR} ${PROJECT_SOURCE})

        #Add libraries
        set(MODULE_LIBS ${MODULE_LIBS} "jansson" "libtomcrypt")

        # Library includes
        include_directories("${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/3rdParty/jansson-2.5/src")
        include_directories("${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/3rdParty/libtomcrypt-1.17/src/headers")

        # Compile files
        file(GLOB_RECURSE PROJECT_SRCS
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalAnalytics.cpp"
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalAppStoreValidator.cpp"
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalCommon.cpp"
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalHighScores.cpp"
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalNetwork.cpp"
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalSDK.cpp"
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalStrings.cpp"
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalTasks.cpp"
                "${ENGINE_ROOT}/../DTPortalSDK/DTPortalLib/DTPortalTextBlob.cpp"
        )
        SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})

        # Build include directories
        HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
        include_directories(${HEADER_INCLUDES})

endif (EXISTS "${PROJECT_MODULE_PORTAL}")

#
# Build Game specific files
#

#set (PROJECT_MODULE "${ENGINE_ROOT}/src_game/")
if (EXISTS "${PROJECT_MODULE_GAME}")

        # Compile files
        file(GLOB_RECURSE PROJECT_SRCS
                "${ENGINE_ROOT}/src_game/AppConfig.cpp"
                "${ENGINE_ROOT}/src_game/Kaiser/*.cpp"
        )
        SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})

        # Build include directories
        HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
        include_directories(${HEADER_INCLUDES})

else (EXISTS "${PROJECT_MODULE_GAME}")
        #MESSAGE(FATAL_ERROR "Game Files are required for building")

endif (EXISTS "${PROJECT_MODULE_GAME}")

#
# Build DT3OpenAL
#

#set (PROJECT_MODULE "${ENGINE_ROOT}/../DT3OpenAL/")
if (EXISTS "${PROJECT_MODULE_AL}")

        # DT3OpenAL/3rdParty
        set (PROJECT_SUBDIR "${ENGINE_ROOT}/../DT3OpenAL/3rdParty")
        add_subdirectory(${PROJECT_SUBDIR} "${CMAKE_CURRENT_BINARY_DIR}/DT3OpenAL/3rdParty")
        set (PROJECT_SOURCE ${PROJECT_SUBDIR} ${PROJECT_SOURCE})

        #Add libraries
        set(MODULE_LIBS ${MODULE_LIBS} "openal" )

        #Library includes
        include_directories("${ENGINE_ROOT}/../DT3OpenAL/3rdParty/openal-soft-android/include")

        # Compile files
        file(GLOB_RECURSE PROJECT_SRCS
                "${ENGINE_ROOT}/../DT3OpenAL/DeviceAudioOpenAL.hpp"
                "${ENGINE_ROOT}/../DT3OpenAL/DeviceAudioOpenAL.cpp"
        )
        SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})

        # Build include directories
        HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
        include_directories(${HEADER_INCLUDES})

endif (EXISTS "${PROJECT_MODULE_AL}")

#
# Build DT3HWVideoPlayer
#

#set (PROJECT_MODULE "${ENGINE_ROOT}/src/DT3HWVideoPlayer/")
#if (EXISTS "${PROJECT_MODULE}")
#
#	#Add libraries
#	set(MODULE_LIBS ${MODULE_LIBS} "libswscale.a" "libavformat.a" "libavcodec.a" "libavfilter.a" "libavutil.a" "libswresample.a"  )
#	set(MODULE_LIBS_DIRS ${MODULE_LIBS_DIRS} "${ENGINE_ROOT}/src/DT3HWVideoPlayer/3rdParty/ffmpeg-2.0.2/ffmpeg-android/lib/${ANDROID_NDK_ABI_NAME}" )
#
#	#Library includes
#	include_directories("${ENGINE_ROOT}/src/DT3HWVideoPlayer/3rdParty/ffmpeg-2.0.2/ffmpeg-android/include")
#
#	# Compile files
#	file(GLOB_RECURSE PROJECT_SRCS
#		"${ENGINE_ROOT}/src/DT3HWVideoPlayer/FFmpeg/*.cpp"
#		"${ENGINE_ROOT}/src/DT3HWVideoPlayer/ScriptingVideoTexture.cpp"
#		"${ENGINE_ROOT}/src/DT3HWVideoPlayer/ComponentGUIVideoPlayer.cpp"
#	)
#	SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})
#
#	# Build include directories
#	HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
#	include_directories(${HEADER_INCLUDES})
#
#endif (EXISTS "${PROJECT_MODULE}")


#
# Build DT3OpenGL
#

set (PROJECT_MODULE_OPENGL "${ENGINE_ROOT}/../DT3OpenGL/")
if (EXISTS "${PROJECT_MODULE_OPENGL}")

        file(GLOB_RECURSE PROJECT_SRCS
                "${ENGINE_ROOT}/../DT3OpenGL/*.hpp"
                "${ENGINE_ROOT}/../DT3OpenGL/*.cpp"
        )
        SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})

        # Build include directories
        HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
        include_directories(${HEADER_INCLUDES})

endif (EXISTS "${PROJECT_MODULE_OPENGL}")


#
# Build DT3Sockets
#

#set (PROJECT_MODULE "${ENGINE_ROOT}/../DT3Sockets/")
if (EXISTS "${PROJECT_MODULE_SOCKETS}")

        file(GLOB_RECURSE PROJECT_SRCS
                "${ENGINE_ROOT}/../DT3Sockets/*.hpp"
                "${ENGINE_ROOT}/../DT3Sockets/*.cpp"
        )
        SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})

        # Build include directories
        HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
        include_directories(${HEADER_INCLUDES})

endif (EXISTS "${PROJECT_MODULE_SOCKETS}")

#
# Build DT3Sprites
#

#set (PROJECT_MODULE "${ENGINE_ROOT}/src/DT3Sprites/")
#if (EXISTS "${PROJECT_MODULE}")
#
#	file(GLOB_RECURSE PROJECT_SRCS
#		"${ENGINE_ROOT}/src/DT3Sprites/*.hpp"
#		"${ENGINE_ROOT}/src/DT3Sprites/*.cpp"
#	)
#	SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})
#
#	# Build include directories
#	HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
#	include_directories(${HEADER_INCLUDES})
#
#endif (EXISTS "${PROJECT_MODULE}")

#
# Build DT3InAppPurchases
#

#set (PROJECT_MODULE "${ENGINE_ROOT}/../DT3InAppPurchases/")
if (EXISTS "${PROJECT_MODULE_IN_APP_PURCHASES}")

        file(GLOB_RECURSE PROJECT_SRCS
                "${ENGINE_ROOT}/../DT3InAppPurchases/InAppPurchases.cpp"
                "${ENGINE_ROOT}/../DT3InAppPurchases/InAppPurchasesProduct.cpp"
                "${ENGINE_ROOT}/../DT3InAppPurchases/Android/InAppPurchasesAndroid.cpp"
        )
        SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})

        # Build include directories
        HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
        include_directories(${HEADER_INCLUDES})

endif (EXISTS "${PROJECT_MODULE_IN_APP_PURCHASES}")

#
# Native Activity
#

#file(GLOB_RECURSE PROJECT_SRCS
#        "${NDK_APP_GLUE}/android_native_app_glue.h"
#        "${NDK_APP_GLUE}/android_native_app_glue.c"
#        "${PROJECT_SOURCE_DIR}/AppNative.hpp"
#        "${PROJECT_SOURCE_DIR}/AppNative.cpp"
#)
SET(PROJECT_SOURCE ${PROJECT_SOURCE} ${PROJECT_SRCS})
SET(LIBRARY_OUTPUT_PATH "${ENGINE_ROOT}/bin/unix/")
# Build include directories
HEADER_DIRECTORIES("${PROJECT_SRCS}" HEADER_INCLUDES)
include_directories(${HEADER_INCLUDES})

#
# Build!
#

link_directories(${NDK_PLATFORM_LIBS} ${MODULE_LIBS_DIRS})

add_library(DT3Core SHARED ${PROJECT_SOURCE})

##
#set_target_properties(DT3Core PROPERTIES
#  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/project/libs/${ANDROID_ABI}"
#)

#target_link_libraries (DT3Core
#        ${NDK_PLATFORM_LIBS}/libm.so
#        ${NDK_PLATFORM_LIBS}/libdl.so
#        ${NDK_PLATFORM_LIBS}/libc.so
#        ${NDK_PLATFORM_LIBS}/liblog.so
#        ${NDK_PLATFORM_LIBS}/libGLESv2.so
#        ${NDK_PLATFORM_LIBS}/libEGL.so
#        ${NDK_PLATFORM_LIBS}/libandroid.so
#        ${NDK_PLATFORM_LIBS}/libstdc++.a
#        ${NDK_PLATFORM_LIBS}/libOpenSLES.so
#        ${MODULE_LIBS}
#)


qt5_use_modules(DT3Core Core Gui)





