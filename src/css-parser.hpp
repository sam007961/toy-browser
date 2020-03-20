#pragma once
#include <parser.hpp>
#include <stylesheet.hpp>

class CssParser : public Parser<css::Stylesheet> {
private:
    typedef std::unique_ptr<css::Stylesheet> Stylesheet;

private:
    std::vector<css::Rule> parse_rules();

public:
    CssParser(const std::string& input);
    Stylesheet parse();
};