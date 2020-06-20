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

__TEST_U(TestMachineMISC, test_slax_0) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 0", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 6, 7, 8, 9, 10), machine.rX);
}

__TEST_U(TestMachineMISC, test_slax_1) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 1", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 2, 3, 4, 5, 6), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 7, 8, 9, 10, 0), machine.rX);
}

__TEST_U(TestMachineMISC, test_slax_3) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 3", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 4, 5, 6, 7, 8), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 9, 10, 0, 0, 0), machine.rX);
}

__TEST_U(TestMachineMISC, test_slax_6) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 6", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 7, 8, 9, 10, 0), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 0, 0, 0, 0, 0), machine.rX);
}

__TEST_U(TestMachineMISC, test_slax_9) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 9", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 10, 0, 0, 0, 0), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 0, 0, 0, 0, 0), machine.rX);
}

__TEST_U(TestMachineMISC, test_srax_0) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 0", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 6, 7, 8, 9, 10), machine.rX);
}

__TEST_U(TestMachineMISC, test_srax_1) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 1", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 1, 2, 3, 4), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 5, 6, 7, 8, 9), machine.rX);
}

__TEST_U(TestMachineMISC, test_srax_3) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 3", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 0, 0, 1, 2), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 3, 4, 5, 6, 7), machine.rX);
}

__TEST_U(TestMachineMISC, test_srax_6) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 6", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 0, 0, 0, 0), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 0, 1, 2, 3, 4), machine.rX);
}

__TEST_U(TestMachineMISC, test_srax_9) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 9", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 0, 0, 0, 0), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 0, 0, 0, 0, 1), machine.rX);
}

__TEST_U(TestMachineMISC, test_slc_1) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLC 1", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 2, 3, 4, 5, 6), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 7, 8, 9, 10, 1), machine.rX);
}

__TEST_U(TestMachineMISC, test_slc_3) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLC 3", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 4, 5, 6, 7, 8), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 9, 10, 1, 2, 3), machine.rX);
}

__TEST_U(TestMachineMISC, test_slc_6) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLC 6", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 7, 8, 9, 10, 1), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 2, 3, 4, 5, 6), machine.rX);
}

__TEST_U(TestMachineMISC, test_slc_9) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLC 9", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 10, 1, 2, 3, 4), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 5, 6, 7, 8, 9), machine.rX);
}

__TEST_U(TestMachineMISC, test_src_1) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRC 1", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 10, 1, 2, 3, 4), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 5, 6, 7, 8, 9), machine.rX);
}

__TEST_U(TestMachineMISC, test_src_3) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRC 3", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 8, 9, 10, 1, 2), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 3, 4, 5, 6, 7), machine.rX);
}

__TEST_U(TestMachineMISC, test_src_6) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRC 6", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 5, 6, 7, 8, 9), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 10, 1, 2, 3, 4), machine.rX);
}

__TEST_U(TestMachineMISC, test_src_9) {
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRC 9", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(mixal::ComputerWord(false, 2, 3, 4, 5, 6), machine.rA);
    __ASSERT_EQ(mixal::ComputerWord(true, 7, 8, 9, 10, 1), machine.rX);
}

}  // namespace test
