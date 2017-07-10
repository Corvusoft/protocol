/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_PROTOCOL_HTTP_H
#define _CORVUSOFT_PROTOCOL_HTTP_H 1

//System Includes
#include <list>
#include <string>
#include <memory>
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
                HTTP( void );
                
                virtual ~HTTP( void );
                
                //Functionality
                virtual std::error_code teardown( void ) noexcept override;
                
                virtual std::error_code setup( const std::shared_ptr< core::RunLoop > runloop, const std::shared_ptr< const core::Settings > settings = nullptr ) noexcept override;
                
                virtual std::error_code parse( const std::shared_ptr< network::Adaptor > adaptor, const std::shared_ptr< Message > message ) noexcept override;
                
                virtual std::error_code parse( const std::shared_ptr< network::Adaptor > adaptor, const std::list< const std::shared_ptr< Message > > messages ) noexcept override;
                
                virtual std::error_code compose( const std::shared_ptr< network::Adaptor > adaptor, const std::shared_ptr< Message > message ) noexcept override;
                
                virtual std::error_code compose( const std::shared_ptr< network::Adaptor > adaptor, const std::list< const std::shared_ptr< Message > > messages ) noexcept override;
                
                //Getters
                virtual const std::string get_name( void ) const override;
                
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
