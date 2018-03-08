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
#add_executable( http_constructor_unit_test_suite ${SOURCE_DIR}/http/constructor.cpp )
#target_link_libraries( http_constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( http_constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_constructor_unit_test_suite )

#add_executable( http_destructor_unit_test_suite ${SOURCE_DIR}/http/destructor.cpp )
#target_link_libraries( http_destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( http_destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_destructor_unit_test_suite )

#add_executable( http_get_name_unit_test_suite ${SOURCE_DIR}/http/get_name.cpp )
#target_link_libraries( http_get_name_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( http_get_name_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_get_name_unit_test_suite )

#add_executable( http_setup_unit_test_suite ${SOURCE_DIR}/http/setup.cpp )
#target_link_libraries( http_setup_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( http_setup_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_setup_unit_test_suite )

#add_executable( http_teardown_unit_test_suite ${SOURCE_DIR}/http/teardown.cpp )
#target_link_libraries( http_teardown_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( http_teardown_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/http_teardown_unit_test_suite )

#add_executable( message_clear_unit_test_suite ${SOURCE_DIR}/message/clear.cpp )
#target_link_libraries( message_clear_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( message_clear_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_clear_unit_test_suite )

#add_executable( message_constructor_unit_test_suite ${SOURCE_DIR}/message/constructor.cpp )
#target_link_libraries( message_constructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( message_constructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_constructor_unit_test_suite )

#add_executable( message_destructor_unit_test_suite ${SOURCE_DIR}/message/destructor.cpp )
#target_link_libraries( message_destructor_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( message_destructor_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_destructor_unit_test_suite )

#add_executable( message_erase_unit_test_suite ${SOURCE_DIR}/message/erase.cpp )
#target_link_libraries( message_erase_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( message_erase_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_erase_unit_test_suite )

#add_executable( message_get_unit_test_suite ${SOURCE_DIR}/message/get.cpp )
#target_link_libraries( message_get_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( message_get_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_get_unit_test_suite )

#add_executable( message_has_unit_test_suite ${SOURCE_DIR}/message/has.cpp )
#target_link_libraries( message_has_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( message_has_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_has_unit_test_suite )

#add_executable( message_set_unit_test_suite ${SOURCE_DIR}/message/set.cpp )
#target_link_libraries( message_set_unit_test_suite ${STATIC_LIBRARY_NAME} )
#add_test( message_set_unit_test_suite ${EXECUTABLE_OUTPUT_PATH}/message_set_unit_test_suite )
