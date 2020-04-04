#include <css-parser.hpp>
#include <iostream>
#include <assert.h>

CssParser::CssParser(const std::string& input) : Parser(input) {}

css::Stylesheet CssParser::parse() {
    return css::Stylesheet(parse_rules());
}

std::vector<css::Rule> CssParser::parse_rules() {
    std::vector<css::Rule> rules;
    for(consume_whitespace(); !eof(); consume_whitespace()) {
        rules.push_back(parse_rule());
    }
    return rules;
}

std::vector<CssParser::Selector> CssParser::parse_selectors() {
    std::vector<Selector> selectors;
    while(!eof()) {
        selectors.push_back(parse_simple_selector());
        consume_whitespace();
        if(next_char() == ',') {
            consume_char();
            consume_whitespace();
        } else if(next_char() == '{') {
            break;   
        } else {
            std::cerr << "Unexpected character: \'"
                << next_char() << "\' in selector list" << std::endl;
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
    for(consume_whitespace(); next_char() != '}'; consume_whitespace()) {
        declarations.push_back(parse_declaration());
    }
    assert(consume_char() == '}');
    return declarations;
}

css::Rule CssParser::parse_rule() {
    auto selectors = parse_selectors();
    auto declarations = parse_declarations();
    return css::Rule(std::move(selectors), declarations);
}

CssParser::Selector CssParser::parse_simple_selector() {
    auto selector = std::make_unique<css::SimpleSelector>();
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

css::Declaration CssParser::parse_declaration() {
    std::string property_name = parse_identifier();
    consume_whitespace();
    assert(consume_char() == ':');
    consume_whitespace();
    css::Value value = parse_value();
    consume_whitespace();
    assert(consume_char() == ';');

    return css::Declaration(property_name, value);
}

std::string CssParser::parse_identifier() {
    return consume_while(CssParser::valid_identifier_char);
}

css::Value CssParser::parse_value() {
    char c = next_char();

    if('0' <= c && c <= '9') { // Length
        return parse_length();
    } else if(c == '#') {      // Color
        return parse_color();
    } else {                   // Keyword
        return parse_identifier();
    }
}

css::Length CssParser::parse_length() {
    float value = parse_float();
    css::Unit unit = parse_unit();
    return css::Length(value, unit); 
}


css::Color CssParser::parse_color() {
    assert(consume_char() == '#');
    unsigned char r = parse_hex_pair();
    unsigned char g = parse_hex_pair();
    unsigned char b = parse_hex_pair();
    return { r, g, b, 255 };
}

float CssParser::parse_float() {
    return std::atof(consume_while([](char c) -> bool {
        return '0' <= c && c <= '9' || c == '.';
    }).c_str());
}

css::Unit CssParser::parse_unit() {
    std::string unit = parse_identifier();
    std::transform(unit.begin(), unit.end(), unit.begin(),
        [](unsigned char c) { return std::tolower(c); }); // to lowercase
    if(unit == "px") {
        return css::Unit::Px;
    } else {
        std::cerr << "Unrecognized unit: \'" << unit << "\'." << std::endl;
        exit(1);
    }
}

unsigned char CssParser::parse_hex_pair() {
    std::string hex = consume_chars(2);
    return std::stoul(hex, nullptr, 16);
}

bool CssParser::valid_identifier_char(char c) {
    return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || '0' <= c && c <= '9'
        || c == '-' || c == '_';
}