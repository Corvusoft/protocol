//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_status.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::OK;
using corvusoft::protocol::NOT_ACCEPTABLE;
using corvusoft::protocol::make_status_code;

//External Namespaces

TEST_CASE( "Assert HTTP status message to status code translation." )
{
    REQUIRE( make_status_code( "OK" ) == OK );
    REQUIRE( make_status_code( "ok" ) == OK );
    
    REQUIRE( make_status_code( "Not Acceptable" ) == NOT_ACCEPTABLE );
    REQUIRE( make_status_code( "NoT aCcEpTaBlE" ) == NOT_ACCEPTABLE );
    
    REQUIRE( make_status_code( "" ) == 0 );
    REQUIRE( make_status_code( "Corvusoft" ) == 0 );
}
