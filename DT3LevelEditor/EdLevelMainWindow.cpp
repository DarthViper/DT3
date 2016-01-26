//==============================================================================
///
///	File: EdLevelMainWindow.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
#include "EdLevelMainWindow.hpp"
#include "ui_EdLevelMainWindow.h"

#include "EdLevelDocument.hpp"
#include "EdLevelWorldWindow.hpp"
#include "EdLevelScriptWindow.hpp"
#include "EdLevelAnimationWindow.hpp"
#include "EdLevelSoundWindow.hpp"
#include "EdLevelConsoleWindow.hpp"
#include "EdLevelResourcesWindow.hpp"
#include "EdLevelLibraryWindow.hpp"
#include "EdLevelPerformanceWindow.hpp"
#include "EdLevelPropertiesWindow.hpp"
#include "EdLevelHierarchyWindow.hpp"
#include "EdLevelLaunchDialog.hpp"
#include "EdLevelWorldLayout.hpp"
#include "EdLevelMeshBuilder.hpp"

// Qt include
#include <QtGui/QtGui>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QSlider>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QMenuBar>
#include <QtOpenGL/QGLFormat>
#include <QtCore/QFile>

// Engine includes
#include "DT3Core/Entry/GameMainThread.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/SystemCallbacks.hpp"
#include "DT3Core/System/Console.hpp"
#include "DT3Core/System/FileManager.hpp"
#include "DT3Core/Types/Utility/CommandContext.hpp"
#include "DT3Core/Types/Utility/MoreStrings.hpp"
#include "DT3Core/Types/Node/Group.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveTextWriter.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveObjectQueue.hpp"
#include "DT3Core/Components/ComponentBase.hpp"
#include "DT3Core/Objects/ObjectBase.hpp"
#include DT3_HAL_INCLUDE_PATH
#include <limits>
#include <set>

//==============================================================================
//==============================================================================

namespace DT3 {
    extern std::map<std::string,std::shared_ptr<CreatorBase>>&	world_map       (void);

    extern std::map<std::string,std::set<std::string>>&         placeable_map	(void);
    extern std::map<std::string,std::set<std::string>>&         component_map	(void);
    extern std::map<std::string,std::set<std::string>>&         script_map      (void);
}

//==============================================================================
//==============================================================================

using namespace DT3;

//==============================================================================
//==============================================================================

EdLevelMainWindow::EdLevelMainWindow(void) : QMainWindow(nullptr), ui(new Ui::EdLevelMainWindow)
{
    // Turn on Anti aliasing
    QGLFormat glf = QGLFormat::defaultFormat();
    glf.setSampleBuffers(true);
    glf.setSamples(4);
    QGLFormat::setDefaultFormat(glf);

    setAttribute(Qt::WA_TranslucentBackground, false);

    ui->setupUi(this);

    createActions();

    // Register error handlers
    AssertImpl::set_callback_assert_msg(make_callback(this, &EdLevelMainWindow::showAssert));
    ErrorImpl::set_callback_error_msg(make_callback(this, &EdLevelMainWindow::showError));
    ErrorImpl::set_callback_warning_msg(make_callback(this, &EdLevelMainWindow::showWarning));

    // Register callbacks for engine events
    SystemCallbacks::add_node_cb().add(make_callback(this, &EdLevelMainWindow::addNodeCB));
    SystemCallbacks::remove_node_cb().add(make_callback(this, &EdLevelMainWindow::removeNodeCB));
    SystemCallbacks::reparent_node_cb().add(make_callback(this, &EdLevelMainWindow::reparentNodeCB));

    SystemCallbacks::add_group_cb().add(make_callback(this, &EdLevelMainWindow::addGroupCB));
    SystemCallbacks::remove_group_cb().add(make_callback(this, &EdLevelMainWindow::removeGroupCB));

    SystemCallbacks::add_component_cb().add(make_callback(this, &EdLevelMainWindow::addComponentCB));
    SystemCallbacks::remove_component_cb().add(make_callback(this, &EdLevelMainWindow::removeComponentCB));

    SystemCallbacks::connect_plug_cb().add(make_callback(this, &EdLevelMainWindow::connectPlugCB));
    SystemCallbacks::disconnect_plug_cb().add(make_callback(this, &EdLevelMainWindow::disconnectPlugCB));
    SystemCallbacks::connect_event_cb().add(make_callback(this, &EdLevelMainWindow::connectEventCB));
    SystemCallbacks::disconnect_event_cb().add(make_callback(this, &EdLevelMainWindow::disconnectEventCB));


    // Create a new document
    _document = new EdLevelDocument();


    // Set editor callbacks
    // Dock config
    setCorner( Qt::TopLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::TopRightCorner, Qt::RightDockWidgetArea );
    setCorner( Qt::BottomLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::BottomRightCorner, Qt::RightDockWidgetArea );

    //
    // World Window
    //

    QWidget *world_section = ui->world_section;

    _world_toolbar = new QToolBar(world_section);
    _world_toolbar->setIconSize(QSize(16,16));

    _world_widget = new EdLevelWorldWindow(world_section, _world_toolbar, _document);
    //_world_widget->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));

    EdLevelWorldLayout *layout1 = new EdLevelWorldLayout();
    layout1->setContentsMargins(0,0,0,0);
    //layout1->setHorizontalSpacing(1);
    //layout1->setVerticalSpacing(1);
    layout1->addWidget(_world_toolbar);
    layout1->addWidget(_world_widget);

    world_section->setLayout(layout1);

    _world_widget->onChangeResolution(0);

    //
    // Views Window
    //

    //QWidget *views_section = new QWidget(this);


    // Script window

    _script_toolbar = new QToolBar(ui->script_section);
    _script_toolbar->setIconSize(QSize(16,16));

    _script_widget = new EdLevelScriptWindow(ui->script_section, _script_toolbar, _document);

    QGridLayout *layout3 = new QGridLayout;
    layout3->setContentsMargins(0,0,0,0);
    layout3->setHorizontalSpacing(1);
    layout3->setVerticalSpacing(1);
    layout3->addWidget(_script_toolbar);
    layout3->addWidget(_script_widget);

    ui->script_section->setLayout(layout3);

    // Animation Window
    _animation_toolbar = new QToolBar(ui->animation_section);
    _animation_toolbar->setIconSize(QSize(16,16));

    _animation_widget = new EdLevelAnimationWindow(ui->animation_section, _animation_toolbar, _document);

    QGridLayout *layout4 = new QGridLayout;
    layout4->setContentsMargins(0,0,0,0);
    layout4->setHorizontalSpacing(1);
    layout4->setVerticalSpacing(1);
    layout4->addWidget(_animation_toolbar);
    layout4->addWidget(_animation_widget);

    ui->animation_section->setLayout(layout4);

    // Sound Window
    _sound_toolbar = new QToolBar(ui->sound_section);
    _sound_toolbar->setIconSize(QSize(16,16));

    _sound_widget = new EdLevelSoundWindow(ui->sound_section, _sound_toolbar, _document);

    QGridLayout *layout8 = new QGridLayout;
    layout8->setContentsMargins(0,0,0,0);
    layout8->setHorizontalSpacing(1);
    layout8->setVerticalSpacing(1);
    layout8->addWidget(_sound_toolbar);
    layout8->addWidget(_sound_widget);

    ui->sound_section->setLayout(layout8);

    /*// Sound FX Window
    QWidget *sound_fx_section = new QWidget(this);

    _sound_fx_toolbar = new QToolBar(sound_fx_section);
    _sound_fx_toolbar->setIconSize(QSize(16,16));

    _sound_fx_widget = new EdLevelSoundFXWindow(sound_fx_section, _sound_fx_toolbar, _document);

    QGridLayout *layout9 = new QGridLayout;
    layout9->setContentsMargins(0,0,0,0);
    layout9->setHorizontalSpacing(1);
    layout9->setVerticalSpacing(1);
    layout9->addWidget(_sound_fx_toolbar);
    layout9->addWidget(_sound_fx_widget);

    sound_fx_section->setLayout(layout9);

    QDockWidget *soundfxDock = new QDockWidget(tr("Sound FX"), this);
    soundfxDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    soundfxDock->setFeatures ( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable );
    soundfxDock->setWidget(sound_fx_section);
    addDockWidget(Qt::BottomDockWidgetArea, soundfxDock);*/


    // Console Window
    _console_toolbar = new QToolBar(ui->console_section);
    _console_toolbar->setIconSize(QSize(16,16));
    //_console_toolbar->addAction(_script_align);

    _console_widget = new EdLevelConsoleWindow(ui->console_section, _console_toolbar, _document);

    QGridLayout *layout5 = new QGridLayout;
    layout5->setContentsMargins(0,0,0,0);
    layout5->setHorizontalSpacing(1);
    layout5->setVerticalSpacing(1);
    layout5->addWidget(_console_toolbar);
    layout5->addWidget(_console_widget);

    ui->console_section->setLayout(layout5);

    // Performance Window

    _performance_toolbar = new QToolBar(ui->performance_section);
    _performance_toolbar->setIconSize(QSize(16,16));
    //_performance_toolbar->addAction(_performance_widget);

    _performance_widget = new EdLevelPerformanceWindow(ui->performance_section, _performance_toolbar, _document);

    QGridLayout *layout7 = new QGridLayout;
    layout7->setContentsMargins(0,0,0,0);
    layout7->setHorizontalSpacing(1);
    layout7->setVerticalSpacing(1);
    layout7->addWidget(_performance_toolbar);
    layout7->addWidget(_performance_widget);

    ui->performance_section->setLayout(layout7);

    tabifyDockWidget ( ui->scriptDock, ui->animationDock);
    tabifyDockWidget ( ui->animationDock, ui->soundDock);
    tabifyDockWidget ( ui->soundDock, ui->consoleDock);
//  tabifyDockWidget ( soundDock, soundfxDock);
//  tabifyDockWidget ( soundfxDock, consoleDock);
    tabifyDockWidget ( ui->consoleDock, ui->performanceDock);

    ui->scriptDock->show();
    ui->scriptDock->raise();


//    QTabWidget *tabWidget = new QTabWidget(this);
//
//    tabWidget->addTab(script_section, QString("Script"));
//    tabWidget->addTab(animation_section, QString("Animation"));
//    tabWidget->addTab(sound_section, QString("Sound"));
//    tabWidget->addTab(sound_fx_section, QString("SoundFX"));
//    tabWidget->addTab(console_section, QString("Console"));
//    //tabWidget->addTab(resources_section, QString("Resources"));
//    //tabWidget->addTab(library_section, QString("Library"));
//    tabWidget->addTab(performance_section, QString("Performance"));
//
//    QGridLayout *layout2 = new QGridLayout;
//    layout2->setContentsMargins(0,0,0,0);
//    layout2->setHorizontalSpacing(1);
//    layout2->setVerticalSpacing(1);
//    layout2->addWidget(tabWidget);
//
//    views_section->setLayout(layout2);


    //
    // Hierarchy Window
    //
    _hierarchy_toolbar = new QToolBar(ui->hierarchy_section);
    _hierarchy_toolbar->setIconSize(QSize(16,16));

    _hierarchy_widget = new EdLevelHierarchyWindow(ui->hierarchy_section, _hierarchy_toolbar, _document);

    QGridLayout *layout11 = new QGridLayout;
    layout11->setContentsMargins(0,0,0,0);
    layout11->setHorizontalSpacing(1);
    layout11->setVerticalSpacing(1);
    layout11->addWidget(_hierarchy_toolbar);
    layout11->addWidget(_hierarchy_widget);

    ui->hierarchy_section->setLayout(layout11);

    //
    // Properties
    //
    _properties_widget = new EdLevelPropertiesWindow(this, NULL, _document);
    // Properties Dock
    ui->propertiesDock->setWidget(_properties_widget);

    //
    // Library
    //
    _library_widget = new EdLevelLibraryWindow(this, NULL, _document);
    // Library Dock
    ui->libraryDock->setWidget(_library_widget);

    //
    // Resources
    //

    // Resources Window
    _resources_toolbar = new QToolBar(ui->resources_section);
    _resources_toolbar->setIconSize(QSize(16,16));

    _resources_widget = new EdLevelResourcesWindow(ui->resources_section, _resources_toolbar, _document,_world_widget);

    QGridLayout *layout6 = new QGridLayout;
    layout6->setContentsMargins(0,0,0,0);
    layout6->setHorizontalSpacing(1);
    layout6->setVerticalSpacing(1);
    layout6->addWidget(_resources_toolbar);
    layout6->addWidget(_resources_widget);

    ui->resources_section->setLayout(layout6);

    //
    // Tabify docks
    //

    tabifyDockWidget ( ui->resourcesDock, ui->libraryDock);
    tabifyDockWidget ( ui->libraryDock, ui->propertiesDock);



//    QSplitter *mainSplitter = new QSplitter(Qt::Vertical);
//    mainSplitter->addWidget(world_section);
//    mainSplitter->addWidget(views_section);

    /*QSplitter *propertiesSplitter = new QSplitter(Qt::Horizontal);
    propertiesSplitter->addWidget(mainSplitter);
    propertiesSplitter->addWidget(propertiesDock);
    propertiesSplitter->setStretchFactor(1, 1);*/

    createMenus();
    createContextMenu();

    setCentralWidget(world_section);
    setWindowTitle(tr("Level Editor"));

    readSettings();

    //setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentLevelFile("");

    connect(this,&EdLevelMainWindow::doSelectionChanged,this,&EdLevelMainWindow::onSelectionChanged);

    connect(this,&EdLevelMainWindow::doSelectionChanged,_hierarchy_widget,&EdLevelHierarchyWindow::onSelectionChanged);
    connect(this,&EdLevelMainWindow::doRefreshHierarchy,_hierarchy_widget,&EdLevelHierarchyWindow::onRefreshHierarchy);

    connect(this,&EdLevelMainWindow::doSelectionChanged,_world_widget,&EdLevelWorldWindow::onSelectionChanged);
    connect(this,&EdLevelMainWindow::doRefreshWorld,_world_widget,&EdLevelWorldWindow::onRefreshWorld);

    connect(this,&EdLevelMainWindow::doSelectionChanged,_script_widget,&EdLevelScriptWindow::onSelectionChanged);
    connect(this,&EdLevelMainWindow::doRefreshScript,_script_widget,&EdLevelScriptWindow::onRefreshScript);

    connect(this,&EdLevelMainWindow::doSelectionChanged,_animation_widget,&EdLevelAnimationWindow::onSelectionChanged);
    connect(this,&EdLevelMainWindow::doRefreshAnimation,_animation_widget,&EdLevelAnimationWindow::onRefreshAnimation);

    connect(this,&EdLevelMainWindow::doSelectionChanged,_sound_widget,&EdLevelSoundWindow::onSelectionChanged);
    connect(this,&EdLevelMainWindow::doRefreshSound,_sound_widget,&EdLevelSoundWindow::onRefreshSound);
    connect(this,&EdLevelMainWindow::doRefreshProperties,_sound_widget,&EdLevelSoundWindow::onRefreshProperties);

    connect(this,&EdLevelMainWindow::doRefreshResources,_resources_widget,&EdLevelResourcesWindow::onRefreshResources);

    connect(this,&EdLevelMainWindow::doRefreshLibrary,_library_widget,&EdLevelLibraryWindow::onRefreshLibrary);

    connect(this,&EdLevelMainWindow::doRefreshPerformance,_performance_widget,&EdLevelPerformanceWindow::onRefreshPerformance);

    connect(this,&EdLevelMainWindow::doSelectionChanged,_properties_widget,&EdLevelPropertiesWindow::onSelectionChanged);
    connect(this,&EdLevelMainWindow::doRefreshProperties,_properties_widget,&EdLevelPropertiesWindow::onRefreshProperties);

    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doSelectionChanged,this,&EdLevelMainWindow::onSelectionChanged);
    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doSelectionChanged,_hierarchy_widget,&EdLevelHierarchyWindow::onSelectionChanged);
    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doSelectionChanged,_world_widget,&EdLevelWorldWindow::onSelectionChanged);
    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doSelectionChanged,_script_widget,&EdLevelScriptWindow::onSelectionChanged);
    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doSelectionChanged,_animation_widget,&EdLevelAnimationWindow::onSelectionChanged);
    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doSelectionChanged,_sound_widget,&EdLevelSoundWindow::onSelectionChanged);
    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doSelectionChanged,_properties_widget,&EdLevelPropertiesWindow::onSelectionChanged);

    connect(_world_widget,&EdLevelWorldWindow::doSelectionChanged,this,&EdLevelMainWindow::onSelectionChanged);
    connect(_world_widget,&EdLevelWorldWindow::doSelectionChanged,_hierarchy_widget,&EdLevelHierarchyWindow::onSelectionChanged);
    connect(_world_widget,&EdLevelWorldWindow::doSelectionChanged,_world_widget,&EdLevelWorldWindow::onSelectionChanged);
    connect(_world_widget,&EdLevelWorldWindow::doSelectionChanged,_script_widget,&EdLevelScriptWindow::onSelectionChanged);
    connect(_world_widget,&EdLevelWorldWindow::doSelectionChanged,_animation_widget,&EdLevelAnimationWindow::onSelectionChanged);
    connect(_world_widget,&EdLevelWorldWindow::doSelectionChanged,_sound_widget,&EdLevelSoundWindow::onSelectionChanged);
    connect(_world_widget,&EdLevelWorldWindow::doSelectionChanged,_properties_widget,&EdLevelPropertiesWindow::onSelectionChanged);

    connect(_script_widget,&EdLevelScriptWindow::doSelectionChanged,this,&EdLevelMainWindow::onSelectionChanged);
    connect(_script_widget,&EdLevelScriptWindow::doSelectionChanged,_hierarchy_widget,&EdLevelHierarchyWindow::onSelectionChanged);
    connect(_script_widget,&EdLevelScriptWindow::doSelectionChanged,_world_widget,&EdLevelWorldWindow::onSelectionChanged);
    connect(_script_widget,&EdLevelScriptWindow::doSelectionChanged,_script_widget,&EdLevelScriptWindow::onSelectionChanged);
    connect(_script_widget,&EdLevelScriptWindow::doSelectionChanged,_animation_widget,&EdLevelAnimationWindow::onSelectionChanged);
    connect(_script_widget,&EdLevelScriptWindow::doSelectionChanged,_sound_widget,&EdLevelSoundWindow::onSelectionChanged);
    connect(_script_widget,&EdLevelScriptWindow::doSelectionChanged,_properties_widget,&EdLevelPropertiesWindow::onSelectionChanged);

    connect(_script_widget,&EdLevelScriptWindow::doRefreshScript,_script_widget,&EdLevelScriptWindow::onRefreshScript);

    connect(_animation_widget,&EdLevelAnimationWindow::doSelectionChanged,this,&EdLevelMainWindow::onSelectionChanged);
    connect(_animation_widget,&EdLevelAnimationWindow::doSelectionChanged,_hierarchy_widget,&EdLevelHierarchyWindow::onSelectionChanged);
    connect(_animation_widget,&EdLevelAnimationWindow::doSelectionChanged,_world_widget,&EdLevelWorldWindow::onSelectionChanged);
    connect(_animation_widget,&EdLevelAnimationWindow::doSelectionChanged,_script_widget,&EdLevelScriptWindow::onSelectionChanged);
    connect(_animation_widget,&EdLevelAnimationWindow::doSelectionChanged,_animation_widget,&EdLevelAnimationWindow::onSelectionChanged);
    connect(_animation_widget,&EdLevelAnimationWindow::doSelectionChanged,_sound_widget,&EdLevelSoundWindow::onSelectionChanged);
    connect(_animation_widget,&EdLevelAnimationWindow::doSelectionChanged,_properties_widget,&EdLevelPropertiesWindow::onSelectionChanged);

// Command connections

    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doCommand,this,&EdLevelMainWindow::onCommand);
    connect(_hierarchy_widget,&EdLevelHierarchyWindow::doUndoBlock,this,&EdLevelMainWindow::onUndoBlock);
    connect(this,&EdLevelMainWindow::doAddNode,_hierarchy_widget,&EdLevelHierarchyWindow::onAddNode);
    connect(this,&EdLevelMainWindow::doRemoveNode,_hierarchy_widget,&EdLevelHierarchyWindow::onRemoveNode);
    connect(this,&EdLevelMainWindow::doReparentNode,_hierarchy_widget,&EdLevelHierarchyWindow::onReparentNode);
    connect(this,&EdLevelMainWindow::doConnectPlug,_hierarchy_widget,&EdLevelHierarchyWindow::onConnectPlug);
    connect(this,&EdLevelMainWindow::doDisconnectPlug,_hierarchy_widget,&EdLevelHierarchyWindow::onDisconnectPlug);
    connect(this,&EdLevelMainWindow::doConnectEvent,_hierarchy_widget,&EdLevelHierarchyWindow::onConnectEvent);
    connect(this,&EdLevelMainWindow::doDisconnectEvent,_hierarchy_widget,&EdLevelHierarchyWindow::onDisconnectEvent);

    connect(_world_widget,&EdLevelWorldWindow::doCommand,this,&EdLevelMainWindow::onCommand);
    connect(_world_widget,&EdLevelWorldWindow::doUndoBlock,this,&EdLevelMainWindow::onUndoBlock);

    connect(_script_widget,&EdLevelScriptWindow::doCommand,this,&EdLevelMainWindow::onCommand);
    connect(_script_widget,&EdLevelScriptWindow::doUndoBlock,this,&EdLevelMainWindow::onUndoBlock);
    connect(this,&EdLevelMainWindow::doAddNode,_script_widget,&EdLevelScriptWindow::onAddNode);
    connect(this,&EdLevelMainWindow::doRemoveNode,_script_widget,&EdLevelScriptWindow::onRemoveNode);
    connect(this,&EdLevelMainWindow::doReparentNode,_script_widget,&EdLevelScriptWindow::onReparentNode);
    connect(this,&EdLevelMainWindow::doAddGroup,_script_widget,&EdLevelScriptWindow::onAddGroup);
    connect(this,&EdLevelMainWindow::doRemoveGroup,_script_widget,&EdLevelScriptWindow::onRemoveGroup);
    connect(this,&EdLevelMainWindow::doAddComponent,_script_widget,&EdLevelScriptWindow::onAddComponent);
    connect(this,&EdLevelMainWindow::doRemoveComponent,_script_widget,&EdLevelScriptWindow::onRemoveComponent);
    connect(this,&EdLevelMainWindow::doConnectPlug,_script_widget,&EdLevelScriptWindow::onConnectPlug);
    connect(this,&EdLevelMainWindow::doDisconnectPlug,_script_widget,&EdLevelScriptWindow::onDisconnectPlug);
    connect(this,&EdLevelMainWindow::doConnectEvent,_script_widget,&EdLevelScriptWindow::onConnectEvent);
    connect(this,&EdLevelMainWindow::doDisconnectEvent,_script_widget,&EdLevelScriptWindow::onDisconnectEvent);

    connect(_animation_widget,&EdLevelAnimationWindow::doCommand,this,&EdLevelMainWindow::onCommand);
    connect(_animation_widget,&EdLevelAnimationWindow::doUndoBlock,this,&EdLevelMainWindow::onUndoBlock);

    connect(_sound_widget,&EdLevelSoundWindow::doCommand,this,&EdLevelMainWindow::onCommand);
    connect(this,&EdLevelMainWindow::doAddNode,_sound_widget,&EdLevelSoundWindow::onAddNode);
    connect(this,&EdLevelMainWindow::doRemoveNode,_sound_widget,&EdLevelSoundWindow::onRemoveNode);
    /*_sound_fx_widget,*/

    connect(_console_widget,&EdLevelConsoleWindow::doCommand,this,&EdLevelMainWindow::onCommand);


    connect(_properties_widget,&EdLevelPropertiesWindow::doCommand,this,&EdLevelMainWindow::onCommand);
    connect(_properties_widget,&EdLevelPropertiesWindow::doUndoBlock,this,&EdLevelMainWindow::onUndoBlock);
    connect(this,&EdLevelMainWindow::doAddComponent,_properties_widget,&EdLevelPropertiesWindow::onAddComponent);
    connect(this,&EdLevelMainWindow::doRemoveComponent,_properties_widget,&EdLevelPropertiesWindow::onRemoveComponent);

    // Context menus
    connect(    _script_widget,         SIGNAL(doNodeContextMenu(std::shared_ptr<WorldNode>, const QPointF &)),
                this,                   SLOT(onNodeContextMenu(std::shared_ptr<WorldNode>, const QPointF &))  );

    connect(    _script_widget,         SIGNAL(doComponentContextMenu(std::shared_ptr<ComponentBase>, const QPointF &)),
                this,                   SLOT(onComponentContextMenu(std::shared_ptr<ComponentBase>, const QPointF &))  );


    /*// Script Tools
    connect(    this,                   SIGNAL(doScriptAlign(void)), _script_widget,         SLOT(onScriptAlign(void))  );
    connect(    this,                   SIGNAL(doScriptToggleValues(void)), _script_widget,         SLOT(onScriptToggleValues(void))  );
    connect(    this,                   SIGNAL(doScriptAddToLibrary(void)), _script_widget,         SLOT(onScriptAddToLibrary(void))  );*/

    // Set the default selection
    std::list<std::shared_ptr<PlugNode>> empty_selection;
    doSelectionChanged(empty_selection);


    _timer.start(200, this);
    _autosave_timer.start(60*1000*1, this); // 1 minute

    emit doRefreshWorld();
//    GameMainThread::show_engine(1,1);
}

EdLevelMainWindow::~EdLevelMainWindow(void)
{
    GameMainThread::hide_engine();

    delete _document;
    delete ui;
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::setSaveIcon (DTboolean icon_state)
{
    ui->_save_level_action->setEnabled(icon_state);
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _timer.timerId()) {

//        DTfloat STEP_SIZE = 200.0F / 1000.0F; // 200 msec

//        if (System::input_manager())          System::input_manager()->tick(STEP_SIZE);
//		if (System::network_manager())		System::network_manager()->tick(STEP_SIZE);
//		if (System::getReplicationManager())	System::getReplicationManager()->tick(STEP_SIZE);
//		if (System::getAudioRenderer())         System::getAudioRenderer()->tick(STEP_SIZE);
//		if (System::getMusicRenderer())         System::getMusicRenderer()->tick(STEP_SIZE);
//		if (System::getRenderer())				System::getRenderer()->tick(STEP_SIZE);

    } else if (event->timerId() == _autosave_timer.timerId()) {

        autosave();

    } else {
        QWidget::timerEvent(event);
    }

}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::closeEvent(QCloseEvent *event)
{
    if (isOkToContinue()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onUpdateMenus()
{
    if (_undo_queue.size() > 0) {
        ui->_undo_action->setEnabled(true);
    } else {
        ui->_undo_action->setEnabled(false);
    }

    const std::list<std::shared_ptr<PlugNode>>& selection = _document->selection();
    if (selection.size() > 0) {
        ui->_export_selection_action->setEnabled(true);
    } else {
        ui->_export_selection_action->setEnabled(false);
    }

}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onOpen()
{

    if (isOkToContinue()) {
        std::string levels_path = FilePath("{ED_LEVELS_PATH}").full_path() + FilePath::path_separator() + "*";

        QString filename = QFileDialog::getOpenFileName(this,
                                   tr("Open Level File"),
                                   levels_path.c_str(),
                                   tr("Level (*.lvl)"));

        if (!filename.isEmpty()) {
            loadLevel(filename);
            ui->_save_level_action->setEnabled(false);
        }
    }
}

bool EdLevelMainWindow::onSaveLevel()
{
    if (_current_level_file.isEmpty()) {
        return onSaveLevelAs();
    } else {
        bool saved = saveLevel(_current_level_file);
        ui->_save_level_action->setEnabled(!saved);
        return saved;
    }
}

bool EdLevelMainWindow::onSaveLevelAs()
{
    QFileDialog fileDialog(this, "Choose level file to save");
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setNameFilter("Level files (*.lvl)");
    fileDialog.setDefaultSuffix("lvl");
    int result = fileDialog.exec();

    if (!result)
        return false;

    QString filename = fileDialog.selectedFiles().first();
    if (filename.isEmpty())
        return false;

    return saveLevel(filename);
}

bool EdLevelMainWindow::onExportSelection()
{
    QFileDialog fileDialog(this, "Choose object file to save");
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setNameFilter("Object files (*.lobj)");
    fileDialog.setDefaultSuffix("lobj");
    int result = fileDialog.exec();

    if (!result)
        return false;

    QString filename = fileDialog.selectedFiles().first();
    if (filename.isEmpty())
        return false;

    onCommand( QString("Export \"") + filename + "\"" );

    //statusBar()->showMessage(tr("Objects exported"), 2000);


    return true;
}

void EdLevelMainWindow::onImportSelection()
{
    QString filename = QFileDialog::getOpenFileName(this,
                               tr("Open Object File"),
                               FilePath("{ED_LEVELS_PATH}").full_path().c_str(),
                               tr("Object file (*.lobj)"));

    if (!filename.isEmpty()) {
        onCommand( QString("Import \"") + filename + "\"" );

        //statusBar()->showMessage(tr("Objects imported"), 2000);
    }
}

void EdLevelMainWindow::onRunScript()
{
    QString filename = QFileDialog::getOpenFileName(this,
                               tr("Run Script"),
                               FilePath("{ED_LEVELS_PATH}").full_path().c_str(),
                               tr("Text file (*.txt)"));

    if (!filename.isEmpty()) {
        onCommand( QString("RunScript \"") + filename + "\"" );

        //statusBar()->showMessage(tr("Script Run"), 2000);
    }
}

void EdLevelMainWindow::onAbout()
{
    /*QMessageBox::On_About(this, tr("On_About Level Editor"),
            tr("<h2>Level Editor 1.1</h2>"
               "<p>Copyright &copy; 2008 Software Inc."
               "<p>Level Editor is a small application that "
               "demonstrates QAction, QEdLevelMainWindow, QMenuBar, "
               "QStatusBar, QTableWidget, QToolBar, and many other "
               "Qt classes."));*/
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onOpenRecent()
{
    QObject *ob = sender();
    for (int i = 0; i < MaxRecentFiles; ++i) {
        if (i < _recent_files.count()) {
            QAction *act = qobject_cast<QAction *>(ob);
            if(!act)
                continue;
            QString file_to_open = act->data().toString();
            qDebug() << "Open recent requested to open file:" << file_to_open;
        }
    }

}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onCreateObject()
{
    onUndoBlock();

    QAction *action = qobject_cast<QAction*>(sender());
    QString object_type = action->data().toString();

    onCommand("Add \"" + object_type + "\"");
}

void EdLevelMainWindow::onCreateComponent()
{
    onUndoBlock();

    const std::list<std::shared_ptr<PlugNode>>& selection = _document->selection ();
    if (selection.size() == 1) {
        QAction *action = qobject_cast<QAction*>(sender());
        QString component_type = action->data().toString();

        onCommand(QString("AddComponent \"") + selection.front()->name().c_str() + "\" \"" + component_type + "\"");
    }

}

void EdLevelMainWindow::onClearComponent (void)
{
    onUndoBlock();

    const std::list<std::shared_ptr<PlugNode>>& selection = _document->selection ();
    if (selection.size() == 1) {
        QAction *action = qobject_cast<QAction*>(sender());
        ComponentBase *component = (ComponentBase *) action->data().value<void*>();

        onCommand(QString("RemoveComponent \"") + selection.front()->name().c_str() + "\" \"" + component->name().c_str() + "\"");
    }

}

void EdLevelMainWindow::onCreateScripts()
{
    onUndoBlock();

    QAction *action = qobject_cast<QAction*>(sender());
    QString object_type = action->data().toString();

    onCommand("add \"" + object_type + "\"");
}

void EdLevelMainWindow::onCreateWorld()
{
    //onUndoBlock();

    QAction *action = qobject_cast<QAction*>(sender());
    QString object_type = action->data().toString();

    std::shared_ptr<World> world = checked_cast<World>(Factory::create_world(object_type.toUtf8().data()));
    if (world) {
        _document->setWorld(world);
        setCurrentLevelFile("");
        _undo_queue.clear();
    }

    updateWidgets(CommandResult::UPDATE_ALL);
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::updateWidgets (DTuint h)
{
    if (h & CommandResult::UPDATE_SCRIPT)       emit doRefreshScript();
    if (h & CommandResult::UPDATE_WORLD)        emit doRefreshWorld();
    if (h & CommandResult::UPDATE_HIERARCHY)    emit doRefreshHierarchy();
    if (h & CommandResult::UPDATE_PROPERTIES)   emit doRefreshProperties();
    if (h & CommandResult::UPDATE_LIBRARY)      emit doRefreshLibrary();
    if (h & CommandResult::UPDATE_RESOURCES)    emit doRefreshResources();
    if (h & CommandResult::UPDATE_ANIMATION)    emit doRefreshAnimation();
    if (h & CommandResult::UPDATE_CONSOLE)      emit doRefreshConsole();
    if (h & CommandResult::UPDATE_PERFORMANCE)  emit doRefreshPerformance();
    if (h & CommandResult::UPDATE_SOUND)        emit doRefreshSound();
}

//==============================================================================
//==============================================================================

bool EdLevelMainWindow::onCommand(QString command)
{
    // Set up the context object for the command
    CommandContext ctx;
    ctx.set_world(_document->world());
    ctx.set_selection(_document->selection());

    // Figure out rect of script view
    QPointF topLeft = _script_widget->mapToScene (0, 0);
    QPointF bottomRight = _script_widget->mapToScene (_script_widget->width(), _script_widget->height());
    ctx.set_selection_rectangle( DT3::Rectangle(topLeft.x(), bottomRight.x(), topLeft.y(), bottomRight.y()) );

    CommandResult result = Console::do_command(ctx, CommandParams(command.toUtf8().data()) );

    // Add to undo queue. If we can't undo, clear the queue.
    if (result.undo_commands().size() > 0) {

        // Copy commands over
        const std::list<CommandParams>& commands = result.undo_commands();
        for (auto i = commands.rbegin(); i != commands.rend(); ++i) {
            _undo_queue.push_front(*i);
        }

        // Update Menu
        ui->_undo_action->setEnabled(true);

    } else {
        _undo_queue.clear();

        // Update Menu
        ui->_undo_action->setEnabled(false);
    }

    _console_widget->append (command + "      // " + QString(result.message().c_str()));

    // Change selection
    if (_document->selection() != ctx.selection())
        emit doSelectionChanged(ctx.selection());

    // Change world
    if (_document->world() != ctx.world())
        _document->setWorld(ctx.world());

    // Refresh Everything
    DTuint h = result.update_hint();
    updateWidgets(h);

    // Reenable save
    ui->_save_level_action->setEnabled(true);

    return result.result();
}

void EdLevelMainWindow::onUndoBlock()
{
    if (_undo_queue.size() > 0 && _undo_queue.front().count() == 0)
        return;

    // Push an empty command to signify a break
    _undo_queue.push_front(CommandParams());
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onUndo()
{
    _console_widget->append ("// Undo Begins");

    // Set up the context object for the command
    CommandContext ctx;
    ctx.set_world(_document->world());
    ctx.set_selection(_document->selection());

    DTuint h = 0;

    // Eat blocks
    while (_undo_queue.size() > 0 && _undo_queue.front().count() == 0) {
        _undo_queue.pop_front();
    }

    // Pop until an empty command is found
    while (_undo_queue.size() > 0) {

        if (_undo_queue.front().count() == 0) {
            break;
        }

        CommandParams   &params = _undo_queue.front();
        CommandResult   result = Console::do_command(ctx, params );

        h |= result.update_hint();

        _console_widget->append (QString(params.original_string().c_str()) + "      // " + QString(result.message().c_str()));

        _undo_queue.pop_front();
    }

    // Eat blocks
    while (_undo_queue.size() > 0 && _undo_queue.front().count() == 0) {
        _undo_queue.pop_front();
    }

    updateWidgets(h);

    if (_undo_queue.size() == 0) {
        // Update Menu
        ui->_undo_action->setEnabled(false);
    }

    _console_widget->append ("// Undo Ends");
}

void EdLevelMainWindow::onCut()
{
    onUndoBlock();
    if (QMetaObject::invokeMethod( QApplication::focusWidget(), "cut", Qt::DirectConnection))
        return;

    onCommand("Cut");
}

void EdLevelMainWindow::onCopy()
{
    onUndoBlock();
    if (QMetaObject::invokeMethod( QApplication::focusWidget(), "copy", Qt::DirectConnection))
        return;

    onCommand("Copy");
}

void EdLevelMainWindow::onPaste()
{
    onUndoBlock();
    if (QMetaObject::invokeMethod( QApplication::focusWidget(), "paste", Qt::DirectConnection))
        return;

    onCommand("Paste");
}

void EdLevelMainWindow::onClear()
{
    onUndoBlock();

    if (QMetaObject::invokeMethod( QApplication::focusWidget(), "clear", Qt::DirectConnection))
        return;

    onCommand("Clear");
}

void EdLevelMainWindow::onSelectAll()
{
    onUndoBlock();
    onCommand("SelectAll");
}

void EdLevelMainWindow::onSelectNone()
{
    onUndoBlock();
    onCommand("SelectNone");
}

void EdLevelMainWindow::onDuplicate()
{
    onUndoBlock();
    onCommand("Duplicate");
}

void EdLevelMainWindow::onDuplicateHierarchy()
{
    onUndoBlock();
    onCommand("DuplicateHierarchy");
}

void EdLevelMainWindow::onGroup()
{
    onUndoBlock();
    onCommand("Group \"New Group\"");
}

void EdLevelMainWindow::onUngroup()
{
    onUndoBlock();
    onCommand("Ungroup");
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onSelectionChanged(const std::list<std::shared_ptr<PlugNode>> &selection_list)
{
    _document->setSelection(selection_list);

    // Update menus
    if (selection_list.size() == 1 && selection_list.front()->isa(ObjectBase::kind()) ) {
        ui->_component_menu->setDisabled(false);
    } else {
        ui->_component_menu->setDisabled(true);
    }


}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onDocumentModified()
{

}

void EdLevelMainWindow::onUpdateStatusBar()
{
    setWindowModified(true);
    onOpenRecent();
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onNodeContextMenu(std::shared_ptr<WorldNode> node, const QPointF &global_pos)
{

    // Context Menu
    QMenu *node_context_menu = new QMenu();
    QMenu *components = node_context_menu->addMenu("Add Component");

    std::map<std::string,std::set<std::string>> &component_types = component_map();

    FOR_EACH (i,component_types) {
        QMenu *menu = components->addMenu(i->first.c_str());

        std::set<std::string> &components = i->second;

        FOR_EACH (j, components) {
            QAction *add_component_action = new QAction(this);
            add_component_action->setVisible(true);
            add_component_action->setText(j->c_str());
            add_component_action->setData(j->c_str());
            add_component_action->setVisible(true);

            connect(add_component_action,   SIGNAL(triggered()),
                    this,                   SLOT(onCreateComponent()));

            menu->addAction(add_component_action);
        }

    }

    node_context_menu->exec(global_pos.toPoint());
}

void EdLevelMainWindow::onComponentContextMenu(std::shared_ptr<ComponentBase> component, const QPointF &global_pos)
{
    // Component contextual menu
    QAction *clear_action = new QAction(tr("Clear"), this);
    clear_action->setStatusTip(tr("Clear the component"));
    clear_action->setData(qVariantFromValue( (void*) component.get()));
    connect(clear_action, SIGNAL(triggered()), this, SLOT(onClearComponent()));

    QMenu *component_context_menu = new QMenu();
    component_context_menu->addAction(clear_action);

    component_context_menu->exec(global_pos.toPoint());
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::createActions()
{
    ui->_new_action->setShortcut(QKeySequence::New);

    ui->_open_action->setShortcut(QKeySequence::Open);
    connect(ui->_open_action, SIGNAL(triggered()), this, SLOT(onOpen()));

    ui->_save_level_action->setShortcut(QKeySequence::Save);
    connect(ui->_save_level_action, SIGNAL(triggered()), this, SLOT(onSaveLevel()));

    connect(ui->_save_level_as_action, SIGNAL(triggered()), this, SLOT(onSaveLevelAs()));

    connect(ui->_export_selection_action, SIGNAL(triggered()), this, SLOT(onExportSelection()));

    connect(ui->_import_selection_action, SIGNAL(triggered()), this, SLOT(onImportSelection()));

    connect(ui->_run_script_action, SIGNAL(triggered()), this, SLOT(onRunScript()));

    for (int i = 0; i < MaxRecentFiles; ++i) {
        _recent_file_actions[i] = new QAction(this);
        _recent_file_actions[i]->setVisible(false);
        connect(_recent_file_actions[i], SIGNAL(triggered()), this, SLOT(onOpenRecent()));
    }

    connect(ui->_exit_action, SIGNAL(triggered()), this, SLOT(close()));

    //
    // Edit menu
    //

    ui->_undo_action->setShortcut(QKeySequence::Undo);
    connect(ui->_undo_action, SIGNAL(triggered()), this, SLOT(onUndo()));

    ui->_cut_action->setShortcut(QKeySequence::Cut);
    connect(ui->_cut_action, SIGNAL(triggered()), this, SLOT(onCut()));

    ui->_copy_action->setShortcut(QKeySequence::Copy);
    connect(ui->_copy_action, SIGNAL(triggered()), this, SLOT(onCopy()));

    ui->_paste_action->setShortcut(QKeySequence::Paste);
    connect(ui->_paste_action, SIGNAL(triggered()), this, SLOT(onPaste()));

    connect(ui->_clear_action, SIGNAL(triggered()), this, SLOT(onClear()));

    ui->_select_all_action->setShortcut(QKeySequence::SelectAll);
    connect(ui->_select_all_action, SIGNAL(triggered()), this, SLOT(onSelectAll()));
    connect(ui->_select_none_action, SIGNAL(triggered()), this, SLOT(onSelectNone()));

    connect(ui->_duplicate_action, SIGNAL(triggered()), this, SLOT(onDuplicate()));
    connect(ui->_duplicate_hierarchy_action, SIGNAL(triggered()), this, SLOT(onDuplicateHierarchy()));

    connect(ui->_group_action, SIGNAL(triggered()), this, SLOT(onGroup()));
    connect(ui->_ungroup_action, SIGNAL(triggered()), this, SLOT(onUngroup()));




    //
    // About item
    //

    connect(ui->_about_action, SIGNAL(triggered()), this, SLOT(onAbout()));

    //
    // Level
    //

    connect(ui->_play_level_action, SIGNAL(triggered()), this, SLOT(onPlayLevel()));
    connect(ui->_play_options_action, SIGNAL(triggered()), this, SLOT(onPlayOptions()));

    //
    // Tools
    //

    connect(ui->_mesh_builder_action, SIGNAL(triggered()), this, SLOT(onMeshBuilder()));

    connect(ui->_package_builder_action, SIGNAL(triggered()), this, SLOT(onPackageBuilder()));
}

void EdLevelMainWindow::createMenus()
{

    //_file_menu->addAction(_new_action);
    QMenu *new_menu = ui->_new_menu;

    std::map<std::string,std::shared_ptr<CreatorBase>> &world_types = world_map();

    FOR_EACH (k,world_types) {
        QAction *add_world_action = new QAction(this);
        add_world_action->setVisible(true);
        add_world_action->setText(k->first.c_str());
        add_world_action->setData(k->first.c_str());
        add_world_action->setVisible(true);

        connect(add_world_action, SIGNAL(triggered()), this, SLOT(onCreateWorld()));

        new_menu->addAction(add_world_action);
    }

    for (int i = 0; i < MaxRecentFiles; ++i)
        ui->menuRecent_Files->addAction(_recent_file_actions[i]);

    // Object Menu
    std::map<std::string,std::set<std::string>> &placeable_types = placeable_map();

    FOR_EACH (i,placeable_types) {
        QMenu *menu = ui->_object_menu->addMenu(i->first.c_str());

        std::set<std::string> &placeable = i->second;

        FOR_EACH (j,placeable) {
            QAction *add_object_action = new QAction(this);
            add_object_action->setVisible(true);
            add_object_action->setText(j->c_str());
            add_object_action->setData(j->c_str());
            add_object_action->setVisible(true);

            connect(add_object_action, SIGNAL(triggered()), this, SLOT(onCreateObject()));

            menu->addAction(add_object_action);
        }

    }

    // Component Menu
    std::map<std::string,std::set<std::string>> &component_types = component_map();

    FOR_EACH (i,component_types) {
        QMenu *menu = ui->_component_menu->addMenu(i->first.c_str());

        std::set<std::string> &components = i->second;

        FOR_EACH (j,components) {
            QAction *add_component_action = new QAction(this);
            add_component_action->setVisible(true);
            add_component_action->setText(j->c_str());
            add_component_action->setData(j->c_str());
            add_component_action->setVisible(true);

            connect(add_component_action,SIGNAL(triggered()),
                    this,                   SLOT(onCreateComponent()));

            menu->addAction(add_component_action);
        }

    }

    // Script Menu
    std::map<std::string,std::set<std::string>> &script_types = script_map();

    for( const std::pair<std::string,std::set<std::string>> &i : script_types) {
        QMenu *menu = ui->_script_menu->addMenu(i.first.c_str());

        const std::set<std::string> &scripts = i.second;

        FOR_EACH (j,scripts) {
            QAction *add_script_action = new QAction(this);
            add_script_action->setVisible(true);
            add_script_action->setText(j->c_str());
            add_script_action->setData(j->c_str());
            add_script_action->setVisible(true);

            connect(add_script_action,   SIGNAL(triggered()), this, SLOT(onCreateScripts()));

            menu->addAction(add_script_action);
        }

    }
}

void EdLevelMainWindow::createContextMenu()
{
    this->addAction(ui->_cut_action);
    this->addAction(ui->_copy_action);
    this->addAction(ui->_paste_action);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::readSettings()
{
    QSettings settings("Smells Like Donkey Software Inc.", "Level Editor");

    restoreGeometry(settings.value("geometry").toByteArray());

    _recent_files = settings.value("recentfiles").toStringList();
    updateRecentFileActions();
}

void EdLevelMainWindow::writeSettings()
{
    QSettings settings("Smells Like Donkey Software Inc.", "Level Editor");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentfiles", _recent_files);
}

//==============================================================================
//==============================================================================

bool EdLevelMainWindow::isOkToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Level Editor"),
                        tr("The document has been modified.\n"
                           "Do you want to On_Save_Level your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return onSaveLevel();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void EdLevelMainWindow::loadObject(std::shared_ptr<BaseClass> obj)
{
    // Wait for a world object and store it.
    if (obj && obj->isa(World::kind())) {
        std::shared_ptr<World> world = checked_static_cast<World>(obj);
        _document->setWorld(world);
    }
}

bool EdLevelMainWindow::loadLevel(const QString &filename)
{
    // Load the world using the specialized "world loading" routines so the document pointer can be set immediately

    // Set up a callback to filter the objects. We need to wait for a world object (probably the first one)
    // so that it can be set in the document immediately. Otherwise the system callbacks won't work.
    std::shared_ptr<Callback<std::shared_ptr<BaseClass>>> cb = make_callback(this, &EdLevelMainWindow::loadObject);

    std::shared_ptr<BaseClass> obj = Factory::create_object_from_stream(FilePath(filename.toUtf8().data()), NULL, cb);

    std::shared_ptr<World> world = _document->world();

    if (world) {
        world->set_streamable(true);
        _undo_queue.clear();

    } else {

        QMessageBox::warning(this, tr("Level Editor"),
            tr("Error loading file. Perhaps you need a new build of the editor?"),
            QMessageBox::Cancel);

    }

    updateWidgets(CommandResult::UPDATE_ALL);

    setCurrentLevelFile(filename);

    return true;
}

bool EdLevelMainWindow::saveLevel(const QString &filename)
{
    FilePath temp_file("{APPDIR}/temp.lvl");

    std::shared_ptr<ArchiveTextWriter> writer = ArchiveTextWriter::create();
    writer->open(FilePath(temp_file));
    ArchiveObjectQueue::queue_out_tree(writer, _document->world() );
    writer->close();

    HAL::delete_file(FilePath(filename.toUtf8().data()));
    HAL::move_file(temp_file,FilePath(filename.toUtf8().data()));

    setCurrentLevelFile(filename);

    //statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void EdLevelMainWindow::autosave(void)
{
    std::shared_ptr<ArchiveTextWriter> writer = ArchiveTextWriter::create();
    writer->open(FilePath("{APPDIR}/autosave.lvl"));
    ArchiveObjectQueue::queue_out_tree(writer, _document->world() );
    writer->close();
}

void EdLevelMainWindow::setCurrentLevelFile(const QString &filename)
{
    _current_level_file = filename;

    setWindowTitle(tr("%1 (%2)")
        .arg( strippedName(_current_level_file.isEmpty() ? "Untitled" : _current_level_file) )
        .arg( _document->world()->class_id_child() )
    );
}

void EdLevelMainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(_recent_files);
    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < _recent_files.count()) {
            QString text = tr("&%1 %2")
                           .arg(j + 1)
                           .arg(strippedName(_recent_files[j]));
            _recent_file_actions[j]->setText(text);
            _recent_file_actions[j]->setData(_recent_files[j]);
            _recent_file_actions[j]->setVisible(true);
        } else {
            _recent_file_actions[j]->setVisible(false);
        }
    }
    ui->menuRecent_Files->setVisible(!_recent_files.isEmpty());
}

QString EdLevelMainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

QString EdLevelMainWindow::strippedDir(const QString &fullFileName)
{
    return QFileInfo(fullFileName).dir().path();
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onPlayLevel(void)
{
    autosave();

    // Level info
    std::string path = Globals::substitute_global("{ED_GAME_PATH}");
    std::string level_path = Globals::substitute_global("{APPDIR}/autosave.lvl");

    // Resolution info
    DTboolean resolution_enabled = MoreStrings::cast_from_string<DTboolean>(Globals::global("ED_RESOLUTION_ENABLED"));
    std::string resolution_width = Globals::global("ED_RESOLUTION_WIDTH");
    std::string resolution_height = Globals::global("ED_RESOLUTION_HEIGHT");

    std::vector<std::string> args;
    args.push_back("-loadlevel");
    args.push_back(level_path);

    if (resolution_enabled) {
        args.push_back("-resolution");
        args.push_back(resolution_width + "x" + resolution_height);
    }

    HAL::run_on_command_line(path, args);
}

void EdLevelMainWindow::onPlayOptions(void)
{
    EdLevelLaunchDialog dialog;
    dialog.exec();
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onMeshBuilder (void)
{
    EdLevelMeshBuilder dialog;
    dialog.exec();
}

void EdLevelMainWindow::onPackageBuilder (void)
{

}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::onAppFocusChanged(QWidget* old, QWidget* now)
{
    if(old == NULL) {
        //Focus regained..This is foreground app now
        FileManager::scan_files();

        SystemCallbacks::reload_resources_cb().fire();

        //emit doRefreshResources();
        //emit doRefreshLibrary();

        update();

    } else if(now == NULL) {
        //Focus lost. This is background app now.
    }

}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::addNodeCB (World *world, WorldNode *node)
{
    if (_document->world().get() != world)
        return;

    emit doAddNode(node);
}

void EdLevelMainWindow::removeNodeCB (World *world, WorldNode *node)
{
    if (_document->world().get() != world)
        return;

    emit doRemoveNode(node);
}

void EdLevelMainWindow::reparentNodeCB (World *world, WorldNode *node, WorldNode *old_parent, WorldNode *new_parent)
{
    if (_document->world().get() != world)
        return;

    emit doReparentNode(node,old_parent,new_parent);
}

void EdLevelMainWindow::addGroupCB (World *world,Group *group)
{
    if (_document->world().get() != world)
        return;

    emit doAddGroup(group);
}

void EdLevelMainWindow::removeGroupCB (World *world, Group *group)
{
    if (_document->world().get() != world)
        return;

    emit doRemoveGroup(group);
}

void EdLevelMainWindow::addComponentCB (World *world, ComponentBase *component)
{
    if (_document->world().get() != world)
        return;

    emit doAddComponent(component);
}

void EdLevelMainWindow::removeComponentCB (World *world, ComponentBase *component)
{
    if (_document->world().get() != world)
        return;

    emit doRemoveComponent(component);
}

void EdLevelMainWindow::connectPlugCB (PlugBase *outgoing, PlugBase *incoming)
{
    emit doConnectPlug (outgoing, incoming);
}

void EdLevelMainWindow::disconnectPlugCB (PlugBase *outgoing, PlugBase *incoming)
{
    emit doDisconnectPlug (outgoing, incoming);
}

void EdLevelMainWindow::connectEventCB (Event *outgoing, Event *incoming)
{
    emit doConnectEvent (outgoing, incoming);
}

void EdLevelMainWindow::disconnectEventCB (Event *outgoing, Event *incoming)
{
    emit doDisconnectEvent (outgoing, incoming);
}

//==============================================================================
//==============================================================================

void EdLevelMainWindow::showAssert (const DTcharacter* file, const DTcharacter* func, const DTint line)
{
    static std::list<ErrorEntry> errors;

    ErrorEntry error_entry(file,func,line);
    if (std::find(errors.begin(), errors.end(), error_entry) == errors.end()) {

        int r = QMessageBox::critical(this, tr("Assertion"),
                    QString("Assertion in file ") + file + QString(" in function ") + func + QString(" on line ") + QString::number(line),
                    QMessageBox::Abort | QMessageBox::Ignore | QMessageBox::Ok);

        if (r == QMessageBox::Abort) {
            exit(1);
        } else if (r == QMessageBox::Ignore) {
            errors.push_back(error_entry);
        } else if (r == QMessageBox::Ok) {
            // Do nothing
        }

    }
}

void EdLevelMainWindow::showError (const DTcharacter* file, const DTcharacter* func, const DTint line, const DTcharacter* msg)
{
    static std::list<ErrorEntry> errors;

    ErrorEntry error_entry(file,func,line);
    if (std::find(errors.begin(), errors.end(), error_entry) == errors.end()) {

        int r = QMessageBox::critical(this, tr("Error"),
                    QString("Error ") + msg + QString(" in file ") + file + QString(" in function ") + func + QString(" on line ") + QString::number(line),
                    QMessageBox::Abort | QMessageBox::Ignore | QMessageBox::Ok);

        if (r == QMessageBox::Abort) {
            exit(1);
        } else if (r == QMessageBox::Ignore) {
            errors.push_back(error_entry);
        } else if (r == QMessageBox::Ok) {
            // Do nothing
        }

    }
}

void EdLevelMainWindow::showWarning (const DTcharacter* file, const DTcharacter* func, const DTint line, const DTcharacter* msg)
{
    static std::list<ErrorEntry> errors;

    ErrorEntry error_entry(file,func,line);
    if (std::find(errors.begin(), errors.end(), error_entry) == errors.end()) {

        int r = QMessageBox::warning(this, tr("Warning"),
                    QString("Warning ") + msg + QString(" in file ") + file + QString(" in function ") + func + QString(" on line ") + QString::number(line),
                    QMessageBox::Abort | QMessageBox::Ignore | QMessageBox::Ok);

        if (r == QMessageBox::Abort) {
            exit(1);
        } else if (r == QMessageBox::Ignore) {
            errors.push_back(error_entry);
        } else if (r == QMessageBox::Ok) {
            // Do nothing
        }
    }
}

void EdLevelMainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
//==============================================================================
//==============================================================================

