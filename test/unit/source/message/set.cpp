//System Includes
#include <memory>

//Project Includes
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::Message;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Set" )
{
    auto message = make_shared< Message >( );
    REQUIRE_NOTHROW( message->set( "name", "value" ) );
    REQUIRE_NOTHROW( message->set( "name", make_bytes( "value" ) ) );
}
