//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_status.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::is_successful;

//External Namespaces

TEST_CASE( "Assert HTTP status is successful." )
{
    REQUIRE( is_successful( 199 ) == false );
    REQUIRE( is_successful( 200 ) == true );
    REQUIRE( is_successful( 249 ) == true );
    REQUIRE( is_successful( 299 ) == true );
    REQUIRE( is_successful( 300 ) == false );
}
