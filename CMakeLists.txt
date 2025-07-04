cmake_minimum_required(VERSION 3.15)
project(Neutron)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)
include_directories(external/glfw/include)
include_directories(external/glad/include)
include_directories(external/stb)

# GLFW
add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Engine
file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS "src/Neutron/**/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS "include/Neutron/**/*.h")

message(STATUS "Engine source files: ${ENGINE_SRC}")
add_library(NeutronEngine ${ENGINE_SRC} ${ENGINE_HEADERS})
target_include_directories(NeutronEngine PUBLIC include)

target_link_libraries(NeutronEngine glfw glad)

# Set output folders
set_target_properties(NeutronEngine PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Example app
add_subdirectory(examples/Sandbox)