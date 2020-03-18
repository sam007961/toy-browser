#pragma once
#include <string>
#include <functional>
#include <dom.hpp>

class Parser {
private:
	typedef std::unique_ptr<dom::Node> Node;
	typedef std::pair<std::string, std::string> Attribute;

private:
	char next_char() const;
	bool starts_with(const std::string& str) const;
	bool eof() const;

	char consume_char();
	std::string consume_while(std::function<bool(char)> test);
	void consume_whitespace();

	std::string parse_tag_name();
	Node parse_node();
	Node parse_text();
	Node parse_element();
	Attribute parse_attr();
	std::string parse_attr_value();
	dom::AttrMap parse_attributes();
	std::vector<Node> parse_nodes();

public:
	Parser(const std::string& input);
	Node parse();

private:
	size_t pos;
	const std::string input;
};