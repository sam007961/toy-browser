#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <variant>
#include <dom.hpp>

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

    struct Selector {
        virtual Specificity specificity() const = 0;
        virtual bool isEqual(const Selector& other) const = 0;
        virtual bool matches(const dom::ElementData& elem) const = 0;
        bool operator==(const Selector& other) const;
        bool operator!=(const Selector& other) const;
        virtual Selector* clone() const = 0;
    };

    struct SimpleSelector : public Selector {
        std::optional<std::string> tag_name;
        std::optional<std::string> id;
        std::vector<std::string> classes;

        SimpleSelector();
        SimpleSelector(const std::string& tag_name);
        SimpleSelector(const std::vector<std::string>& classes);
        SimpleSelector(const std::string& id, int dummy);
        virtual Specificity specificity() const;
        virtual bool isEqual(const Selector& other) const;
        virtual bool matches(const dom::ElementData& elem) const;
        virtual Selector* clone() const;
    };


    typedef std::unique_ptr<Selector> SelectorPtr;

    struct Declaration {
        std::string name;
        Value value;

        Declaration(std::string name, Value value);
        bool operator==(const Declaration& other) const;
        bool operator!=(const Declaration& other) const;
    };

    struct Rule {
        std::vector<SelectorPtr> selectors;
        std::vector<Declaration> declarations;

        Rule();
        Rule(const std::vector<SelectorPtr>& selectors,
            const std::vector<Declaration>& declarations);
        Rule(std::vector<SelectorPtr>&& selectors,
            const std::vector<Declaration>& declarations);
        Rule(Rule&& rule);
        Rule(const Rule& rule);
        Rule& operator=(Rule&& rule);
        Rule& operator=(const Rule& rule);

        bool operator==(const Rule& other) const;
        bool operator!=(const Rule& other) const;

    private:
        void copy_selectors(const Rule& rule);
        void copy_selectors(const std::vector<SelectorPtr>& selectors);
    };

    struct Stylesheet {
        std::vector<Rule> rules;
        Stylesheet(const std::vector<Rule>& rules);
        Stylesheet(std::vector<Rule>&& rules);

        bool operator==(const Stylesheet& other) const;
    };
}