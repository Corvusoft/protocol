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
using std::string;
using std::multimap;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTPFrame;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Assert instance accessors." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_body( "data value 1." );
    REQUIRE( frame->get_body( ) == make_bytes( "data value 1." ) );
    
    frame->set_body( make_bytes( "data value 2." ) );
    REQUIRE( frame->get_body( ) == make_bytes( "data value 2." ) );
    
    frame->set_path( "/resource/1" );
    REQUIRE( frame->get_path( ) == make_bytes( "/resource/1" ) );
    
    frame->set_method( "DELETE" );
    REQUIRE( frame->get_method( ) == make_bytes( "DELETE" ) );
    
    frame->set_version( "1.1" );
    REQUIRE( frame->get_version( ) == make_bytes( "1.1" ) );
    
    frame->set_protocol( "HTTP" );
    REQUIRE( frame->get_protocol( ) == make_bytes( "HTTP" ) );
    
    frame->set_status_code( "201" );
    REQUIRE( frame->get_status_code( ) == make_bytes( "201" ) );
    
    frame->set_status_message( "Created" );
    REQUIRE( frame->get_status_message( ) == make_bytes( "Created" ) );
    
    frame->set_header( "", "" );
    auto headers = multimap< string, Bytes > { };
    headers.emplace( "", make_bytes( ) );
    REQUIRE( frame->get_headers( ) == headers );
    
    frame = make_shared< HTTPFrame >( );
    frame->set_header( "Host", "" );
    headers = multimap< string, Bytes > { };
    headers.emplace( "Host", make_bytes( ) );
    REQUIRE( frame->get_headers( ) == headers );
    
    frame = make_shared< HTTPFrame >( );
    frame->set_header( "", "http://corvusoft.co.uk" );
    headers = multimap< string, Bytes > { };
    headers.emplace( "", make_bytes( "http://corvusoft.co.uk" ) );
    REQUIRE( frame->get_headers( ) == headers );
    
    frame = make_shared< HTTPFrame >( );
    frame->set_header( "Host", "http://corvusoft.co.uk" );
    headers = multimap< string, Bytes > { };
    headers.emplace( "Host", make_bytes( "http://corvusoft.co.uk" ) );
    REQUIRE( frame->get_headers( ) == headers );
}
