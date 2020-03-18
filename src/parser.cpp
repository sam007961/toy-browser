#include <assert.h>
#include <parser.hpp>

char Parser::next_char() const {
	return input[pos];
}

bool Parser::starts_with(const std::string& str) const {
	return input.substr(pos, str.length()) == str;
}

bool Parser::eof() const { return pos >= input.length(); }

char Parser::consume_char() { return input[pos++]; }

std::string Parser::consume_while(std::function<bool(char)> test) {
	std::string result;
	while (!eof() && test(next_char())) {
		result.push_back(consume_char());
	}
	return result;
}

void Parser::consume_whitespace() {
	const auto _ = consume_while([](char c) -> bool { return c != ' '; });
}

std::string Parser::parse_tag_name() {
	return consume_while(
		[](char c) -> bool {
			return 
				'a' <= c && c <= 'z' ||
				'A' <= c && c <= 'Z' ||
				'0' <= c && c <= '9';
		}
	);
}

Parser::Node Parser::parse_node() {
	switch (next_char()) {
	case '<':
		return parse_element();
	default:
		return parse_text();
	}
}

Parser::Node Parser::parse_text() {
	return Node(new dom::TextNode(consume_while(
		[](char c) -> bool {return c != '<';}
	)));
}


Parser::Node Parser::parse_element() {
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

	return Node(new dom::ElementNode(tag_name, attrs, children));
}

Parser::Attribute Parser::parse_attr() {
	auto name = parse_tag_name();
	assert(consume_char() == '=');
	auto value = parse_attr_value();
	return { name, value };
}

std::string Parser::parse_attr_value() {
	auto open_quote = consume_char();
	assert(open_quote == '"' || open_quote == '\'');
	auto value = consume_while(
		[open_quote](char c) -> bool { return c != open_quote; }
	);
	assert(consume_char() == open_quote);
	return value;
}

dom::AttrMap Parser::parse_attributes() {
	dom::AttrMap attributes;
	for (consume_whitespace(); next_char() != '>'; consume_whitespace()) {
		attributes.insert(parse_attr());
	}
	return attributes;
}

std::vector<Parser::Node> Parser::parse_nodes() {
	std::vector<Node> nodes;
	for (consume_whitespace(); !eof() && !starts_with("</"); consume_whitespace()) {
		nodes.push_back(parse_node());
	}
	return nodes;
}

Parser::Parser(const std::string& input) : input(input) {}

Parser::Node Parser::parse() {
	auto nodes = parse_nodes();
	if (nodes.size() == 1) {
		return std::move(nodes.back());
	} else {
		return Node(new dom::ElementNode("html", dom::AttrMap(), nodes));
	}
}