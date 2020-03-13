############################################################################
# CMakeLists.txt file for building analysis code for ICAL
# @author
# @mail 
############################################################################
cmake_minimum_required(VERSION 3.9)

# set the project name
project(icalanalysis VERSION 1.0.0 LANGUAGES CXX)


# Set the output folder where your program will be created
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# sub directorires
#add_subdirectory(src)

#including root
find_package(ROOT 6.18 CONFIG REQUIRED)
#----------------------------------------------------------------------------
# Setup Root include directories and compile definitions
#
include("${ROOT_USE_FILE}")
#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

add_executable(icalanalysis analysis.cc ${sources} ${headers})

target_compile_features(icalanalysis PRIVATE cxx_lambda_init_captures)
target_link_libraries(icalanalysis PUBLIC ${ROOT_LIBRARIES} )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Testing
enable_testing()
