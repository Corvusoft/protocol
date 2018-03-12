//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_status.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::is_server_error;

//External Namespaces

TEST_CASE( "Assert HTTP status is server error." )
{
    REQUIRE( is_server_error( 499 ) == false );
    REQUIRE( is_server_error( 500 ) == true );
    REQUIRE( is_server_error( 549 ) == true );
    REQUIRE( is_server_error( 599 ) == true );
    REQUIRE( is_server_error( 600 ) == false );
}
