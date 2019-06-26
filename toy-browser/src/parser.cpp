#pragma once
#include <parser.hpp>

char Parser::next_char() const {
	return input[pos];
}

bool Parser::starts_with(const std::string& str) const {
	return input.substr(0, str.length()) == str;
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