######################################################################
# QT Project file
######################################################################

## LIBRARIES STUFF
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/../DT3Core/3rdParty/zlib-1.2.5
               ${CMAKE_CURRENT_SOURCE_DIR}/../DT3Core/3rdParty/lpng151
               ${CMAKE_CURRENT_SOURCE_DIR}/../DT3Core/3rdParty/md5-cc
               ${CMAKE_CURRENT_SOURCE_DIR}/../DT3Core/3rdParty/freetype-2.4.7/include
               ${CMAKE_CURRENT_SOURCE_DIR}/../DT3Core/3rdParty/libjpeg-turbo-1.3.0/libjpeg-turbo-android/include
)
include_directories(
                  .
                  ../../DT3
                  ../DT3Core/Resources/ResourceTypes
                  ./Animation
                  ./Console
                  ./Hierarchy
                  ./Library
                  ./MeshBuilder
                  ./Performance
                  ./Properties
                  ./Resources
                  ./Scripting
                  ./Sound
                  ./Tools
                  ./World
                  )

LINK_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/../DT3Core/3rdParty/bin/unix )

set(HEADERS
     ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelAppMain.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelMainWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertiesWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyBase.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyDefaultField.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyVector2Field.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyVector3Field.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyMatrix3Field.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyColorField.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyTitleField.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyBoolField.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyEventField.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyEnumField.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyRangeField.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelColorSwatch.hpp
     #${CMAKE_CURRENT_SOURCE_DIR}/Game/EdLevelGame.hpp
     #${CMAKE_CURRENT_SOURCE_DIR}/Game/EdLevelGameGL.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Hierarchy/EdLevelHierarchyWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Hierarchy/EdLevelHierarchyWindowMIME.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptConnectionRubberBand.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptEventConnection.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptNodeStandard.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptPlugConnection.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptSelectionRubberBand.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Console/EdLevelConsoleWindow.hpp
     ##${CMAKE_CURRENT_SOURCE_DIR}/Console/ConsoleStream.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Performance/EdLevelPerformanceWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelResourcesWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Library/EdLevelLibraryWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Library/EdLevelLibraryDialog.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/World/EdLevelWorldWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Animation/EdLevelAnimationWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Sound/EdLevelSoundWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Sound/EdLevelSoundBus.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Sound/EdLevelSoundVUMeter.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelToolWindow.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelImageThumbnail.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelSoundThumbnail.hpp
     #${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelMaterialThumbnail.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelResourceImage.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelResourceSound.hpp
     #${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelResourceMaterial.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelLineEdit.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelLaunchDialog.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/MeshBuilder/EdLevelMeshBuilder.hpp
    EdLevelDocument.hpp
    EdLevelToolEvent.hpp
    EdLevelManipPan.hpp
    EdLevelManipRotate.hpp
    EdLevelManipScale.hpp
    EdLevelTool.hpp
    Scripting/EdLevelGroup.hpp
    Scripting/EdLevelScriptConnection.hpp
    World/EdLevelWorldLayout.hpp
)
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelAppMain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelMainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertiesWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyDefaultField.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyVector2Field.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyVector3Field.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyMatrix3Field.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyColorField.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyTitleField.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyBoolField.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyEventField.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyEnumField.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelPropertyRangeField.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Properties/EdLevelColorSwatch.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/Game/EdLevelGame.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Game/EdLevelGameGL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hierarchy/EdLevelHierarchyWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Hierarchy/EdLevelHierarchyWindowMIME.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptConnectionRubberBand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptEventConnection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptNodeStandard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptPlugConnection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptSelectionRubberBand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Console/EdLevelConsoleWindow.cpp
    ##${CMAKE_CURRENT_SOURCE_DIR}/Console/ConsoleStream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Performance/EdLevelPerformanceWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelResourcesWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/EdLevelLibraryWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/EdLevelLibraryDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/World/EdLevelWorldWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Animation/EdLevelAnimationWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sound/EdLevelSoundWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sound/EdLevelSoundBus.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sound/EdLevelSoundVUMeter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelToolWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelImageThumbnail.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelSoundThumbnail.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelMaterialThumbnail.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelResourceImage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelResourceSound.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Resources/EdLevelResourceMaterial.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelLineEdit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelLaunchDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MeshBuilder/EdLevelMeshBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelGroup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting/EdLevelScriptConnection.cpp
    EdLevelDocument.cpp
    EdLevelToolEvent.cpp
    EdLevelMainWindow_cmd.cpp
    EdLevelManipPan.cpp
    EdLevelManipRotate.cpp
    EdLevelManipScale.cpp
    EdLevelTool.cpp
    World/EdLevelWorldLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LevelEditor.qrc
)
add_executable(LevelEditor ${SOURCES} ${HEADERS})
target_link_libraries(LevelEditor DT3Core freetype png jpeg zlib jenkins md5 GLEW GL pthread dl)

qt5_use_modules(LevelEditor Core Gui Widgets OpenGL Multimedia)


#QMAKE_CXXFLAGS+= -std=c++11 -fpic -fno-short-enums -fno-strict-aliasing

#QMAKE_LFLAGS +=  -std=c++11
#    QMAKE_CXXFLAGS+= -finline-limit=64



