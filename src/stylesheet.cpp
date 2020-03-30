#include <stylesheet.hpp>
#include <stylesheet-visitor.hpp>

css::Specificity css::SimpleSelector::specificity() const {
    int a = id ? id->length() : 0;
    int b = classes.size();
    int c = tag_name ? tag_name->length() : 0;

    return { a, b, c };
}
void css::SimpleSelector::accept(StylesheetVisitor& visitor) { visitor.visit(*this); }

css::Declaration::Declaration(std::string name, Value value) : name(name), value(value) {}
void css::Declaration::accept(StylesheetVisitor& visitor) { visitor.visit(*this); }

css::Rule::Rule() {}
css::Rule::Rule(std::vector<SelectorPtr>&& selectors,
            std::vector<Declaration> declarations) :
            selectors(std::move(selectors)), declarations(declarations) {}
css::Rule::Rule(Rule&& rule) : 
    selectors(std::move(rule.selectors)), declarations(rule.declarations) {}
void css::Rule::accept(StylesheetVisitor& visitor) { visitor.visit(*this); }

css::Stylesheet::Stylesheet(std::vector<Rule>&& rules) : rules(std::move(rules)) {}
void css::Stylesheet::accept(StylesheetVisitor& visitor) { visitor.visit(*this); }