#pragma once
#include <string>
#include <functional>
#include <dom.hpp>

class ParserBase {
protected:
	char next_char() const;
	bool starts_with(const std::string& str) const;
	bool eof() const;

	char consume_char();
	std::string consume_while(std::function<bool(char)> test);
	void consume_whitespace();


public:
	ParserBase(const std::string& input);

private:
	size_t pos;
	const std::string input;
};

template<typename T>
class Parser : public ParserBase {
public:
	Parser(const std::string& input) : ParserBase(input) {}
	virtual T parse() = 0; 
};