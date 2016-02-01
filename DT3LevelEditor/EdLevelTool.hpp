#pragma once
//==============================================================================
///
///	File: EdLevelTool.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
// Qt include
#include <QtCore/QObject>

#include <list>
#include "DT3Core/Types/Base/BaseClass.hpp"

//==============================================================================
/// Forward declarations
//==============================================================================

namespace DT3 {
    class PlugNode;
    class Vector3;
    class Matrix4;
    class CameraObject;
}

class EdLevelToolEvent;
class EdLevelToolWindow;

//==============================================================================
//==============================================================================

using namespace DT3;

//==============================================================================
/// Class
//==============================================================================

class EdLevelTool : public QObject,public BaseClass
{
    Q_OBJECT
public:
    DEFINE_TYPE(EdLevelTool, BaseClass)

    EdLevelTool(void) = default;
    virtual ~EdLevelTool(void) = default;

public:
    /// Description
    /// \param param description
    /// \return description
    virtual void draw(const std::shared_ptr<CameraObject> &camera, float scale) {}

    /// Description
    /// \param param description
    /// \return description
    virtual void doEvent(const EdLevelToolEvent &event) {}

    /// Description
    /// \param param description
    /// \return description
    Matrix4 getCombinedTransform(void) const;

    /// Description
    /// \param param description
    /// \return description
    void applyCombinedTransform(const Matrix4 &transform, float grid = 0.0F);

    /// Description
    /// \param param description
    /// \return description
    void applyCombinedScale(float scale);

    /// Description
    /// \param param description
    /// \return description
    virtual Matrix4 getManipulatorTransform(void) const = 0;

    /// Description
    /// \param param description
    /// \return description
    void snapToGrid(Vector3 &translation, float grid);

    /// Description
    /// \param param description
    /// \return description
    void clearSelection(void);

    /// Description
    /// \param param description
    /// \return description
    void setSelection(const std::list<std::shared_ptr<PlugNode>> &s);

    /// Description
    /// \param param description
    /// \return description
    const std::list<std::shared_ptr<PlugNode>> &getSelection(void) const { return _selection; }
Q_SIGNALS:
    void doCommand(const QString &cmd);
private:
    std::list<std::shared_ptr<PlugNode>> _selection;
};

//==============================================================================
//==============================================================================
