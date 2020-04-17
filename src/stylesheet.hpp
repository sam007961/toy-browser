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

        bool operator==(const Color& other) const;
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
        virtual bool isEqual(const Selector& other) const = 0;
        bool operator==(const Selector& other) const;
        bool operator!=(const Selector& other) const;
    };

    struct SimpleSelector : public Selector {
        std::optional<std::string> tag_name;
        std::optional<std::string> id;
        std::vector<std::string> classes;

        SimpleSelector();
        SimpleSelector(const std::string& tag_name);
        virtual Specificity specificity() const;
        virtual void accept(StylesheetVisitor& visitor);
        virtual bool isEqual(const Selector& other) const;
    };

    struct Declaration : public StylesheetElement {
        std::string name;
        Value value;

        Declaration(std::string name, Value value);
        virtual void accept(StylesheetVisitor& visitor);
        bool operator==(const Declaration& other) const;
        bool operator!=(const Declaration& other) const;
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
        bool operator==(const Rule& other) const;
        bool operator!=(const Rule& other) const;
    };

    struct Stylesheet : StylesheetElement {
        std::vector<Rule> rules;
        Stylesheet(std::vector<Rule>&& rules);

        virtual void accept(StylesheetVisitor& visitor);
        bool operator==(const Stylesheet& other) const;
    };
}