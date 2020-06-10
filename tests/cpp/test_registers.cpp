#include "test.h"
#include "registers.h"

namespace test {

class TestRegisters : public UnitTest {};

__TEST_U(TestRegisters, test_register2_length) {
    __ASSERT_EQ(3U, sizeof(mixal::Register2));
}

__TEST_U(TestRegisters, test_invalid_get) {
    mixal::Register2 reg;
    __ASSERT_THROW(reg[0], std::runtime_error);
    __ASSERT_THROW(reg[3], std::runtime_error);
}

__TEST_U(TestRegisters, test_invalid_set) {
    mixal::Register2 reg;
    reg.set(true, 0, 0);
    __ASSERT_THROW(reg.set(0, 0), std::runtime_error);
    __ASSERT_THROW(reg.set(3, 0), std::runtime_error);
}

}  // namespace test
