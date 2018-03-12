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
using corvusoft::protocol::Frame;
using corvusoft::protocol::HTTPFrameBuilder;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Assert disassembled request with valid status." )
{
    auto frame = make_shared< Frame >( );
    frame->meta.emplace( "method", make_bytes( "GET" ) );
    frame->meta.emplace( "path", make_bytes( "/" ) );
    frame->meta.emplace( "protocol", make_bytes( "HTTP" ) );
    frame->meta.emplace( "version", make_bytes( "1.1" ) );
    
    auto data = make_bytes( "GET / HTTP/1.1\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled request with valid status and headers." )
{
    auto frame = make_shared< Frame >( );
    frame->meta.emplace( "method", make_bytes( "DELETE" ) );
    frame->meta.emplace( "path", make_bytes( "/resource/1" ) );
    frame->meta.emplace( "protocol", make_bytes( "HTTP" ) );
    frame->meta.emplace( "version", make_bytes( "1.0" ) );
    frame->meta.emplace( "Host", make_bytes( "http://www.corvusoft.co.uk" ) );
    
    auto data = make_bytes( "DELETE /resource/1 HTTP/1.0\r\nHost: http://www.corvusoft.co.uk\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled request with valid status, headers and body." )
{
    auto frame = make_shared< Frame >( );
    frame->meta.emplace( "method", make_bytes( "POST" ) );
    frame->meta.emplace( "path", make_bytes( "/resource/1" ) );
    frame->meta.emplace( "protocol", make_bytes( "HTTP" ) );
    frame->meta.emplace( "version", make_bytes( "1.0" ) );
    frame->meta.emplace( "Content-Type", make_bytes( "text/plain" ) );
    frame->meta.emplace( "Content-Length", make_bytes( "17" ) );
    frame->data.emplace( "body", make_bytes( "resource payload." ) );
    
    auto data = make_bytes( "POST /resource/1 HTTP/1.0\r\nContent-Length: 17\r\nContent-Type: text/plain\r\n\r\nresource payload." );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled response with valid status." )
{
    auto frame = make_shared< Frame >( );
    frame->meta.emplace( "protocol", make_bytes( "HTTP" ) );
    frame->meta.emplace( "version", make_bytes( "1.1" ) );
    frame->meta.emplace( "status", make_bytes( "202" ) );
    frame->meta.emplace( "message", make_bytes( "Accepted" ) );
    
    auto data = make_bytes( "HTTP/1.1 202 Accepted\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
    
    
    frame = make_shared< Frame >( );
    frame->meta.emplace( "protocol", make_bytes( "HTTP" ) );
    frame->meta.emplace( "version", make_bytes( "1.1" ) );
    frame->meta.emplace( "status", make_bytes( "202" ) );
    
    data = make_bytes( "HTTP/1.1 202\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled response with valid status and headers." )
{
    auto frame = make_shared< Frame >( );
    frame->meta.emplace( "protocol", make_bytes( "HTTP" ) );
    frame->meta.emplace( "version", make_bytes( "1.0" ) );
    frame->meta.emplace( "status", make_bytes( "201" ) );
    frame->meta.emplace( "message", make_bytes( "Created" ) );
    frame->meta.emplace( "Host", make_bytes( "http://www.corvusoft.co.uk" ) );
    
    auto data = make_bytes( "HTTP/1.0 201 Created\r\nHost: http://www.corvusoft.co.uk\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled response with valid status, headers and body." )
{
    auto frame = make_shared< Frame >( );
    frame->meta.emplace( "protocol", make_bytes( "HTTP" ) );
    frame->meta.emplace( "version", make_bytes( "1.0" ) );
    frame->meta.emplace( "status", make_bytes( "201" ) );
    frame->meta.emplace( "message", make_bytes( "Created" ) );
    frame->meta.emplace( "Content-Length", make_bytes( "17" ) );
    frame->meta.emplace( "Content-Type", make_bytes( "text/plain" ) );
    frame->data.emplace( "body", make_bytes( "resource payload." ) );
    
    auto data = make_bytes( "HTTP/1.0 201 Created\r\nContent-Length: 17\r\nContent-Type: text/plain\r\n\r\nresource payload." );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}
