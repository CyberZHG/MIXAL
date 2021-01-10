#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachineMISC, test_sla_0) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 0", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
}

TEST(TestMachineMISC, test_sla_1) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 1", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 2, 3, 4, 5, 0), machine.rA);
}

TEST(TestMachineMISC, test_sla_2) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 2", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 3, 4, 5, 0, 0), machine.rA);
}

TEST(TestMachineMISC, test_sla_3) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 3", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 4, 5, 0, 0, 0), machine.rA);
}

TEST(TestMachineMISC, test_sla_4) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 4", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 5, 0, 0, 0, 0), machine.rA);
}

TEST(TestMachineMISC, test_sla_5) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SLA 5", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
}

TEST(TestMachineMISC, test_sra_0) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 0", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
}

TEST(TestMachineMISC, test_sra_1) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 1", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 0, 1, 2, 3, 4), machine.rA);
}

TEST(TestMachineMISC, test_sra_2) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 2", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 0, 0, 1, 2, 3), machine.rA);
}

TEST(TestMachineMISC, test_sra_3) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 3", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 0, 0, 0, 1, 2), machine.rA);
}

TEST(TestMachineMISC, test_sra_4) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 4", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 0, 0, 0, 0, 1), machine.rA);
}

TEST(TestMachineMISC, test_sra_5) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("SRA 5", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
}

TEST(TestMachineMISC, test_slax_0) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 0", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 6, 7, 8, 9, 10), machine.rX);
}

TEST(TestMachineMISC, test_slax_1) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 1", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 2, 3, 4, 5, 6), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 7, 8, 9, 10, 0), machine.rX);
}

TEST(TestMachineMISC, test_slax_3) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 3", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 4, 5, 6, 7, 8), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 9, 10, 0, 0, 0), machine.rX);
}

TEST(TestMachineMISC, test_slax_6) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 6", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 7, 8, 9, 10, 0), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 0, 0, 0, 0, 0), machine.rX);
}

TEST(TestMachineMISC, test_slax_9) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLAX 9", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 10, 0, 0, 0, 0), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 0, 0, 0, 0, 0), machine.rX);
}

TEST(TestMachineMISC, test_srax_0) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 0", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 1, 2, 3, 4, 5), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 6, 7, 8, 9, 10), machine.rX);
}

TEST(TestMachineMISC, test_srax_1) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 1", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 0, 1, 2, 3, 4), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 5, 6, 7, 8, 9), machine.rX);
}

TEST(TestMachineMISC, test_srax_3) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 3", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 0, 0, 0, 1, 2), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 3, 4, 5, 6, 7), machine.rX);
}

TEST(TestMachineMISC, test_srax_6) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 6", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 0, 0, 0, 0, 0), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 0, 1, 2, 3, 4), machine.rX);
}

TEST(TestMachineMISC, test_srax_9) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRAX 9", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 0, 0, 0, 0, 0), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 0, 0, 0, 0, 1), machine.rX);
}

TEST(TestMachineMISC, test_slc_1) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLC 1", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 2, 3, 4, 5, 6), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 7, 8, 9, 10, 1), machine.rX);
}

TEST(TestMachineMISC, test_slc_3) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLC 3", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 4, 5, 6, 7, 8), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 9, 10, 1, 2, 3), machine.rX);
}

TEST(TestMachineMISC, test_slc_6) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLC 6", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 7, 8, 9, 10, 1), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 2, 3, 4, 5, 6), machine.rX);
}

TEST(TestMachineMISC, test_slc_9) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SLC 9", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 10, 1, 2, 3, 4), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 5, 6, 7, 8, 9), machine.rX);
}

TEST(TestMachineMISC, test_src_1) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRC 1", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 10, 1, 2, 3, 4), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 5, 6, 7, 8, 9), machine.rX);
}

TEST(TestMachineMISC, test_src_3) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRC 3", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 8, 9, 10, 1, 2), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 3, 4, 5, 6, 7), machine.rX);
}

TEST(TestMachineMISC, test_src_6) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRC 6", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 5, 6, 7, 8, 9), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 10, 1, 2, 3, 4), machine.rX);
}

TEST(TestMachineMISC, test_src_9) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 2, 3, 4, 5);
    machine.rX.set(true, 6, 7, 8, 9, 10);
    auto result = mixal::Parser::parseLine("SRC 9", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(mixal::ComputerWord(false, 2, 3, 4, 5, 6), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(true, 7, 8, 9, 10, 1), machine.rX);
}

TEST(TestMachineMISC, test_move_safe) {
    mixal::Computer machine;
    machine.rI1.set(999);
    machine.memory[1000].set(1);
    machine.memory[1001].set(12);
    machine.memory[1002].set(123);
    auto result = mixal::Parser::parseLine("MOVE 1000(3)", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(1, machine.memory[999].value());
    EXPECT_EQ(12, machine.memory[1000].value());
    EXPECT_EQ(123, machine.memory[1001].value());
    EXPECT_EQ(123, machine.memory[1002].value());
}

TEST(TestMachineMISC, test_move_unsafe) {
    mixal::Computer machine;
    machine.rI1.set(1001);
    machine.memory[1000].set(1);
    machine.memory[1001].set(12);
    auto result = mixal::Parser::parseLine("MOVE 1000(3)", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(1, machine.memory[1000].value());
    EXPECT_EQ(1, machine.memory[1001].value());
    EXPECT_EQ(1, machine.memory[1002].value());
    EXPECT_EQ(1, machine.memory[1003].value());
}

TEST(TestMachineMISC, test_move_stacked) {
    mixal::Computer machine;
    machine.rI1.set(999);
    machine.memory[1000].set(1);
    machine.memory[1001].set(12);
    machine.memory[1002].set(123);
    auto result = mixal::Parser::parseLine("MOVE 1000(1)", "", false);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("MOVE 1001(1)", "", false);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("MOVE 1002(1)", "", false);
    machine.executeSingle(&result);
    EXPECT_EQ(1, machine.memory[999].value());
    EXPECT_EQ(12, machine.memory[1000].value());
    EXPECT_EQ(123, machine.memory[1001].value());
    EXPECT_EQ(123, machine.memory[1002].value());
}

TEST(TestMachineMISC, test_move_out_of_range) {
    mixal::Computer machine;
    machine.rI1.set(4000);
    machine.memory[1000].set(1);
    auto result = mixal::Parser::parseLine("MOVE 1000(1)", "", false);
    machine.executeSingle(&result);
}

TEST(TestMachineMISC, test_hlt) {
    mixal::Computer machine;
    machine.loadCodes({
        "     ORIG 3000",
        "     HLT",
        "     LDA  =23=",
        "     HLT",
    });
    machine.executeUntilHalt();
    EXPECT_EQ(0, machine.rA.value());
    machine.executeUntilHalt();
    EXPECT_EQ(23, machine.rA.value());
}
