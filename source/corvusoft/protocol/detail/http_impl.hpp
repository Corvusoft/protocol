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
                // static bool is_header( const std::string& value )
                // {
                //     const size_t start_at = 1;
                //     const char delimiter = ':';
                //     return value.find_first_of( delimiter, start_at );
                // }
                
                static bool is_request( const std::vector< const std::string >& value )
                {
                    static const std::regex pattern( "^[a-z]+\\s+.+\\s+.+$", std::regex::icase );
                    return std::regex_match( value.at( 0 ), pattern );
                }
                
                static bool is_response( const std::vector< const std::string >& value )
                {
                    static const std::regex pattern( "^HTTP/[a-z0-9]+\\.[a-z0-9]+\\s+[0-9]+\\s+.+$", std::regex::icase );
                    return std::regex_match( value.at( 0 ), pattern );
                }
                
                static std::size_t parse_request( const std::vector< const std::string >& data, const std::shared_ptr< Message >& message, std::error_code& error )
                {
                    // const auto status = data.at( 0 );
                    // auto index = status.find_first_of( ' ' );
                    // if ( index == string::npos ) return make_error_code( std::errc::wrong_protocol_type );
                    // message->set( "request:method", status.substr( 0, index ) );
                    
                    // index = status.find_first_of( ' ', index );
                    // if ( index == string::npos ) return make_error_code( std::errc::wrong_protocol_type );
                    // message->set( "request:path", status, substr( index, index ) );
                    
                    // index = status.find_first_of( '/', index );
                    // if ( index == string::npos ) return make_error_code( std::errc::wrong_protocol_type );
                    // message->set( "request:protocol", status.substr( index, index ) );
                    
                    // message->set( "request:version", status.substr( ) );
                    
                    // const auto length = data.length( );
                    // for ( index = 1; index not_eq length; index++ )
                    // {
                    //     if ( entry == "\r\n" ) break;
                    //     message->set( matches[ 1 ].str( ), matches[ 2 ].str( ) ); //must allow duplicates
                    //     //bad message on malformed header
                    // }
                    
                    // error;
                    return 0;
                }
                
                static std::size_t parse_response( const std::vector< const std::string >& data, const std::shared_ptr< Message >& message, std::error_code& error )
                {
                
                }
                
                static std::size_t compose_request( const core::Bytes& data, const std::shared_ptr< Message >& message, std::error_code& error )
                {
                
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
