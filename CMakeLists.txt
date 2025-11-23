cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME MultiStack)
project(${PROJECT_NAME})

set(application MultiStackApplication)
set(library MultiStackLibrary)


set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/StackLib)

add_subdirectory(Example)
add_subdirectory(StackLib)
add_subdirectory(gtest)
add_subdirectory(test)


#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

#set(MP2_LIBRARY "${PROJECT_NAME}")
#set(MP2_TESTS   "test_${PROJECT_NAME}")
#set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

#include_directories("${MP2_INCLUDE}" gtest)

 #BUILD
#add_subdirectory(VectorLib)
#add_subdirectory(Vector)
#add_subdirectory(gtest)
#add_subdirectory(test)

 #REPORT
#message( STATUS "")
#message( STATUS "General configuration for ${PROJECT_NAME}")
#message( STATUS "======================================")
#message( STATUS "")
#message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
#message( STATUS "")
