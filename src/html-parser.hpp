#pragma once
#include <parser.hpp>
#include <dom.hpp>

class HtmlParser : public Parser<dom::Node> {
private:
	typedef std::unique_ptr<dom::Node> Node;
	typedef std::pair<std::string, std::string> Attribute;

private:
	std::string parse_tag_name();
	Node parse_node();
	Node parse_text();
	Node parse_element();
	Attribute parse_attr();
	std::string parse_attr_value();
	dom::AttrMap parse_attributes();
	std::vector<Node> parse_nodes();

public:
	HtmlParser(const std::string& input);
	Node parse();
};