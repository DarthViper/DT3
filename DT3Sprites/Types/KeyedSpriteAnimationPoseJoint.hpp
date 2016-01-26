#ifndef DT3_KEYEDSPRITEANIMATIONPART
#define DT3_KEYEDSPRITEANIMATIONPART
//==============================================================================
///
///    File: KeyedSpriteAnimationPoseJoint.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Math/Matrix3.hpp"
//#include "DT3Core/Types/Array.hpp"
#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/Base/BaseClass.hpp"
#include "DT3Core/Types/FileBuffer/FilePath.hpp"
//#include "PoolAllocator.hpp"
#include "DT3Core/Resources/ResourceTypes/MaterialResource.hpp"
#include "KeyedSpriteAnimationKeyframe.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

class Archive;
class DrawBatcher;

//==============================================================================
//==============================================================================

class KeyedSpriteAnimationPoseJoint: public BaseClass {
    public:
        DEFINE_TYPE(KeyedSpriteAnimationPoseJoint, BaseClass)
        DEFINE_CREATE_AND_CLONE
                //DEFINE_POOL_ALLOCATOR


                                                KeyedSpriteAnimationPoseJoint    (void);
                                                KeyedSpriteAnimationPoseJoint    (const KeyedSpriteAnimationPoseJoint &rhs);
        KeyedSpriteAnimationPoseJoint &         operator =                      (const KeyedSpriteAnimationPoseJoint &rhs);
        virtual                                 ~KeyedSpriteAnimationPoseJoint    (void);

        void                                    archiveRead                 (Archive *archive);
        void                                    archiveWrite                (Archive *archive);

        public:

                //DEFINE_ACCESSORS_REFERENCED(getJointToObjectTransform, setJointToObjectTransform, Matrix3, _joint_to_object_transform);

                /// Sets the name of the bone
                /// \param param description
                /// \return description
        void                                    setName                     (const std::string &name);

                /// Returns the name of the bone
                /// \param param description
                /// \return description
        const std::string                       getName                     (void) const                                {   return _name;                        }

                /// Returns the name hash of the object
                /// \param param description
                /// \return description
        DTuint                                  getNameHash                 (void) const                                {   return _name_hash;                    }

                /// Description
                /// \param param description
                /// \return description
        void                                    setWithKey                  (const KeyedSpriteAnimationKeyframe& key);

                /// Description
                /// \param param description
                /// \return description
        KeyedSpriteAnimationKeyframe            getAsKey                    (void) const;

        const Matrix3 & getJointToObjectTransform() const {return _joint_to_object_transform;}

                DEFINE_ACCESSORS_REFERENCED(getTranslation, setTranslation, Vector2, _translation)
                DEFINE_ACCESSORS(getRotation, setRotation, DTfloat, _rotation)

                /// Description
                /// \param param description
                /// \return description
                DTfloat                                    getRotationDegrees            (void) const;

                /// Description
                /// \param param description
                /// \return description
                void                                    setRotationDegrees            (const DTfloat rotation);

                DEFINE_ACCESSORS(getVisible, setVisible, DTboolean, _visible)
                DEFINE_ACCESSORS(getScale, setScale, DTfloat, _scale)

                DTfloat                                 getPlusX() const { return _plus_x; }
                void                                    setPlusX(DTfloat v) { _plus_x=v; }
                DTfloat                                 getMinusX() const { return _minus_x; }
                void                                    setMinusX(DTfloat v) { _minus_x=v; }

                DTfloat                                 getPlusY() const { return _plus_y; }
                void                                    setPlusY(DTfloat v) { _plus_y=v; }
                DTfloat                                 getMinusY() const { return _minus_y; }
                void                                    setMinusY(DTfloat v) { _minus_y=v; }

                DTfloat                                 getPlusU() const { return _plus_u; }
                void                                    setPlusU(DTfloat v) { _plus_u=v; }
                DTfloat                                 getMinusU() const { return _minus_u; }
                void                                    setMinusU(DTfloat v) { _minus_u=v; }

                DTfloat                                 getPlusV() const { return _plus_v; }
                void                                    setPlusV(DTfloat v) { _plus_v=v; }
                DTfloat                                 getMinusV() const { return _minus_v; }
                void                                    setMinusV(DTfloat v) { _minus_v=v; }

//                DEFINE_ACCESSORS(getOrder, setOrder, DTfloat, _order);
//                DEFINE_ACCESSORS(getGroups, setGroups, DTushort, _groups);

                /// Description
                /// \param param description
                /// \return description
        void                            setGridSizeX                (DTint size_x);

                /// Description
                /// \param param description
                /// \return description
        DTint                           getGridSizeX                (void) const;

                /// Description
                /// \param param description
                /// \return description
        void                            setGridSizeY                (DTint size_y);

                /// Description
                /// \param param description
                /// \return description
        DTint                           getGridSizeY                (void) const;

                /// Description
                /// \param param description
                /// \return description
        std::vector<Vector2>&                 gridPoints                  (void)       {    return _grid; }
        const std::vector<Vector2>&           gridPoints                  (void) const {    return _grid; }

                /// Description
                /// \param param description
                /// \return description
        void                            resetGrid                   (void);

        /// Description
                /// \param param description
                /// \return description
        void                            draw                        (DrawBatcher &b);

        private:
        void                            allocateGrid                (void);

                friend class KeyedSpriteResource;
        friend class KeyedSpriteAnimationTrack;

                std::string                                  _name;
        DTuint                                  _name_hash;

                Matrix3                                 _joint_to_object_transform;

                KeyedSpriteAnimationPoseJoint*            _parent;
                std::vector<KeyedSpriteAnimationPoseJoint*>    _children;

                Vector2                                 _translation;
                DTfloat                                 _rotation;
                DTfloat                                 _scale;

                DTfloat                                 _plus_x;
                DTfloat                                 _minus_x;
                DTfloat                                 _plus_y;
                DTfloat                                 _minus_y;

                DTfloat                                 _plus_u;
                DTfloat                                 _minus_u;

                DTfloat                                 _plus_v;
                DTfloat                                 _minus_v;

            DTboolean                               _visible;
            DTfloat                                 _order;

            DTint                                   _grid_size_x;
            DTint                                   _grid_size_y;

            DTushort                                _groups;

            std::vector<Vector2>                          _grid;

};

//==============================================================================
//==============================================================================

} // DT3

#endif

