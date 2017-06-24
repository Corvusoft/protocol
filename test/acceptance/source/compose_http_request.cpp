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

TEST_CASE( "Compose HTTP request" )
{
    auto data = make_bytes( );
    auto message = make_shared< Message >( );
    auto adaptor = make_shared< MockAdaptor >( );
    auto protocol = make_shared< HTTP >( );
    auto status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    REQUIRE( adaptor->get_data( ) == data );
    
    message->set( "method", "GeT" );
    message->set( "version", "1.2" );
    message->set( "protocol", "HtTp" );
    message->set( "Content-Length", "10" );
    message->set( "content-Type", "text/plain" );
    message->set( "body", make_bytes( "0123456789" ) );
    message->set( "path", "/query/endpoint?a=1&B=3#Title" );
    
    status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.1\r\nContent-Length: 10\r\ncontent-Type: text/plain\r\n\r\n0123456789" );
    REQUIRE( adaptor->get_data( ) == data );
}
