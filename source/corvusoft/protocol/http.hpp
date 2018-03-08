/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_HTTP_H
#define _CORVUSOFT_PROTOCOL_HTTP_H 1

//System Includes
#include <string>
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/protocol/message.hpp>
#include <corvusoft/protocol/protocol.hpp>

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
        namespace detail
        {
            struct HTTPImpl;
        }
        
        class HTTP final : public Protocol
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                HTTP( const std::shared_ptr< core::RunLoop > runloop );
                
                virtual ~HTTP( void );
                
                //Functionality
                std::error_code setup( const std::shared_ptr< const core::Settings > settings = nullptr ) override;
                
                std::error_code teardown( void ) override;
                
                void initiate( const std::shared_ptr< network::Adaptor > adaptor, const std::function< std::error_code ( const std::shared_ptr< network::Adaptor >, const std::error_code ) > completion_handler ) override;
                
                void terminate( const std::shared_ptr< network::Adaptor > adaptor, const std::function< std::error_code ( const std::shared_ptr< network::Adaptor >, const std::error_code ) > completion_handler ) override;
                
                void parse( const std::shared_ptr< network::Adaptor > adaptor, const std::function< std::error_code ( const std::shared_ptr< network::Adaptor >, const std::shared_ptr< Message >, const std::error_code ) > completion_handler ) override;
                
                void compose( const std::shared_ptr< network::Adaptor > adaptor, const std::shared_ptr< Message > message, const std::function< std::error_code ( const std::shared_ptr< network::Adaptor >, const std::error_code ) > completion_handler ) override;
                
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
                HTTP( void ) = delete;
                
                HTTP( const HTTP& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                HTTP& operator =( const HTTP& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::HTTPImpl > m_pimpl;
        };
    }
}

#endif  /* _CORVUSOFT_PROTOCOL_HTTP_H */
