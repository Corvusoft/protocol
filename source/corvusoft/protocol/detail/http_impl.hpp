/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_DETAIL_HTTP_IMPL_H
#define _CORVUSOFT_PROTOCOL_DETAIL_HTTP_IMPL_H 1

//System Includes
#include <regex>
#include <vector>
#include <memory>
#include <utility>
#include <ctype.h>
#include <algorithm>

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
            
            struct HTTPImpl
            {
                static bool is_request( const std::vector< const std::string >& value )
                {
                    static const std::regex pattern( "^[a-z]+\\s+.+\\s+HTTP\\/[0-9]+\\.[0-9]+$", std::regex::icase );
                    return std::regex_match( value.at( 0 ), pattern );
                }
                
                static bool is_response( const std::vector< const std::string >& value )
                {
                    static const std::regex pattern( "^HTTP\\/[0-9]+\\.[0-9]+\\s+[0-9]+(?:\\s+.*){0,1}$", std::regex::icase );
                    return std::regex_match( value.at( 0 ), pattern );
                }
                
                static std::size_t parse_request( const std::vector< const std::string >& data, const std::shared_ptr< Message >& message, std::error_code& error )
                {
                    const std::string status = data.at( 0 );
                    std::string::size_type start = 0;
                    std::string::size_type stop = status.find_first_of( ' ' );
                    if ( stop == std::string::npos )
                    {
                        error = std::make_error_code( std::errc::bad_message );
                        return 0;
                    }
                    else message->set( "request:method", status.substr( start, stop ) );
                    
                    start = ++stop;
                    stop = status.find_first_of( ' ', start );
                    if ( stop == std::string::npos )
                    {
                        error = std::make_error_code( std::errc::bad_message );
                        return 0;
                    }
                    else message->set( "request:path", status.substr( start, stop - start ) );
                    
                    start = ++stop;
                    stop = status.find_first_of( '/', start );
                    if ( stop == std::string::npos )
                    {
                        error = std::make_error_code( std::errc::bad_message );
                        return 0;
                    }
                    else message->set( "request:protocol", status.substr( start, stop - start ) );
                    
                    start = ++stop;
                    message->set( "request:version", status.substr( start ) );
                    
                    const auto size = parse_headers( data, message, error );
                    if ( error ) return 0;
                    
                    return size + status.length( );
                }
                
                static std::size_t parse_response( const std::vector< const std::string >& data, const std::shared_ptr< Message >& message, std::error_code& error )
                {
                    const std::string status = data.at( 0 );
                    std::string::size_type start = 0;
                    std::string::size_type stop = status.find_first_of( '/' );
                    if ( stop == std::string::npos )
                    {
                        error = std::make_error_code( std::errc::bad_message );
                        return 0;
                    }
                    else message->set( "response:protocol", status.substr( start, stop ) );
                    
                    start = ++stop;
                    stop = status.find_first_of( ' ', start );
                    if ( stop == std::string::npos )
                    {
                        error = std::make_error_code( std::errc::bad_message );
                        return 0;
                    }
                    else message->set( "response:version", status.substr( start, stop - start ) );
                    
                    start = ++stop;
                    stop = status.find_first_of( ' ', start );
                    if ( stop == std::string::npos ) stop = status.length( );    
                    message->set( "response:status", status.substr( start, stop - start ) );

                    if ( stop not_eq status.length( ) )
                    {
                        start = ++stop;
                        message->set( "response:message", status.substr( start ) );
                    }
                    
                    const auto size = parse_headers( data, message, error );
                    if ( error ) return 0;
                    
                    return size + status.length( );
                }
                
                static std::size_t parse_headers( const std::vector< const std::string >& data, const std::shared_ptr< Message >& message, std::error_code& error )
                {
                    std::size_t size = 0;
                    std::string::size_type stop = 0;
                    const auto length = data.size( );
                    for ( std::string::size_type index = 1; index not_eq length; index++ )
                    {
                        const auto entry = data.at( index );
                        if ( entry.empty( ) ) break;
                        
                        stop = entry.find_first_of( ':' );
                        if ( stop == std::string::npos )
                        {
                            error = std::make_error_code( std::errc::bad_message );
                            return 0;
                        }
                        
                        const auto name = entry.substr( 0, stop );
                        auto value = entry.substr( stop + 1 );
                        if ( not value.empty( ) and value.at( 0 ) == ' ' )
                        {
                            size++;
                            value.erase( 0, 1 );
                        }
                        
                        message->set( name, value );
                        size += name.length( ) + value.length( ) + 1;
                    }
                    
                    return size;
                }
                
                static void compose_request( core::Bytes& data, const std::shared_ptr< Message >& message )
                {
                    data = message->get( "request:method" );
                    data.emplace_back( ' ' );
                    
                    auto field = message->get( "request:path" );
                    data.insert( data.end( ), field.begin( ), field.end( ) );
                    data.emplace_back( ' ' );
                    
                    field = message->get( "request:protocol" );
                    data.insert( data.end( ), field.begin( ), field.end( ) );
                    data.emplace_back( '/' );
                    
                    field = message->get( "request:version" );
                    data.insert( data.end( ), field.begin( ), field.end( ) );
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                    
                    for ( const auto property : message->get( ) )
                        if ( is_request_header( property ) )
                            compose_header( data, property );
                            
                    compose_body( data, message->get( "request:body" ) );
                }
                
                static void compose_response( core::Bytes& data, const std::shared_ptr< Message >& message )
                {
                    data = message->get( "response:protocol" );
                    data.emplace_back( '/' );
                    
                    auto field = message->get( "response:version" );
                    data.insert( data.end( ), field.begin( ), field.end( ) );
                    data.emplace_back( ' ' );
                    
                    field = message->get( "response:status" );
                    data.insert( data.end( ), field.begin( ), field.end( ) );
                    data.emplace_back( ' ' );
                    
                    field = message->get( "response:message" );
                    data.insert( data.end( ), field.begin( ), field.end( ) );
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                    
                    for ( const auto property : message->get( ) )
                        if ( is_response_header( property ) )
                            compose_header( data, property );
                            
                    compose_body( data, message->get( "response:body" ) );
                }
                
                static void compose_header( core::Bytes& data, const std::pair< const std::string, const core::Bytes >& property )
                {
                    const auto& name = property.first;
                    data.insert( data.end( ), name.begin( ), name.end( ) );
                    data.emplace_back( ':' );
                    data.emplace_back( ' ' );
                    
                    const auto& value = property.second;
                    data.insert( data.end( ), value.begin( ), value.end( ) );
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                }
                
                static void compose_body( core::Bytes& data, const core::Bytes& value )
                {
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                    data.insert( data.end( ), value.begin( ), value.end( ) );
                }
                
                static bool is_delimiter( const core::Byte value )
                {
                    return value == '\r' or value == '\n';
                }
                
                static bool is_request_header( const std::pair< const std::string, const core::Bytes >& property )
                {
                    const auto& name = property.first;
                    return name not_eq "request:body"     and
                           name not_eq "request:path"     and
                           name not_eq "request:method"   and
                           name not_eq "request:version"  and
                           name not_eq "request:protocol";
                }
                
                static bool is_response_header( const std::pair< const std::string, const core::Bytes >& property )
                {
                    const auto& name = property.first;
                    return name not_eq "response:body"     and
                           name not_eq "response:status"   and
                           name not_eq "response:version"  and
                           name not_eq "response:protocol" and
                           name not_eq "response:message";
                }
                
                static std::vector< const std::string > extract( const core::Bytes& value )
                {
                    std::string data;
                    std::vector< const std::string > record;
                    
                    for ( auto position = value.begin( ); position not_eq value.end( ); position++ )
                    {
                        core::Byte byte = *position;
                        if ( is_delimiter( byte ) )
                        {
                            if ( is_delimiter( *( position + 1 ) ) )
                                position++;
                                
                            record.emplace_back( data );
                            data.clear( );
                        }
                        else data.push_back( byte );
                    }
                    
                    return record;
                }
                
                static std::string uppercase( const core::Bytes& values )
                {
                    std::string result;
                    for ( const auto value : values )
                        result.push_back( ::toupper( value ) );
                    return result;
                }
            };
        }
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_DETAIL_HTTP_IMPL_H */
