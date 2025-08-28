cmake_minimum_required(VERSION 3.16)
project(musicbrainz-explorer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

# Try to find nlohmann_json, fallback to FetchContent if not found
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

add_executable(explorer
    src/main.cpp
    src/musicbrainz_client.cpp
)

target_include_directories(explorer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(explorer PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)

target_compile_options(explorer PRIVATE
    -Wall -Wextra -Wpedantic
)