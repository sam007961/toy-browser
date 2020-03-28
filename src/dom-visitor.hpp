#pragma once
#include <dom.hpp>

class DomVisitor {
public:
    virtual void visit(dom::TextNode& textNode) = 0;
    virtual void visit(dom::ElementNode& elementNode) = 0;
};