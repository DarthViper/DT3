#pragma once
//==============================================================================
///
///    File: PlugNode.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseClass.hpp"
#include <string>
#include <mutex>
#include <list>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class Event;
class EventInfo;
class PlugInfo;
class EventInfo;

//==============================================================================
/// Class
//==============================================================================

// Class kind structure. Used for various class information
struct DTnodekind {
    DTnodekind(DTnodekind *super_class, void (*fn)(DTnodekind *)) {
        _plugs = (super_class ? super_class->_plugs : NULL);    // initialize with nodes from super class
        _events = (super_class ? super_class->_events : NULL);    // initialize with nodes from super class
        fn(this);
    }

    PlugInfo    *_plugs;
    EventInfo   *_events;
};

#define DEFINE_PLUG_NODE                                                                            \
    inline static DTnodekind*    plug_info_static    (void) {                                        \
        static DTnodekind plug_info(super_type::plug_info_static(), &type::initialize_plugs);       \
        return &plug_info;                                                                            \
    }                                                                                                \
    virtual DTnodekind*            plug_info_child     (void) const override {                          \
        return plug_info_static();                                                                  \
    }                                                                                                \
    DTnodekind*                    plug_info           (void) const {                                    \
        return plug_info_static();                                                                  \
    }                                                                                               \
    static void                 initialize_plugs    (DTnodekind *plug_node_info);

#define DEFINE_PLUG_NODE_BASE                                                       \
    inline static DTnodekind*    plug_info_static    (void) {                        \
        static DTnodekind plug_info(NULL, &type::initialize_plugs);                 \
        return &plug_info;                                                          \
    }                                                                               \
    virtual DTnodekind*            plug_info_child     (void) const {                  \
        return plug_info_static();                                                  \
    }                                                                               \
    DTnodekind*                    plug_info           (void) const {                  \
        return plug_info_static();                                                  \
    }                                                                               \
    static void                 initialize_plugs    (DTnodekind *plug_node_info);



#define IMPLEMENT_PLUG_NODE(Class)                                                  \
    namespace {                                                                     \
        struct registration_node_class##Class: public StaticInitializerCallback {   \
            void initialize() {                                                     \
                Class::plug_info_static();                                          \
            }                                                                       \
        } registration_node_obj##Class;                                             \
    }

#define BEGIN_IMPLEMENT_PLUGS(Class)                                                \
    void Class::initialize_plugs (DTnodekind *plug_node_info) {

#define END_IMPLEMENT_PLUGS                                                         \
    }

//==============================================================================
/// Forward declarations
//==============================================================================

class PlugBase;

//==============================================================================
/// Class
//==============================================================================

class PlugNode: public BaseClass {
    public:
        DEFINE_TYPE(PlugNode,BaseClass)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE_BASE

                                        PlugNode                    (void);
                                        PlugNode                    (const PlugNode &rhs);
        PlugNode &                        operator =                  (const PlugNode &rhs);
        virtual                            ~PlugNode                   (void);

        virtual void                    archive                     (const std::shared_ptr<Archive> &archive)  override;
        virtual void                    archive_done                (const std::shared_ptr<Archive> &archive)  override;

    public:
        DEFINE_ACCESSORS_REF(name, set_name, std::string, _name)

        virtual std::string             full_name                           (void) const;
        virtual std::string             preferred_name                      (void) const;
        PlugBase*                        plug_by_name                        (const std::string &name);
        void                            all_plugs                           (std::list<PlugBase*> &plugs);
        Event*                          event_by_name                       (const std::string &name);
        void                            all_events                          (std::list<Event*> &events);
        virtual bool                    compute                             (const PlugBase *plug);
        void                            disconnect_all_plugs                (void);
        void                            disconnect_all_events               (void);

        virtual void                    outgoing_plug_was_disconnected      (PlugBase *outgoing, PlugBase *incoming);
        virtual void                    outgoing_plug_was_attached          (PlugBase *outgoing, PlugBase *incoming);
        virtual void                    incoming_plug_was_disconnected      (PlugBase *outgoing, PlugBase *incoming);
        virtual void                    incoming_plug_was_attached          (PlugBase *outgoing, PlugBase *incoming);
        virtual void                    outgoing_event_was_disconnected     (Event *outgoing, Event *incoming);
        virtual void                    outgoing_event_was_attached         (Event *outgoing, Event *incoming);
        virtual void                    incoming_event_was_disconnected     (Event *outgoing, Event *incoming);
        virtual void                    incoming_event_was_attached         (Event *outgoing, Event *incoming);
        /// Returns a mutex for computing this plug
        /// \return mutex
        std::recursive_mutex&           lock                                (void)  {   return _lock;   }
        /// This is a known plug pointer that is created for use in the unit tests for testing the compute
        /// chain. It doesn't get actually used anywhere.
        /// \return standard pointer
        static PlugBase*                test_compute_chain_plug             (void)  {   return reinterpret_cast<PlugBase*>(0xFFFFFFFF); }

    private:
        std::string                     _name;
        mutable std::recursive_mutex    _lock;

};

//==============================================================================
//==============================================================================

class PlugIter {
    public:
                                    PlugIter                    (PlugNode* o)   {    _node = o;    _info = _node->plug_info_child()->_plugs;    }

    private:
                                    PlugIter                    (const PlugIter &rhs);
        PlugIter &                    operator =                    (const PlugIter &rhs);

    public:
        virtual                        ~PlugIter                    (void)            {}

        // Increment the iterator to the next item
        PlugIter&            operator ++                    (void);

        // Return the current item
        PlugBase*            operator ->                    (void) const;
        PlugBase*            operator ()                    (void) const;

        // Returns non-zero value if the iterator is valid
        inline                         operator const void *        (void) const    {    return (void*) (_info != NULL);    }

    private:
        PlugInfo        *_info;
        PlugNode        *_node;
};


//==============================================================================
//==============================================================================

class EventIter {
    public:
                                    EventIter                    (PlugNode *o)   {    _node = o;    _info = _node->plug_info_child()->_events;    }

    private:
                                    EventIter                    (const EventIter &rhs);
        EventIter &                    operator =                    (const EventIter &rhs);

    public:
        virtual                        ~EventIter                    (void) = default;

        // Increment the iterator to the next item
        EventIter&            operator ++                    (void);

        // Return the current item
        Event*               operator ->                    (void) const;
        Event*               operator ()                    (void) const;

        // Returns non-zero value if the iterator is valid
        inline                         operator const void *        (void) const    {    return (void*) (_info != NULL);    }

    private:
        EventInfo       *_info;
        PlugNode        *_node;
};
//==============================================================================
//==============================================================================

} // DT3
