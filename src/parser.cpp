#include <parser.hpp>
#include <assert.h>

Tokenizer::Tokenizer(const std::string& input) : input(input), pos(0) {}

char Tokenizer::next_char() const {
    return input[pos];
}

bool Tokenizer::starts_with(const std::string& str) const {
    return input.substr(pos, str.length()) == str;
}

bool Tokenizer::eof() const { return pos >= input.length(); }

char Tokenizer::consume_char() { return input[pos++]; }

std::string Tokenizer::consume_chars(int n) {
    std::string result = input.substr(pos, n);
    pos += n;
    return result;
}

std::string Tokenizer::consume_while(std::function<bool(char)> test) {
    std::string result;
    while (!eof() && test(next_char())) {
        result.push_back(consume_char());
    }
    return result;
}

void Tokenizer::consume_whitespace() {
    const auto _ = consume_while([](char c) -> bool { 
        return c == ' ' || c == '\n' || c == '\r' || c == '\t';
    });
}