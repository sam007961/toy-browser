#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <variant>

namespace css {

    enum Unit {
        Px
    };

    struct Color {
        unsigned char r, g, b, a;
    };

    typedef std::string Keyword;
    typedef std::pair<float, Unit> Length;

    typedef std::variant<Keyword, Length, Color> Value;

    class Selector {};

    struct SimpleSelector : public Selector {
        std::optional<std::string> tag_name;
        std::optional<std::string> id;
        std::vector<std::string> classes;
    };

    struct Declaration {
        std::string name;
        Value value;
    };

    struct Rule {
        std::vector<std::reference_wrapper<Selector>> selectors;
        std::vector<Declaration> declarations;
    };

    struct Stylesheet {
        std::vector<Rule> rules;
        Stylesheet();
        Stylesheet(const std::vector<Rule>& rules);
    };
}