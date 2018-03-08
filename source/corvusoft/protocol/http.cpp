/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/protocol/http.hpp"
#include "corvusoft/protocol/http_message.hpp"
#include "corvusoft/protocol/detail/http_impl.hpp"

//External Includes
#include <corvusoft/core/byte.hpp>
#include <corvusoft/core/settings.hpp>
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/network/adaptor.hpp>

//System Namespaces
using std::bind;
using std::size_t;
using std::string;
using std::function;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::make_error_code;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

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
        HTTP::HTTP( const shared_ptr< RunLoop > ) : Protocol( ),
            m_pimpl( new HTTPImpl )
        {
            return;
        }
        
        HTTP::~HTTP( void )
        {
            return;
        }
        
        error_code HTTP::setup( const shared_ptr< const Settings > )
        {
            //setup timeout/circuit-breaker.
            return error_code( );
        }
        
        error_code HTTP::teardown( void )
        {
            return error_code( );
        }
        
        void HTTP::initiate( const shared_ptr< Adaptor > adaptor, const function< error_code ( const shared_ptr< Adaptor >, const error_code ) > completion_handler )
        {
            if ( completion_handler not_eq nullptr )
                completion_handler( adaptor, error_code( ) );
        }
        
        void HTTP::terminate( const shared_ptr< Adaptor > adaptor, const function< error_code ( const shared_ptr< Adaptor >, const error_code ) > completion_handler )
        {
            if ( completion_handler not_eq nullptr )
                completion_handler( adaptor, error_code( ) );
        }
        
        void HTTP::parse( const shared_ptr< Adaptor > adaptor, const function< error_code ( const shared_ptr< Adaptor >, const shared_ptr< Message >, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            else if ( adaptor == nullptr ) completion_handler( adaptor, nullptr, make_error_code( std::errc::invalid_argument ) );
            else
            {
                const function< error_code ( const shared_ptr< Adaptor >, const Bytes, const error_code ) > consumption_handler = bind( m_pimpl->parse, _1, _2, _3, make_shared< HTTPMessage >( ), completion_handler );
                adaptor->consume( consumption_handler );
            }
        }
        
        void HTTP::compose( const shared_ptr< Adaptor > adaptor, const shared_ptr< Message > message, const function< error_code ( const shared_ptr< Adaptor >, const error_code ) > completion_handler )
        {
            if ( completion_handler == nullptr ) return;
            else if ( adaptor == nullptr ) completion_handler( adaptor, make_error_code( std::errc::invalid_argument ) );
            else if ( message == nullptr ) completion_handler( adaptor, make_error_code( std::errc::invalid_argument ) );
            else
            {
                const function< error_code ( const shared_ptr< Adaptor >, const size_t, const error_code ) > production_handler = bind( m_pimpl->compose, _1, _2, _3, completion_handler );
                adaptor->produce( message->to_bytes( ), production_handler );
            }
        }
    }
}
