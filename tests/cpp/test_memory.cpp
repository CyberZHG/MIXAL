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
}

__TEST_U(TestMemory, test_invalid_set) {
    mixal::ComputerWord word;
    word.set(true, 0, 0, 0, 0, 0);
    __ASSERT_THROW(word.set(0, 0), std::runtime_error);
    __ASSERT_THROW(word.set(7, 0), std::runtime_error);
}

}  // namespace test
