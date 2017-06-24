//System Includes
#include <set>
#include <string>
#include <memory>

//Project Includes
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::set;
using std::string;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::Message;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Get names" )
{
    auto message = make_shared< Message >( );
    message->set( "name", "value" );
    message->set( "data", make_bytes( "123abc" ) );
    
    REQUIRE( message->get_names( ) == set< const string >( { "name", "data" } ) );
}
