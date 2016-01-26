INCLUDE_DIRECTORIES(
    ../DT3Sprites/Types
    ../DT3Sprites/Resources
    ../DT3Sprites/Resources/Importers
    ../DT3Sprites/Resources/ResourcesTypes
)



# Input
set(HEADERS
        EdSpriteAppMain.hpp
        EdSpriteBitfield.hpp
        EdSpriteMainWindow.hpp
        EdSpriteEditor.hpp
        EdSpriteUVEditor.hpp
        EdSpriteTimeline.hpp
        EdSpriteProperties.hpp
        EdSpriteAnimationProperties.hpp
        EdSpriteJointProperties.hpp
        EdSpriteJointList.hpp
        EdSpriteLineEdit.hpp
        EdSpritePropertyBase.hpp
        EdSpriteAnimations.hpp
        EdSpritePropertyBoolField.hpp
        EdSpritePropertyDefaultField.hpp
        EdSpritePropertyBitfieldField.hpp
        EdSpriteAnimationTransferDialog.hpp
        EdSpriteNewEventDialog.hpp
)
set(CPP_SOURCES
        EdSpriteAppMain.cpp
        EdSpriteBitfield.cpp
        EdSpriteMainWindow.cpp
        EdSpriteEditor.cpp
        EdSpriteUVEditor.cpp
        EdSpriteTimeline.cpp
        EdSpriteProperties.cpp
        EdSpriteAnimationProperties.cpp
        EdSpriteJointProperties.cpp
        EdSpriteJointList.cpp
        EdSpriteLineEdit.cpp
        EdSpritePropertyBase.cpp
        EdSpriteAnimations.cpp
        EdSpritePropertyBoolField.cpp
        EdSpritePropertyDefaultField.cpp
        EdSpritePropertyBitfieldField.cpp
        EdSpriteAnimationTransferDialog.cpp
        EdSpriteNewEventDialog.cpp
        SpriteEditor.qrc
)

add_executable(SpriteEditor ${CPP_SOURCES} ${HEADERS})

target_link_libraries(SpriteEditor DT3Core  freetype png jpeg zlib jenkins md5 GLEW GL pthread dl) #DT3Sprites

qt5_use_modules(SpriteEditor Core Gui Widgets OpenGL Multimedia)

