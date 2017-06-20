//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include "corvusoft/protocol/http.hpp"

//External Includes
#include <catch.hpp>
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/core/settings.hpp>

//System Namespaces
using std::error_code;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using corvusoft::protocol::HTTP;

//External Namespaces
using corvusoft::core::RunLoop;
using corvusoft::core::Settings;

TEST_CASE( "Setup" )
{
    const auto protocol = make_shared< HTTP >( );
    auto status = protocol->setup( nullptr );
    REQUIRE( status == error_code( ) );
    
    status = protocol->setup( nullptr, nullptr );
    REQUIRE( status == error_code( ) );
    
    status = protocol->setup( nullptr, make_shared< Settings >( ) );
    REQUIRE( status == error_code( ) );
    
    status = protocol->setup( make_shared< RunLoop >( ), nullptr );
    REQUIRE( status == error_code( ) );
    
    status = protocol->setup( make_shared< RunLoop >( ), make_shared< Settings >( ) );
    REQUIRE( status == error_code( ) );
}
