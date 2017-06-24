cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

project( "protocol" VERSION 1.0.0 LANGUAGES CXX )
message( "Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved." )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" )

find_package( core REQUIRED )
find_package( catch REQUIRED )
find_package( runloop REQUIRED )
find_package( network REQUIRED )

#
# Configuration
#
include( "${CMAKE_SOURCE_DIR}/cmake/configuration.cmake" )

set( INCLUDE_DIR "${CMAKE_SOURCE_DIR}/source" )
include_directories( ${INCLUDE_DIR} SYSTEM ${core_INCLUDE} ${runloop_INCLUDE} ${network_INCLUDE} )

#
# Build
#
file( GLOB_RECURSE MANIFEST "source/*.cpp" )

set( STATIC_LIBRARY_NAME "${PROJECT_NAME}-static" )
add_library( ${STATIC_LIBRARY_NAME} STATIC ${MANIFEST} )
set_property( TARGET ${STATIC_LIBRARY_NAME} PROPERTY CXX_STANDARD 14 )
set_property( TARGET ${STATIC_LIBRARY_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )
set_target_properties( ${STATIC_LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )
target_link_libraries( ${STATIC_LIBRARY_NAME} ${core_STATIC_LIBRARY} ${runloop_STATIC_LIBRARY} )

set( SHARED_LIBRARY_NAME "${PROJECT_NAME}-shared" )
add_library( ${SHARED_LIBRARY_NAME} SHARED ${MANIFEST} )
set_property( TARGET ${SHARED_LIBRARY_NAME} PROPERTY CXX_STANDARD 14 )
set_property( TARGET ${SHARED_LIBRARY_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )
set_target_properties( ${SHARED_LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )
set_target_properties( ${SHARED_LIBRARY_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR} VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} )
target_link_libraries( ${SHARED_LIBRARY_NAME} ${core_SHARED_LIBRARY} ${runloop_SHARED_LIBRARY} )

enable_testing( )
add_subdirectory( "${CMAKE_SOURCE_DIR}/test/unit" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/test/acceptance" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/test/integration" )

#
# Install
#
file( GLOB ARTIFACTS "source/corvusoft/${PROJECT_NAME}/*.hpp" )

if ( NOT DEFINED CMAKE_INSTALL_LIBDIR )
    set( CMAKE_INSTALL_LIBDIR library )
endif ( )

install( FILES ${ARTIFACTS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/corvusoft/${PROJECT_NAME}" )
install( TARGETS ${STATIC_LIBRARY_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )
install( TARGETS ${SHARED_LIBRARY_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )
