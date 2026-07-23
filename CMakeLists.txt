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
# Source Files
# --------------------------------------------------

set(SOURCES
    src/crawler/crawler.cpp
    src/fetcher/fetcher.cpp
    src/url_normalizer/url_normalizer.cpp
    src/frontier/frontier.cpp
    src/page_storage/page_storage.cpp
    src/link_extractor/link_extractor.cpp
    src/seen_store/seen_store.cpp
    
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
# Include Directories
# --------------------------------------------------
target_include_directories(webcrawler PRIVATE
    include
    external/collections-library/include
)





# --------------------------------------------------
# Tests
# --------------------------------------------------

# add_subdirectory(tests)