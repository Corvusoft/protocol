/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <vector>

//Project Includes
#include "corvusoft/protocol/http.hpp"
#include "corvusoft/protocol/detail/http_impl.hpp"

//External Includes
#include <corvusoft/core/byte.hpp>
#include <corvusoft/core/settings.hpp>
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/network/adaptor.hpp>

//System Namespaces
using std::list;
using std::size_t;
using std::string;
using std::vector;
using std::shared_ptr;
using std::error_code;
using std::make_error_code;

//Project Namespaces
using corvusoft::protocol::detail::HTTPImpl;

//External Namespaces
using corvusoft::core::Byte;
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;
using corvusoft::core::RunLoop;
using corvusoft::core::Settings;
using corvusoft::network::Adaptor;

namespace corvusoft
{
    namespace protocol
    {
        HTTP::HTTP( void ) : Protocol( ),
            m_pimpl( new HTTPImpl )
        {
            return;
        }
        
        HTTP::~HTTP( void )
        {
            return;
        }
        
        error_code HTTP::teardown( void ) noexcept
        {
            return error_code( );
        }
        
        error_code HTTP::setup( const shared_ptr< RunLoop >, const shared_ptr< const Settings > ) noexcept
        {
            return error_code( );
        }
        
        error_code HTTP::parse( const shared_ptr< Adaptor > adaptor, const shared_ptr< Message > message ) noexcept
        {
            if ( adaptor == nullptr ) return make_error_code( std::errc::invalid_argument );
            if ( message == nullptr ) return make_error_code( std::errc::invalid_argument );
            
            error_code error;
            const auto buffer = adaptor->consume( error );
            if ( error ) return error;
            
            size_t length = 0;
            const auto data = m_pimpl->extract( buffer );
            if ( data.size( ) <= 1 ) return make_error_code( std::errc::wrong_protocol_type );
            
            if ( m_pimpl->is_request( data ) )
                length = m_pimpl->parse_request( data, message, error );
            else if ( m_pimpl->is_response( data ) )
                length = m_pimpl->parse_response( data, message, error );
            else
                return make_error_code( std::errc::wrong_protocol_type );
                
            //adaptor->purge( length, error );
            return error;
        }
        
        error_code HTTP::parse( const shared_ptr< Adaptor > adaptor, const list< const shared_ptr< Message > > messages ) noexcept
        {
            return error_code( );
        }
        
        error_code HTTP::compose( const shared_ptr< Adaptor > adaptor, const shared_ptr< Message > message ) noexcept
        {
            if ( adaptor == nullptr ) return make_error_code( std::errc::invalid_argument );
            if ( message == nullptr ) return make_error_code( std::errc::invalid_argument );
            
            Bytes data;
            if ( m_pimpl->uppercase( message->get( "request:protocol" ) ) == "HTTP" )
                m_pimpl->compose_request( data, message );
            else if ( m_pimpl->uppercase( message->get( "response:protocol" ) ) == "HTTP" )
                m_pimpl->compose_response( data, message );
            else
                return std::make_error_code( std::errc::wrong_protocol_type );
                
            error_code error;
            adaptor->produce( data, error );
            if ( not error )
                //adaptor->flush( data.size( ), error );
                
                return error;
        }
        
        error_code HTTP::compose( const shared_ptr< Adaptor > adaptor, const list< const shared_ptr< Message > > messages ) noexcept
        {
            return error_code( );
        }
        
        const string HTTP::get_name( void ) const
        {
            return "HTTP";
        }
    }
}
