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

TEST_CASE( "Erase" )
{
    auto message = make_shared< Message >( );
    message->set( "forename", "Bob" );
    message->set( "surname", make_bytes( "Metcalfe" ) );
    message->erase( "forename" );
    
    REQUIRE( message->get( "forename" ) == make_bytes( "" ) );
    REQUIRE( message->get( "surname" ) == make_bytes( "Metcalfe" ) );
    REQUIRE( message->get_names( ) == set< const string >( { "surname" } ) );
}
