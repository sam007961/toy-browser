#include <gtest/gtest.h>
#include <parser.hpp>

TEST(TokenizerTest, TestCharIteration) {
    Tokenizer t("1234");

    ASSERT_EQ(t.next_char(), '1');
    ASSERT_EQ(t.consume_char(), '1');
    ASSERT_EQ(t.next_char(), '2');
    ASSERT_EQ(t.consume_char(), '2');
    ASSERT_EQ(t.next_char(), '3');
    ASSERT_EQ(t.consume_char(), '3');
    ASSERT_EQ(t.next_char(), '4');
    ASSERT_EQ(t.consume_char(), '4');
    ASSERT_TRUE(t.eof());
}

TEST(TokenizerTest, TestStartsWith) {
    Tokenizer t("abcd");

    ASSERT_TRUE(t.starts_with("a"));
    ASSERT_TRUE(t.starts_with("ab"));
    ASSERT_TRUE(t.starts_with("abc"));
    ASSERT_TRUE(t.starts_with("abcd"));

    ASSERT_FALSE(t.starts_with("b"));
    ASSERT_FALSE(t.starts_with("ac"));
    ASSERT_FALSE(t.starts_with("acd"));
    ASSERT_FALSE(t.starts_with("abd"));
    ASSERT_FALSE(t.starts_with("abce"));

    t.consume_char();

    ASSERT_TRUE(t.starts_with("b"));
    ASSERT_TRUE(t.starts_with("bc"));
    ASSERT_TRUE(t.starts_with("bcd"));
}

TEST(TokenizerTest, TestConsumeChars) {
    Tokenizer t("abcdef");
    ASSERT_EQ(t.consume_chars(1), "a");
    ASSERT_EQ(t.consume_chars(2), "bc");
    ASSERT_EQ(t.consume_chars(3), "def");
}

TEST(TokenizerTest, TestConsumeWhile) {
    Tokenizer t("aaabcdEFG123h");
    ASSERT_EQ(t.consume_while([] (char c) -> bool { return c == 'a'; }), "aaa");
    ASSERT_EQ(t.consume_while([] (char c) -> bool { return 'a' <= c && c <= 'z'; }), "bcd");
    ASSERT_EQ(t.consume_while([] (char c) -> bool { return 'A' <= c && c <= 'Z'; }), "EFG");
    ASSERT_EQ(t.consume_while([] (char c) -> bool { return '0' <= c && c <= '9'; }), "123");
    ASSERT_EQ(t.consume_char(), 'h');
}

TEST(TokenizerTest, TestConsumeWhitespace){
    Tokenizer t(" \na b  c   d    e\nf\n\ng\n\n\nh\n \n  i");

    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'a');
    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'b');
    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'c');
    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'd');
    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'e');
    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'f');
    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'g');
    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'h');
    t.consume_whitespace();
    ASSERT_EQ(t.consume_char(), 'i');
}