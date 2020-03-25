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
    typedef std::tuple<int, int, int> Specificity;

    struct Selector {
        virtual Specificity specificity() const = 0;
    };

    struct SimpleSelector : public Selector {
        std::optional<std::string> tag_name;
        std::optional<std::string> id;
        std::vector<std::string> classes;

        virtual Specificity specificity() const;
    };

    struct Declaration {
        std::string name;
        Value value;
    };

    struct Rule {
        std::vector<std::unique_ptr<Selector>> selectors;
        std::vector<Declaration> declarations;

        Rule();
        Rule(Rule&& rule);
        Rule& operator=(Rule&& rule);
    };

    struct Stylesheet {
        std::vector<Rule> rules;
        Stylesheet(std::vector<Rule>& rules);
        Stylesheet(std::vector<Rule>&& rules);
    };
}