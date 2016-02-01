#pragma once
//==============================================================================
///
///	File: EdLevelMainWindow.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
#include "EdLevelLineEdit.hpp"

// Qt include
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTextEdit>
#include <QtCore/QTimer>
#include <QtCore/QProcess>

// Engine includes
#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/Utility/CommandParams.hpp"
#include <list>
#include <memory>

namespace Ui {
class EdLevelMainWindow;
}
//==============================================================================
/// Forward declarations
//==============================================================================

namespace DT3 {
    class PlugNode;
    class ComponentBase;
    class World;
    class WorldNode;
    class Group;
    class BaseClass;
    class PlugBase;
    class Event;
}

class QAction;
class QLabel;
class QGLWidget;
class QListView;
class QComboBox;
class WorldWindow;
class EdLevelScriptWindow;
class EdLevelAnimationWindow;
class EdLevelSoundWindow;
class EdLevelSoundFXWindow;
class EdLevelConsoleWindow;
class EdLevelResourcesWindow;
class EdLevelLibraryWindow;
class EdLevelPerformanceWindow;
class EdLevelPropertiesWindow;
class EdLevelHierarchyWindow;
class EdLevelDocument;

//==============================================================================
//==============================================================================

using namespace DT3;

//==============================================================================
/// Class
//==============================================================================

class EdLevelMainWindow : public QMainWindow
{
    Q_OBJECT
    friend class QApplication; // allow access to onAppFocusChanged slot
    public:
        EdLevelMainWindow(void);
        ~EdLevelMainWindow(void);

        void                                    timerEvent          (QTimerEvent *event);
        void                                    setSaveIcon         (bool icon_state);

    protected:
        void									closeEvent(QCloseEvent *event);

    private:
        // Create GUI
        void 									createActions();
        void 									createMenus();
        void 									createContextMenu();

        // Read and Write prefs
        void 									readSettings();
        void 									writeSettings();

        // Loading and saving data
        bool 									isOkToContinue();

        void                                    loadObject(std::shared_ptr<BaseClass> obj);
        bool 									loadLevel(const QString &filename);

        bool 									saveLevel(const QString &filename);
        void                                    autosave(void);

        // File management
        void 									setCurrentLevelFile(const QString &filename);
        void 									updateRecentFileActions();
        QString 								strippedName(const QString &fullFileName);
        QString 								strippedDir(const QString &fullFileName);

        void                                    updateWidgets (unsigned int h);

        // GUI Widgets
        WorldWindow						*_world_widget;
        EdLevelScriptWindow						*_script_widget;
        EdLevelAnimationWindow                  *_animation_widget;
        EdLevelSoundWindow                      *_sound_widget;
        EdLevelConsoleWindow					*_console_widget;
        EdLevelResourcesWindow                  *_resources_widget;
        EdLevelLibraryWindow                    *_library_widget;
        EdLevelPerformanceWindow				*_performance_widget;
        EdLevelPropertiesWindow                 *_properties_widget;
        EdLevelHierarchyWindow                  *_hierarchy_widget;

        QString									_current_level_file;
        QStringList								_recent_files;

        QBasicTimer                             _timer;
        QBasicTimer                             _autosave_timer;

        static const int MaxRecentFiles = 5;
        QAction *								_recent_file_actions[MaxRecentFiles];

        QToolBar *								_world_toolbar;
        QToolBar *								_script_toolbar;
        QToolBar *								_animation_toolbar;
        QToolBar *								_sound_toolbar;
        QToolBar *								_sound_fx_toolbar;
        QToolBar *								_console_toolbar;
        QToolBar *								_resources_toolbar;
        QToolBar *								_library_toolbar;
        QToolBar *								_hierarchy_toolbar;
        QToolBar *								_performance_toolbar;


        // Undo Queue
        std::list<CommandParams>                _undo_queue;

        // Document
        EdLevelDocument                         *_document;
        Ui::EdLevelMainWindow *                 ui;

        // Error handlers
        struct ErrorEntry {
            ErrorEntry (const char* file, const char* func, const int line)
                :   _file(file),
                    _func(func),
                    _line(line)
            {}

            bool operator == (const ErrorEntry &rhs) {
                return ( (_file == rhs._file) && (_func == rhs._func) && (_line == rhs._line) );
            }

            const char* _file;
            const char* _func;
            const int _line;
        };

        void                                    showAssert  (const char* file, const char* func, const int line);
        void                                    showError   (const char* file, const char* func, const int line, const char*);
        void                                    showWarning (const char* file, const char* func, const int line, const char *);

    //==========================================================================
    // Callbacks
    //==========================================================================

        void                                    addNodeCB               (World *world, WorldNode *node);
        void                                    removeNodeCB            (World *world, WorldNode *node);
        void                                    reparentNodeCB          (World *world, WorldNode *node, WorldNode *old_parent, WorldNode *new_parent);

        void                                    addGroupCB              (World *world, Group *group);
        void                                    removeGroupCB           (World *world, Group *group);

        void                                    addComponentCB          (World *world, ComponentBase *component);
        void                                    removeComponentCB       (World *world, ComponentBase *component);

        void                                    connectPlugCB           (PlugBase *outgoing, PlugBase *incoming);
        void                                    disconnectPlugCB        (PlugBase *outgoing, PlugBase *incoming);
        void                                    connectEventCB          (Event *outgoing, Event *incoming);
        void                                    disconnectEventCB       (Event *outgoing, Event *incoming);

    //==========================================================================
    /// Qt Signals and slots
    //==========================================================================
    private slots:
        void									onOpen();
        bool									onSaveLevel();
        bool									onSaveLevelAs();
        bool									onExportSelection();
        void									onImportSelection();
        void									onRunScript();
        void									onAbout();
        void									onOpenRecent();

        void                                    onUndo();
        void                                    onCut();
        void                                    onCopy();
        void                                    onPaste();
        void                                    onClear();
        void                                    onSelectAll();
        void                                    onSelectNone();
        void                                    onDuplicate();
        void                                    onDuplicateHierarchy();
        void                                    onGroup();
        void                                    onUngroup();

        void 									onDocumentModified();
        void									onUpdateStatusBar();
        void                                    onUpdateMenus();

        void									onCreateObject();
        void									onCreateComponent();
        void                                    onClearComponent (void);

        void									onCreateScripts();
        void									onCreateWorld();

        bool                                    onCommand(QString command);
        void                                    onUndoBlock();

        void                                    onSelectionChanged(const std::list<std::shared_ptr<PlugNode>> &selection_list);

        void                                    onNodeContextMenu(std::shared_ptr<WorldNode> node, const QPointF &global_pos);
        void                                    onComponentContextMenu(std::shared_ptr<ComponentBase> component, const QPointF &global_pos);

        void                                    onPlayLevel                 (void);
        void                                    onPlayOptions               (void);

        void                                    onMeshBuilder               (void);
        void                                    onPackageBuilder            (void);
        void                                    onAppFocusChanged           (QWidget* old, QWidget* now);

    signals:
        void                                    doAddNode(WorldNode *node);
        void                                    doRemoveNode(WorldNode *node);
        void                                    doReparentNode(WorldNode *node, WorldNode *old_parent, WorldNode *new_parent);

        void                                    doAddGroup(Group *group);
        void                                    doRemoveGroup(Group *group);

        void                                    doAddComponent(ComponentBase *node);
        void                                    doRemoveComponent(ComponentBase *node);

        void                                    doConnectPlug (PlugBase *outgoing, PlugBase *incoming);
        void                                    doDisconnectPlug (PlugBase *outgoing, PlugBase *incoming);
        void                                    doConnectEvent (Event *outgoing, Event *incoming);
        void                                    doDisconnectEvent (Event *outgoing, Event *incoming);

        void                                    doRefreshScript();
        void                                    doRefreshWorld();
        void                                    doRefreshHierarchy();
        void                                    doRefreshProperties();
        void                                    doRefreshLibrary();
        void                                    doRefreshResources();
        void                                    doRefreshAnimation();
        void                                    doRefreshConsole();
        void                                    doRefreshPerformance();
        void                                    doRefreshSound();
        void                                    doRefreshSoundFX();

        void                                    doSelectionChanged(const std::list<std::shared_ptr<PlugNode>> &selection_list);
    protected:
        void                                    changeEvent(QEvent *e);
};

//==============================================================================
//==============================================================================
