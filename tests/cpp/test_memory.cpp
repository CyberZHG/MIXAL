#include "test.h"
#include "memory.h"

namespace test {

class TestMemory : public UnitTest {};

__TEST_U(TestMemory, test_word_length) {
    __ASSERT_EQ(6U, sizeof(mixal::ComputerWord));
}

__TEST_U(TestMemory, test_invalid_get) {
    mixal::ComputerWord word;
    __ASSERT_THROW(word[0], std::runtime_error);
    __ASSERT_THROW(word[6], std::runtime_error);
    const auto& ref = word;
    __ASSERT_THROW(ref.getAt(-1), std::runtime_error);
}

__TEST_U(TestMemory, test_invalid_set) {
    mixal::ComputerWord word;
    word.set(true, 0, 0, 0, 0, 0);
    __ASSERT_THROW(word.set(0, 0), std::runtime_error);
    __ASSERT_THROW(word.set(7, 0), std::runtime_error);
}

__TEST_U(TestMemory, test_invalid_sign) {
    __ASSERT_THROW(mixal::ComputerWord('*', 1, 2, 3, 4, 5), std::runtime_error);
    __ASSERT_THROW(mixal::ComputerWord('*', 1, 2, 3, 4), std::runtime_error);
    mixal::ComputerWord word;
    word.set(true, 0, 0, 0, 0, 0);
    __ASSERT_THROW(word.set('*', 1, 2, 3, 4, 5), std::runtime_error);
    __ASSERT_THROW(word.set('*', 1, 2, 3, 4), std::runtime_error);
}

__TEST_U(TestMemory, test_value) {
    __ASSERT_EQ(-42, mixal::ComputerWord(-42).value());
}

__TEST_U(TestMemory, test_get_bytes_string) {
    mixal::ComputerWord word;
    word.set('-', 0, 12, 3, 43, 49);
    __ASSERT_EQ("-  0 12  3 43 49", word.getBytesString());
    word.set('+', 12, 3, 43, 49);
    __ASSERT_EQ("+  0 12  3 43 49", word.getBytesString());
}

__TEST_U(TestMemory, test_set_address) {
    mixal::ComputerWord word;
    word.setAddress(-12);
    __ASSERT_EQ(-12, word.addressValue());
}

__TEST_U(TestMemory, test_get_characters) {
    mixal::ComputerWord word('+', 1, 2, 3, 4);
    word.set("A4+ -");
    word.set(2, 10);
    word.set(3, 63);
    __ASSERT_EQ("A´  -", word.getCharacters());
}

__TEST_U(TestMemory, test_set_characters_invalid_length) {
    mixal::ComputerWord word;
    __ASSERT_THROW(word.set("A4+ -s"), std::runtime_error);
}

}  // namespace test
