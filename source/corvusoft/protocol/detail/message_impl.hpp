/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_DETAIL_MESSAGE_IMPL_H
#define _CORVUSOFT_PROTOCOL_DETAIL_MESSAGE_IMPL_H 1

//System Includes
#include <set>
#include <map>
#include <string>

//Project Includes

//External Includes
#include "corvusoft/core/byte.hpp"

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace protocol
    {
        //Forward Declarations
        
        namespace detail
        {
            //Forward Declarations
            
            struct MessageImpl
            {
                std::set< const std::string > names { };
                
                std::map< const std::string, core::Bytes > properties { };
            };
        }
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_DETAIL_MESSAGE_IMPL_H */
