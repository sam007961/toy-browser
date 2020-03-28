#pragma once
#include <stylesheet.hpp>

class StylesheetVisitor {
public:
    virtual void visit(css::Selector& selector) = 0;
    virtual void visit(css::Declaration& declaration) = 0;
    virtual void visit(css::Rule& rule) = 0;
    virtual void visit(css::Stylesheet& stylesheet) = 0;
};