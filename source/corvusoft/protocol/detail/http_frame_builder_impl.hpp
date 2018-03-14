/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_DETAIL_HTTP_FRAME_BUILDER_IMPL_H
#define _CORVUSOFT_PROTOCOL_DETAIL_HTTP_FRAME_BUILDER_IMPL_H 1

//System Includes
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include <iterator>
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
            static const auto FIELD_DELIMITER = core::make_bytes( "\r\n" );
            static const auto FIELD_DELIMITER_BEGIN = std::begin( FIELD_DELIMITER );
            static const auto FIELD_DELIMITER_END = std::end( FIELD_DELIMITER );
            
            static const auto BODY_DELIMITER = core::make_bytes( "\r\n\r\n" );
            static const auto BODY_DELIMITER_BEGIN = std::begin( BODY_DELIMITER );
            static const auto BODY_DELIMITER_END = std::end( BODY_DELIMITER );
            
            struct HTTPFrameBuilderImpl
            {
                core::Bytes data { };
                
                std::shared_ptr< Frame > frame = nullptr;
                
                bool is_malformed = false;
                
                bool is_finalised = false;
                
                void assemble( void )
                {
                    is_malformed = false;
                    is_finalised = false;
                    
                    finalise( );
                    if ( not is_finalised ) return;
                    
                    auto values = tokenise( );
                    if ( values.empty( ) ) return;
                    
                    frame = std::make_shared< Frame >( );
                    if ( is_request( values.at( 0 ) ) ) return parse_request( values );
                    if ( is_response( values.at( 0 ) ) ) return parse_response( values );
                    
                    is_malformed = true;
                }
                
                void finalise( void )
                {
                    auto iterator = std::search( data.begin( ), data.end( ), BODY_DELIMITER_BEGIN, BODY_DELIMITER_END );
                    is_finalised = iterator not_eq data.end( );
                }
                
                std::vector< const std::string > tokenise( void )
                {
                    static const auto delimiter_length = FIELD_DELIMITER.size( );
                    
                    auto iterator_begin = data.begin( );
                    auto iterator_end = std::search( data.begin( ), data.end( ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    std::vector< const std::string > values;
                    
                    while ( iterator_end not_eq data.end( ) )
                    {
                        auto value = core::Bytes( iterator_begin, iterator_end );
                        if ( value.empty( ) or value == FIELD_DELIMITER ) break;
                        
                        values.emplace_back( core::make_string( value ) );
                        
                        iterator_begin = iterator_end + delimiter_length;
                        iterator_end = std::search( iterator_begin, data.end( ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    }
                    
                    is_malformed = values.empty( );
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
                    const auto value = values.at( 0 );
                    auto start = value.begin( );
                    auto stop = std::find( start, value.end( ), ' ' );
                    is_malformed = stop == value.end( );
                    if ( is_malformed ) return;
                    frame->meta.emplace( "method", core::Bytes( start, stop ) );
                    
                    start = ++stop;
                    stop = std::find( start, value.end( ), ' ' );
                    is_malformed = stop == value.end( );
                    if ( is_malformed ) return;
                    frame->meta.emplace( "path", core::Bytes( start, stop ) );
                    
                    start = ++stop;
                    stop = std::find( start, value.end( ), '/' );
                    is_malformed = stop == value.end( );
                    if ( is_malformed ) return;
                    frame->meta.emplace( "protocol", core::Bytes( start, stop ) );
                    
                    start = ++stop;
                    is_malformed = ( start == value.end( ) or stop == value.end( ) );
                    if ( is_malformed ) return;
                    frame->meta.emplace( "version", core::Bytes( start, value.end( ) ) );
                    
                    parse_headers( values );
                    parse_body( );
                }
                
                void parse_response( const std::vector< const std::string >& values )
                {
                    const auto value = values.at( 0 );
                    auto start = value.begin( );
                    auto stop = std::find( start, value.end( ), '/' );
                    is_malformed = stop == value.end( );
                    if ( is_malformed ) return;
                    frame->meta.emplace( "protocol", core::Bytes( start, stop ) );
                    
                    start = ++stop;
                    stop = std::find( start, value.end( ), ' ' );
                    is_malformed = stop == value.end( );
                    if ( is_malformed ) return;
                    frame->meta.emplace( "version", core::Bytes( start, stop ) );
                    
                    start = ++stop;
                    is_malformed = start == value.end( );
                    if ( is_malformed ) return;
                    stop = std::find( start, value.end( ), ' ' );
                    frame->meta.emplace( "status", core::Bytes( start, stop ) );
                    
                    if ( stop not_eq value.end( ) )
                        frame->meta.emplace( "message", core::Bytes( ++stop, value.end( ) ) );
                        
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
                    static const auto delimiter_length = BODY_DELIMITER.size( );
                    auto iterator = std::search( data.begin( ), data.end( ), BODY_DELIMITER_BEGIN, BODY_DELIMITER_END );
                    frame->data.emplace( "body", core::Bytes( iterator + delimiter_length, data.end( ) ) );
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
                    data.insert( data.end( ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    
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
                    
                    iterator = frame->meta.find( "message" );
                    if ( iterator not_eq frame->meta.end( ) )
                    {
                        data.emplace_back( ' ' );
                        data.insert( data.end( ), iterator->second.begin( ), iterator->second.end( ) );
                    }
                    data.insert( data.end( ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    
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
                            data.insert( data.end( ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                        }
                    }
                }
                
                void compose_body( void )
                {
                    data.insert( data.end( ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    
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
