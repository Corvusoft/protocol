/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/protocol/http_frame.hpp"

//External Includes

//System Namespaces
using std::string;
using std::multimap;

//Project Namespaces

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

namespace corvusoft
{
    namespace protocol
    {
        HTTPFrame::HTTPFrame( void ) : Frame( )
        {
            return;
        }
        
        HTTPFrame::~HTTPFrame( void )
        {
            return;
        }
        
        bool HTTPFrame::is_request( void ) const
        {
            return meta.count( "method" )
                   and meta.count( "path" )
                   and meta.count( "version" )
                   and meta.count( "protocol" )
                   and not meta.count( "status" )
                   and not meta.count( "message" );
        }
        
        bool HTTPFrame::is_response( void ) const
        {
            return meta.count( "status" )
                   and meta.count( "version" )
                   and meta.count( "protocol" )
                   and not meta.count( "path" )
                   and not meta.count( "method" );
        }
        
        Bytes HTTPFrame::get_body( void ) const
        {
            auto iterator = data.find( "body" );
            if ( iterator == end( data ) ) return { };
            
            return iterator->second;
        }
        
        Bytes HTTPFrame::get_path( void ) const
        {
            auto iterator = meta.find( "path" );
            if ( iterator == end( meta ) ) return { };
            
            return iterator->second;
        }
        
        Bytes HTTPFrame::get_method( void ) const
        {
            auto iterator = meta.find( "method" );
            if ( iterator == end( meta ) ) return { };
            
            return iterator->second;
        }
        
        Bytes HTTPFrame::get_version( void ) const
        {
            auto iterator = meta.find( "version" );
            if ( iterator == end( meta ) ) return { };
            
            return iterator->second;
        }
        
        Bytes HTTPFrame::get_protocol( void ) const
        {
            auto iterator = meta.find( "protocol" );
            if ( iterator == end( meta ) ) return { };
            
            return iterator->second;
        }
        
        Bytes HTTPFrame::get_status_code( void ) const
        {
            auto iterator = meta.find( "status" );
            if ( iterator == end( meta ) ) return { };
            
            return iterator->second;
        }
        
        Bytes HTTPFrame::get_status_message( void ) const
        {
            auto iterator = meta.find( "message" );
            if ( iterator == end( meta ) ) return { };
            
            return iterator->second;
        }
        
        multimap< string, Bytes > HTTPFrame::get_headers( void ) const
        {
            multimap< string, Bytes > headers;
            
            for ( const auto value : meta )
                if ( value.first not_eq "method" and value.first not_eq "path" and value.first not_eq "protocol" and
                        value.first not_eq "version" and value.first not_eq "status" and value.first not_eq "message" )
                    headers.emplace( value.first, value.second );
                    
            return headers;
        }
        
        void HTTPFrame::set_body( const Bytes& value )
        {
            auto iterator = data.find( "body" );
            if ( iterator == end( data ) )
                data.emplace( "body", value );
            else
                iterator->second = value;
        }
        
        void HTTPFrame::set_body( const string& value )
        {
            set_body( make_bytes( value ) );
        }
        
        void HTTPFrame::set_path( const string& value )
        {
            auto iterator = meta.find( "path" );
            if ( iterator == end( meta ) )
                meta.emplace( "path", make_bytes( value ) );
            else
                iterator->second = make_bytes( value );
        }
        
        void HTTPFrame::set_method( const string& value )
        {
            auto iterator = meta.find( "method" );
            if ( iterator == end( meta ) )
                meta.emplace( "method", make_bytes( value ) );
            else
                iterator->second = make_bytes( value );
        }
        
        void HTTPFrame::set_version( const string& value )
        {
            auto iterator = meta.find( "version" );
            if ( iterator == end( meta ) )
                meta.emplace( "version", make_bytes( value ) );
            else
                iterator->second = make_bytes( value );
        }
        
        void HTTPFrame::set_protocol( const string& value )
        {
            auto iterator = meta.find( "protocol" );
            if ( iterator == end( meta ) )
                meta.emplace( "protocol", make_bytes( value ) );
            else
                iterator->second = make_bytes( value );
        }
        
        void HTTPFrame::set_status_code( const string& value )
        {
            auto iterator = meta.find( "status" );
            if ( iterator == end( meta ) )
                meta.emplace( "status", make_bytes( value ) );
            else
                iterator->second = make_bytes( value );
        }
        
        void HTTPFrame::set_status_message( const string& value )
        {
            auto iterator = meta.find( "message" );
            if ( iterator == end( meta ) )
                meta.emplace( "message", make_bytes( value ) );
            else
                iterator->second = make_bytes( value );
        }
        
        void HTTPFrame::set_header( const string& name, const string& value )
        {
            meta.emplace( name, make_bytes( value ) );
        }
    }
}
