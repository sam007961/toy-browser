#pragma once
#include <string>
#include <functional>
#include <dom.hpp>

class Tokenizer {
protected:
	char next_char() const;
	bool starts_with(const std::string& str) const;
	bool eof() const;

	char consume_char();
	std::string consume_chars(int n);
	std::string consume_while(std::function<bool(char)> test);
	void consume_whitespace();

public:
	Tokenizer(const std::string& input);

private:
	size_t pos;
	const std::string input;
};

template<typename T>
class Parser : public Tokenizer {
public:
	Parser(const std::string& input) : Tokenizer(input) {}
	virtual T parse() = 0; 
};