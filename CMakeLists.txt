cmake_minimum_required(VERSION 3.16)
project(musicbrainz-explorer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

add_executable(explorer
    src/main.cpp
    src/musicbrainz_client.cpp
)

target_include_directories(explorer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(explorer PRIVATE
    CURL::libcurl
)

target_compile_options(explorer PRIVATE
    -Wall -Wextra -Wpedantic
)