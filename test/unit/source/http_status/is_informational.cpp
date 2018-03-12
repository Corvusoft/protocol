//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_status.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::is_informational;

//External Namespaces

TEST_CASE( "Assert HTTP status is informational." )
{
    REQUIRE( is_informational(  99 ) == false );
    REQUIRE( is_informational( 100 ) == true );
    REQUIRE( is_informational( 149 ) == true );
    REQUIRE( is_informational( 199 ) == true );
    REQUIRE( is_informational( 200 ) == false );
}
