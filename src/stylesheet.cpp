#include <stylesheet.hpp>

css::Stylesheet::Stylesheet() {}
css::Stylesheet::Stylesheet(const std::vector<Rule>& rules) : rules(rules) {}

css::Specificity css::SimpleSelector::specificity() const {
    int a = id ? id->length() : 0;
    int b = classes.size();
    int c = tag_name ? tag_name->length() : 0;

    return { a, b, c };
}