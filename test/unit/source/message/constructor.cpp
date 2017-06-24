//System Includes

//Project Includes
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces

//Project Namespaces
using corvusoft::protocol::Message;

//External Namespaces

TEST_CASE( "Constructor" )
{
    REQUIRE_NOTHROW( Message( ) );
}
