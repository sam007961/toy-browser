#pragma once
#include <dom-visitor.hpp>

class DomPrinter : public DomVisitor {
private:
    dom::Node& root;
    std::string output;

private:
    inline void add_space();
    inline void add_separator(bool empty);
    inline void add_empty_separator();
    inline void add_newline();

public: 
    DomPrinter(dom::Node& root);
    virtual void visit(dom::TextNode& textNode);
    virtual void visit(dom::ElementNode& elementNode);

    std::string&& print(); 
};
