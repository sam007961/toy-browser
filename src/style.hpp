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

        bool operator==(const StyledNode& other) const;
    };

    bool compare_style_tree(const StyledNode& a, const StyledNode& b);

    // returns a MatchedRule if the element matches the rule, otherwise nullopt
    std::optional<MatchedRule> match_rule(const dom::ElementData& elem,
        const css::Rule& rule);

    class StyleTreeBuilder : public DomVisitor {
    private:
        // find the rules that match this element
        std::vector<MatchedRule> matching_rules(const dom::ElementData& elem,
            const css::Stylesheet& stylesheet);

        // get the property values that apply to this element
        PropertyMap specified_values(const dom::ElementData& elem,
                const css::Stylesheet& stylesheet);
        
    public:
        virtual void visit(dom::TextNode& textNode);
        virtual void visit(dom::ElementNode& elemNode);
        StyleTreeBuilder(const css::Stylesheet& stylesheet);
        StyledNode build(dom::Node& root);
    
    private:
        StyledNode result;
        const css::Stylesheet& stylesheet;
    };
}
