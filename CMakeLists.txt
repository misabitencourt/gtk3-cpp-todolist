cmake_minimum_required(VERSION 3.0)
project(todolist_app)
set(CMAKE_CXX_STANDARD 17)

# Find GTK3 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

file(GLOB SOURCES
    "src/sample.cpp"
)

add_compile_options(-fpermissive)
include_directories(./)
include_directories(${GTK3_INCLUDE_DIRS})

add_executable(todolist_app ${SOURCES})


target_link_libraries(todolist_app ${GTK3_LIBRARIES})

add_definitions(${GTK3_CFLAGS_OTHER})