#pragma once
#include <unordered_map>
#include <string>
#include <stylesheet.hpp>

namespace style {
    typedef std::unordered_map<std::string, css::Value> PropertyMap;

    struct StyledNode {
        dom::Node* node;
        PropertyMap specifed_values;
        std::vector<StyledNode> children;
    };
}