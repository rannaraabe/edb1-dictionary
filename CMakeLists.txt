cmake_minimum_required(VERSION 3.5)
project (dictionary VERSION 1.0.0 LANGUAGES CXX )

#=== FINDING PACKAGES ===#

# Locate GTest package (library)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

#Include dir
include_directories( include )

#=== Test target ===

# Add test files.
file(GLOB SOURCES_TEST "src/*.cpp")
#add_executable(dic ${SOURCES_TEST})
add_executable(dic "src/driver_dictionary.cpp" )

# Link with the google test libraries.
target_link_libraries(dic PRIVATE ${GTEST_LIBRARIES} PRIVATE pthread )