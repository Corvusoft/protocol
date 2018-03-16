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

TEST_CASE( "Assert response state." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.1" );
    frame->set_status_code( "202" );
    frame->set_status_message( "Accepted" );
    REQUIRE( frame->is_response( ) == true );
    REQUIRE( frame->is_request( ) == false );
    
    frame = make_shared< HTTPFrame >( );
    frame->set_method( "DELETE" );
    frame->set_path( "/api/delete" );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.0" );
    REQUIRE( frame->is_response( ) == false );
    REQUIRE( frame->is_request( ) == true );
    
    frame = make_shared< HTTPFrame >( );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.1" );
    frame->set_status_code( "202" );
    frame->set_status_message( "Accepted" );
    frame->set_method( "DELETE" );
    frame->set_path( "/api/delete" );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.0" );
    REQUIRE( frame->is_response( ) == false );
    REQUIRE( frame->is_request( ) == false );
}
