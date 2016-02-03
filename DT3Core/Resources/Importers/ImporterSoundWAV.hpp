#pragma once
#ifndef DT3_IMPORTERSOUNDWAV
#define DT3_IMPORTERSOUNDWAV
//==============================================================================
///
///	File: ImporterSoundWAV.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Resources/Importers/ImporterSound.hpp"
#include "DT3Core/Types/FileBuffer/FilePath.hpp"
#include "DT3Core/Types/FileBuffer/BinaryFileStream.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================


//==============================================================================
/// Class
//==============================================================================

class ImporterSoundWAV: public ImporterSound {
    public:
        DEFINE_TYPE(ImporterSoundWAV,ImporterSound)
        DEFINE_CREATE

                                        ImporterSoundWAV		(void);

    private:
                                        ImporterSoundWAV		(const ImporterSoundWAV &rhs);
        ImporterSoundWAV &              operator =				(const ImporterSoundWAV &rhs);

    public:
        virtual							~ImporterSoundWAV       (void);

    public:
        /// Imports a sound into an SoundResource
        /// \param target object to import sound into
        /// \param args arguments to importer
        /// \return error code
        virtual DTerr					import					(SoundResource *target, std::string args);

        /// Loads sound data from the file
        /// \param data pointer to buffer
        /// \param start start of sound data (doesn't include header)
        /// \param length length of sound data in bytes
        virtual DTsize					stream					(uint8_t *data, DTsize start, DTsize length);

        /// Returns length of sound data
        /// \return length of sound data in bytes
        virtual DTsize					length                  (void);

    private:

        struct ChunkHeader {
            DTcharacter	id[4];
            uint32_t		length;
        };

        bool						is_type					(DTcharacter id[4], const DTcharacter *id_str);

        void							read					(BinaryFileStream &infile, uint8_t &v);
        void							read					(BinaryFileStream &infile, uint16_t &v);
        void							read					(BinaryFileStream &infile, int16_t &v);
        void							read					(BinaryFileStream &infile, int32_t &v);
        void							read					(BinaryFileStream &infile, uint32_t &v);
        void							read					(BinaryFileStream &infile, DTcharacter id[4]);
        void							read					(BinaryFileStream &infile, ChunkHeader &v);


        enum FORMAT_TAG {
            FMT_WAVE_FORMAT_PCM		= 0x0001,
            FMT_FORMAT_MULAW		= 0x0101,
            FMT_IBM_FORMAT_ALAW		= 0x0102,
            FMT_IBM_FORMAT_ADPCM	= 0x0103
        };

        //
        // Format chunk
        //

        // WAVE_FORMAT_PCM
        struct WaveFormatPCM{
            uint16_t            _bits_per_sample;
        };

        // FORMAT_MULAW
        struct FormatMuLAW{
        };

        // IBM_FORMAT_ALAW
        struct IBMFormatALAW{
        };

        // IBM_FORMAT_ADPCM
        struct IBMFormatADPCM{
        };

        struct Format {
            uint16_t            _format_tag;			// Format category
            uint16_t            _channels;              // Number of channels
            uint32_t              _samples_per_sec;		// Sampling rate
            uint32_t              _avg_bytes_per_sec;		// For buffer estimation
            uint16_t            _block_align;			// Data block size

            union {
                WaveFormatPCM	_wave_format_PCM;
                FormatMuLAW		_format_MuLAW;
                IBMFormatALAW	_ibm_format_ALAW;
                IBMFormatADPCM	_ibm_format_ADPCM;
            };

        } _format;

        FilePath                _pathname;
        BinaryFileStream        _infile;

        DTsize                  _data_start;
        DTsize                  _data_length;


        uint8_t                 *_preloaded_chunk;
        DTsize                  _preloaded_chunk_size;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
