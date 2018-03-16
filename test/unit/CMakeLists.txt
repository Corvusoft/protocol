cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

project( "unit test suite" LANGUAGES CXX )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
add_executable( http_frame_constructor_unit_test_suite ${SOURCE_DIR}/http_frame/constructor.cpp )
target_link_libraries( http_frame_constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_constructor_unit_test_suite )

add_executable( http_frame_destructor_unit_test_suite ${SOURCE_DIR}/http_frame/destructor.cpp )
target_link_libraries( http_frame_destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_destructor_unit_test_suite )

add_executable( http_frame_getters_unit_test_suite ${SOURCE_DIR}/http_frame/getters.cpp )
target_link_libraries( http_frame_getters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_getters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_getters_unit_test_suite )

add_executable( http_frame_is_request_unit_test_suite ${SOURCE_DIR}/http_frame/is_request.cpp )
target_link_libraries( http_frame_is_request_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_is_request_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_is_request_unit_test_suite )

add_executable( http_frame_is_response_unit_test_suite ${SOURCE_DIR}/http_frame/is_response.cpp )
target_link_libraries( http_frame_is_response_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_is_response_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_is_response_unit_test_suite )

add_executable( http_frame_setters_unit_test_suite ${SOURCE_DIR}/http_frame/setters.cpp )
target_link_libraries( http_frame_setters_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_setters_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_setters_unit_test_suite )

add_executable( http_frame_builder_constructor_unit_test_suite ${SOURCE_DIR}/http_frame_builder/constructor.cpp )
target_link_libraries( http_frame_builder_constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_builder_constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_builder_constructor_unit_test_suite )

add_executable( http_frame_builder_destructor_unit_test_suite ${SOURCE_DIR}/http_frame_builder/destructor.cpp )
target_link_libraries( http_frame_builder_destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_builder_destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_builder_destructor_unit_test_suite )

add_executable( http_frame_builder_is_finalised_unit_test_suite ${SOURCE_DIR}/http_frame_builder/is_finalised.cpp )
target_link_libraries( http_frame_builder_is_finalised_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_builder_is_finalised_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_builder_is_finalised_unit_test_suite )

add_executable( http_frame_builder_is_malformed_unit_test_suite ${SOURCE_DIR}/http_frame_builder/is_malformed.cpp )
target_link_libraries( http_frame_builder_is_malformed_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_frame_builder_is_malformed_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_frame_builder_is_malformed_unit_test_suite )

add_executable( http_status_is_client_error_unit_test_suite ${SOURCE_DIR}/http_status/is_client_error.cpp )
target_link_libraries( http_status_is_client_error_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_status_is_client_error_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_status_is_client_error_unit_test_suite )

add_executable( http_status_is_informational_unit_test_suite ${SOURCE_DIR}/http_status/is_informational.cpp )
target_link_libraries( http_status_is_informational_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_status_is_informational_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_status_is_informational_unit_test_suite )

add_executable( http_status_is_redirectional_unit_test_suite ${SOURCE_DIR}/http_status/is_redirectional.cpp )
target_link_libraries( http_status_is_redirectional_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_status_is_redirectional_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_status_is_redirectional_unit_test_suite )

add_executable( http_status_is_server_error_unit_test_suite ${SOURCE_DIR}/http_status/is_server_error.cpp )
target_link_libraries( http_status_is_server_error_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_status_is_server_error_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_status_is_server_error_unit_test_suite )

add_executable( http_status_is_successful_unit_test_suite ${SOURCE_DIR}/http_status/is_successful.cpp )
target_link_libraries( http_status_is_successful_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_status_is_successful_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_status_is_successful_unit_test_suite )

add_executable( http_status_make_status_code_unit_test_suite ${SOURCE_DIR}/http_status/make_status_code.cpp )
target_link_libraries( http_status_make_status_code_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_status_make_status_code_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_status_make_status_code_unit_test_suite )

add_executable( http_status_make_status_message_unit_test_suite ${SOURCE_DIR}/http_status/make_status_message.cpp )
target_link_libraries( http_status_make_status_message_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( http_status_make_status_message_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_status_make_status_message_unit_test_suite )
