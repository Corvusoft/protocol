//System Includes
#include <memory>

//Project Includes
#include "corvusoft/protocol/http.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTP;

//External Namespaces

TEST_CASE( "Get Key" )
{
    const auto protocol = make_shared< HTTP >( );
    REQUIRE( protocol->get_key( ) == "HTTP" );
}
