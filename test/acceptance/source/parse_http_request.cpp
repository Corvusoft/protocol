//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include "mock_adaptor.hpp"
#include "corvusoft/protocol/http.hpp"
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::error_code;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTP;
using corvusoft::protocol::Message;

//External Namespaces

TEST_CASE( "Parse http request" )
{
    auto message = make_shared< Message >( );
    message->set( "method", "GeT" );
    message->set( "version", "1.1" );
    message->set( "protocol", "HTTP" );
    message->set( "Content-Length", "10" );
    message->set( "content-Type", "text/plain" );
    message->set( "body", make_bytes( "0123456789" ) );
    message->set( "path", "/query/endpoint?a=1&b=3#title" );
    
    auto adaptor = make_shared< MockAdaptor >( );
    auto protocol = make_shared< HTTP >( );
    status = protocol->parse( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    auto result = adaptor->get_payload( );
}
