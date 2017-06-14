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
add_executable( accept_unit_test_suite ${SOURCE_DIR}/accept.cpp )
target_link_libraries( accept_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( accept_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/accept_unit_test_suite )

add_executable( constructor_unit_test_suite ${SOURCE_DIR}/constructor.cpp )
target_link_libraries( constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/constructor_unit_test_suite )

add_executable( destructor_unit_test_suite ${SOURCE_DIR}/destructor.cpp )
target_link_libraries( destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/destructor_unit_test_suite )

add_executable( get_key_unit_test_suite ${SOURCE_DIR}/get_key.cpp )
target_link_libraries( get_key_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( get_key_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/get_key_unit_test_suite )

add_executable( setup_unit_test_suite ${SOURCE_DIR}/setup.cpp )
target_link_libraries( setup_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( setup_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/setup_unit_test_suite )

add_executable( teardown_unit_test_suite ${SOURCE_DIR}/teardown.cpp )
target_link_libraries( teardown_unit_test_suite ${STATIC_LIBRARY_NAME} )
add_test( teardown_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/teardown_unit_test_suite )
