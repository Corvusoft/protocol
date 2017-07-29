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
    auto message = make_shared< Message >( );
    message->set( "request:method", "GeT" );
    message->set( "request:version", "1.2" );
    message->set( "request:protocol", "HtTp" );
    message->set( "Content-Type", "text/plain" );
    message->set( "content-Length", "10" );
    message->set( "request:body", make_bytes( "0123456789" ) );
    message->set( "request:path", "/query/endpoint?a=1&B=3#Title" );
    
    auto adaptor = make_shared< MockAdaptor >( );
    auto protocol = make_shared< HTTP >( );
    const auto status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    const auto data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.2\r\nContent-Type: text/plain\r\ncontent-Length: 10\r\n\r\n0123456789" );
    REQUIRE( adaptor->get_data( ) == data );
}
