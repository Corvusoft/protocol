//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_status.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::is_client_error;

//External Namespaces

TEST_CASE( "Assert HTTP status is client error." )
{
    REQUIRE( is_client_error( 399 ) == false );
    REQUIRE( is_client_error( 400 ) == true );
    REQUIRE( is_client_error( 449 ) == true );
    REQUIRE( is_client_error( 499 ) == true );
    REQUIRE( is_client_error( 500 ) == false );
}
