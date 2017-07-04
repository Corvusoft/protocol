#ifndef _CORVUSOFT_MOCK_ADAPTOR_H
#define _CORVUSOFT_MOCK_ADAPTOR_H 1

//System Includes
#include <string>
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/network/adaptor.hpp>

//External Includes
#include <corvusoft/core/byte.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

//Forward Declarations
namespace core
{
    class RunLoop;
    class Settings;
}

class MockAdaptor final : public corvusoft::network::Adaptor
{
    public:
        //Friends
        
        //Definitions
        
        //Constructors
        MockAdaptor( const corvusoft::core::Bytes& data = { } ) : Adaptor( "" ),
            m_data( data )
        {
            return;
        }
        
        virtual ~MockAdaptor( void )
        {
            return;
        }
        
        //Functionality
        virtual std::error_code teardown( void ) override
        {
            return std::error_code( );
        }
        
        virtual std::error_code setup( const std::shared_ptr< const corvusoft::core::Settings >& ) override
        {
            return std::error_code( );
        }
        
        virtual std::error_code setup( const std::shared_ptr< corvusoft::core::RunLoop >&, const std::shared_ptr< const corvusoft::core::Settings >& ) override
        {
            return std::error_code( );
        }
        
        virtual std::error_code close( void ) override
        {
            return std::error_code( );
        }
        
        virtual std::error_code open( const std::shared_ptr< const corvusoft::core::Settings >& ) override
        {
            return std::error_code( );
        }
        
        virtual std::error_code listen( const std::shared_ptr< const corvusoft::core::Settings >& ) override
        {
            return std::error_code( );
        }
        
        virtual const corvusoft::core::Bytes peek( std::error_code& ) override
        {
            return m_data;
        }
        
        virtual const corvusoft::core::Bytes consume( std::error_code& ) override
        {
            return m_data;
        }
        
        virtual std::size_t produce( const corvusoft::core::Bytes& data, std::error_code& ) override
        {
            m_data = data;
            return m_data.size( );
        }
        
        //Getters
        corvusoft::core::Bytes get_data( void ) const
        {
            return m_data;
        }
        
        virtual std::string get_key( void ) const override
        {
            return "";
        }
        
        virtual std::string get_local_endpoint( void ) override
        {
            return "";
        }
        
        virtual std::string get_remote_endpoint( void ) override
        {
            return "";
        }
        
        virtual std::shared_ptr< corvusoft::core::RunLoop > get_runloop( void ) override
        {
            return nullptr;
        }
        
        //Setters
        virtual void set_open_handler( const std::function< void ( const std::shared_ptr< corvusoft::network::Adaptor > ) >& ) override
        {
            return;
        }
        
        virtual void set_close_handler( const std::function< void ( const std::shared_ptr< corvusoft::network::Adaptor > ) >& ) override
        {
            return;
        }
        
        virtual void set_error_handler( const std::function< void ( const std::shared_ptr< corvusoft::network::Adaptor >, const std::error_code ) >& ) override
        {
            return;
        }
        
        virtual void set_message_handler( const std::function< void ( const std::shared_ptr< corvusoft::network::Adaptor > ) >& ) override
        {
            return;
        }
        
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
        
        //Functionality
        
        //Getters
        
        //Setters
        
        //Operators
        
        //Properties
        corvusoft::core::Bytes m_data;
};

#endif  /* _CORVUSOFT_MOCK_ADAPTOR_H */
