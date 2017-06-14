//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include "corvusoft/protocol/http.hpp"

//External Includes
#include <catch.hpp>
#include <corvusoft/network/adaptor.hpp>

//System Namespaces
using std::error_code;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTP;

//External Namespaces
using corvusoft::network::Adaptor;

TEST_CASE( "Protocol acceptor" )
{
    const auto protocol = make_shared< HTTP >( );
    auto status = protocol->accept( nullptr );
    REQUIRE( status == std::errc::invalid_argument );
}
