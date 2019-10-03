cmake_minimum_required(VERSION 3.0.0)

project(beaver)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    app
    src/main.cc
)

target_include_directories(
    app PRIVATE
    /usr/local/include
)

target_link_directories(
    app PRIVATE
    /usr/local/lib
)

target_link_libraries(
    app
    librdkafka++.a
    librocksdb.a
)