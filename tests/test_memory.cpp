#include <gtest/gtest.h>
#include "memory.h"

TEST(TestMemory, test_word_length) {
    EXPECT_EQ(6U, sizeof(mixal::ComputerWord));
}

TEST(TestMemory, test_invalid_get) {
    mixal::ComputerWord word;
    EXPECT_THROW(word[0], std::runtime_error);
    EXPECT_THROW(word[6], std::runtime_error);
    const auto& ref = word;
    EXPECT_THROW(ref.getAt(-1), std::runtime_error);
}

TEST(TestMemory, test_invalid_set) {
    mixal::ComputerWord word;
    word.set(true, 0, 0, 0, 0, 0);
    EXPECT_THROW(word.set(0, 0), std::runtime_error);
    EXPECT_THROW(word.set(7, 0), std::runtime_error);
}

TEST(TestMemory, test_invalid_sign) {
    EXPECT_THROW(mixal::ComputerWord('*', 1, 2, 3, 4, 5), std::runtime_error);
    EXPECT_THROW(mixal::ComputerWord('*', 1, 2, 3, 4), std::runtime_error);
    mixal::ComputerWord word;
    word.set(true, 0, 0, 0, 0, 0);
    EXPECT_THROW(word.set('*', 1, 2, 3, 4, 5), std::runtime_error);
    EXPECT_THROW(word.set('*', 1, 2, 3, 4), std::runtime_error);
}

TEST(TestMemory, test_value) {
    EXPECT_EQ(-42, mixal::ComputerWord(-42).value());
}

TEST(TestMemory, test_get_bytes_string) {
    mixal::ComputerWord word;
    word.set('-', 0, 12, 3, 43, 49);
    EXPECT_EQ("-  0 12  3 43 49", word.getBytesString());
    word.set('+', 12, 3, 43, 49);
    EXPECT_EQ("+  0 12  3 43 49", word.getBytesString());
}

TEST(TestMemory, test_set_address) {
    mixal::ComputerWord word;
    word.setAddress(-12);
    EXPECT_EQ(-12, word.addressValue());
}

TEST(TestMemory, test_get_characters) {
    mixal::ComputerWord word('+', 1, 2, 3, 4);
    word.set("A4+ -");
    word.set(2, 10);
    word.set(3, 63);
    EXPECT_EQ("A´  -", word.getCharacters());
}

TEST(TestMemory, test_set_characters_invalid_length) {
    mixal::ComputerWord word;
    EXPECT_THROW(word.set("A4+ -s"), std::runtime_error);
}
