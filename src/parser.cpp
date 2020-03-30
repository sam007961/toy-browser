#include <parser.hpp>
#include <assert.h>

ParserBase::ParserBase(const std::string& input) : input(input), pos(0) {}

char ParserBase::next_char() const {
	return input[pos];
}

bool ParserBase::starts_with(const std::string& str) const {
	return input.substr(pos, str.length()) == str;
}

bool ParserBase::eof() const { return pos >= input.length(); }

char ParserBase::consume_char() { return input[pos++]; }

std::string ParserBase::consume_chars(int n) {
	return input.substr(pos, pos += n);
}

std::string ParserBase::consume_while(std::function<bool(char)> test) {
	std::string result;
	while (!eof() && test(next_char())) {
		result.push_back(consume_char());
	}
	return result;
}

void ParserBase::consume_whitespace() {
	const auto _ = consume_while([](char c) -> bool { 
		return c == ' ' || c == '\n' || c == '\r' || c == '\t';
	});
}