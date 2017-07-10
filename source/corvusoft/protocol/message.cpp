/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <utility>

//Project Includes
#include "corvusoft/protocol/message.hpp"
#include "corvusoft/protocol/detail/message_impl.hpp"

//External Includes

//System Namespaces
using std::vector;
using std::string;
using std::make_pair;
using std::unique_ptr;

//Project Namespaces
using corvusoft::protocol::detail::MessageImpl;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;

namespace corvusoft
{
    namespace protocol
    {
        Message::Message( void ) : m_pimpl( new MessageImpl )
        {
            return;
        }
        
        Message::~Message( void )
        {
            return;
        }
        
        void Message::clear( void )
        {
            m_pimpl->properties.clear( );
        }
        
        void Message::erase( const std::string& name )
        {
            m_pimpl->properties.erase( name );
        }
        
        vector< const string > Message::get_names( void ) const
        {
            vector< const string > names;
            
            for ( const auto entry : m_pimpl->properties )
                names.emplace_back( entry.first );
                
            return names;
        }
        
        Bytes Message::get( const string& name, const Bytes& default_value ) const
        {
            return ( m_pimpl->properties.count( name ) ) ? m_pimpl->properties.lower_bound( name )->second : default_value;
        }
        
        void Message::set( const string& name, const Bytes& value )
        {
            m_pimpl->properties.emplace( make_pair( name, value ) );
        }
        
        void Message::set( const string& name, const string& value )
        {
            set( name, make_bytes( value ) );
        }
    }
}
