//System Includes
#include <vector>
#include <string>
#include <memory>
#include <utility>

//Project Includes
#include "corvusoft/protocol/message.hpp"

//External Includes
#include <catch.hpp>
#include <corvusoft/core/byte.hpp>

//System Namespaces
using std::pair;
using std::string;
using std::vector;
using std::make_pair;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::Message;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

TEST_CASE( "Get" )
{
    auto message = make_shared< Message >( );
    message->set( "name", "value1" );
    message->set( "name", "value2" );
    REQUIRE( message->get( "name" ) == make_bytes( "value1" ) );
    
    vector< pair< string, Bytes > > properties;
    properties.emplace_back( make_pair( "name", make_bytes( "value1" ) ) );
    properties.emplace_back( make_pair( "name", make_bytes( "value2" ) ) );
    REQUIRE( message->get( ) == properties );
    
    vector< pair< string, Bytes > > results;
    message->get( "name", results );
    REQUIRE( results == properties );
}
