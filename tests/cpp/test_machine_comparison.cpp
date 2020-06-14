#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineComparison : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineComparison() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineComparison, test_cmpa) {
    machine.rA.set(-12345);
    machine.memory[1000].set(12345);
    auto result = mixal::Parser::parseLine("CMPA 1000(1:5)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComparisonIndicator::EQUAL, machine.comparison);
    result = mixal::Parser::parseLine("CMPA 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComparisonIndicator::LESS, machine.comparison);
}

__TEST_U(TestMachineComparison, test_cmpx) {
    machine.rA.set(0);
    machine.rI6().set(-1);
    machine.memory[1000].set(-12345);
    auto result = mixal::Parser::parseLine("CMPX 1000,6", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComparisonIndicator::EQUAL, machine.comparison);
    result = mixal::Parser::parseLine("CMPX 1000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComparisonIndicator::GREATER, machine.comparison);
}

__TEST_U(TestMachineComparison, test_cmpi) {
    machine.rI6().set(false, 6, 5);
    machine.memory[1000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("CMP6 1000(1:2)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComparisonIndicator::LESS, machine.comparison);
    result = mixal::Parser::parseLine("CMP6 1000(4:4)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComparisonIndicator::GREATER, machine.comparison);
    result = mixal::Parser::parseLine("CMP6 1000(5:5)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComparisonIndicator::EQUAL, machine.comparison);
    result = mixal::Parser::parseLine("CMP6 1000(0:0)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(mixal::ComparisonIndicator::EQUAL, machine.comparison);
}


}  // namespace test
