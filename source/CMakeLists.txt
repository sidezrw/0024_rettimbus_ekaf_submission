
cmake_minimum_required(VERSION 3.15)
project(submission_0024 LANGUAGES C CXX)

# C++ version (SEAL requires 17)
set(CMAKE_CXX_STANDARD 17) # C++ standard C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add OpenMP for multithreading
find_package (OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

set(${PROJECT_NAME}_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/benchmarks/bfv/seal_bfv_dot_product_benchmark.h"
    )

set(${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/benchmarks/bfv/seal_bfv_dot_product_benchmark.cpp"
    )

# engine
list(APPEND ${PROJECT_NAME}_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/engine/seal_context.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/engine/seal_engine.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/engine/seal_types.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/engine/seal_version.h"
    )

list(APPEND ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/seal_context.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/seal_engine.cpp"
    )

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# All external libraries are assumed to be pre-compiled for tutorial simplicity.

# find the hebench_cpp archive
#set(HEBENCH_API_INCLUDE_DIR "/include/directory/for/api_bridge")
set(HEBENCH_API_INCLUDE_DIR "/home/ernesto/Documents/documents/repos/hebench/api-bridge/build/debug/install/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${HEBENCH_API_INCLUDE_DIR}) # point to include for api_bridge
#find_library(hebench_cpp_FOUND NAMES libhebench_cpp.a HINTS "/directory/containing/libhebench_cpp.a")
find_library(hebench_cpp_FOUND NAMES libhebench_cpp.a HINTS "/home/ernesto/Documents/documents/repos/hebench/api-bridge/build/debug/install/lib")
if(hebench_cpp_FOUND)
    add_library(hebench_cpp UNKNOWN IMPORTED)
    # populate the found library with its properties
    set_property(TARGET hebench_cpp PROPERTY IMPORTED_LOCATION ${hebench_cpp_FOUND})
    set_property(TARGET hebench_cpp APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${HEBENCH_API_INCLUDE_DIR})
    message(STATUS "libhebench_cpp.a found")
else()
    message(FATAL_ERROR "libhebench_cpp.a not found.")
endif()

# link found library
target_link_libraries(${PROJECT_NAME} PUBLIC "-Wl,--whole-archive" hebench_cpp "-Wl,--no-whole-archive")

# find other third party dependencies
# pre-built Microsoft SEAL 3.6
#set(SEAL_INCLUDE_DIR "/usr/local/include/SEAL-3.6")
set(SEAL_INCLUDE_DIR "/home/ernesto/Downloads/downloads/SEAL/install/include/SEAL-3.6")
target_include_directories(${PROJECT_NAME} PRIVATE ${SEAL_INCLUDE_DIR}) # point to include for SEAL
#find_library(SEAL_FOUND NAMES libseal-3.6.a HINTS "/usr/local/lib")
find_library(SEAL_FOUND NAMES libseal-3.6.a HINTS "/home/ernesto/Downloads/downloads/SEAL/install/lib")
if(SEAL_FOUND)
    add_library(seal-3.6 UNKNOWN IMPORTED)
    # populate the found library with its properties
    set_property(TARGET seal-3.6 PROPERTY IMPORTED_LOCATION ${SEAL_FOUND})
    set_property(TARGET seal-3.6 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SEAL_INCLUDE_DIR})
else()
    message(FATAL_ERROR "libseal-3.6.a not found.")
endif()

# link found library
target_link_libraries(${PROJECT_NAME} PUBLIC "-Wl,--whole-archive" seal-3.6 "-Wl,--no-whole-archive")

# extra compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra) # show warnings

# install options
include(GNUInstallDirs)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
