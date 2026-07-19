cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0135 NEW)

project(WebCrawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------
# CURL
# --------------------------------------------------

find_package(CURL REQUIRED)

# --------------------------------------------------
# Google Test
# --------------------------------------------------

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# --------------------------------------------------
# Include Directories
# --------------------------------------------------

include_directories(
    include
    external/collections-library/include
)

# --------------------------------------------------
# Source Files
# --------------------------------------------------

set(SOURCES

    src/fetcher/fetcher.cpp

)

# --------------------------------------------------
# Main Executable
# --------------------------------------------------

add_executable(webcrawler
    main.cpp
    ${SOURCES}
)

target_link_libraries(webcrawler
    CURL::libcurl
)

# --------------------------------------------------
# Tests
# --------------------------------------------------

# add_subdirectory(tests)