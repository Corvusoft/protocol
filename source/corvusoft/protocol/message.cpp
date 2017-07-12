/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <algorithm>

//Project Includes
#include "corvusoft/protocol/message.hpp"
#include "corvusoft/protocol/detail/message_impl.hpp"

//External Includes

//System Namespaces
using std::pair;
using std::vector;
using std::string;
using std::make_pair;
using std::remove_if;
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
        
        void Message::erase( const string& name )
        {
            auto& properties = m_pimpl->properties;
            properties.erase(
                remove_if( properties.begin( ), properties.end( ),
                           [ &name ]( const auto & property )
            {
                return property.first == name;
            }
                         ),
            properties.end( )
            );
        }
        
        vector< pair< string, Bytes > > Message::get( void ) const
        {
            return m_pimpl->properties;
        }
        
        Bytes Message::get( const string& name, const Bytes& default_value ) const
        {
            vector< pair< string, Bytes > > properties;
            get( name, properties );
            
            return properties.empty( ) ? default_value : properties.at( 0 ).second;
        }
        
        void Message::get( const string& name, vector< pair< string, Bytes > >& values ) const
        {
            for ( const auto property : m_pimpl->properties )
                if ( property.first == name )
                    values.emplace_back( property );
        }
        
        void Message::set( const string& name, const Bytes& value )
        {
            m_pimpl->properties.emplace_back( make_pair( name, value ) );
        }
        
        void Message::set( const string& name, const string& value )
        {
            set( name, make_bytes( value ) );
        }
    }
}
