#include <gtest/gtest.h>
#include <dom.hpp>

TEST(TestDomComparison, TestCompareSingleTextNode) {
    dom::TextNode t0("abc");
    dom::TextNode t1("def");
    dom::TextNode t3("abc");

    EXPECT_TRUE(dom::compare(t0, t3));
    EXPECT_TRUE(dom::compare(t3, t0));
    EXPECT_TRUE(dom::compare(t3, t3));
    EXPECT_TRUE(dom::compare(t0, t0));

    EXPECT_FALSE(dom::compare(t0, t1));
    EXPECT_FALSE(dom::compare(t1, t0));
    EXPECT_FALSE(dom::compare(t1, t3));
    EXPECT_FALSE(dom::compare(t3, t1));
}

TEST(TestDomComparison, TestCompareSingleElementNode) {
    dom::ElementNode e0("x", {
        {"a0", "b0"},
        {"a1", "b1"}
    });
    dom::ElementNode e1("y", {
        {"a0", "c0"},
        {"a1", "b1"}
    });
    dom::ElementNode e2("x", {
        {"d2", "f0"},
        {"a1", "b1"}
    });
    dom::ElementNode e3("y", {
        {"a0", "b0"},
        {"a1", "b1"}
    });
    dom::ElementNode e4("x", {
        {"a0", "b0"},
        {"a1", "b1"},
        {"a2", "b2"}
    });
    dom::ElementNode e5("x", {
        {"a0", "b0"},
        {"a1", "b1"},
    });

    EXPECT_TRUE(dom::compare(e0, e5));
    EXPECT_TRUE(dom::compare(e5, e0));
    EXPECT_TRUE(dom::compare(e0, e0));
    EXPECT_TRUE(dom::compare(e5, e5));

    EXPECT_FALSE(dom::compare(e0, e1)); // different name and attrs
    EXPECT_FALSE(dom::compare(e1, e0)); 
    EXPECT_FALSE(dom::compare(e0, e2)); // same name, different attrs
    EXPECT_FALSE(dom::compare(e2, e0));
    EXPECT_FALSE(dom::compare(e0, e3)); // different name, same attrs
    EXPECT_FALSE(dom::compare(e3, e0));
    EXPECT_FALSE(dom::compare(e0, e4)); // extra attr
    EXPECT_FALSE(dom::compare(e4, e0));
}

TEST(TestDomComparison, TestElementWithSingleChild) {
    std::vector<dom::NodePtr> e0_children;
    e0_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    dom::ElementNode e0("x", {}, std::move(e0_children));

    std::vector<dom::NodePtr> e1_children;
    e1_children.push_back(std::make_unique<dom::TextNode>("world"));
    dom::ElementNode e1("x", {}, std::move(e1_children));

    std::vector<dom::NodePtr> e2_children;
    e2_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    dom::ElementNode e2("y", {}, std::move(e2_children));

    dom::ElementNode e3("x");

    std::vector<dom::NodePtr> e4_children;
    e4_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    dom::ElementNode e4("x", {}, std::move(e4_children));

    EXPECT_TRUE(dom::compare(e0, e4));
    EXPECT_TRUE(dom::compare(e4, e0));

    EXPECT_FALSE(dom::compare(e0, e1)); // different parent, same child
    EXPECT_FALSE(dom::compare(e1, e0));
    EXPECT_FALSE(dom::compare(e0, e2)); // same parent, different child
    EXPECT_FALSE(dom::compare(e2, e0));
    EXPECT_FALSE(dom::compare(e0, e3)); // same parent, missing child
    EXPECT_FALSE(dom::compare(e3, e0));
}

TEST(TestDomComparison, TestCompareElementWithMultipleChildren) {
    std::vector<dom::NodePtr> e0_children;
    e0_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    e0_children.push_back(std::make_unique<dom::TextNode>("bye world"));
    dom::ElementNode e0("x", {}, std::move(e0_children));

    std::vector<dom::NodePtr> e1_children;
    e1_children.push_back(std::make_unique<dom::TextNode>("bye world"));
    dom::ElementNode e1("x", {}, std::move(e1_children));

    std::vector<dom::NodePtr> e2_children;
    e2_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    dom::ElementNode e2("x", {}, std::move(e2_children));

    std::vector<dom::NodePtr> e3_children;
    e3_children.push_back(std::make_unique<dom::TextNode>("hello"));
    e3_children.push_back(std::make_unique<dom::TextNode>("bye world"));
    dom::ElementNode e3("x", {}, std::move(e3_children));

    std::vector<dom::NodePtr> e4_children;
    e4_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    e4_children.push_back(std::make_unique<dom::TextNode>("world"));
    dom::ElementNode e4("x", {}, std::move(e4_children));

    std::vector<dom::NodePtr> e5_children;
    e5_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    e5_children.push_back(std::make_unique<dom::TextNode>("bye world"));
    dom::ElementNode e5("y", {}, std::move(e5_children));

    std::vector<dom::NodePtr> e6_children;
    e6_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    e6_children.push_back(std::make_unique<dom::TextNode>("bye world"));
    e6_children.push_back(std::make_unique<dom::TextNode>("goodbye world"));
    dom::ElementNode e6("x", {}, std::move(e6_children));
    
    std::vector<dom::NodePtr> e7_children;
    e7_children.push_back(std::make_unique<dom::TextNode>("hello world"));
    e7_children.push_back(std::make_unique<dom::TextNode>("bye world"));
    dom::ElementNode e7("x", {}, std::move(e7_children));

    EXPECT_TRUE(dom::compare(e0, e7));
    EXPECT_TRUE(dom::compare(e7, e0));

    EXPECT_FALSE(dom::compare(e0, e1));
    EXPECT_FALSE(dom::compare(e1, e0));
    EXPECT_FALSE(dom::compare(e0, e2));
    EXPECT_FALSE(dom::compare(e2, e0));
    EXPECT_FALSE(dom::compare(e0, e3));
    EXPECT_FALSE(dom::compare(e0, e3));
    EXPECT_FALSE(dom::compare(e0, e4));
    EXPECT_FALSE(dom::compare(e4, e0));
    EXPECT_FALSE(dom::compare(e0, e5));
    EXPECT_FALSE(dom::compare(e5, e0));
    EXPECT_FALSE(dom::compare(e0, e6));
    EXPECT_FALSE(dom::compare(e6, e0));
}