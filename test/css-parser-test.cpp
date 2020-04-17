#include <gtest/gtest.h>
#include <css-parser.hpp>

TEST(CssParserTest, TestEmptyStylesheet) {
    CssParser parser("");

    EXPECT_EQ(parser.parse(), css::Stylesheet({}));    
}

TEST(CssParserTest, TestSimpleEmptyRule) {
    CssParser parser("h3 { }");
    auto h3 = std::make_unique<css::SimpleSelector>(); h3->tag_name = "h3";
    std::vector<std::unique_ptr<css::Selector>> selectors;
    selectors.push_back(std::move(h3));
    css::Rule simple_rule(std::move(selectors), {});
    std::vector<css::Rule> rules;
    rules.push_back(std::move(simple_rule));
    css::Stylesheet simple_stylesheet(std::move(rules));
    EXPECT_EQ(parser.parse(), simple_stylesheet);
}