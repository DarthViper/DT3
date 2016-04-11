//==============================================================================
///    
///    File: PlugNode.cpp
///    
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///    
//==============================================================================

#include "DT3Core/Types/Node/PlugNode.hpp"
#include "DT3Core/Types/Node/Plug.hpp"
#include "DT3Core/Types/Node/Event.hpp"
#include "DT3Core/Types/Node/EventInfo.hpp"
#include "DT3Core/Types/Node/PlugInfo.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/SystemCallbacks.hpp"
#include "DT3Core/Types/FileBuffer/Archive.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveData.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveProcessPlugs.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveProcessEvents.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION(PlugNode)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(PlugNode)


END_IMPLEMENT_PLUGS
}
using namespace DT3;
//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

PlugNode::PlugNode (void)
    :   _name                    ("Unnamed")
{  

}
        
PlugNode::PlugNode (const PlugNode &rhs)
    :   BaseClass                (rhs),
        _name                    (rhs._name)
{   

}

PlugNode & PlugNode::operator = (const PlugNode &rhs)
{
    BaseClass::operator = (rhs);

    _name = rhs._name;
    return (*this);
}
            
PlugNode::~PlugNode (void)
{

}

//==============================================================================
//==============================================================================

void PlugNode::archive (const std::shared_ptr<Archive> &archive)
{
    BaseClass::archive(archive);

    archive->push_domain (class_id ());
    
    *archive << ARCHIVE_DATA(_name, DATA_PERSISTENT | DATA_SETTABLE);

    if (archive->is_reading()) {
    
        DTsize num_plugs = 0;
        *archive << ARCHIVE_DATA(num_plugs, DATA_PERSISTENT);
        
        // Read in a bunch of plugs
        for (DTsize i = 0; i < num_plugs; ++i) {
            archive->add_post_process(ARCHIVE_PROCESS_PLUGS(archive, (PlugBase*) NULL));    // NULL because the plug will be searched for later
        }
        
        DTsize num_events = 0;
        *archive << ARCHIVE_DATA(num_events, DATA_PERSISTENT);
        
        // Read in a bunch of plugs
        for (DTsize i = 0; i < num_events; ++i) {
            archive->add_post_process(ARCHIVE_PROCESS_EVENTS(archive, (Event*) NULL));    // NULL because the plug will be searched for later
        }
        
    } else {
        
        // Count the number of plugs that are connected
        DTsize num_plugs = 0;
        
        for (PlugIter iter(this); iter; ++iter) {
            if (iter()->incoming_connection())
                ++num_plugs;
        }

        // Write out the plugs
        *archive << ARCHIVE_DATA(num_plugs, DATA_PERSISTENT);

        for (PlugIter iter(this); iter; ++iter) {
            if (iter()->incoming_connection())
                archive->add_post_process(ARCHIVE_PROCESS_PLUGS(archive, iter()));
        }

        // Count the number of plugs that are connected
        DTsize num_events = 0;
        
        for (EventIter iter(this); iter; ++iter) {
            if (iter()->incoming_connections().size() > 0)
                ++num_events;
        }

        // Write out the events
        *archive << ARCHIVE_DATA(num_events, DATA_PERSISTENT);

        for (EventIter iter(this); iter; ++iter) {
            if (iter()->incoming_connections().size() > 0)
                archive->add_post_process(ARCHIVE_PROCESS_EVENTS(archive, iter()));
        }
    
    }
    
    archive->pop_domain ();
}

void PlugNode::archive_done (const std::shared_ptr<Archive> &archive)
{
    BaseClass::archive_done(archive);

    if (archive->is_writing())
        return;

    for (PlugIter iter(this); iter; ++iter) {
        iter->set_dirty();
    }
}

//==============================================================================
//==============================================================================

/// Returns the full name of object that uniquely identifies it
/// \return full name of object
std::string PlugNode::full_name (void) const
{
    std::unique_lock<std::recursive_mutex> lock(_lock);

    return name();
}

/// Returns the preferred name of the object for when it is created
/// \return preferred name of object
std::string PlugNode::preferred_name (void) const
{
    std::unique_lock<std::recursive_mutex> lock(_lock);

    return class_id_child();
}

//==============================================================================
//==============================================================================

/// Returns a plug with matching name
/// \return matching plug
PlugBase* PlugNode::plug_by_name (const std::string &name)
{    
    std::unique_lock<std::recursive_mutex> lock(_lock);

    for (PlugIter iter(this); iter; ++iter) {
        if (iter->name() == name)
            return iter();
    }
    
    return NULL;
}

/// Builds a list of all of the plugs
/// \param plugs all plugs in the node
void PlugNode::all_plugs (std::list<PlugBase*> &plugs)
{
    std::unique_lock<std::recursive_mutex> lock(_lock);

    plugs.clear();
    
    for (PlugIter iter(this); iter; ++iter) {
        plugs.push_front(iter());
    }
}

//==============================================================================
//==============================================================================

/// Returns an event with matching name
/// \return matching event
Event* PlugNode::event_by_name (const std::string &name)
{    
    std::unique_lock<std::recursive_mutex> lock(_lock);

    for (EventIter iter(this); iter; ++iter) {
        if (iter->name() == name)
            return iter();
    }
    
    return NULL;
}

/// Builds a list of all of the events
/// \param events all events in the node
void PlugNode::all_events (std::list<Event*> &events)
{
    std::unique_lock<std::recursive_mutex> lock(_lock);

    events.clear();
    
    for (EventIter iter(this); iter; ++iter) {
        events.push_front(iter());
    }
}

//==============================================================================
//==============================================================================

/// Disconnect all of the plugs
void PlugNode::disconnect_all_plugs    (void)
{
    std::unique_lock<std::recursive_mutex> lock(_lock);

    // Remove incoming and outgoing connections on all plugs
    for (PlugIter iter(this); iter; ++iter) {
        iter()->remove_incoming_connection();
        iter()->remove_outgoing_connections();
    }
}

//==============================================================================
//==============================================================================

/// Disconnect all of the events
void PlugNode::disconnect_all_events    (void)
{
    std::unique_lock<std::recursive_mutex> lock(_lock);

    // Remove incoming and outgoing connections on all events
    for (EventIter iter(this); iter; ++iter) {
        iter()->remove_incoming_connections();
        iter()->remove_outgoing_connections();
    }
}

//==============================================================================
//==============================================================================

/// Called when an outgoing plug is disconnected
/// \param outgoing outgoing plug
/// \param incoming other incoming plug
void PlugNode::outgoing_plug_was_disconnected (PlugBase *outgoing, PlugBase *incoming)
{
    SystemCallbacks::disconnect_plug_cb().fire(outgoing, incoming);
}

/// Called when an outgoing plug is attached
/// \param outgoing outgoing plug
/// \param incoming other incoming plug
void PlugNode::outgoing_plug_was_attached (PlugBase *outgoing, PlugBase *incoming)
{
    SystemCallbacks::connect_plug_cb().fire(outgoing,incoming);
}

/// Called when an incoming plug is disconnected
/// \param outgoing other outgoing plug
/// \param incoming incoming plug
void PlugNode::incoming_plug_was_disconnected (PlugBase *outgoing, PlugBase *incoming)
{
    // Messages sent by outgoing plugs above
    //callDisconnectPlugCB (outgoing, incoming);
}

/// Called when an outgoing plug is attached
/// \param outgoing other outgoing plug
/// \param incoming incoming plug
void PlugNode::incoming_plug_was_attached (PlugBase *outgoing, PlugBase *incoming)
{
    // Messages sent by outgoing plugs above
    //callConnectPlugCB (outgoing, incoming);
}


/// Called when an outgoing event is disconnected
/// \param outgoing outgoing event
/// \param incoming other incoming event
void PlugNode::outgoing_event_was_disconnected (Event *outgoing, Event *incoming)
{
    SystemCallbacks::disconnect_event_cb().fire(outgoing, incoming);
}

/// Called when an outgoing event is attached
/// \param outgoing outgoing event
/// \param incoming other incoming event
void PlugNode::outgoing_event_was_attached (Event *outgoing, Event *incoming)
{
    SystemCallbacks::connect_event_cb().fire(outgoing,incoming);
}

/// Called when an incoming event is disconnected
/// \param outgoing other outgoing event
/// \param incoming incoming event
void PlugNode::incoming_event_was_disconnected (Event *outgoing, Event *incoming)
{
    // Messages sent by outgoing events above
    //getDisconnectEventCB().fire(outgoing, incoming);
}

/// Called when an outgoing event is attached
/// \param outgoing other outgoing event
/// \param incoming incoming event
void PlugNode::incoming_event_was_attached (Event *outgoing, Event *incoming)
{
    // Messages sent by outgoing events above
    //getConnectEventCB().fire(outgoing,incoming);
}

//==============================================================================
//==============================================================================

/// Compute function called when a plug value needs to be calculated
/// \param plug plug to compute
/// \return Compute successful
bool PlugNode::compute (const PlugBase *plug)
{
    if (plug == test_compute_chain_plug())
        return true;
    
    return false;
}

//==============================================================================
//==============================================================================

EventIter &EventIter::operator ++()            {    _info = _info->next_info(); return *this;    }
Event *EventIter::operator ->() const    {    return _info->node_to_event(_node);    }
Event *EventIter::operator ()() const    {    return _info->node_to_event(_node);    }

PlugIter &PlugIter::operator ++()            {    _info = _info->next_info(); return *this;    }

PlugBase *PlugIter::operator ->() const    {    return _info->node_to_plug(_node);    }

PlugBase *PlugIter::operator ()() const    {    return _info->node_to_plug(_node);    }
