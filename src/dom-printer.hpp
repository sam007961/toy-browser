#pragma once
#include <dom-visitor.hpp>
#include <sstream>

class DomPrinter : public DomVisitor {
private:
    dom::Node& root;
    std::string output;

private:
    inline void add_space();
    inline void add_newline();

public: 
    DomPrinter(dom::Node& root);
    virtual void visit(dom::TextNode& textNode);
    virtual void visit(dom::ElementNode& elementNode);

    std::string&& print(); 
};
