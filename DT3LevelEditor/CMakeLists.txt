######################################################################
# QT Project file
######################################################################

## LIBRARIES STUFF
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include_directories(
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
     World/WorldWindow.h
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
    EditorObjectFactory.h
    EngineObjectTools.h
)
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/EdLevelAppMain.cpp
    EdLevelMainWindow.cpp
    EdLevelMainWindow.ui
    Properties/EdLevelPropertiesWindow.cpp
    Properties/EdLevelPropertyBase.cpp
    Properties/EdLevelPropertyDefaultField.cpp
    Properties/EdLevelPropertyVector2Field.cpp
    Properties/EdLevelPropertyVector3Field.cpp
    Properties/EdLevelPropertyMatrix3Field.cpp
    Properties/EdLevelPropertyColorField.cpp
    Properties/EdLevelPropertyTitleField.cpp
    Properties/EdLevelPropertyBoolField.cpp
    Properties/EdLevelPropertyEventField.cpp
    Properties/EdLevelPropertyEnumField.cpp
    Properties/EdLevelPropertyRangeField.cpp
    Properties/EdLevelColorSwatch.cpp
    # Game/EdLevelGame.cpp
    #Game/EdLevelGameGL.cpp
    Hierarchy/EdLevelHierarchyWindow.cpp
    Hierarchy/EdLevelHierarchyWindowMIME.cpp
    Scripting/EdLevelScriptConnectionRubberBand.cpp
    Scripting/EdLevelScriptEventConnection.cpp
    Scripting/EdLevelScriptNodeStandard.cpp
    Scripting/EdLevelScriptPlugConnection.cpp
    Scripting/EdLevelScriptSelectionRubberBand.cpp
    Scripting/EdLevelScriptWindow.cpp
    Console/EdLevelConsoleWindow.cpp
    Console/EdLevelConsoleWindow.ui
    Performance/EdLevelPerformanceWindow.cpp
    Resources/EdLevelResourcesWindow.cpp
    Library/EdLevelLibraryWindow.cpp
    Library/EdLevelLibraryDialog.cpp
    World/WorldWindow.cpp
    World/WorldWindow.ui
    Animation/EdLevelAnimationWindow.cpp
    Sound/EdLevelSoundWindow.cpp
    Sound/EdLevelSoundBus.cpp
    Sound/EdLevelSoundVUMeter.cpp
    EdLevelToolWindow.cpp
    Resources/EdLevelImageThumbnail.cpp
    Resources/EdLevelSoundThumbnail.cpp
    #Resources/EdLevelMaterialThumbnail.cpp
    Resources/EdLevelResourceImage.cpp
    Resources/EdLevelResourceSound.cpp
    #Resources/EdLevelResourceMaterial.cpp
    EdLevelLineEdit.cpp
    EdLevelLaunchDialog.cpp
    MeshBuilder/EdLevelMeshBuilder.cpp
    Scripting/EdLevelGroup.cpp
    Scripting/EdLevelScriptConnection.cpp
    EdLevelDocument.cpp
    EdLevelToolEvent.cpp
    EdLevelMainWindow_cmd.cpp
    EdLevelManipPan.cpp
    EdLevelManipRotate.cpp
    EdLevelManipScale.cpp
    EdLevelTool.cpp
    World/EdLevelWorldLayout.cpp
    LevelEditor.qrc

    EditorObjectFactory.cpp
    EngineObjectTools.cpp
)
add_executable(LevelEditor ${SOURCES} ${HEADERS})
target_link_libraries(LevelEditor DT3Core freetype jpeg jenkins GLEW GL pthread dl)
target_link_libraries(LevelEditor ${PNG_LIBRARIES} ${ZLIB_LIBRARIES} ${FREETYPE_LIBRARIES})
qt5_use_modules(LevelEditor Core Gui Widgets OpenGL Multimedia)


#QMAKE_CXXFLAGS+= -std=c++11 -fpic -fno-short-enums -fno-strict-aliasing

#QMAKE_LFLAGS +=  -std=c++11
#    QMAKE_CXXFLAGS+= -finline-limit=64



