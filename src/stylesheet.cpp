#include <stylesheet.hpp>
#include <stylesheet-visitor.hpp>

css::Specificity css::SimpleSelector::specificity() const {
    int a = id ? id->length() : 0;
    int b = classes.size();
    int c = tag_name ? tag_name->length() : 0;

    return { a, b, c };
}
void css::SimpleSelector::accept(StylesheetVisitor& visitor) { visitor.visit(*this); }

void css::Declaration::accept(StylesheetVisitor& visitor) { visitor.visit(*this); }

css::Rule::Rule() {}
css::Rule::Rule(Rule&& rule) : 
    selectors(std::move(rule.selectors)), declarations(rule.declarations) {}
void css::Rule::accept(StylesheetVisitor& visitor) { visitor.visit(*this); }

css::Stylesheet::Stylesheet(std::vector<Rule>& rules) : rules(std::move(rules)) {}
css::Stylesheet::Stylesheet(std::vector<Rule>&& rules) : rules(std::move(rules)) {}
void css::Stylesheet::accept(StylesheetVisitor& visitor) { visitor.visit(*this); }