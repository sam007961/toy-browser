#include <gtest/gtest.h>
#include <css-parser.hpp>

TEST(TestCssParser, TestEmptyStylesheet) {
    CssParser parser("");

    EXPECT_EQ(parser.parse(), css::Stylesheet({}));    
}

TEST(TestCssParser, TestEmptyRule) {
    CssParser parser("h3 { }");

    std::vector<css::SelectorPtr> selectors;
        selectors.push_back(std::make_unique<css::SimpleSelector>("h3"));
    css::Rule simple_rule(std::move(selectors), {});

    std::vector<css::Rule> rules;
    rules.push_back(std::move(simple_rule));
    css::Stylesheet simple_stylesheet(std::move(rules));

    EXPECT_EQ(parser.parse(), simple_stylesheet);
}

TEST(TestCssParser, TestSimpleRule) {
    CssParser parser("h2, h3 { margin: 10px;\ncolor:#121314; text-align: center; }");
    std::vector<css::SelectorPtr> selectors;
        selectors.push_back(std::make_unique<css::SimpleSelector>("h2"));
        selectors.push_back(std::make_unique<css::SimpleSelector>("h3"));

    std::vector<css::Declaration> declarations {
        css::Declaration("margin", css::Length { 10, css::Unit::Px }),
        css::Declaration("color", css::Color { 18, 19, 20, 255 }),
        css::Declaration("text-align", "center")
    };
    css::Rule rule(std::move(selectors), declarations);

    std::vector<css::Rule> rules;
    rules.push_back(std::move(rule)); 
    css::Stylesheet stylesheet(std::move(rules));

    EXPECT_EQ(parser.parse(), stylesheet);
}

// TODO: test selector specificty ordering in rule