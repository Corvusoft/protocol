//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/frame.hpp>
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

TEST_CASE( "Assert assembled request with valid status." )
{
    auto data = make_bytes( "GET / HTTP/1.1\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    auto frame = builder->assemble( data );
    
    auto iterator = frame->meta.find( "method" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "GET" ) );
    
    iterator = frame->meta.find( "path" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "/" ) );
    
    iterator = frame->meta.find( "protocol" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "HTTP" ) );
    
    iterator = frame->meta.find( "version" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "1.1" ) );
}

TEST_CASE( "Assert assembled request with valid status and headers." )
{
    auto data = make_bytes( "DELETE /resource/1 HTTP/1.0\r\nHost: http://www.corvusoft.co.uk\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    auto frame = builder->assemble( data );
    
    auto iterator = frame->meta.find( "method" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "DELETE" ) );
    
    iterator = frame->meta.find( "path" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "/resource/1" ) );
    
    iterator = frame->meta.find( "protocol" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "HTTP" ) );
    
    iterator = frame->meta.find( "version" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "1.0" ) );
    
    iterator = frame->meta.find( "Host" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "http://www.corvusoft.co.uk" ) );
}

TEST_CASE( "Assert assembled request with valid status, headers and body." )
{
    auto data = make_bytes( "POST /resource/1 HTTP/1.0\r\nContent-Type: text/plain\r\nContent-Length:17\r\n\r\nresource payload." );
    auto builder = make_shared< HTTPFrameBuilder >( );
    auto frame = builder->assemble( data );
    
    auto iterator = frame->meta.find( "method" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "POST" ) );
    
    iterator = frame->meta.find( "path" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "/resource/1" ) );
    
    iterator = frame->meta.find( "protocol" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "HTTP" ) );
    
    iterator = frame->meta.find( "version" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "1.0" ) );
    
    iterator = frame->meta.find( "Content-Type" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "text/plain" ) );
    
    iterator = frame->meta.find( "Content-Length" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "17" ) );
    
    iterator = frame->data.find( "body" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "resource payload." ) );
}

TEST_CASE( "Assert assembled request with no '\\r\\n\\r\\n' line." )
{
    auto data = make_bytes( "POST /resource/1 HTTP/1.0\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    auto frame = builder->assemble( data );
    REQUIRE( frame == nullptr );
}

TEST_CASE( "Assert assembled response with valid status." )
{
    auto data = make_bytes( "HTTP/1.1 200 OK\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    auto frame = builder->assemble( data );
    
    auto iterator = frame->meta.find( "protocol" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "HTTP" ) );
    
    iterator = frame->meta.find( "version" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "1.1" ) );
    
    iterator = frame->meta.find( "status" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "200" ) );
    
    iterator = frame->meta.find( "message" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "OK" ) );
    
    
    data = make_bytes( "HTTP/1.1 200\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    frame = builder->assemble( data );
    
    iterator = frame->meta.find( "protocol" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "HTTP" ) );
    
    iterator = frame->meta.find( "version" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "1.1" ) );
    
    iterator = frame->meta.find( "status" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "200" ) );
    
    iterator = frame->meta.find( "message" );
    REQUIRE( iterator == frame->meta.end( ) );
}

TEST_CASE( "Assert assembled response with valid status and headers." )
{
    auto data = make_bytes( "HTTP/1.0 201 Created\r\nHost: http://www.corvusoft.co.uk\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    auto frame = builder->assemble( data );
    
    auto iterator = frame->meta.find( "protocol" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "HTTP" ) );
    
    iterator = frame->meta.find( "version" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "1.0" ) );
    
    iterator = frame->meta.find( "status" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "201" ) );
    
    iterator = frame->meta.find( "message" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "Created" ) );
    
    iterator = frame->meta.find( "Host" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "http://www.corvusoft.co.uk" ) );
}

TEST_CASE( "Assert assembled response with valid status, headers and body." )
{
    auto data = make_bytes( "HTTP/1.0 201 Created\r\nContent-Type: text/plain\r\nContent-Length:17\r\n\r\nresource payload." );
    auto builder = make_shared< HTTPFrameBuilder >( );
    auto frame = builder->assemble( data );
    
    auto iterator = frame->meta.find( "protocol" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "HTTP" ) );
    
    iterator = frame->meta.find( "version" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "1.0" ) );
    
    iterator = frame->meta.find( "status" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "201" ) );
    
    iterator = frame->meta.find( "message" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "Created" ) );
    
    iterator = frame->meta.find( "Content-Type" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "text/plain" ) );
    
    iterator = frame->meta.find( "Content-Length" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "17" ) );
    
    iterator = frame->data.find( "body" );
    REQUIRE( iterator not_eq frame->meta.end( ) );
    REQUIRE( iterator->second == make_bytes( "resource payload." ) );
}

TEST_CASE( "Assert assembled response with no '\\r\\n\\r\\n' line." )
{
    auto data = make_bytes( "HTTP/1.1 200 OK\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    auto frame = builder->assemble( data );
    REQUIRE( frame == nullptr );
}
