cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

project( "integration test suite" LANGUAGES CXX )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
add_executable( http_compose_integration_test_suite ${SOURCE_DIR}/http/compose.cpp )
target_link_libraries( http_compose_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_compose_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_compose_integration_test_suite )

add_executable( http_parse_integration_test_suite ${SOURCE_DIR}/http/parse.cpp )
target_link_libraries( http_parse_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_parse_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_parse_integration_test_suite )

add_executable( message_clear_integration_test_suite ${SOURCE_DIR}/message/clear.cpp )
target_link_libraries( message_clear_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( message_clear_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_clear_integration_test_suite )

add_executable( message_erase_integration_test_suite ${SOURCE_DIR}/message/erase.cpp )
target_link_libraries( message_erase_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( message_erase_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_erase_integration_test_suite )

add_executable( message_get_integration_test_suite ${SOURCE_DIR}/message/get.cpp )
target_link_libraries( message_get_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( message_get_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_get_integration_test_suite )
