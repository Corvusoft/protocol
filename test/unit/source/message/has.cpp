//System Includes
#include <string>
#include <memory>

//Project Includes
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::Message;

//External Namespaces

TEST_CASE( "Has" )
{
    auto message = make_shared< Message >( );
    REQUIRE( message->has( "" ) == false );
    REQUIRE( message->has( "name" ) == false );
}
