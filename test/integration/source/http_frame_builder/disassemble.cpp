//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/http_frame.hpp>
#include <corvusoft/protocol/http_frame_builder.hpp>

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTPFrame;
using corvusoft::protocol::HTTPFrameBuilder;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Assert disassembled request with valid status." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_method( "GET" );
    frame->set_path( "/" );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.1" );
    
    auto data = make_bytes( "GET / HTTP/1.1\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled request with valid status and headers." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_method( "DELETE" );
    frame->set_path( "/resource/1" );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.0" );
    frame->set_header( "Host", "http://www.corvusoft.co.uk" );
    
    auto data = make_bytes( "DELETE /resource/1 HTTP/1.0\r\nHost: http://www.corvusoft.co.uk\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled request with valid status, headers and body." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_method( "POST" );
    frame->set_path( "/resource/1" );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.0" );
    frame->set_header( "Content-Type", "text/plain" );
    frame->set_header( "Content-Length", "17" );
    frame->set_body( "resource payload." );
    
    auto data = make_bytes( "POST /resource/1 HTTP/1.0\r\nContent-Length: 17\r\nContent-Type: text/plain\r\n\r\nresource payload." );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled response with valid status." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.1" );
    frame->set_status_code( "202" );
    frame->set_status_message( "Accepted" );
    
    auto data = make_bytes( "HTTP/1.1 202 Accepted\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
    
    
    frame = make_shared< HTTPFrame >( );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.1" );
    frame->set_status_code( "202" );
    
    data = make_bytes( "HTTP/1.1 202\r\n\r\n" );
    builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled response with valid status and headers." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.0" );
    frame->set_status_code( "201" );
    frame->set_status_message( "Created" );
    frame->set_header( "Host", "http://www.corvusoft.co.uk" );
    
    auto data = make_bytes( "HTTP/1.0 201 Created\r\nHost: http://www.corvusoft.co.uk\r\n\r\n" );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}

TEST_CASE( "Assert disassembled response with valid status, headers and body." )
{
    auto frame = make_shared< HTTPFrame >( );
    frame->set_protocol( "HTTP" );
    frame->set_version( "1.0" );
    frame->set_status_code( "201" );
    frame->set_status_message( "Created" );
    frame->set_header( "Content-Length", "17" );
    frame->set_header( "Content-Type", "text/plain" );
    frame->set_body( "resource payload." );
    
    auto data = make_bytes( "HTTP/1.0 201 Created\r\nContent-Length: 17\r\nContent-Type: text/plain\r\n\r\nresource payload." );
    auto builder = make_shared< HTTPFrameBuilder >( );
    REQUIRE( builder->disassemble( frame ) == data );
}
