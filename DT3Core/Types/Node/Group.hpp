#pragma once
//==============================================================================
///
///    File: Group.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Node/PlugNode.hpp"
#include "DT3Core/Types/Math/Vector2.hpp"
#include "DT3Core/Types/Math/Color4f.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class World;
class WorldNode;

//==============================================================================
/// Base object for groups in the engine.
//==============================================================================

class Group: public PlugNode {
    public:
        DEFINE_TYPE(Group,PlugNode)
        DEFINE_CREATE_AND_CLONE

                                                Group               (void);
                                                Group               (const Group &rhs);
        Group &                                 operator =            (const Group &rhs);
        virtual                                 ~Group              (void);

        virtual void                            archive             (const std::shared_ptr<Archive> &archive) override;

    public:
        void                                    add_node            (const std::shared_ptr<WorldNode> &node);
        void                                    add_nodes           (const std::list<std::shared_ptr<WorldNode>> &nodes);
        void                                    remove_node         (const std::shared_ptr<WorldNode> &node);

        /// Returns a list of nodes that the group contains
        /// \return list of nodes
        std::list<std::shared_ptr<WorldNode>>&  nodes               (void)                          {    return _nodes;                  }

        void                                    remove_all_nodes    (void);
        void                                    set_nodes_center    (const Vector2 &center);

        /// Sets the color of the group
        /// \param group_color group color
        void                                    set_group_color     (const Color4f &group_color)    {    _group_color = group_color;     }

        /// Returns the color of the group
        /// \return group color
        const Color4f&                          group_color         (void) const                    {    return _group_color;            }



        /// Returns the world that the group belongs to.
        /// \return world
        World*                                  world               (void) const                    {   return _world;                  }
        virtual void add_to_world(World *world);
        virtual void remove_from_world(void);


        DEFINE_ACCESSORS_REF(description, set_description, std::string, _description)

    private:
        World                                   *_world;         // weak reference - no ref count
        Color4f                                 _group_color;   // Editor group color

        std::list<std::shared_ptr<WorldNode>>   _nodes;
        std::string                             _description;
};

//==============================================================================
//==============================================================================

} // DT3
