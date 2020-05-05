#pragma once
#include <unordered_map>
#include <string>
#include <stylesheet.hpp>
#include <dom-visitor.hpp>

namespace style {
    typedef std::unordered_map<std::string, css::Value> PropertyMap;
    typedef std::pair<css::Specificity, css::Rule> MatchedRule;

    struct StyledNode {
        dom::Node* node;
        PropertyMap specifed_values;
        std::vector<StyledNode> children;
    };

    class RuleMatcher : public DomVisitor {
    public:
        virtual void visit(dom::TextNode& textNode);
        virtual void visit(dom::ElementNode& elementNode);

    public:
        RuleMatcher(const css::Rule& rule);
        std::optional<MatchedRule> match(dom::Node& node);
    
    private:
        const css::Rule& rule;
        std::optional<MatchedRule> matched;
    };

    class StyleTreeBuilder : public DomVisitor {
        
    };
}