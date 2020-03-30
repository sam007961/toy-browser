#include <dom-printer.hpp>
#include <sstream>
#include <queue>

DomPrinter::DomPrinter(dom::Node& root) : root(root) {}

void DomPrinter::visit(dom::TextNode& textNode) {
    std::stringstream fmt;
    fmt << "{\'" << textNode.text << "\'}";
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

inline void DomPrinter::add_separator(bool empty) {
    output += empty ? "| " : " | ";
}

inline void DomPrinter::add_newline() {
    output += '\n';
}

std::string&& DomPrinter::print() {
    // nodes are tagged based on whether they are the last child node
    // or the last node in a layer
    enum Tag { NONE, SEPARATOR, LAYER };

    // BFS on DOM
    std::queue<std::pair<Tag, dom::Node*>> nodes;
    nodes.push({ LAYER, &root });
    bool empty_layer = false;

    while(!nodes.empty()) {

        auto[tag, node] = nodes.front();
        nodes.pop();

        if(node) { // check if empty separator
            empty_layer = false; // indicate that next layer is not empty
            node->accept(*this);
            if(node->children.size()) {
                for(auto& child : node->children) {
                    nodes.push({ NONE, child.get() });
                }
                nodes.back().first = SEPARATOR; // tag last child
            } else {
                // nullptr indicates that the node has no children to
                // insert empty separator on the next layer
                nodes.push({ SEPARATOR, nullptr });
            }
        }

        if(tag == SEPARATOR) {
            add_separator(!node);
        } else if (tag == LAYER) {
            if(empty_layer) break;
            empty_layer = true;
            add_newline();
            nodes.back().first = LAYER; // tag the last node of the layer below
        } else {
            add_space();
        }
    }

    return std::move(output);
}