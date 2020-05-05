#pragma once
#include <parser.hpp>
#include <stylesheet.hpp>

class CssParser : public Parser<css::Stylesheet> {
private:
    css::SelectorPtr parse_simple_selector();
    std::string parse_identifier();
    css::Value parse_value();
    css::Length parse_length();
    css::Color parse_color();
    float parse_float();
    css::Unit parse_unit();
    unsigned char parse_hex_pair();
    static bool valid_identifier_char(char c);

public:
    std::vector<css::Rule> parse_rules();
    std::vector<css::SelectorPtr> parse_selectors();
    std::vector<css::Declaration> parse_declarations();

    css::Rule parse_rule(); 
    css::SelectorPtr parse_selector();
    css::Declaration parse_declaration();


public:
    CssParser(const std::string& input);
    virtual css::Stylesheet parse();
};