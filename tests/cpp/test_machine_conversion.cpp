#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineConversion : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineConversion() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineConversion, test_num) {
    machine.rA.set(true, 0, 0, 31, 32, 39);
    machine.rX.set(false, 37, 57, 47, 30, 30);
    auto result = mixal::Parser::parseLine("NUM", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12977700, machine.rA.value());
    __ASSERT_EQ(mixal::ComputerWord(false, 37, 57, 47, 30, 30), machine.rX);
}

__TEST_U(TestMachineConversion, test_num_overflow) {
    machine.rA.set(false, 39, 39, 31, 32, 39);
    machine.rX.set(false, 37, 57, 47, 30, 30);
    auto result = mixal::Parser::parseLine("NUM", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(249301284, machine.rA.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineConversion, test_char) {
    machine.rA.set(-12977699);
    machine.rX.set(false, 37, 57, 47, 30, 30);
    auto result = mixal::Parser::parseLine("CHAR", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComputerWord(true, 30, 30, 31, 32, 39), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(false, 37, 37, 36, 39, 39), machine.rX);
}

}  // namespace test
