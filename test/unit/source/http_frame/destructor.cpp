//System Includes

//Project Includes
#include <corvusoft/protocol/http_frame.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::HTTPFrame;

//External Namespaces

TEST_CASE( "Destroy class instance." )
{
    const auto builder = new HTTPFrame( );
    REQUIRE_NOTHROW( delete builder );
}
