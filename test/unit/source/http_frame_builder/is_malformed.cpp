//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_frame_builder.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTPFrameBuilder;

//External Namespaces

TEST_CASE( "Validate default malformed state." )
{
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->is_malformed( ) == false );
}
