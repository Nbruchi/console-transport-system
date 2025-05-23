cmake_minimum_required(VERSION 3.10)
project(RwandaTransport VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/City.cpp
    src/Road.cpp
    src/Graph.cpp
    src/FileManager.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Create data directory if it doesn't exist
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/data) 