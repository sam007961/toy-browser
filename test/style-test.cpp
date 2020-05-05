#include <gtest/gtest.h>
#include <dom.hpp>
#include <style.hpp>
using ils = std::initializer_list<std::string>;

TEST(TestRuleMatcher, TestSimpleSelector) {
    dom::ElementNode h2("h2");

    std::vector<css::SelectorPtr> selectors;
    selectors.push_back(std::make_unique<css::SimpleSelector>("h2"));

    css::Rule tagRule(std::move(selectors), {});
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

    std::vector<css::SelectorPtr> selectors;
        selectors.push_back(
            std::make_unique<css::SimpleSelector>("h2"));
        selectors.push_back(
            std::make_unique<css::SimpleSelector>(ils { "c2" }));
        selectors.push_back(
            std::make_unique<css::SimpleSelector>(ils { "c0", "c1" }));
    std::sort(selectors.begin(), selectors.end(),
        [](const auto& a, const auto& b) -> bool {
            return b->specificity() < a->specificity();
    });

    css::Rule multiRule(std::move(selectors), {});
    auto match = style::match_rule(h2.data, multiRule);

    ASSERT_TRUE(match);
    css::Specificity spec; css::Rule rule;
    std::tie(spec, rule) = std::move(*match);

    css::Specificity expected { 0, 2, 0 };
    ASSERT_EQ(spec, expected);
    ASSERT_EQ(rule, multiRule);
}