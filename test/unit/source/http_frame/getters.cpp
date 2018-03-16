//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes
#include <corvusoft/protocol/http_frame.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::map;
using std::string;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTPFrame;

//External Namespaces
using corvusoft::core::Bytes;

TEST_CASE( "Assert default getter state." )
{
    auto frame = make_shared< HTTPFrame >( );
    REQUIRE( frame->get_body( ).empty( ) );
    REQUIRE( frame->get_path( ).empty( ) );
    REQUIRE( frame->get_method( ).empty( ) );
    REQUIRE( frame->get_version( ).empty( ) );
    REQUIRE( frame->get_protocol( ).empty( ) );
    REQUIRE( frame->get_status_code( ).empty( ) );
    REQUIRE( frame->get_status_message( ).empty( ) );
    REQUIRE( frame->get_headers( ).empty( ) );
}
