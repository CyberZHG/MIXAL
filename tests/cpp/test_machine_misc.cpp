#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineMISC : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineMISC() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineMISC, test_sla_0) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 0", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
}

__TEST_U(TestMachineMISC, test_sla_1) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 1", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 2, 3, 4, 5, 0), machine.rA);
}

__TEST_U(TestMachineMISC, test_sla_2) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 2", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 3, 4, 5, 0, 0), machine.rA);
}

__TEST_U(TestMachineMISC, test_sla_3) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 3", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 4, 5, 0, 0, 0), machine.rA);
}

__TEST_U(TestMachineMISC, test_sla_4) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 4", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 5, 0, 0, 0, 0), machine.rA);
}

__TEST_U(TestMachineMISC, test_sla_5) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 5", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
}

__TEST_U(TestMachineMISC, test_sra_0) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 0", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
}

__TEST_U(TestMachineMISC, test_sra_1) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 1", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 1, 2, 3, 4), machine.rA);
}

__TEST_U(TestMachineMISC, test_sra_2) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 2", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 0, 1, 2, 3), machine.rA);
}

__TEST_U(TestMachineMISC, test_sra_3) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 3", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 0, 0, 1, 2), machine.rA);
}

__TEST_U(TestMachineMISC, test_sra_4) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 4", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 0, 0, 0, 1), machine.rA);
}

__TEST_U(TestMachineMISC, test_sra_5) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 5", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
}

}  // namespace test
