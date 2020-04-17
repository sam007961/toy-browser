#include <gtest/gtest.h>
#include <stylesheet.hpp>

TEST(TestStylesheetComparison, TestCompareSelector) {
    css::SimpleSelector s0;
    s0.tag_name = "abc"; s0.id = "123"; s0.classes = { "a", "b", "c" };
    css::SimpleSelector s1;
    s1.tag_name = "abc"; s1.id = "123"; s1.classes = { "a", "b", "d" };
    css::SimpleSelector s2;
    s2.tag_name = "abd"; s2.id = "123"; s2.classes = { "a", "b", "c" };
    css::SimpleSelector s3;
    s3.tag_name = "abc"; s3.id = "124"; s3.classes = { "a", "b", "c" };
    css::SimpleSelector s4;
    s4.tag_name = "abc"; s4.classes = { "a", "b", "c" };
    css::SimpleSelector s5;
    s5.id = "123"; s5.classes = { "a", "b", "c" };
    css::SimpleSelector s6;
    s6.tag_name = "abc"; s6.id = "123"; s6.classes = { "a", "b", "c" };

    EXPECT_EQ(s0, s6);
    EXPECT_EQ(s6, s0);

    EXPECT_NE(s0, s1); // different classes
    EXPECT_NE(s1, s0); 
    EXPECT_NE(s0, s2); // different tag
    EXPECT_NE(s2, s0);
    EXPECT_NE(s0, s3); // different id
    EXPECT_NE(s3, s0);
    EXPECT_NE(s0, s4); // missing id
    EXPECT_NE(s4, s0);
    EXPECT_NE(s0, s5); // missing tag
    EXPECT_NE(s5, s0);
}

TEST(TestStylesheetComparison, TestCompareDeclaration) {
   css::Declaration d0("margin", css::Length { 10, css::Unit::Px });
   css::Declaration d1("color", css::Color { 18, 19, 20, 255 });
   css::Declaration d2("text-align", "center"); 
   css::Declaration d3("margin", css::Length { 10, css::Unit::Px });
   css::Declaration d4("color", css::Color { 18, 19, 20, 255 });
   css::Declaration d5("text-align", "center"); 

   EXPECT_EQ(d0, d3);
   EXPECT_EQ(d1, d4);
   EXPECT_EQ(d2, d5);
}

TEST(TestStylesheetComparison, TestCompareRule) {

}

TEST(TestStylesheetComparison, TestCompareStylesheet) {

}