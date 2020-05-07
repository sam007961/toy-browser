#pragma once
#include <parser.hpp>
#include <dom.hpp>

class HtmlParser : public Parser<dom::NodePtr> {
private:
    typedef std::pair<std::string, std::string> Attribute;

private:
    std::string parse_tag_name();
    dom::NodePtr parse_text();
    dom::NodePtr parse_element();
    Attribute parse_attr();
    std::string parse_attr_value();
    dom::AttrMap parse_attributes();

public:
    dom::NodePtr parse_node();
    std::vector<dom::NodePtr> parse_nodes();

public:
    HtmlParser(const std::string& input);
    virtual dom::NodePtr parse();
};