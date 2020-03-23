#include <css-parser.hpp>
#include <iostream>
#include <assert.h>


CssParser::Stylesheet CssParser::parse() {
    return Stylesheet(new css::Stylesheet(parse_rules()));
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
        [](const css::Selector& a, const css::Selector& b) -> bool {
            b.specificity() > a.specificity();
    });

    return selectors;
}

std::vector<css::Declaration> CssParser::parse_declarations() {
    assert(consume_char() == '{');
    std::vector<css::Declaration> declarations;
    while(!eof()) {
        
    }
}

CssParser::SimpleSelector CssParser::parse_simple_selector() {
    
}
