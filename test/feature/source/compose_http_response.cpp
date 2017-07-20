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

TEST_CASE( "Compose HTTP response" )
{
    auto message = make_shared< Message >( );
    message->set( "response:version", "1.0" );
    message->set( "response:protocol", "HtTp" );
    message->set( "Content-Length", "10" );
    message->set( "content-type", "text/plain" );
    message->set( "response:body", make_bytes( "0123456789" ) );
    message->set( "response:status", "201" );
    message->set( "response:message", "Created" );
    
    auto adaptor = make_shared< MockAdaptor >( );
    auto protocol = make_shared< HTTP >( );
    const auto status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
    
    const auto data = make_bytes( "HtTp/1.0 201 Created\r\nContent-Length: 10\r\ncontent-type: text/plain\r\n\r\n0123456789" );
    REQUIRE( adaptor->get_data( ) == data );
}
