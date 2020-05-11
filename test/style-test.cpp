#include <gtest/gtest.h>
#include <dom.hpp>
#include <style.hpp>
#include <html-parser.hpp>
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
    expected.specified_values["color"] = css::Color(255, 255, 255, 255);

    auto style_tree = style::StyleTreeBuilder(stylesheet).build(h2);
    ASSERT_EQ(style_tree, expected);
}

TEST(TestStyleTreeBuilder, TestMultiNodeMultiRule) {
    auto dom = HtmlParser(
        "<html>"
        "<h1>Hello</h1>"
        "<h2>Goodbye</h2>"
        "<h2 class='c0'>Farewell!</h2>"
        "<div class='c1 c2'>"
            "<h1>See ya!</h1>"
        "</div>"
        "</html>"
    ).parse();

    auto stylesheet = CssParser(
        "h1 { color: #FFFFFF; }"
        "h2 { border: 2px; border-color: #000000; }"
        ".c0 { border: None; }"
        ".c1 { color: #FF0000; }"
        ".c2 { color: #00FF00; }"
        ".c1.c2 { color: #0000FF; }"
    ).parse();

    style::StyledNode expected_html;
    expected_html.node = dom.get();

    style::StyledNode expected_h11;
    expected_h11.node = dom->children[0].get();
    expected_h11.specified_values["color"] = css::Color(255, 255, 255, 255);

    style::StyledNode expected_h11_text;
    expected_h11_text.node = dom->children[0]->children[0].get();

    style::StyledNode expected_h21;
    expected_h21.node = dom->children[1].get();
    expected_h21.specified_values["border"] = css::Length(2, css::Unit::Px);
    expected_h21.specified_values["border-color"] = css::Color(0, 0, 0, 255);

    style::StyledNode expected_h21_text;
    expected_h21_text.node = dom->children[1]->children[0].get();

    style::StyledNode expected_h22;
    expected_h22.node = dom->children[2].get();
    expected_h22.specified_values["border"] = css::Keyword("None");
    expected_h22.specified_values["border-color"] = css::Color(0, 0, 0, 255);

    style::StyledNode expected_h22_text;
    expected_h22_text.node = dom->children[2]->children[0].get();

    style::StyledNode expected_div;
    expected_div.node = dom->children[3].get();
    expected_div.specified_values["color"] = css::Color(0, 0, 255, 255);

    style::StyledNode expected_h12;
    expected_h12.node = dom->children[3]->children[0].get();
    expected_h12.specified_values["color"] = css::Color(255, 255, 255, 255);

    style::StyledNode expected_h12_text;
    expected_h12_text.node = dom->children[3]->children[0]->children[0].get();

    expected_h11.children = { expected_h11_text };
    expected_h21.children = { expected_h21_text };
    expected_h22.children = { expected_h22_text };
    expected_h12.children = { expected_h12_text };
    expected_div.children = { expected_h12 };
    expected_html.children = { expected_h11, expected_h21, expected_h22, expected_div };

    auto style_tree = style::StyleTreeBuilder(stylesheet).build(*dom);
    ASSERT_TRUE(style::compare(style_tree, expected_html));
}