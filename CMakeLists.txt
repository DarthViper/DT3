project(DT3)
cmake_minimum_required(VERSION 2.8)

IF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D__UNIX__ -D_CRT_NONSTDC_NO_DEPRECATE)
    ADD_DEFINITIONS(/W4)
ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wno-unused-parameter -Wno-unknown-pragmas -Wno-comment -Wno-reorder -Wall -std=c++11") #-pedantic -Wextra
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c99")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} "  ) #--coverage
ENDIF()

find_package(Qt5Core)
find_package(Qt5Xml)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Multimedia)
find_package(Threads REQUIRED)

set (ENGINE_ROOT "${PROJECT_SOURCE_DIR}/DT3Core")
INCLUDE_DIRECTORIES(.)
add_subdirectory(DT3Core)
add_subdirectory(DT3LevelEditor)
