/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/protocol/http_message.hpp"

//External Includes

//System Namespaces
using std::string;

//Project Namespaces

//External Namespaces
using corvusoft::core::Bytes;

namespace corvusoft
{
    namespace protocol
    {
        HTTPMessage::HTTPMessage( void ) : Message( )
        {
            return;
        }
        
        HTTPMessage::~HTTPMessage( void )
        {
            return;
        }
        
        bool HTTPMessage::is_finalised( void ) const
        {
        
        }
        
        bool HTTPMessage::is_malformed( void ) const
        {
        
        }
        
        Bytes HTTPMessage::to_bytes( void ) const
        {
        
        }
        
        void HTTPMessage::assemble( const Bytes& data )
        {
        
        }
        
        Bytes HTTPMessage::get( const string& name ) const
        {
        
        }
        
        void HTTPMessage::set( const string& name, const Bytes& value )
        {
        
        }
    }
}
