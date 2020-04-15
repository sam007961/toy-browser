set(Sources
    main.cpp
    tokenizer-test.cpp
    dom-comparison-test.cpp
    stylesheet-comparison-test.cpp
    html-parser-test.cpp
    css-parser-test.cpp
)

add_executable(toy-browser-test ${Sources})
target_link_libraries(toy-browser-test PUBLIC toy-browser-lib gtest_main)

add_test(NAME toy-browser-test COMMAND toy-browser-test)