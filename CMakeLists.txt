cmake_minimum_required(VERSION 3.10)
project(ProyectoFinalProgramacion)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directory for headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libraries/include)


# Find and link the raylib library
if (WIN32)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libraries/lib/raylib.lib winmm)

    find_library(RAYLIB_LIBRARY raylib PATHS ${CMAKE_SOURCE_DIR}/libraries/lib)
    if (RAYLIB_LIBRARY)
        target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARY})
    else()
        message(FATAL_ERROR "raylib library not found in ${CMAKE_SOURCE_DIR}/libraries/lib")
    endif()
elseif (UNIX)
    find_library(RAYLIB_LIBRARY raylib PATHS ${CMAKE_SOURCE_DIR}/libraries/lib)
    if (RAYLIB_LIBRARY)
        target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARY})
    else()
        message("raylib shared library not found in ${CMAKE_SOURCE_DIR}/libraries/lib")
    endif()
endif()


# Set the output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
)
