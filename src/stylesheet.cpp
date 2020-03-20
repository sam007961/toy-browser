#include <stylesheet.hpp>

css::Stylesheet::Stylesheet() {}
css::Stylesheet::Stylesheet(const std::vector<Rule>& rules) : rules(rules) {}