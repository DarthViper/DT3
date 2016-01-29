set( CPP_SOURCES ./Resources/Importers/ImporterKeyedSprite.cpp
./Resources/Importers/ImporterKeyedSpriteAnimation.cpp
./Resources/Importers/ImporterKeyedSpriteAnimationKANI.cpp
./Resources/Importers/ImporterKeyedSpriteKSPR.cpp
./Resources/ResourceTypes/KeyedSpriteAnimationResource.cpp
./Resources/ResourceTypes/KeyedSpriteResource.cpp
./Types/KeyedSpriteAnimation.cpp
./Types/KeyedSpriteAnimationEvent.cpp
./Types/KeyedSpriteAnimationEventTrack.cpp
./Types/KeyedSpriteAnimationKeyframe.cpp
./Types/KeyedSpriteAnimationPose.cpp
./Types/KeyedSpriteAnimationPoseJoint.cpp
./Types/KeyedSpriteAnimationTrack.cpp
)
set ( HEADERS
./Resources/Importers/ImporterKeyedSprite.hpp
./Resources/Importers/ImporterKeyedSpriteAnimation.hpp
./Resources/Importers/ImporterKeyedSpriteAnimationKANI.hpp
./Resources/Importers/ImporterKeyedSpriteKSPR.hpp
./Resources/ResourceTypes/KeyedSpriteAnimationResource.hpp
./Resources/ResourceTypes/KeyedSpriteResource.hpp
./Types/KeyedSpriteAnimation.hpp
./Types/KeyedSpriteAnimationEvent.hpp
./Types/KeyedSpriteAnimationEventTrack.hpp
./Types/KeyedSpriteAnimationKeyframe.hpp
./Types/KeyedSpriteAnimationPose.hpp
./Types/KeyedSpriteAnimationPoseJoint.hpp
./Types/KeyedSpriteAnimationTrack.hpp
)
add_library(DT3Sprites SHARED ${CPP_SOURCES} ${HEADERS} )
