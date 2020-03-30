#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <variant>

class StylesheetVisitor;

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

    struct StylesheetElement {
        virtual void accept(StylesheetVisitor& visitor) = 0;
    };

    struct Selector : public StylesheetElement {
        virtual Specificity specificity() const = 0;
    };

    struct SimpleSelector : public Selector {
        std::optional<std::string> tag_name;
        std::optional<std::string> id;
        std::vector<std::string> classes;

        virtual Specificity specificity() const;
        virtual void accept(StylesheetVisitor& visitor);
    };

    struct Declaration : public StylesheetElement {
        std::string name;
        Value value;

        Declaration(std::string name, Value value);
        virtual void accept(StylesheetVisitor& visitor);
    };

    struct Rule : StylesheetElement {
        typedef std::unique_ptr<Selector> SelectorPtr;

        std::vector<SelectorPtr> selectors;
        std::vector<Declaration> declarations;

        Rule();
        Rule(std::vector<SelectorPtr>&& selectors,
            std::vector<Declaration> declarations);
        Rule(Rule&& rule);
        Rule& operator=(Rule&& rule);

        virtual void accept(StylesheetVisitor& visitor);
    };

    struct Stylesheet : StylesheetElement {
        std::vector<Rule> rules;
        Stylesheet(std::vector<Rule>&& rules);

        virtual void accept(StylesheetVisitor& visitor);
    };
}