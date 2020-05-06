#include <gtest/gtest.h>
#include <dom.hpp>
#include <style.hpp>
#include <css-parser.hpp>
using ils = std::initializer_list<std::string>;

TEST(TestRuleMatcher, TestSimpleSelector) {
    dom::ElementNode h2("h2");

    auto tagRule = CssParser("h2 { }").parse_rule();
    auto match = style::match_rule(h2.data, tagRule);

    ASSERT_TRUE(match);
    css::Specificity spec; css::Rule rule;
    std::tie(spec, rule) = std::move(*match);

    css::Specificity expected { 0, 0, 2 };
    ASSERT_EQ(spec, expected);
    ASSERT_EQ(rule, tagRule);
}

TEST(TestRuleMatcher, TestMultipleSelectors) {
    dom::ElementNode h2("h2", {
        { "class", "c0 c1 c2" }
    });

    auto multiRule = CssParser("h2, .c2, .c0.c1 { }").parse_rule();
    auto match = style::match_rule(h2.data, multiRule);

    ASSERT_TRUE(match);
    css::Specificity spec; css::Rule rule;
    std::tie(spec, rule) = std::move(*match);

    css::Specificity expected { 0, 2, 0 };
    ASSERT_EQ(spec, expected);
    ASSERT_EQ(rule, multiRule);
}

TEST(TestStyleTreeBuilder, TestSingleNodeSingleRule) {
    dom::ElementNode h2("h2");
    auto stylesheet = CssParser("h2 { color: #FFFFFF; }").parse();

    style::StyledNode expected;
    expected.node = &h2;
    expected.specifed_values["color"] = css::Color(255, 255, 255, 255);

    auto styled = style::StyleTreeBuilder(stylesheet).build(h2);
    ASSERT_EQ(styled, expected);
}