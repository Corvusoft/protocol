//System Includes

//Project Includes
#include <corvusoft/protocol/http_frame_builder.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::HTTPFrameBuilder;

//External Namespaces

TEST_CASE( "Create class instance." )
{
    REQUIRE_NOTHROW( HTTPFrameBuilder( ) );
}
