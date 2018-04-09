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
#include "corvusoft/protocol/http_frame.hpp"

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
                
                std::shared_ptr< HTTPFrame > frame = nullptr;
                
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
                    
                    frame = std::make_shared< HTTPFrame >( );
                    if ( is_request( values.at( 0 ) ) ) return parse_request( values );
                    if ( is_response( values.at( 0 ) ) ) return parse_response( values );
                    
                    is_malformed = true;
                }
                
                void finalise( void )
                {
                    auto iterator = std::search( std::begin( data ), std::end( data ), BODY_DELIMITER_BEGIN, BODY_DELIMITER_END );
                    is_finalised = iterator not_eq std::end( data );
                }
                
                std::vector< const std::string > tokenise( void )
                {
                    static const auto delimiter_length = FIELD_DELIMITER.size( );
                    
                    auto iterator_begin = std::begin( data );
                    auto iterator_end = std::search( std::begin( data ), std::end( data ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    std::vector< const std::string > values;
                    
                    while ( iterator_end not_eq std::end( data ) )
                    {
                        auto value = core::Bytes( iterator_begin, iterator_end );
                        if ( value.empty( ) or value == FIELD_DELIMITER ) break;
                        
                        values.emplace_back( core::make_string( value ) );
                        
                        iterator_begin = iterator_end + delimiter_length;
                        iterator_end = std::search( iterator_begin, std::end( data ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
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
                    size_t start = 0;
                    size_t stop = value.find( ' ' );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->set_method( value.substr( start, stop ) );
                    
                    start = stop + 1;
                    stop = value.find( ' ', start );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->set_path( value.substr( start, stop - start ) );
                    
                    start = stop + 1;
                    stop = value.find( '/', start );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->set_protocol( value.substr( start, stop - start ) );
                    
                    start = stop + 1;
                    is_malformed = ( start == std::string::npos or stop == std::string::npos );
                    if ( is_malformed ) return;
                    frame->set_version( value.substr( start, std::string::npos ) );
                    
                    parse_headers( values );
                    parse_body( );
                }
                
                void parse_response( const std::vector< const std::string >& values )
                {
                    const auto value = values.at( 0 );
                    size_t start = 0;
                    size_t stop = value.find( '/' );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->set_protocol( value.substr( start, stop ) );
                    
                    start = stop + 1;
                    stop = value.find( ' ', start );
                    is_malformed = stop == std::string::npos;
                    if ( is_malformed ) return;
                    frame->set_version( value.substr( start, stop - start ) );
                    
                    start = stop + 1;
                    stop = value.find( ' ', start );
                    is_malformed = start == std::string::npos;
                    if ( is_malformed ) return;
                    frame->set_status_code( value.substr( start, stop - start ) );
                    
                    if ( stop not_eq std::string::npos )
                        frame->set_status_message( value.substr( ++stop, std::string::npos ) );
                        
                    parse_headers( values );
                    parse_body( );
                }
                
                void parse_headers( const std::vector< const std::string >& values )
                {
                    std::string::size_type stop = 0;
                    const auto length = values.size( );
                    for ( std::string::size_type index = 1; index not_eq length; index++ )
                    {
                        auto value = values.at( index );
                        stop = value.find( ':' );
                        
                        is_malformed = stop == std::string::npos;
                        if ( is_malformed ) return;
                        
                        auto name = value.substr( 0, stop );
                        is_malformed = name.empty( );
                        if ( is_malformed ) return;
                        
                        value = value.substr( stop + 1 );
                        if ( value.at( 0 ) == ' ' ) value.erase( 0, 1 );
                        
                        frame->set_header( name, value );
                    }
                }
                
                void parse_body( void )
                {
                    static const auto delimiter_length = BODY_DELIMITER.size( );
                    auto iterator = std::search( std::begin( data ), std::end( data ), BODY_DELIMITER_BEGIN, BODY_DELIMITER_END );
                    frame->set_body( core::Bytes( iterator + delimiter_length, std::end( data ) ) );
                }
                
                void disassemble( void )
                {
                    is_malformed = true;
                    is_finalised = false;
                    if ( frame == nullptr ) return;
                    
                    data.clear( );
                    
                    if ( frame->is_request( ) ) return compose_request( );
                    if ( frame->is_response( ) ) return compose_response( );
                }
                
                void compose_request( void )
                {
                    auto value = frame->get_method( );
                    data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                    data.emplace_back( ' ' );
                    
                    value = frame->get_path( );
                    data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                    data.emplace_back( ' ' );
                    
                    value = frame->get_protocol( );
                    data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                    data.emplace_back( '/' );
                    
                    value = frame->get_version( );
                    data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                    data.insert( std::end( data ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    
                    compose_headers( );
                    compose_body( );
                    
                    is_malformed = false;
                    is_finalised = true;
                }
                
                void compose_response( void )
                {
                    auto value = frame->get_protocol( );
                    data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                    data.emplace_back( '/' );
                    
                    value = frame->get_version( );
                    data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                    data.emplace_back( ' ' );
                    
                    value = frame->get_status_code( );
                    data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                    
                    value = frame->get_status_message( );
                    if ( not value.empty( ) )
                    {
                        data.emplace_back( ' ' );
                        data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                    }
                    data.insert( std::end( data ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    
                    compose_headers( );
                    compose_body( );
                    
                    is_malformed = false;
                    is_finalised = true;
                }
                
                void compose_headers( void )
                {
                    for ( const auto header : frame->get_headers( ) )
                    {
                        auto value = core::make_bytes( header.first + ": " );
                        value.insert( std::end( value ), std::begin( header.second ), std::end( header.second ) );
                        
                        data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                        data.insert( std::end( data ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    }
                }
                
                void compose_body( void )
                {
                    data.insert( std::end( data ), FIELD_DELIMITER_BEGIN, FIELD_DELIMITER_END );
                    auto value = frame->get_body( );
                    data.insert( std::end( data ), std::begin( value ), std::end( value ) );
                }
            };
        }
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_DETAIL_HTTP_FRAME_BUILDER_IMPL_H */
