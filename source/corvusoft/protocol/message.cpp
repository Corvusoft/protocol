/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/protocol/message.hpp"
#include "corvusoft/protocol/detail/message_impl.hpp"

//External Includes

//System Namespaces
using std::set;
using std::string;
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
            m_pimpl->names.clear( );
            m_pimpl->properties.clear( );
        }
        
        void Message::erase( const std::string& name )
        {
            m_pimpl->names.erase( name );
            m_pimpl->properties.erase( name );
        }
        
        std::set< const std::string > Message::get_names( void ) const
        {
            return m_pimpl->names;
        }
        
        Bytes Message::get( const string& name, const Bytes& default_value ) const
        {
            return ( m_pimpl->properties.count( name ) ) ? m_pimpl->properties.at( name ) : default_value;
        }
        
        void Message::set( const string& name, const Bytes& value )
        {
            m_pimpl->names.insert( name );
            m_pimpl->properties[ name ] = value;
        }
        
        void Message::set( const string& name, const string& value )
        {
            set( name, make_bytes( value ) );
        }
    }
}
