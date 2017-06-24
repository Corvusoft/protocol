/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_MESSAGE_H
#define _CORVUSOFT_PROTOCOL_MESSAGE_H 1

//System Includes
#include <set>
#include <string>
#include <memory>

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
        namespace detail
        {
            struct MessageImpl;
        }
        
        class Message
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Message( void );
                
                virtual ~Message( void );
                
                //Functionality
                void clear( void );
                
                void erase( const std::string& name );
                
                //Getters
                std::set< const std::string > get_names( void ) const;
                
                core::Bytes get( const std::string& name, const core::Bytes& default_value = { } ) const;
                
                //Setters
                void set( const std::string& name, const core::Bytes& value );
                
                void set( const std::string& name, const std::string& value );
                
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
                Message( const Message& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Message& operator =( const Message& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::MessageImpl > m_pimpl;
        };
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_MESSAGE_H */
