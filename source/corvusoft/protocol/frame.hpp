/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

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
            Frame( void ) : meta( ),
                data( )
            {
                return;
            }

            virtual ~Frame( void ) = default;
            
            std::multimap< std::string, core::Bytes > meta;
            
            std::multimap< std::string, core::Bytes > data;
        };
    }
}
