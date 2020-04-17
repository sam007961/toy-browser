#include <gtest/gtest.h>
#include <css-parser.hpp>

TEST(CssParserTest, TestEmptyStylesheet) {
    CssParser parser("");

    EXPECT_EQ(parser.parse(), css::Stylesheet({}));    
}

TEST(CssParserTest, TestEmptyRule) {
    CssParser parser("h3 { }");
    auto h3 = std::make_unique<css::SimpleSelector>("h3");

    std::vector<std::unique_ptr<css::Selector>> selectors;
    selectors.push_back(std::move(h3));
    css::Rule simple_rule(std::move(selectors), {});

    std::vector<css::Rule> rules;
    rules.push_back(std::move(simple_rule));
    css::Stylesheet simple_stylesheet(std::move(rules));

    EXPECT_EQ(parser.parse(), simple_stylesheet);
}

TEST(CssParserTest, TestSimpleRule) {
    CssParser parser("h2, h3 { margin: 10px;\ncolor:#121314; text-align: center; }");
    auto h2 = std::make_unique<css::SimpleSelector>("h2");
    auto h3 = std::make_unique<css::SimpleSelector>("h3");

    css::Declaration margin("margin", css::Length { 10, css::Unit::Px });
    css::Declaration color("color", css::Color { 18, 19, 20, 255 });
    css::Declaration text_align("text-align", "center");

    std::vector<std::unique_ptr<css::Selector>> selectors;
    std::vector<css::Declaration> declarations { margin, color, text_align };
    selectors.push_back(std::move(h2));
    selectors.push_back(std::move(h3));
    css::Rule rule(std::move(selectors), declarations);

    std::vector<css::Rule> rules;
    rules.push_back(std::move(rule));
    css::Stylesheet stylesheet(std::move(rules));

    // auto temp = parser.parse();
    EXPECT_EQ(parser.parse(), stylesheet);
}