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

TEST_CASE( "Assert request state." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_method( "GET" );
    frame->set_path( "/" );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.1" );
    REQUIRE( frame->is_request( ) == true );
    REQUIRE( frame->is_response( ) == false );
    
    frame = make_shared< HTTPFrame >( );
    frame->set_protocol( "SPY" );
    frame->set_version( "1.5" );
    frame->set_status_code( "637637" );
    frame->set_status_message( "Accepted by server." );
    REQUIRE( frame->is_request( ) == false );
    REQUIRE( frame->is_response( ) == true );
    
    frame = make_shared< HTTPFrame >( );
    frame->set_protocol( "SPY" );
    frame->set_version( "1.5" );
    frame->set_status_code( "637637" );
    frame->set_status_message( "Accepted by server." );
    frame->set_method( "GET" );
    frame->set_path( "/" );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.1" );
    REQUIRE( frame->is_request( ) == false );
    REQUIRE( frame->is_response( ) == false );
}
