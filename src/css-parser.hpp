#pragma once
#include <parser.hpp>
#include <stylesheet.hpp>

class CssParser : public Parser<css::Stylesheet> {
private:
    typedef std::unique_ptr<css::Stylesheet> Stylesheet;
    typedef std::unique_ptr<css::Selector> Selector;
    typedef std::unique_ptr<css::SimpleSelector> SimpleSelector;

private:
    std::vector<css::Rule> parse_rules();
    std::vector<Selector> parse_selectors();
    std::vector<css::Declaration> parse_declarations();

    css::Rule parse_rule(); 
    SimpleSelector parse_simple_selector();
    css::Declaration parse_declaration();
    std::string parse_identifier();
    bool valid_identifier_char(char c);

public:
    CssParser(const std::string& input);
    virtual Stylesheet parse();
};