/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <memory>

//Project Includes
#include <corvusoft/protocol/frame_builder.hpp>

//External Includes
#include <corvusoft/core/byte.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace protocol
    {
        //Forward Declarations
        
        namespace detail
        {
            struct HTTPFrameBuilderImpl;
        }
        
        class HTTPFrameBuilder final : public FrameBuilder
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                HTTPFrameBuilder( void );
                
                virtual ~HTTPFrameBuilder( void );
                
                //Functionality
                bool is_malformed( void ) const override;
                
                bool is_finalised( void ) const override;
                
                std::shared_ptr< Frame > assemble( const core::Bytes& value ) override;
                
                core::Bytes disassemble( const std::shared_ptr< Frame > value ) override;
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                HTTPFrameBuilder( const HTTPFrameBuilder& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                HTTPFrameBuilder& operator =( const HTTPFrameBuilder& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::HTTPFrameBuilderImpl > m_pimpl;
        };
    }
}
