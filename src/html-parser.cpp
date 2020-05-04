#include <html-parser.hpp>
#include <assert.h>

HtmlParser::HtmlParser(const std::string& input) : Parser(input) {}

std::string HtmlParser::parse_tag_name() {
	return consume_while(
		[](char c) -> bool {
			return 
				'a' <= c && c <= 'z' ||
				'A' <= c && c <= 'Z' ||
				'0' <= c && c <= '9';
		}
	);
}

dom::NodePtr HtmlParser::parse_node() {
	switch (next_char()) {
	case '<':
		return parse_element();
	default:
		return parse_text();
	}
}

dom::NodePtr HtmlParser::parse_text() {
	return std::make_unique<dom::TextNode>(consume_while(
		[](char c) -> bool {return c != '<';}
	));
}

dom::NodePtr HtmlParser::parse_element() {
	// Opening tag
	assert(consume_char() == '<');
	auto tag_name = parse_tag_name();
	auto attrs = parse_attributes();
	assert(consume_char() == '>');

	// Contents
	auto children = parse_nodes();

	// Closing tag
	assert(consume_char() == '<');
	assert(consume_char() == '/');
	assert(parse_tag_name() == tag_name);
	assert(consume_char() == '>');

	return std::make_unique<dom::ElementNode>(tag_name, attrs, std::move(children));
}

HtmlParser::Attribute HtmlParser::parse_attr() {
	auto name = parse_tag_name();
	assert(consume_char() == '=');
	auto value = parse_attr_value();
	return { name, value };
}

std::string HtmlParser::parse_attr_value() {
	auto open_quote = consume_char();
	assert(open_quote == '"' || open_quote == '\'');
	auto value = consume_while(
		[open_quote](char c) -> bool { return c != open_quote; }
	);
	assert(consume_char() == open_quote);
	return value;
}

dom::AttrMap HtmlParser::parse_attributes() {
	dom::AttrMap attributes;
	for(consume_whitespace(); next_char() != '>'; consume_whitespace()) {
		attributes.insert(parse_attr());
	}
	return attributes;
}

std::vector<dom::NodePtr> HtmlParser::parse_nodes() {
	std::vector<dom::NodePtr> nodes;
	for(consume_whitespace(); !eof() && !starts_with("</"); consume_whitespace()) {
		nodes.push_back(parse_node());
	}
	return nodes;
}


dom::NodePtr HtmlParser::parse() {
	auto nodes = parse_nodes();
	if (nodes.size() == 1) {
		return std::move(nodes.back());
	} else {
		return std::make_unique<dom::ElementNode>("html",
			dom::AttrMap(), std::move(nodes));
	}
}