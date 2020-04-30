#include <gtest/gtest.h>
#include <dom.hpp>

TEST(TestDomElementNode, TestId) {
    dom::ElementData d0("test", {
        {"abc", "123"},
        {"id", "test-id"}
    });

    EXPECT_EQ(d0.id(), "test-id");
}

TEST(TestDomElementNode, TestClasses) {
    dom::ElementData d0("test", {
        {"abc", "123"},
        {"class", "cls0 cls1 cls2"}
    });

    auto classes = std::unordered_set<std::string> { "cls0", "cls1", "cls2" };
    EXPECT_EQ(d0.classes(), classes);
}