/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <regex>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iterator>
#include <algorithm>

//Project Includes
#include "corvusoft/protocol/http.hpp"

//External Includes
#include <corvusoft/core/byte.hpp>
#include <corvusoft/core/settings.hpp>
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/network/adaptor.hpp>

//System Namespaces
using std::size_t;
using std::regex;
using std::smatch;
using std::regex_match;
using std::string;
using std::vector;
using std::find_if;
using std::shared_ptr;
using std::error_code;
using std::make_error_code;

//Project Namespaces

//External Namespaces
using corvusoft::core::Byte;
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;
using corvusoft::core::RunLoop;
using corvusoft::core::Settings;
using corvusoft::network::Adaptor;

namespace corvusoft
{
    namespace protocol
    {
        HTTP::HTTP( void ) : Protocol( )
        {
            return;
        }
        
        HTTP::~HTTP( void )
        {
            return;
        }
        
        error_code HTTP::teardown( void ) noexcept
        {
            return error_code( );
        }
        
        error_code HTTP::setup( const shared_ptr< RunLoop >&, const shared_ptr< const Settings >& ) noexcept
        {
            return error_code( );
        }
        
        error_code HTTP::accept( const shared_ptr< Adaptor >& ) noexcept
        {
            return error_code( );
        }
        
        error_code HTTP::compose( const shared_ptr< Adaptor >&, const shared_ptr< Message >& ) noexcept
        {
            return error_code( );
        }
        
        error_code HTTP::parse( const shared_ptr< Adaptor >, const shared_ptr< Message >& ) noexcept
        {
            //mention in documentation this only reads to the start of body!
            return error_code( );
        }
        
        string HTTP::get_name( void ) const
        {
            return "HTTP";
        }
    }
}
