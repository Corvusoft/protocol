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

TEST_CASE( "Parse" )
{
    auto protocol = make_shared< HTTP >( );
    auto status = protocol->parse( nullptr, nullptr );
    REQUIRE( status == std::errc::invalid_argument );
    
    protocol = make_shared< HTTP >( );
    auto message = make_shared< Message >( );
    status = protocol->parse( nullptr, message );
    REQUIRE( status == std::errc::invalid_argument );
    
    protocol = make_shared< HTTP >( );
    auto adaptor = make_shared< MockAdaptor >( );
    status = protocol->parse( adaptor, nullptr );
    REQUIRE( status == std::errc::invalid_argument );
    
    protocol = make_shared< HTTP >( );
    status = protocol->parse( adaptor, message );
    REQUIRE( status == std::errc::wrong_protocol_type );
}
