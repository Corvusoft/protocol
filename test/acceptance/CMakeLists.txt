cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

project( "acceptance test suite" LANGUAGES CXX )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
add_executable( compose_http_request_acceptance_test_suite ${SOURCE_DIR}/compose_http_request.cpp )
target_link_libraries( compose_http_request_acceptance_test_suite ${STATIC_LIBRARY_NAME} )
add_test( compose_http_request_acceptance_test_suite ${EXECUTABLE_OUTPUT_PATH}/compose_http_request_acceptance_test_suite )

add_executable( parse_http_request_acceptance_test_suite ${SOURCE_DIR}/parse_http_request.cpp )
target_link_libraries( parse_http_request_acceptance_test_suite ${STATIC_LIBRARY_NAME} )
add_test( parse_http_request_acceptance_test_suite ${EXECUTABLE_OUTPUT_PATH}/parse_http_request_acceptance_test_suite )
