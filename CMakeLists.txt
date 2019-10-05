cmake_minimum_required(VERSION 3.0.0)

project(beaver)

set(CMAKE_CXX_STANDARD 14)

set(
    SOURCES
    src/config.cc
    src/datastream.cc
    src/main.cc
)

add_executable(app ${SOURCES})

target_include_directories(
    app PRIVATE
    ${PROJECT_SOURCE_DIR}/include
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