#include <stylesheet.hpp>
#include <algorithm>

bool css::Color::operator==(const Color& other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

bool css::Selector::operator==(const Selector& other) const {
    return typeid(*this) == typeid(other) && isEqual(other);
}
bool css::Selector::operator!=(const Selector& other) const {
    return !(*this == other);
}

css::Specificity css::SimpleSelector::specificity() const {
    int a = id ? id->length() : 0;
    int b = classes.size();
    int c = tag_name ? tag_name->length() : 0;

    return { a, b, c };
}
css::SimpleSelector::SimpleSelector() {}
css::SimpleSelector::SimpleSelector(const std::string& tag_name) : tag_name(tag_name) {}
bool css::SimpleSelector::isEqual(const Selector& other) const {
    const auto& other_simple = static_cast<const SimpleSelector&>(other);
    return tag_name == other_simple.tag_name && id == other_simple.id
        && classes == other_simple.classes; 
}
bool css::SimpleSelector::matches(const dom::ElementData& elem) const {
    if(tag_name && tag_name != elem.tag_name) {
        return false;
    }

    if(id && id != elem.id()) {
        return false;
    }

    auto elem_classes = elem.classes();
    if(std::any_of(classes.begin(), classes.end(),
        [elem_classes](const std::string& cls) -> bool {
            return elem_classes.find(cls) == elem_classes.end();
        })) {
        return false;
    }
    return true;
}

css::Declaration::Declaration(std::string name, Value value) : name(name), value(value) {}
bool css::Declaration::operator==(const Declaration& other) const {
    return name == other.name && value == other.value;
}
bool css::Declaration::operator!=(const Declaration& other) const {
    return !(*this == other);
}

css::Rule::Rule() {}
css::Rule::Rule(std::vector<SelectorPtr>&& selectors,
            std::vector<Declaration> declarations) :
            selectors(std::move(selectors)), declarations(declarations) {}
css::Rule::Rule(Rule&& rule) : 
    selectors(std::move(rule.selectors)), declarations(rule.declarations) {}
bool css::Rule::operator==(const Rule& other) const {
    return std::equal(
        selectors.begin(), selectors.end(),
        other.selectors.begin(), other.selectors.end(), 
        [](const auto& lhs,  const auto&  rhs) {return *lhs == *rhs; })
    && declarations == other.declarations;
}
bool css::Rule::operator!=(const Rule& other) const {
    return !(*this == other);
}

css::Stylesheet::Stylesheet(std::vector<Rule>&& rules) : rules(std::move(rules)) {}
bool css::Stylesheet::operator==(const Stylesheet& other) const {
    return rules == other.rules;
}