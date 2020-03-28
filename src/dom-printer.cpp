#include <dom-printer.hpp>
#include <queue>

DomPrinter::DomPrinter(dom::Node& root) : root(root) {}

void DomPrinter::visit(dom::TextNode& textNode) {
    std::stringstream fmt;
    fmt << '{' << textNode.text << '}';
    output += fmt.str();
}

void DomPrinter::visit(dom::ElementNode& elementNode) {
    std::stringstream fmt;
    fmt << "{[" << elementNode.data.tag_name << ']';
    for(const auto& attr : elementNode.data.attributes) {
        fmt << '(' << attr.first << " : " << attr.second << ')';
    }
    fmt << '}';
    output += fmt.str();
}

inline void DomPrinter::add_space() {
    output += ' ';
}

inline void DomPrinter::add_newline() {
    output += '\n';
}

std::string&& DomPrinter::print() {
    std::queue<dom::Node*> nodes;
    nodes.push(&root);
    dom::Node* layer_end = &root;
    while(!nodes.empty()) {
        dom::Node* node = nodes.front();
        node->accept(*this);
        for(auto& child : node->children) {
            nodes.push(child.get());
        }
        nodes.pop();
        if(node == layer_end) {
            layer_end = nodes.back();
            add_newline();
        } else {
            add_space();
        }
    }

    return std::move(output);
}