/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_PROTOCOL_H
#define _CORVUSOFT_PROTOCOL_PROTOCOL_H 1

//System Includes
#include <list>
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/protocol/message.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    namespace core
    {
        class RunLoop;
        class Settings;
    }
    
    namespace network
    {
        class Adaptor;
    }
    
    namespace protocol
    {
        //Forward Declarations
        
        class Protocol
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                virtual std::error_code setup( const std::shared_ptr< const core::Settings > settings = nullptr ) = 0;
                
                virtual std::error_code teardown( void ) = 0;
                
                virtual void initiate( const std::shared_ptr< network::Adaptor > adaptor, const std::function< std::error_code ( const std::shared_ptr< network::Adaptor >, const std::error_code ) > completion_handler ) = 0;
                
                virtual void terminate( const std::shared_ptr< network::Adaptor > adaptor, const std::function< std::error_code ( const std::shared_ptr< network::Adaptor >, const std::error_code ) > completion_handler ) = 0;
                
                virtual void parse( const std::shared_ptr< network::Adaptor > adaptor, const std::function< std::error_code ( const std::shared_ptr< network::Adaptor >, const std::shared_ptr< Message >, const std::error_code ) > completion_handler ) = 0;
                
                virtual void compose( const std::shared_ptr< network::Adaptor > adaptor, const std::shared_ptr< Message > message, const std::function< std::error_code ( const std::shared_ptr< network::Adaptor >, const std::error_code ) > completion_handler ) = 0;
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                Protocol( void ) = default;
                
                virtual ~Protocol( void ) = default;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                Protocol( const Protocol& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Protocol& operator =( const Protocol& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_PROTOCOL_H */
