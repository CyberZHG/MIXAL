#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineArithmetic : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineArithmetic() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineArithmetic, test_add_all_ra_bytes) {
    machine.rA.set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STA 2000", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("LDA 2000(5:5)", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(4:4)", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(3:3)", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(2:2)", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(1:1)", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.sign);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
    __ASSERT_EQ(15, machine.rA[5]);
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_add_packed) {
    machine.rA.set(false, 1234, 1, 150 / 64, 150 % 64);
    machine.memory[1000].set(false, 100, 5, 0, 50);
    auto result = mixal::Parser::parseLine("ADD 1000", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.sign);
    __ASSERT_EQ(1334, machine.rA.bytes12());
    __ASSERT_EQ(6, machine.rA[3]);
    __ASSERT_EQ(200, machine.rA.bytes45());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_add_negative_zero) {
    machine.rA.set(-123);
    machine.memory[1000].set(123);
    auto result = mixal::Parser::parseLine("ADD 1000", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
    __ASSERT_EQ(0, machine.rA[5]);
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_add_overflow_positive) {
    machine.rA.set(1000000000);
    machine.memory[1000].set(1000000000);
    auto result = mixal::Parser::parseLine("ADD 1000", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.sign);
    __ASSERT_EQ(926258176, machine.rA.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_add_overflow_negative) {
    machine.rA.set(-1000000000);
    machine.memory[1000].set(-1000000000);
    auto result = mixal::Parser::parseLine("ADD 1000", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(-926258176, machine.rA.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_sub_packed) {
    machine.rA.set(true, 1234, 0, 0, 9);
    machine.memory[1000].set(true, 2000, 150 / 64, 150 % 64, 0);
    auto result = mixal::Parser::parseLine("SUB 1000", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.sign);
    __ASSERT_EQ(766, machine.rA.bytes12());
    __ASSERT_EQ(149, machine.rA.bytes34());
    __ASSERT_FALSE(machine.overflow);
}

}  // namespace test
