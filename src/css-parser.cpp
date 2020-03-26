#include <css-parser.hpp>
#include <iostream>
#include <assert.h>


css::Stylesheet CssParser::parse() {
    return css::Stylesheet(parse_rules());
}

std::vector<css::Rule> CssParser::parse_rules() {
    std::vector<css::Rule> rules;
    consume_whitespace();
    while(!eof()) {
        rules.push_back(parse_rule());
        consume_whitespace();
    }
    return rules;
}

std::vector<CssParser::Selector> CssParser::parse_selectors() {
    std::vector<Selector> selectors;
    while(next_char() != '{') {
        selectors.push_back(parse_simple_selector());
        if(next_char() == ',') {
            consume_char();
            consume_whitespace();
        } else {
            std::cerr << "Unexpected character "
                << next_char() << "in selector list" << std::endl;
            exit(1);
        }
    }
    std::sort(selectors.begin(), selectors.end(), 
        [](const auto& a, const auto& b) -> bool {
            return b->specificity() > a->specificity();
    });

    return selectors;
}

std::vector<css::Declaration> CssParser::parse_declarations() {
    assert(consume_char() == '{');
    std::vector<css::Declaration> declarations;

    return declarations;
}

css::Rule CssParser::parse_rule() {
    return css::Rule();
}

CssParser::SimpleSelector CssParser::parse_simple_selector() {
    SimpleSelector selector;
    while(!eof()) {
        char c = next_char();
        if(c == '#') {
            consume_char();
            selector->id = parse_identifier();
        } else if(c == '.') {
            consume_char();
            selector->classes.push_back(parse_identifier());
        } else if(c == '*') {
            consume_char();
        } else if(valid_identifier_char(c)) {
            selector->tag_name = parse_identifier();
        } else break;
    }

    return selector;
}

std::string CssParser::parse_identifier() {
    return "";
}

bool CssParser::valid_identifier_char(char c) { return true; }