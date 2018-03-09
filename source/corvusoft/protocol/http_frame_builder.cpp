/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/protocol/http_frame_builder.hpp"
#include "corvusoft/protocol/detail/http_frame_builder_impl.hpp"

//External Includes

//System Namespaces
using std::shared_ptr;

//Project Namespaces
using corvusoft::protocol::detail::HTTPFrameBuilderImpl;

//External Namespaces
using corvusoft::core::Bytes;

namespace corvusoft
{
    namespace protocol
    {
        HTTPFrameBuilder::HTTPFrameBuilder( void ) : FrameBuilder( ),
            m_pimpl( new HTTPFrameBuilderImpl )
        {
            return;
        }
        
        HTTPFrameBuilder::~HTTPFrameBuilder( void )
        {
            return;
        }
        
        bool HTTPFrameBuilder::is_malformed( void ) const
        {
            return m_pimpl->is_malformed;
        }
        
        bool HTTPFrameBuilder::is_finalised( void ) const
        {
            return m_pimpl->is_finalised;
        }
        
        shared_ptr< Frame > HTTPFrameBuilder::assemble( const Bytes& value )
        {
            m_pimpl->data.insert( m_pimpl->data.begin( ), value.begin( ), value.end( ) );
            m_pimpl->assemble( );
            return m_pimpl->frame;
        }
        
        Bytes HTTPFrameBuilder::disassemble( const shared_ptr< Frame > value )
        {
            m_pimpl->frame = value;
            m_pimpl->disassemble( );
            return m_pimpl->data;
        }
    }
}
