#pragma once
//==============================================================================
///
///	File: EdLevelWorldLayout.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Qt include
#include <QtWidgets/QLayout>
#include <QtCore/QVector>

//==============================================================================
/// Class
//==============================================================================

class EdLevelWorldLayout : public QLayout
{
public:
    EdLevelWorldLayout(QWidget *parent);
    EdLevelWorldLayout(void) = default;
    ~EdLevelWorldLayout(void);

public:
    QSize        sizeHint(void) const;
    QSize        minimumSize(void) const;
    QLayoutItem *itemAt(int i) const;
    QLayoutItem *takeAt(int i);
    void addItem(QLayoutItem *item);
    void setGeometry(const QRect &rect);
    int count(void) const { return _list.count(); }

private:
    QVector<QLayoutItem *> _list;
};

//==============================================================================
//==============================================================================
