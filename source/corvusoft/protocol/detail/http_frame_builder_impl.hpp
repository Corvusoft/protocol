/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_DETAIL_HTTP_FRAME_BUILDER_IMPL_H
#define _CORVUSOFT_PROTOCOL_DETAIL_HTTP_FRAME_BUILDER_IMPL_H 1

//System Includes
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

//Project Includes
#include "corvusoft/protocol/frame.hpp"

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
        
        namespace detail
        {
            //Forward Declarations
            
            struct HTTPFrameBuilderImpl
            {
                core::Bytes data { };
                
                std::shared_ptr< Frame > frame = nullptr;
                
                bool is_malformed = false; //indactes the data supplied contained invalid content as specified by the protocol semantics.
                
                bool is_finalised = false; //indicates sufficient data was supplied to the builder to create a protocol frame. //give HTTP example in docs.
                
                void assemble( void )
                {
                    is_malformed = false;
                    is_finalised = false;
                    
                    finalise( );
                    if ( not is_finalised ) return;
                    
                    frame = std::make_shared< Frame >( );
                    
                    auto values = tokenise( );
                    if ( is_request( values.at( 0 ) ) ) return parse_request( values );
                    if ( is_response( values.at( 0 ) ) ) return parse_response( values );
                    
                    is_malformed = true;
                }
                
                void finalise( void )
                {
                    static const auto delimiter = core::Bytes{ '\r', '\n', '\r', '\n' };
                    is_finalised = std::includes( data.begin( ), data.end( ), delimiter.begin( ), delimiter.end( ) );
                }
                
                std::vector< const std::string > tokenise( void )
                {
                    static const auto delimiter = core::Bytes { '\r', '\n' };
                    static const auto delimiter_length = delimiter.size( );
                    
                    auto iterator_begin = data.begin( );
                    auto iterator_end = std::search( data.begin( ), data.end( ), delimiter.begin( ), delimiter.end( ) );
                    std::vector< const std::string > values;
                    
                    while ( iterator_end not_eq data.end( ) )
                    {
                        auto value = core::make_string( core::Bytes( iterator_begin, iterator_end ) );
                        if ( value.empty( ) or value == "\r\n" ) break;
                        
                        values.emplace_back( value );
                        
                        iterator_begin = iterator_end + delimiter_length;
                        iterator_end = std::search( iterator_begin, data.end( ), delimiter.begin( ), delimiter.end( ) );
                    }
                    
                    return values;
                }
                
                static bool is_request( const std::string& value )
                {
                    static const std::regex pattern( "^[a-z]+\\s+.+\\s+HTTP\\/[0-9]+\\.[0-9]+$", std::regex::icase );
                    return std::regex_match( value, pattern );
                }
                
                static bool is_response( const std::string& value )
                {
                    static const std::regex pattern( "^HTTP\\/[0-9]+\\.[0-9]+\\s+[0-9]+(?:\\s+.*){0,1}$", std::regex::icase );
                    return std::regex_match( value, pattern );
                }
                
                void parse_request( const std::vector< const std::string >& values )
                {
                    const std::string value = values.at( 0 );
                    std::string::size_type start = 0;
                    std::string::size_type stop = value.find_first_of( ' ' );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->meta.emplace( "method", core::make_bytes( value.substr( start, stop ) ) );
                    
                    start = ++stop;
                    stop = value.find_first_of( ' ', start );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->meta.emplace( "path", core::make_bytes( value.substr( start, stop ) ) );
                    
                    start = ++stop;
                    stop = value.find_first_of( '/', start );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->meta.emplace( "protocol", core::make_bytes( value.substr( start, stop ) ) );
                    
                    start = ++stop;
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->meta.emplace( "version", core::make_bytes( value.substr( start, stop ) ) );
                    
                    parse_headers( values );
                    parse_body( );
                }
                
                void parse_response( const std::vector< const std::string >& values )
                {
                    const std::string value = values.at( 0 );
                    std::string::size_type start = 0;
                    std::string::size_type stop = value.find_first_of( '/' );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->meta.emplace( "protocol", core::make_bytes( value.substr( start, stop ) ) );
                    
                    start = ++stop;
                    stop = value.find_first_of( ' ', start );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->meta.emplace( "version", core::make_bytes( value.substr( start, stop - start ) ) );
                    
                    start = ++stop;
                    stop = value.find_first_of( ' ', start );
                    if ( stop == std::string::npos ) stop = value.length( );
                    frame->meta.emplace( "status", core::make_bytes( value.substr( start, stop - start ) ) );
                    
                    if ( stop not_eq value.length( ) )
                        frame->meta.emplace( "message", core::make_bytes( value.substr( ++stop ) ) );
                        
                    parse_headers( values );
                    parse_body( );
                }
                
                void parse_headers( const std::vector< const std::string >& values )
                {
                    std::string::size_type stop = 0;
                    const auto length = values.size( );
                    for ( std::string::size_type index = 1; index not_eq length; index++ )
                    {
                        const auto value = values.at( index );
                        stop = value.find_first_of( ':' );
                        
                        is_malformed = stop == std::string::npos;
                        if ( is_malformed ) return;
                        
                        const auto header_name = value.substr( 0, stop );
                        auto header_value = value.substr( stop + 1 );
                        if ( not header_value.empty( ) and header_value.at( 0 ) == ' ' ) header_value.erase( 0, 1 );
                        
                        frame->meta.emplace( header_name, core::make_bytes( header_value ) );
                    }
                }
                
                void parse_body( void )
                {
                    static const auto delimiter = core::Bytes{ '\r', '\n', '\r', '\n' };
                    auto iterator = std::search( data.begin( ), data.end( ), delimiter.begin( ), delimiter.end( ) );
                    frame->data.emplace( "body", core::Bytes( iterator, data.end( ) ) );
                }
                
                void disassemble( void )
                {
                    is_malformed = true;
                    is_finalised = false;
                    if ( frame == nullptr ) return;
                    
                    data.clear( );
                    
                    if ( frame->meta.count( "method" ) ) return compose_request( );
                    if ( frame->meta.count( "status" ) ) return compose_response( );
                }
                
                void compose_request( void )
                {
                    auto iterator = frame->meta.find( "method" );
                    if ( iterator == frame->meta.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    data.emplace_back( ' ' );
                    
                    iterator = frame->meta.find( "path" );
                    if ( iterator == frame->meta.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    data.emplace_back( ' ' );
                    
                    iterator = frame->meta.find( "protocol" );
                    if ( iterator == frame->meta.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    data.emplace_back( '/' );
                    
                    iterator = frame->meta.find( "version" );
                    if ( iterator == frame->meta.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                    
                    compose_headers( );
                    compose_body( );
                    
                    is_malformed = false;
                    is_finalised = true;
                }
                
                void compose_response( void )
                {
                    auto iterator = frame->meta.find( "protocol" );
                    if ( iterator == frame->meta.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    data.emplace_back( '/' );
                    
                    iterator = frame->meta.find( "version" );
                    if ( iterator == frame->meta.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    data.emplace_back( ' ' );
                    
                    iterator = frame->meta.find( "status" );
                    if ( iterator == frame->meta.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    data.emplace_back( ' ' );
                    
                    iterator = frame->meta.find( "message" );
                    if ( iterator == frame->meta.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                    
                    compose_headers( );
                    compose_body( );
                    
                    is_malformed = false;
                    is_finalised = true;
                }
                
                void compose_headers( void )
                {
                    for ( const auto meta : frame->meta )
                    {
                        if ( is_header( meta.first ) )
                        {
                            auto header = core::make_bytes( meta.first + ": " );
                            header.insert( header.end( ), meta.second.begin( ), meta.second.end( ) );
                            data.insert( data.end( ), header.begin( ), header.end( ) );
                        }
                    }
                }
                
                void compose_body( void )
                {
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                    
                    auto iterator = frame->data.find( "body" );
                    if ( iterator == frame->data.end( ) ) return;
                    data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                }
                
                bool is_header( const std::string& name )
                {
                    return not ( name == "method" or name == "path" or name == "protocol" or name == "version" or name == "status" or name == "message" );
                }
            };
        }
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_DETAIL_HTTP_FRAME_BUILDER_IMPL_H */
