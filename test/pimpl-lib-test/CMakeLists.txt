cmake_minimum_required(VERSION 3.16.3)

# Target name and language
project(PimplLibTest CXX)

# compile setting.
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()
if (NOT CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DNDEBUG)
endif ()
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the directories where include files can be found.
include_directories(${CMAKE_SOURCE_DIR}/src/pimpl-lib/include)

# Set the source files.
aux_source_directory(${PROJECT_SOURCE_DIR} TEST_SRC)

# Build the executable
add_executable(${PROJECT_NAME} ${TEST_SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Link staticlibraries
target_link_libraries(${PROJECT_NAME} pimpl-lib ${CONAN_LIBS})
if (UNIX)
    target_link_libraries(${PROJECT_NAME} dl pthread)
endif ()

# test setting
add_test(
    NAME ${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
