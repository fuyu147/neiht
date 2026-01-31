cmake_minimum_required(VERSION 3.10)
project(sgrok)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED "gio-2.0")

file(GLOB SRC_FILES
    source/*.cc
    source/*/*.cc
)

add_executable(sgrok ${SRC_FILES})

target_compile_definitions(sgrok PRIVATE DEBUG)

target_include_directories(sgrok PRIVATE ${GIO_INCLUDE_DIRS})
target_link_libraries(sgrok PRIVATE raylib ${GIO_LIBRARIES})
