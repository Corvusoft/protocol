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

TEST_CASE( "Assert finalised state with complete HTTP request." )
{
    auto data = make_bytes( "GET / HTTP/1.1\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == true );
    
    data = make_bytes( "GET / HTTP/1.1\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == true );
}

TEST_CASE( "Assert finalised state with incomplete HTTP request." )
{
    auto data = make_bytes( "GET / HTTP/1.1\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == false );
    
    data = make_bytes( "GET / HTTP/1.1\r\nHost: www.corvusoft.co.uk\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == false );
}

TEST_CASE( "Assert finalised state with invalid HTTP request." )
{
    auto data = make_bytes( "\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == true );
}

TEST_CASE( "Assert finalised state with complete HTTP response." )
{
    auto data = make_bytes( "HTTP/1.1 200 OK\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == true );
    
    data = make_bytes( "HTTP/1.1 200\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == true );
    
    data = make_bytes( "HTTP/1.1 200 OK\r\nHost: www.corvusoft.co.uk\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == true );
}

TEST_CASE( "Assert finalised state with incomplete HTTP response." )
{
    auto data = make_bytes( "HTTP/1.1 200 OK\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == false );
    
    data = make_bytes( "HTTP/1.1 200\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == false );
    
    data = make_bytes( "HTTP/1.1 200 OK\r\nHost: www.corvusoft.co.uk\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == false );
}

TEST_CASE( "Assert finalised state with invalid HTTP response." )
{
    auto data = make_bytes( "\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    builder->assemble( data );
    REQUIRE( builder->is_finalised( ) == true );
}
