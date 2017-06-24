//System Includes
#include <string>
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
using std::string;
using std::error_code;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTP;
using corvusoft::protocol::Message;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Parse HTTP response" )
{
    auto data = make_bytes( "HtTp/1.0 201 Created\r\nContent-Length: 10\r\nContent-Type: text/plain\r\n\r\n0123456789" );
    auto adaptor = make_shared< MockAdaptor >( data );
    auto protocol = make_shared< HTTP >( );
    auto message = make_shared< Message >( );
    
    auto status = protocol->parse( adaptor, message );
    REQUIRE( status == error_code( ) );
    REQUIRE( message->get( "status" ) == make_bytes( "201" ) );
    REQUIRE( message->get( "version" ) == make_bytes( "1.0" ) );
    REQUIRE( message->get( "protocol" ) == make_bytes( "HtTp" ) );
    REQUIRE( message->get( "message" ) == make_bytes( "Created" ) );
    REQUIRE( message->get( "body" ) == make_bytes( "0123456789" ) );
    REQUIRE( message->get( "Content-Length" ) == make_bytes( "10" ) );
    REQUIRE( message->get( "content-Type" ) == make_bytes( "text/plain" ) );
}
