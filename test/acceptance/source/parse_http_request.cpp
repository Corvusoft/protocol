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

TEST_CASE( "Parse HTTP request" )
{
    auto data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.4\r\nContent-Length:999\r\ncontent-Type: text/xml\r\n\r\nabcdefghijkl" );
    auto adaptor = make_shared< MockAdaptor >( data );
    auto protocol = make_shared< HTTP >( );
    auto message = make_shared< Message >( );
    
    auto status = protocol->parse( adaptor, message );
    REQUIRE( status == error_code( ) );
    REQUIRE( message->get( "request:method" ) == make_bytes( "GeT" ) );
    REQUIRE( message->get( "request:path" ) == make_bytes( "/query/endpoint?a=1&B=3#Title" ) );
    REQUIRE( message->get( "request:protocol" ) == make_bytes( "HtTp" ) );
    REQUIRE( message->get( "request:version" ) == make_bytes( "1.4" ) );
    REQUIRE( message->get( "request:body" ) == make_bytes( "" ) );
    REQUIRE( message->get( "Content-Length" ) == make_bytes( "999" ) );
    REQUIRE( message->get( "content-Type" ) == make_bytes( "text/xml" ) );
}
