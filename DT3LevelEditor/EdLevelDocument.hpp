#pragma once
//==============================================================================
///
///	File: EdLevelDocument.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include

// Qt include
#include <QtOpenGL/QGLWidget>
#include <memory>
#include <list>

//==============================================================================
/// Forward declarations
//==============================================================================
namespace DT3
{
class World;
class PlugNode;
}

//==============================================================================
/// Class
//==============================================================================

class EdLevelDocument
{
public:
    EdLevelDocument(void);
    ~EdLevelDocument(void) = default;

    /// Description
    /// \param param description
    /// \return description
    void setWorld(const std::shared_ptr<DT3::World> &w);

    /// Description
    /// \param param description
    /// \return description
    const std::shared_ptr<DT3::World> &world(void) { return _world; }

    /// Description
    /// \param param description
    /// \return description
    void clearSelection(void);

    /// Description
    /// \param param description
    /// \return description
    void setSelection(const std::list<std::shared_ptr<DT3::PlugNode>> &s);

    /// Description
    /// \param param description
    /// \return description
    const std::list<std::shared_ptr<DT3::PlugNode>> &selection(void) const { return _selection; }

    /// Description
    /// \param param description
    /// \return description
    bool isSelected(const std::shared_ptr<DT3::PlugNode> &node) const;

public:
    std::shared_ptr<DT3::World>               _world;
    std::list<std::shared_ptr<DT3::PlugNode>> _selection;
};

//==============================================================================
//==============================================================================
