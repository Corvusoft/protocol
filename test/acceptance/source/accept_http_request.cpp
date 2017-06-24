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

TEST_CASE( "Accept HTTP request" )
{
    auto data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.1\r\nContent-Length: 10\r\nContent-Type: text/plain\r\n\r\n0123456789" );
    auto adaptor = make_shared< MockAdaptor >( data );
    auto protocol = make_shared< HTTP >( );
    auto status = protocol->accept( adaptor );
    REQUIRE( status == error_code( ) );
    
    data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.1\n\rContent-Length: 10\n\rContent-Type: text/plain\n\r\n\r0123456789" );
    adaptor = make_shared< MockAdaptor >( data );
    status = protocol->accept( adaptor );
    REQUIRE( status == error_code( ) );
    
    data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.1\n\nContent-Length: 10\n\nContent-Type: text/plain\n\n\n\n0123456789" );
    adaptor = make_shared< MockAdaptor >( data );
    status = protocol->accept( adaptor );
    REQUIRE( status == error_code( ) );
    
    data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.1\r\rContent-Length: 10\r\rContent-Type: text/plain\r\r\r\r0123456789" );
    adaptor = make_shared< MockAdaptor >( data );
    status = protocol->accept( adaptor );
    REQUIRE( status == error_code( ) );
    
    data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.1\nContent-Length: 10\nContent-Type: text/plain\n\n0123456789" );
    adaptor = make_shared< MockAdaptor >( data );
    status = protocol->accept( adaptor );
    REQUIRE( status == error_code( ) );
    
    data = make_bytes( "GeT /query/endpoint?a=1&B=3#Title HtTp/1.1\rContent-Length: 10\rContent-Type: text/plain\r\r0123456789" );
    adaptor = make_shared< MockAdaptor >( data );
    status = protocol->accept( adaptor );
    REQUIRE( status == error_code( ) );
    
    data = make_bytes( "jfhi4ry2938fsdhfjksdhfjksdhf 01uo28 uehfkjh23 3 hkjrhksdf8 8y 8hfsdkjfhskjdfhsjkhf" );
    adaptor = make_shared< MockAdaptor >( data );
    status = protocol->accept( adaptor );
    REQUIRE( status == std::errc::wrong_protocol_type );
}
