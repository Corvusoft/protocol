//System Includes

//Project Includes
#include "corvusoft/protocol/http.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::HTTP;

//External Namespaces

TEST_CASE( "Destructor" )
{
    const auto protocol = new HTTP( );
    REQUIRE_NOTHROW( delete protocol );
}
