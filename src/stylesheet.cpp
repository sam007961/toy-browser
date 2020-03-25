#include <stylesheet.hpp>

css::Stylesheet::Stylesheet(std::vector<Rule>& rules) : rules(std::move(rules)) {}
css::Stylesheet::Stylesheet(std::vector<Rule>&& rules) : rules(std::move(rules)) {}

css::Specificity css::SimpleSelector::specificity() const {
    int a = id ? id->length() : 0;
    int b = classes.size();
    int c = tag_name ? tag_name->length() : 0;

    return { a, b, c };
}

css::Rule::Rule() {}
css::Rule::Rule(Rule&& rule) : 
    selectors(std::move(rule.selectors)), declarations(rule.declarations) {}