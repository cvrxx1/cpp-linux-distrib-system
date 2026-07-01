cmake_minimum_required(VERSION 3.10)
project(LinuxDistribSystemCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SQLite3 REQUIRED)
find_package(nlohmann_json REQUIRED)


set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES 
    "${SRC_DIR}/*.cpp"
)

add_executable(linux_distrib ${SOURCES})

target_include_directories(linux_distrib PRIVATE
    ${SRC_DIR}
)

target_link_libraries(linux_distrib 
    SQLite::SQLite3
    nlohmann_json::nlohmann_json
)