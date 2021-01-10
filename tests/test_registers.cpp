#include <gtest/gtest.h>
#include "registers.h"

TEST(TestRegisters, test_register2_length) {
    EXPECT_EQ(3U, sizeof(mixal::Register2));
}

TEST(TestRegisters, test_invalid_get) {
    mixal::Register2 reg;
    EXPECT_THROW(reg[0], std::runtime_error);
    EXPECT_THROW(reg[3], std::runtime_error);
}

TEST(TestRegisters, test_invalid_set) {
    mixal::Register2 reg;
    reg.set(true, 0, 0);
    EXPECT_THROW(reg.set(0, 0), std::runtime_error);
    EXPECT_THROW(reg.set(3, 0), std::runtime_error);
}

TEST(TestRegisters, test_invalid_sign) {
    EXPECT_THROW(mixal::Register2('*', 0, 1), std::runtime_error);
    mixal::Register2 reg('-', 0, 0);
    reg.set('+', 0, 0);
    EXPECT_THROW(reg.set('*', 2, 3), std::runtime_error);
}

TEST(TestRegisters, test_value) {
    EXPECT_EQ(1, mixal::Register2(1).value());
    EXPECT_EQ(-1, mixal::Register2(true, 0, 1).value());
}
