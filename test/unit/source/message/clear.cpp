//System Includes
#include <memory>

//Project Includes
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::Message;

//External Namespaces

TEST_CASE( "Clear" )
{
    auto message = make_shared< Message >( );
    REQUIRE_NOTHROW( message->clear( ) );
}
