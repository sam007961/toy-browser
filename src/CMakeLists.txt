add_executable(toy-browser main.cpp dom.cpp parser.cpp)

target_include_directories(toy-browser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})