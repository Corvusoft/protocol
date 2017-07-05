/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_DETAIL_HTTP_IMPL_H
#define _CORVUSOFT_PROTOCOL_DETAIL_HTTP_IMPL_H 1

//System Includes
#include <regex>
#include <vector>
#include <memory>

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
                //static const Byte HEADER_DELIMITER = ': ';
                //static const Byte
                
                static bool is_request( const std::vector< const std::string >& value )
                {
                    static const std::regex pattern( "^[a-z]+\\s+.+\\s+.+$", std::regex::icase ); //validate \r\n any order and HTTP/*.*
                    return std::regex_match( value.at( 0 ), pattern );
                }
                
                static bool is_response( const std::vector< const std::string >& value )
                {
                    static const std::regex pattern( "^HTTP/[a-z0-9]+\\.[a-z0-9]+\\s+[0-9]+\\s+.+$", std::regex::icase ); //validate \r\n any order
                    return std::regex_match( value.at( 0 ), pattern );
                }
                
                static std::size_t parse_request( const std::vector< const std::string >& data, const std::shared_ptr< Message >& message, std::error_code& error )
                {
                    const std::string status = data.at( 0 );
                    std::string::size_type size = 0;
                    std::string::size_type start = 0;
                    std::string::size_type stop = status.find_first_of( ' ' );
                    message->set( "request:method", status.substr( start, stop ) );
                    
                    size += stop;
                    start = stop;
                    stop = status.find_first_of( ' ', start );
                    message->set( "request:path", status.substr( start, stop ) );
                    
                    size += stop;
                    start = stop;
                    start = status.find_first_of( ' ', start );
                    size += start;
                    stop = status.find_first_of( '/', start );
                    message->set( "request:protocol", status.substr( start, stop ) );
                    
                    size += stop;
                    start = stop;
                    message->set( "request:version", status.substr( start ) );
                    
                    const auto length = data.size( );
                    for ( std::string::size_type index = 1; index not_eq length; index++ )
                    {
                        const auto entry = data.at( index );
                        if ( entry == "\r\n" ) break;
                        
                        stop = entry.find_first_of( ':' );
                        if ( stop == std::string::npos )
                        {
                            error = std::make_error_code( std::errc::bad_message );
                            return 0;
                        }
                        
                        message->set( entry.substr( 0, stop ), entry.substr( stop ) );
                    }
                    
                    return size;
                }
                
                static std::size_t parse_response( const std::vector< const std::string >& data, const std::shared_ptr< Message >& message, std::error_code& error )
                {
                
                }
                
                static std::size_t compose_request( core::Bytes& data, const std::shared_ptr< Message >& message, std::error_code& error )
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
                    
                    for ( const auto name : message->get_names( ) )
                    {
                        if ( is_request_header_field( name ) )
                        {
                            data.insert( field.end( ), name.begin( ), name.end( ) );
                            data.emplace_back( ':' );
                            data.emplace_back( ' ' );
                            field = message->get( name );
                            data.insert( data.end( ), field.begin( ), field.end( ) );
                            data.emplace_back( '\r' );
                            data.emplace_back( '\n' );
                        }
                    }
                    
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                    field = message->get( "request:body" );
                    data.insert( data.end( ), field.begin( ), field.end( ) );
                }
                
                static std::size_t compose_response( core::Bytes& data, const std::shared_ptr< Message >& message, std::error_code& error )
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
                    
                    for ( const auto name : message->get_names( ) )
                    {
                        if ( is_response_header_field( name ) )
                        {
                            data.insert( field.end( ), name.begin( ), name.end( ) );
                            data.emplace_back( ':' );
                            data.emplace_back( ' ' );
                            field = message->get( name );
                            data.insert( data.end( ), field.begin( ), field.end( ) );
                            data.emplace_back( '\r' );
                            data.emplace_back( '\n' );
                        }
                    }
                    
                    data.emplace_back( '\r' );
                    data.emplace_back( '\n' );
                    field = message->get( "response:body" );
                    data.insert( data.end( ), field.begin( ), field.end( ) );
                }
                
                static bool is_delimiter( const core::Byte value )
                {
                    return value == '\r' or value == '\n';
                }
                
                static bool is_request_header_field( const std::string& name )
                {
                    return name not_eq "request:body"     and
                           name not_eq "request:path"     and
                           name not_eq "request:status"   and
                           name not_eq "request:version"  and
                           name not_eq "request:protocol";
                }
                
                static bool is_response_header_field( const std::string& name )
                {
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
                                
                            record.push_back( data );
                            data.clear( );
                        }
                        else data.push_back( byte );
                    }
                    
                    return record;
                }
            };
        }
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_DETAIL_HTTP_IMPL_H */
