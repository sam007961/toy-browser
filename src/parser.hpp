#pragma once
#include <string>
#include <functional>
#include <dom.hpp>

class Parser {
protected:
	char next_char() const;
	bool starts_with(const std::string& str) const;
	bool eof() const;

	char consume_char();
	std::string consume_while(std::function<bool(char)> test);
	void consume_whitespace();


public:
	Parser(const std::string& input);

private:
	size_t pos;
	const std::string input;
};