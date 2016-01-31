//==============================================================================
///	
///	File: ScriptingDelayOff.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Scripting/ScriptingDelayOff.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/Profiler.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveData.hpp"
#include "DT3Core/Types/FileBuffer/Archive.hpp"
#include "DT3Core/World/World.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_SCRIPT(ScriptingDelayOff,"Timers",NULL)
IMPLEMENT_PLUG_NODE(ScriptingDelayOff)

IMPLEMENT_PLUG_INFO_INDEX(_in)
IMPLEMENT_PLUG_INFO_INDEX(_out)
		
//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ScriptingDelayOff)

	PLUG_INIT(_in,"In")
		.set_input(true)
		.affects(PLUG_INFO_INDEX(_out));

	PLUG_INIT(_out,"Out")
		.set_output(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ScriptingDelayOff::ScriptingDelayOff (void)
    :   _time		(0.0F),
		_in			(PLUG_INFO_INDEX(_in), false),
		_delay		(1.0F),
		_out		(PLUG_INFO_INDEX(_out), false)
{  

}
		
ScriptingDelayOff::ScriptingDelayOff (const ScriptingDelayOff &rhs)
    :   ScriptingBase	(rhs),
		_time			(rhs._time),
		_in				(rhs._in),
		_delay			(rhs._delay),
		_out			(rhs._out)
{   

}

ScriptingDelayOff & ScriptingDelayOff::operator = (const ScriptingDelayOff &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ScriptingBase::operator = (rhs);

		_time = rhs._time;
		_in = rhs._in;
		_delay = rhs._delay;
		_out = rhs._out;
	 }
    return (*this);
}
			
ScriptingDelayOff::~ScriptingDelayOff (void)
{

}

//==============================================================================
//==============================================================================

void ScriptingDelayOff::archive (const std::shared_ptr<Archive> &archive)
{
    ScriptingBase::archive(archive);

	archive->push_domain (class_id ());
	
    *archive << ARCHIVE_DATA(_time, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_in, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_DATA(_delay, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_out, DATA_PERSISTENT);
	        					
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

void ScriptingDelayOff::tick (const DTfloat dt)
{
	PROFILER(SCRIPTING);

    _time += dt;
		
    if (_in) {
        _time = 0.0F;
        _out = true;
    } else {
        if (_time >= _delay)	_out = false;
        else					_out = true;
    }
}

//==============================================================================
//==============================================================================

void ScriptingDelayOff::add_to_world(World *world)
{
    ScriptingBase::add_to_world(world);
    
    world->register_for_tick(this, make_callback(this, &type::tick));
}

void ScriptingDelayOff::remove_from_world (void)
{
    world()->unregister_for_tick(this, make_callback(this, &type::tick));

    ScriptingBase::remove_from_world();
}

//==============================================================================
//==============================================================================

} // DT3

