#include <css-parser.hpp>


CssParser::Stylesheet CssParser::parse() {
    return Stylesheet(new css::Stylesheet(parse_rules()));
}

std::vector<css::Rule> CssParser::parse_rules() {
    std::vector<css::Rule> rules;
    while(!eof()) {
        consume_whitespace();
        rules.push(self.parse_rule());
    }
    return rules;
}
