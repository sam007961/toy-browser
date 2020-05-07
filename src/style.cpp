#include <algorithm>
#include <style.hpp>
#include <dom.hpp>
#include <stylesheet.hpp>


bool style::compare(const StyledNode& a, const StyledNode& b) {
    return a == b && std::equal(
        a.children.begin(), a.children.end(),
        b.children.begin(), b.children.end(),
        [](const StyledNode& a, const StyledNode& b) -> bool {
            return compare(a, b);
        });
}

std::optional<style::MatchedRule> style::match_rule(const dom::ElementData& elem,
        const css::Rule& rule) {
    auto selIt = std::find_if(rule.selectors.begin(), rule.selectors.end(),
        [elem](const css::SelectorPtr& sel) -> bool {
            return sel->matches(elem);
        });

    if(selIt != rule.selectors.end())
        return MatchedRule { (*selIt)->specificity(), rule };
    else return std::nullopt;
}


std::vector<style::MatchedRule> style::StyleTreeBuilder::matching_rules(
        const dom::ElementData& elem, const css::Stylesheet& stylesheet) {
    std::vector<MatchedRule> result;
    for(auto it = stylesheet.rules.begin(); it !=  stylesheet.rules.end(); ++it) {
        auto match = match_rule(elem, *it);
        if(match) {
            result.push_back(*match);
        }
    }
    return result;
}

style::PropertyMap style::StyleTreeBuilder::specified_values(
        const dom::ElementData& elem,
        const css::Stylesheet& stylesheet) {
    PropertyMap values;
    auto rules = matching_rules(elem, stylesheet);

    // sort rules by specificity, lowest to highest
    std::sort(rules.begin(), rules.end(),
        [](const MatchedRule& a, const MatchedRule& b) -> bool {
            return b.first < a.first;
        });

    // collect the properties of the matched rules
    for(auto it = rules.begin(); it != rules.end(); ++it) {
        const auto& rule = it->second;
        for(auto decl : rule.declarations) {
            values.insert({ decl.name, decl.value });
        }
    }
    return values;
}

style::StyleTreeBuilder::StyleTreeBuilder(const css::Stylesheet& stylesheet)
    : stylesheet(stylesheet) {}

void style::StyleTreeBuilder::visit(dom::TextNode& textNode) {
    result.node = &textNode;
}

void style::StyleTreeBuilder::visit(dom::ElementNode& elemNode) {
    result.node = &elemNode;
    result.specifed_values = specified_values(elemNode.data, stylesheet);
}

style::StyledNode style::StyleTreeBuilder::build(dom::Node& root) {
    root.accept(*this);
    for(auto it = root.children.begin(); it != root.children.end(); ++it) {
        result.children.push_back(StyleTreeBuilder(stylesheet).build(*it->get()));
    }
    return std::move(result);
}

bool style::StyledNode::operator==(const StyledNode& other) const {
    return node == other.node && specifed_values == other.specifed_values;
}
