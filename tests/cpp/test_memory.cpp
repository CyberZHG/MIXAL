#include "test.h"
#include "memory.h"

namespace test {

class TestMemory : public UnitTest {};

__TEST_U(TestMemory, test_word_length) {
    __ASSERT_EQ(8U, sizeof(mixal::ComputerWord));
}

}  // namespace test
