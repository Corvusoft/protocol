//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_frame_builder.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTPFrameBuilder;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Assert malformed state with complete HTTP request." )
{
    auto data = make_bytes( "GET / HTTP/1.1\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
    
    data = make_bytes( "GET / HTTP/1.1\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
}

TEST_CASE( "Assert malformed state with incomplete HTTP request." )
{
    auto data = make_bytes( "GET / HTTP/1.1\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
    
    data = make_bytes( "GET / HTTP/1.1\r\nHost: www.corvusoft.co.uk\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
}

TEST_CASE( "Assert malformed state with invalid HTTP request." )
{
    auto data = make_bytes( "GET HTTP/1.1\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "/?a=z HTTP/1.1\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "PUT /#abc /1.1\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "PUT /#abc HTTP/\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "PUT /#abc HTTP\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "PUT /#abc SPDY/1.2\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "DELETE\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "GET HTTP/1.1\r\nHostwww.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "\r\n\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
}

TEST_CASE( "Assert malformed state with complete HTTP response." )
{
    auto data = make_bytes( "HTTP/1.1 200 OK\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
    
    data = make_bytes( "HTTP/1.1 201\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
    
    data = make_bytes( "HTTP/1.1 200 OK\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
}

TEST_CASE( "Assert malformed state with incomplete HTTP response." )
{
    auto data = make_bytes( "HTTP/1.1 200 OK\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
    
    data = make_bytes( "HTTP/1.1 201 Created\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
    
    data = make_bytes( "HTTP/1.1 200 OK\r\nHost: www.corvusoft.co.uk\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == false );
}

TEST_CASE( "Assert malformed state with invalid HTTP response." )
{
    auto data = make_bytes( "HTTP/1.1 Created\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "/1.1 201 Created\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "SPDY/1.1 201 Created\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "SPDY/ 201 Created\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "SPDY/jklj 201 Created\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "HTTP 201 Created\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "201 Created\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "201\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "HTTP/1.1 201 Created\r\nHostwww.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
    
    data = make_bytes( "\r\n\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_malformed( ) == true );
}
