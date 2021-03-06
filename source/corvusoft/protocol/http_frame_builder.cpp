/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <iterator>

//Project Includes
#include "corvusoft/protocol/http_frame_builder.hpp"
#include "corvusoft/protocol/detail/http_frame_builder_impl.hpp"

//External Includes

//System Namespaces
using std::end;
using std::begin;
using std::shared_ptr;
using std::dynamic_pointer_cast;

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
            m_pimpl->data.insert( end( m_pimpl->data ), begin( value ), end( value ) );
            m_pimpl->assemble( );
            return m_pimpl->frame;
        }
        
        Bytes HTTPFrameBuilder::disassemble( const shared_ptr< Frame > value )
        {
            m_pimpl->frame = std::dynamic_pointer_cast< HTTPFrame >( value );
            m_pimpl->disassemble( );
            return m_pimpl->data;
        }
    }
}
