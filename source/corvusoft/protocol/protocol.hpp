/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_PROTOCOL_H
#define _CORVUSOFT_PROTOCOL_PROTOCOL_H 1

//System Includes
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
                virtual std::error_code teardown( void ) noexcept = 0;
                
                virtual std::error_code setup( const std::shared_ptr< core::RunLoop >& runloop,
                                               const std::shared_ptr< const core::Settings >& settings = nullptr ) noexcept = 0;
                                               
                virtual std::error_code accept( const std::shared_ptr< network::Adaptor >& adaptor ) noexcept = 0; //should return std::errc::wrong_protocol_type if able to service adaptor.
                
                virtual std::error_code compose( const std::shared_ptr< network::Adaptor >& adaptor, const std::shared_ptr< Message >& message ) noexcept = 0;
                
                virtual std::error_code parse( const std::shared_ptr< network::Adaptor > adaptor, const std::shared_ptr< Message >& message ) noexcept = 0;
                
                //Getters
                virtual std::string get_key( void ) const = 0;
                
                //Setters
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                Protocol( void )
                {
                    return;
                };
                
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
