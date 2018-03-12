//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_status.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::OK;
using corvusoft::protocol::CONTINUE;
using corvusoft::protocol::make_status_message;

//External Namespaces

TEST_CASE( "Assert HTTP status code to status message translation." )
{
    REQUIRE( make_status_message( OK ) == "OK" );
    REQUIRE( make_status_message( CONTINUE ) == "Continue" );
    
    REQUIRE( make_status_message( -1 ) == "" );
    REQUIRE( make_status_message( 512 ) == "" );
    REQUIRE( make_status_message( 51024 ) == "" );
}
