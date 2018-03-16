//System Includes
#include <memory>
#include <string>

//Project Includes
#include <corvusoft/protocol/http_frame.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::string;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTPFrame;

//External Namespaces
using corvusoft::core::Bytes;

TEST_CASE( "Assert default setter state." )
{
    auto frame = make_shared< HTTPFrame >( );
    REQUIRE_NOTHROW( frame->set_body( "" ) );
    REQUIRE_NOTHROW( frame->set_body( "data value." ) );
    REQUIRE_NOTHROW( frame->set_body( Bytes{ } ) );
    REQUIRE_NOTHROW( frame->set_body( Bytes{ 'd', 'a', 't', 'a' } ) );
    
    REQUIRE_NOTHROW( frame->set_path( "" ) );
    REQUIRE_NOTHROW( frame->set_path( "/resource/1" ) );
    
    REQUIRE_NOTHROW( frame->set_method( "" ) );
    REQUIRE_NOTHROW( frame->set_method( "DELETE" ) );
    
    REQUIRE_NOTHROW( frame->set_version( "" ) );
    REQUIRE_NOTHROW( frame->set_version( "1.1" ) );
    
    REQUIRE_NOTHROW( frame->set_protocol( "" ) );
    REQUIRE_NOTHROW( frame->set_protocol( "HTTP" ) );
    
    REQUIRE_NOTHROW( frame->set_status_code( "" ) );
    REQUIRE_NOTHROW( frame->set_status_code( "301" ) );
    
    REQUIRE_NOTHROW( frame->set_status_message( "" ) );
    REQUIRE_NOTHROW( frame->set_status_message( "Continue" ) );
    
    REQUIRE_NOTHROW( frame->set_header( "", "" ) );
    REQUIRE_NOTHROW( frame->set_header( "Host", "" ) );
    REQUIRE_NOTHROW( frame->set_header( "", "http://corvusoft.co.uk" ) );
    REQUIRE_NOTHROW( frame->set_header( "Host", "http://corvusoft.co.uk" ) );
}
