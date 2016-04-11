#pragma once
//==============================================================================
///
///	File: BaseClass.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include <memory>
#include <atomic>
#include <cassert>
//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class Archive;

//==============================================================================
/// Class
//==============================================================================

class BaseClass: public std::enable_shared_from_this<BaseClass> {
    public:
        DEFINE_TYPE_BASE(BaseClass)

                                    BaseClass                       (void);
                                    BaseClass                       (const BaseClass &rhs);
                                    virtual ~BaseClass                      ()   {}
        BaseClass &					operator =                      (const BaseClass &rhs);

        virtual void                archive                         (const std::shared_ptr<Archive> &archive);
        virtual void                archive_done                    (const std::shared_ptr<Archive> &UNUSED(archive))  {}
        virtual std::shared_ptr<BaseClass>   clone(void) const      { assert(false); return nullptr; }
    public:

        //
        // Archiving
        //

        /// Returns the unique ID for this object. The object ID is guaranteed to be unique per
        /// execution of the applcation.
        /// \return unique ID
        inline uint32_t				unique_id                       (void) const			{   return _unique_id;					}

        /// Forces the object to get a new unique ID
        void						new_unique_id                   (void);

        /// Sets whether the object will be streamed or not
        /// \param streamable object is streamable
        void						set_streamable                  (bool streamable)	{	_streamable = streamable;			}

        /// Returns whether the object will be streamed or not
        /// \return streamable
        bool					streamable                      (void) const			{	return _streamable;					}

    private:
        static std::atomic<uint32_t>  _unique_id_counter;
        uint32_t						_unique_id;
        bool					_streamable;
};

//==============================================================================
//==============================================================================


} // DT3
