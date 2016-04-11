#pragma once
#ifndef DT3_WAVWRITER
#define DT3_WAVWRITER
//==============================================================================
///
///    File: WAVWriter.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include <fstream>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class FilePath;

//==============================================================================
/// Class
//==============================================================================

class WAVWriter {
    public:
                                WAVWriter            (void);
                                WAVWriter            (const WAVWriter &rhs);
        WAVWriter &             operator =            (const WAVWriter &rhs);
                                ~WAVWriter            (void);

    public:
        /// Open a blank sound file
        /// \param pathname Path of file to write
        /// \param num_channels number of channels in the file
        /// \param sample_rate sample rate of sound data
        /// \param bits_per_sample number of bits per sample
        /// \return error
        DTerr                   begin_write         (   const FilePath &pathname,
                                                        uint16_t num_channels = 2,
                                                        int32_t sample_rate = 44100,
                                                        uint16_t bits_per_sample = 16);

        /// Write some sound data
        /// \param pointer to raw sound data
        /// \param size of raw sound data
        /// \return error
        DTerr                   write               (uint8_t *data, uint32_t size);

        /// Finish writing sound file
        /// \return error
        DTerr                   end_write           (void);

    private:
        struct ChunkHeader {
            DTcharacter    id[4];
            uint32_t        length;
        };

        enum FORMAT_TAG {
            FMT_WAVE_FORMAT_PCM        = 0x0001
        };

        //
        // Format chunk
        //

        struct Format {
            uint16_t    formatTag;            // Format category
            uint16_t    channels;            // Number of channels
            uint32_t        samplesPerSec;        // Sampling rate
            uint32_t        avgBytesPerSec;        // For buffer estimation
            uint16_t    blockAlign;            // Data block size
            uint16_t    bitsPerSample;
        };

        void                    write                (std::ofstream &outfile, uint8_t &v);
        void                    write                (std::ofstream &outfile, uint16_t &v);
        void                    write                (std::ofstream &outfile, int16_t &v);
        void                    write                (std::ofstream &outfile, int32_t &v);
        void                    write                (std::ofstream &outfile, uint32_t &v);
        void                    write                (std::ofstream &outfile, DTcharacter id[4]);
        void                    write                (std::ofstream &outfile, ChunkHeader &v);
        void                    set_type            (DTcharacter id[4], const DTcharacter *id_str);

        std::ofstream           _outfile;
        uint32_t                  _header_length_offset;
        uint32_t                  _data_length_offset;
        uint32_t                  _data_size;


};

//==============================================================================
//==============================================================================

} // DT3

#endif
