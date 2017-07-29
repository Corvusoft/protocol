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
    message->set( "name1", "value1" );
    message->set( "name1", "value2" );
    message->set( "name2", "value3" );
    REQUIRE( message->has( "name1" ) == true );
    REQUIRE( message->has( "name2" ) == true );
    REQUIRE( message->has( "name3" ) == false );
}
