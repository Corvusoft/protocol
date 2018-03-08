/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_MESSAGE_H
#define _CORVUSOFT_PROTOCOL_MESSAGE_H 1

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
        
        class Message
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                virtual bool is_finalised( void ) const = 0;
                
                virtual bool is_malformed( void ) const = 0;
                
                virtual core::Bytes to_bytes( void ) const = 0;
                
                virtual void assemble( const core::Bytes& data ) = 0;
                
                //Getters
                virtual core::Bytes get( const std::string& name ) const = 0;
                
                //Setters
                virtual void set( const std::string& name, const core::Bytes& value ) = 0;
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                Message( void ) = default;
                
                virtual ~Message( void ) = default;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                Message( const Message& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Message& operator =( const Message& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_MESSAGE_H */
