//System Includes

//Project Includes
#include <corvusoft/protocol/http_frame.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::HTTPFrame;

//External Namespaces

TEST_CASE( "Create class instance." )
{
    REQUIRE_NOTHROW( HTTPFrame( ) );
}
