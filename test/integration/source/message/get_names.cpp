//System Includes
#include <memory>
#include <string>
#include <vector>

//Project Includes
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::string;
using std::vector;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::Message;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Get names" )
{
    auto message = make_shared< Message >( );
    message->set( "name1", "value1" );
    REQUIRE( message->get_names( ) == vector< const string >( { "name1" } ) );
    
    message->set( "name2", "value2" );
    REQUIRE( message->get_names( ) == vector< const string >( { "name1", "name2" } ) );
}
