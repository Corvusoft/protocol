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
    REQUIRE( status == error_code( ) );
    
    protocol = make_shared< HTTP >( );
    status = protocol->compose( adaptor, message );
    REQUIRE( status == error_code( ) );
}
