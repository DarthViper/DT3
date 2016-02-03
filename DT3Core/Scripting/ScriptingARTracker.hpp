#pragma once
//==============================================================================
///
///	File: ScriptingARTracker.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Scripting/ScriptingBase.hpp"
#include "DT3Core/Types/Utility/TimerHires.hpp"
#include "DT3Core/Types/Math/Matrix4.hpp"
#include "DT3Core/Types/Math/Vector3.hpp"
#include "DT3Core/Types/Node/Event.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Base object for the different placeable types of objects in the engine.
//==============================================================================

class ScriptingARTracker: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingARTracker,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingARTracker      (void);
                                    ScriptingARTracker      (const ScriptingARTracker &rhs);
        ScriptingARTracker &        operator =              (const ScriptingARTracker &rhs);
        virtual                     ~ScriptingARTracker     (void);

        virtual void                archive                 (const std::shared_ptr<Archive> &archive);

        /// Object was added to a world
        /// world world that object was added to
        virtual void                add_to_world            (World *world);

        /// Object was removed from a world
        virtual void                remove_from_world       (void);

    public:
        /// Called in gyro callback
        void                        gyro                    (const Vector3 &w);

        /// Called in accelerometer callback
        void                        accelerometer           (const Vector3 &a);

        /// Called in magnetometer callback
        void                        magnetometer            (const Vector3 &m);

        /// Registered with world to tick this node
        /// \param dt delta time
        void                        tick                    (const DTfloat dt);

        /// Starts the auto calibration
        void                        begin_auto_calibration  (PlugNode *sender);

    private:
        Event                       _begin_auto_calibration;

        TimerHires                  _gyro_sample_timer;
        Matrix3                     _gyro_orientation;

        Vector3                     _accelerometer;
        Vector3                     _magnetometer;

        Plug<Matrix3>               _orientation;

        DTfloat                     _correction_mix_factor;

        enum {
            CORRECTION_NONE = 0,
            CORRECTION_ACCELEROMETER = 1,
            CORRECTION_ACCELEROMETER_AND_MAGNETOMETER = 2
        };

        int32_t                       _correction_mode;

        // Calibration state
        Plug<bool>             _is_calibrating;
        Plug<bool>             _is_calibrated;

        // For tracking when calibration is complete
        uint32_t                      _calibration_directions;

        // Best set of calibration samples
        Vector3                     _calibration_samples[6];
        int32_t                       _num_calibration_samples;

        // Calibrated magnetometer offset
        Vector3                     _calibration;


        bool                   append_calibration_sample   (const Vector3 &m);
        bool                   process_calibration_samples (void);
};

//==============================================================================
//==============================================================================

} // DT3
