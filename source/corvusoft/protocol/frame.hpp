/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_FRAME_H
#define _CORVUSOFT_PROTOCOL_FRAME_H 1

//System Includes
#include <map>
#include <string>

//Project Includes

//External Includes
#include <corvusoft/core/byte.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace protocol
    {
        //Forward Declarations
        
        struct Frame
        {
            virtual ~Frame( void ) = default;
            
            std::multimap< std::string, core::Bytes > meta;
            
            std::multimap< std::string, core::Bytes > data;
        };
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_FRAME_H */
