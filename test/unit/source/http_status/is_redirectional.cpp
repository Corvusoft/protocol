//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_status.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::is_redirectional;

//External Namespaces

TEST_CASE( "Assert HTTP status is redirectional." )
{
    REQUIRE( is_redirectional( 299 ) == false );
    REQUIRE( is_redirectional( 300 ) == true );
    REQUIRE( is_redirectional( 349 ) == true );
    REQUIRE( is_redirectional( 399 ) == true );
    REQUIRE( is_redirectional( 400 ) == false );
}
