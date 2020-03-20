cmake_minimum_required(VERSION 3.0.0)

project(toy-browser VERSION 0.1.0)

set(Sources
    src/main.cpp
    src/dom.cpp
    src/parser.cpp
    src/html-parser.cpp
)

add_executable(toy-browser ${Sources})
target_include_directories(toy-browser PRIVATE ${PROJECT_SOURCE_DIR}/src)
configure_file(test/test.html test/test.html COPYONLY)