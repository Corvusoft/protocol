/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes
#include <corvusoft/protocol/frame.hpp>

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
        
        class HTTPFrame final : public Frame
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                HTTPFrame( void );
                
                virtual ~HTTPFrame( void );
                
                //Functionality
                bool is_request( void ) const;
                
                bool is_response( void ) const;
                
                //Getters
                core::Bytes get_body( void ) const;
                
                core::Bytes get_path( void ) const;
                
                core::Bytes get_method( void ) const;
                
                core::Bytes get_version( void ) const;
                
                core::Bytes get_protocol( void ) const;
                
                core::Bytes get_status_code( void ) const;
                
                core::Bytes get_status_message( void ) const;
                
                std::multimap< std::string, core::Bytes > get_headers( void ) const;
                
                //Setters
                void set_body( const core::Bytes& value );
                
                void set_body( const std::string& value );
                
                void set_path( const std::string& value );
                
                void set_method( const std::string& value );
                
                void set_version( const std::string& value );
                
                void set_protocol( const std::string& value );
                
                void set_status_code( const std::string& value );
                
                void set_status_message( const std::string& value );
                
                void set_header( const std::string& name, const std::string& value );
                
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
                HTTPFrame( const HTTPFrame& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                HTTPFrame& operator =( const HTTPFrame& value ) = delete;
                
                //Properties
        };
    }
}
