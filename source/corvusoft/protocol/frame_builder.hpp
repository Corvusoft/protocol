/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_FRAME_BUILDER_H
#define _CORVUSOFT_PROTOCOL_FRAME_BUILDER_H 1

//System Includes

//Project Includes
#include <corvusoft/core/byte.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace protocol
    {
        //Forward Declarations
        struct Frame;
        
        class FrameBuilder
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                virtual bool is_malformed( void ) const = 0;
                
                virtual bool is_finalised( void ) const = 0;
                
                virtual std::shared_ptr< Frame > assemble( const core::Bytes& value ) = 0;
                
                virtual core::Bytes disassemble( const std::shared_ptr< Frame > value ) = 0;
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                FrameBuilder( void ) = default;
                
                virtual ~FrameBuilder( void ) = default;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                FrameBuilder( const FrameBuilder& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                FrameBuilder& operator =( const FrameBuilder& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_FRAME_BUILDER_H */
