//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_frame.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTPFrame;

//External Namespaces

TEST_CASE( "Assert default response state." )
{
    auto frame = make_shared< HTTPFrame >( );
    REQUIRE( frame->is_response( ) == false );
}
