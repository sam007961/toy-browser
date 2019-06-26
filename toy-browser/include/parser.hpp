#pragma once
#include <string>
#include <functional>

class Parser {
public:
	char next_char() const;
	bool starts_with(const std::string& str) const;
	bool eof() const;

	char consume_char();
	std::string consume_while(std::function<bool(char)> test);
	void consume_whitespace();
	std::string parse_tag_name();

private:
	size_t pos;
	const std::string input;
};