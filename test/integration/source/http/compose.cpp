//System Includes
#include <list>
#include <memory>
#include <system_error>

//Project Includes
#include "mock_adaptor.hpp"
#include "corvusoft/protocol/http.hpp"
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::list;
using std::error_code;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTP;
using corvusoft::protocol::Message;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Compose" )
{
    auto protocol = make_shared< HTTP >( );
    auto status = protocol->compose( nullptr, nullptr );
    REQUIRE( status == std::errc::invalid_argument );
    
    protocol = make_shared< HTTP >( );
    auto message = make_shared< Message >( );
    status = protocol->compose( nullptr, message );
    REQUIRE( status == std::errc::invalid_argument );
    
    protocol = make_shared< HTTP >( );
    auto adaptor = make_shared< MockAdaptor >( );
    status = protocol->compose( adaptor, nullptr );
    REQUIRE( status == std::errc::invalid_argument );
    
    protocol = make_shared< HTTP >( );
    status = protocol->compose( adaptor, message );
    REQUIRE( status == std::errc::wrong_protocol_type );
    
    protocol = make_shared< HTTP >( );
    status = protocol->compose( adaptor, list< const shared_ptr< Message > >( ) );
    REQUIRE( status == error_code( ) );
    
    message->set( "request:protocol", make_bytes( "http" ) );
    status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    message->set( "request:protocol", make_bytes( "HTTP" ) );
    status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    message->set( "request:protocol", make_bytes( "hTtP" ) );
    status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    message->set( "response:protocol", make_bytes( "http" ) );
    status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    message->set( "response:protocol", make_bytes( "HTTP" ) );
    status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    message->set( "response:protocol", make_bytes( "hTtP" ) );
    status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
}
