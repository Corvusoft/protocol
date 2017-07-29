//System Includes
#include <map>
#include <string>
#include <memory>

//Project Includes
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::Message;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Get" )
{
    auto message = make_shared< Message >( );
    REQUIRE( message->get( "name" ) == Bytes( { } ) );
    REQUIRE( message->get( "name", make_bytes( "default" ) ) == Bytes( { 'd', 'e', 'f', 'a', 'u', 'l', 't' } ) );
    
    multimap< string, Bytes > properties;
    REQUIRE( message->get( ) == properties );
    
    message->get( "name", properties );
    REQUIRE( properties.empty( ) );
}
