#pragma once
#ifndef DT3_NETWORKSOCKET
#define DT3_NETWORKSOCKET
//==============================================================================
///
///    File: NetworkSocket.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseClass.hpp"
#include <vector>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Class
//==============================================================================

class NetworkSocket: public BaseClass {
    public:
        DEFINE_TYPE(NetworkSocket,BaseClass)
        DEFINE_CREATE_AND_CLONE

                                NetworkSocket                (void);
                                NetworkSocket                (const uint8_t *socket_structure, uint32_t length);
                                NetworkSocket                (const NetworkSocket &rhs);
                                NetworkSocket                (NetworkSocket &&rhs);
        NetworkSocket &            operator =                    (const NetworkSocket &rhs);
        NetworkSocket &            operator =                    (NetworkSocket &&rhs);
                                ~NetworkSocket                (void);

    public:

        /// Raw socket structure data
        /// \param socket_structure pointer to socket structure data
        /// \param length length of socket structure data
        void                    set_network_socket_data        (const uint8_t *socket_structure, uint32_t length);

        /// Returns raw socket structure data
        /// \return socket structure data
        uint8_t*                network_socket_data         (void) const                {    return (uint8_t*) &_data[0];        }

        /// Returns raw socket structure data length
        /// \return socket structure data length
        DTsize                  network_socket_length       (void) const                {    return _data.size();                }

        /// Clear socket structure data
        void                    clear                        (void)                        {    _data.clear();                        }

        /// Checks if the socket structure address is empty or not
        /// \return Socket is empty
        bool                is_empty                    (void) const                {    return _data.size() == 0;            }

    private:
        friend int operator == (const NetworkSocket& a, const NetworkSocket& b);
        friend int operator != (const NetworkSocket& a, const NetworkSocket& b);
        friend int operator < (const NetworkSocket& a, const NetworkSocket& b);

        std::vector<uint8_t>    _data;
};

//==============================================================================
//==============================================================================

inline int operator == (const NetworkSocket& a, const NetworkSocket& b)
{
    return (a._data == b._data);
}

inline int operator != (const NetworkSocket& a, const NetworkSocket& b)
{
    return (a._data != b._data);
}

inline int operator < (const NetworkSocket& a, const NetworkSocket& b)
{
    return (a._data < b._data);
}

//==============================================================================
//==============================================================================

} // DT3

#endif
