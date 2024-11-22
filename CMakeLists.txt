cmake_minimum_required(VERSION 3.10) # Minimum CMake version
project(MyProject)                  # Name of the project

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/libraries/include)

# Link directory for prebuilt libraries
link_directories(${CMAKE_SOURCE_DIR}/libraries/lib/)

# Link the library to your target
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libraries/lib/libraylib.so)

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
	    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.."
		)

