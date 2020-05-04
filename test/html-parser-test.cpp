#include <gtest/gtest.h>
#include <html-parser.hpp>

TEST(TestHtmlParser, TestEmptyDocument) {
    HtmlParser parser("");

    EXPECT_TRUE(dom::compare(*parser.parse(), dom::ElementNode("html")));
}

TEST(TestHtmlParser, TestEmptyHtmlTag) {
    HtmlParser parser("<html></html>");

    EXPECT_TRUE(dom::compare(*parser.parse(), dom::ElementNode("html")));
}

TEST(TestHtmlParser, TestSingleTextChild) {
    HtmlParser parser("<html>hello world!</html>");
    std::vector<dom::NodePtr> children;
    children.push_back(std::make_unique<dom::TextNode>("hello world!"));

    EXPECT_TRUE(dom::compare(*parser.parse(),
        dom::ElementNode("html", dom::AttrMap(), std::move(children))));
}

TEST(TestHtmlParser, TestSingleElementChild) {
    HtmlParser parser("<html><div></div></html>");
    std::vector<dom::NodePtr> children;    
    children.push_back(std::make_unique<dom::ElementNode>("div"));

    EXPECT_TRUE(dom::compare(*parser.parse(),
        dom::ElementNode("html", dom::AttrMap(), std::move(children))));
}

TEST(TestHtmlParser, TestMultipleChildren) {
    HtmlParser parser("<html><div></div><p></p></html>");
    std::vector<dom::NodePtr> children;
    children.push_back(std::make_unique<dom::ElementNode>("div"));
    children.push_back(std::make_unique<dom::ElementNode>("p"));

    EXPECT_TRUE(dom::compare(*parser.parse(),
        dom::ElementNode("html", dom::AttrMap(), std::move(children))));
}

TEST(TestHtmlParser, TestThreeLayers) {
    HtmlParser parser("<html><div><p></p></div></html>");
    std::vector<dom::NodePtr> children;
    children.push_back(std::make_unique<dom::ElementNode>("p"));
    auto div = std::make_unique<dom::ElementNode>("div", dom::AttrMap(), std::move(children));
    children.push_back(std::move(div));

    EXPECT_TRUE(dom::compare(*parser.parse(),
        dom::ElementNode("html", dom::AttrMap(), std::move(children))));
}


TEST(TestHtmlParser, TestAttributes) {
    HtmlParser parser("<html>\n<div id=\'simple-div\'>\n" 
        "<div id=\"nested-div\" class=\'background-red\'></div>" 
        "</div><p id=\'main-paragraph\'>Hello World!</p></html>");
    std::vector<dom::NodePtr> children;
    children.push_back(std::make_unique<dom::ElementNode>("div", dom::AttrMap {
        {"id", "nested-div"},
        {"class", "background-red"}
    }));
    auto div = std::make_unique<dom::ElementNode>("div", dom::AttrMap {
        {"id", "simple-div"}
    }, std::move(children));
    children.push_back(std::make_unique<dom::TextNode>("Hello World!"));
    auto p = std::make_unique<dom::ElementNode>("p", dom::AttrMap {
        {"id", "main-paragraph"}
    }, std::move(children));
    children.push_back(std::move(div));
    children.push_back(std::move(p));

    EXPECT_TRUE(dom::compare(*parser.parse(),
        dom::ElementNode("html", dom::AttrMap(), std::move(children))));
}