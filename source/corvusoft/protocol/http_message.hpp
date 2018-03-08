/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_HTTP_MESSAGE_H
#define _CORVUSOFT_PROTOCOL_HTTP_MESSAGE_H 1

//System Includes
#include <string>

//Project Includes
#include <corvusoft/protocol/message.hpp>

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
        
        class HTTPMessage final : public Message
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                HTTPMessage( void );
                
                virtual ~HTTPMessage( void );
                
                //Functionality
                bool is_finalised( void ) const override;
                
                bool is_malformed( void ) const override;
                
                core::Bytes to_bytes( void ) const override;
                
                void assemble( const core::Bytes& data ) override;
                
                //Getters
                core::Bytes get( const std::string& name ) const override;
                
                //Setters
                void set( const std::string& name, const core::Bytes& value ) override;
                
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
                HTTPMessage( const HTTPMessage& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                HTTPMessage& operator =( const HTTPMessage& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_HTTP_MESSAGE_H */
