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
    auto result = mixal::Parser::parseLine("STA 2000", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("LDA 2000(5:5)", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(4:4)", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(3:3)", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(2:2)", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(1:1)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
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
    auto result = mixal::Parser::parseLine("ADD 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(1334, machine.rA.bytes12());
    __ASSERT_EQ(6, machine.rA[3]);
    __ASSERT_EQ(200, machine.rA.bytes45());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_add_negative_zero) {
    machine.rA.set(-123);
    machine.memory[1000].set(123);
    auto result = mixal::Parser::parseLine("ADD 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.negative);
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
    auto result = mixal::Parser::parseLine("ADD 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(926258176, machine.rA.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_add_overflow_negative) {
    machine.rA.set(-1000000000);
    machine.memory[1000].set(-1000000000);
    auto result = mixal::Parser::parseLine("ADD 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.negative);
    __ASSERT_EQ(-926258176, machine.rA.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_sub_packed) {
    machine.rA.set(true, 1234, 0, 0, 9);
    machine.memory[1000].set(true, 2000, 150 / 64, 150 % 64, 0);
    auto result = mixal::Parser::parseLine("SUB 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(766, machine.rA.bytes12());
    __ASSERT_EQ(149, machine.rA.bytes34());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_sub_overflow) {
    machine.rA.set(true, 0, 0, 0, 0, 1);
    machine.memory[1000].set(false, 63, 63, 63, 63, 63);
    auto result = mixal::Parser::parseLine("SUB 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(true, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_mul_all) {
    machine.rA.set(false, 1, 1, 1, 1, 1);
    machine.memory[1000].set(false, 1, 1, 1, 1, 1);
    auto result = mixal::Parser::parseLine("MUL 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(1, machine.rA[2]);
    __ASSERT_EQ(2, machine.rA[3]);
    __ASSERT_EQ(3, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
    __ASSERT_EQ(0, machine.rX.negative);
    __ASSERT_EQ(5, machine.rX[1]);
    __ASSERT_EQ(4, machine.rX[2]);
    __ASSERT_EQ(3, machine.rX[3]);
    __ASSERT_EQ(2, machine.rX[4]);
    __ASSERT_EQ(1, machine.rX[5]);
}

__TEST_U(TestMachineArithmetic, test_mul_one_byte) {
    machine.rA.set(-112);
    machine.memory[1000].set(true, 2, 3, 4, 5, 6);
    auto result = mixal::Parser::parseLine("MUL 1000(1:1)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
    __ASSERT_EQ(0, machine.rA[5]);
    __ASSERT_EQ(1, machine.rX.negative);
    __ASSERT_EQ(-224, machine.rX.value());
}

__TEST_U(TestMachineArithmetic, test_mul_packed) {
    machine.rA.set(true, 50, 0, 112 / 64, 112 % 64, 4);
    machine.memory[1000].set(true, 2, 0, 0, 0, 0);
    auto result = mixal::Parser::parseLine("MUL 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(100, machine.rA.bytes12());
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(224, machine.rA.bytes45());
    __ASSERT_EQ(0, machine.rX.negative);
    __ASSERT_EQ(8, machine.rX[1]);
    __ASSERT_EQ(0, machine.rX[2]);
    __ASSERT_EQ(0, machine.rX[3]);
    __ASSERT_EQ(0, machine.rX[4]);
    __ASSERT_EQ(0, machine.rX[5]);
}

__TEST_U(TestMachineArithmetic, test_div_all) {
    machine.rA.set(0);
    machine.rX.set(17);
    machine.memory[1000].set(3);
    auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(5, machine.rA.value());
    __ASSERT_EQ(0, machine.rX.negative);
    __ASSERT_EQ(2, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_div_all_negative_rx) {
    machine.rA.set(0);
    machine.rX.set(-17);
    machine.memory[1000].set(3);
    auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(5, machine.rA.value());
    __ASSERT_EQ(0, machine.rX.negative);
    __ASSERT_EQ(2, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_div_packed) {
    machine.rA.set(true, 0, 0, 0, 0, 0);
    machine.rX.set(false, 1235, 0, 3, 1);
    machine.memory[1000].set(true, 0, 0, 0, 2, 0);
    auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(617, machine.rA.bytes23());
    __ASSERT_EQ(1, machine.rX.negative);
    __ASSERT_EQ(0, machine.rX[1]);
    __ASSERT_EQ(0, machine.rX[2]);
    __ASSERT_EQ(0, machine.rX[3]);
    __ASSERT_EQ(1, machine.rX[5]);
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_div_overflow) {
    machine.rA.set(true, 64, 0, 0, 0, 0);
    machine.rX.set(false, 0, 0, 0, 0);
    machine.memory[1000].set(false, 0, 0, 0, 0, 3);
    auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-357913941, machine.rA.value());
    __ASSERT_EQ(-1, machine.rX.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineArithmetic, test_div_zero) {
    machine.rA.set(true, 64, 0, 0, 0, 0);
    machine.rX.set(false, 0, 0, 0, 0);
    machine.memory[1000].set(false, 0, 0, 0, 0, 0);
    auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    __ASSERT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    try {
        machine.executeSingle(result.word);
    } catch (mixal::RuntimeError& error) {
        __ASSERT_EQ(std::string("Divisor cannot be 0"), std::string(error.what()));
    }
}

}  // namespace test
