#include <style.hpp>
#include <dom.hpp>
#include <stylesheet.hpp>
#include <algorithm>


style::RuleMatcher::RuleMatcher(const css::Rule& rule) : rule(rule) {}
void style::RuleMatcher::visit(dom::TextNode& textNode) {}
void style::RuleMatcher::visit(dom::ElementNode& elemNode) {
    auto selIt = std::find_if(rule.selectors.begin(), rule.selectors.end(),
        [elemNode](const css::Selector& sel) -> bool { return sel.matches(elemNode.data) ;});
    if(selIt != rule.selectors.end()) {
        matched = { (*selIt)->specificity(), &rule };
    }
}
std::optional<style::MatchedRule> style::RuleMatcher::match(dom::Node& node) {
    node.accept(*this);
    return matched;
}