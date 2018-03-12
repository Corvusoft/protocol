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
add_executable( http_frame_builder_assemble_integration_test_suite ${SOURCE_DIR}/http_frame_builder/assemble.cpp )
target_link_libraries( http_frame_builder_assemble_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_builder_assemble_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_builder_assemble_integration_test_suite )

add_executable( http_frame_builder_disassemble_integration_test_suite ${SOURCE_DIR}/http_frame_builder/disassemble.cpp )
target_link_libraries( http_frame_builder_disassemble_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_builder_disassemble_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_builder_disassemble_integration_test_suite )

add_executable( http_frame_builder_is_finalised_integration_test_suite ${SOURCE_DIR}/http_frame_builder/is_finalised.cpp )
target_link_libraries( http_frame_builder_is_finalised_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_builder_is_finalised_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_builder_is_finalised_integration_test_suite )

add_executable( http_frame_builder_is_malformed_integration_test_suite ${SOURCE_DIR}/http_frame_builder/is_malformed.cpp )
target_link_libraries( http_frame_builder_is_malformed_integration_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_builder_is_malformed_integration_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_builder_is_malformed_integration_test_suite )
