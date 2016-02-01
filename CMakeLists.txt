project(DT3)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_scripts")

IF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D__UNIX__ -D_CRT_NONSTDC_NO_DEPRECATE)
    ADD_DEFINITIONS(/W4)
ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wno-unused-parameter -Wno-unknown-pragmas -Wno-comment -Wno-reorder -Wall -std=c++14") #-pedantic -Wextra
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c99")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} "  ) #--coverage
ENDIF()

find_package(Qt5Core 5.4.0)
find_package(Qt5Xml 5.4.0)
find_package(Qt5Gui 5.4.0)
find_package(Qt5Widgets 5.4.0)
find_package(Qt5Multimedia 5.4.0)
find_package(Threads REQUIRED)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(Freetype REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${PNG_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
option(USE_SDL2 "Use SDL2 library" OFF)
if(USE_SDL2)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
endif()
set (ENGINE_ROOT "${PROJECT_SOURCE_DIR}/DT3Core")
INCLUDE_DIRECTORIES(.)
add_subdirectory(DT3Core)
#add_subdirectory(DT3Sprites)
#add_subdirectory(DT3SpriteEditor)

add_subdirectory(DT3LevelEditor)

