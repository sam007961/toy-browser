#include <gtest/gtest.h>
#include <css-parser.hpp>

TEST(CssParserTest, TestEmptyStylesheet) {
    CssParser parser("");

    EXPECT_EQ(parser.parse(), css::Stylesheet({}));    
}

TEST(CssParserTest, TestSimpleEmptyRule) {
    CssParser parser("h3 { }");
    css::SimpleSelector h3; h3.tag_name = "h3";
    // css::Rule simple_rule({ h3 })
}