#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachineLoad, test_lda_all) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDA 2000", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachineLoad, test_lda_1_to_5) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDA 2000(1:5)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachineLoad, test_lda_3_to_5) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDA 2000(3:5)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(0, machine.rA[2]);
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachineLoad, test_lda_0_to_3) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDA 2000(0:3)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(0, machine.rA[2]);
    EXPECT_EQ(80, machine.rA.bytes34());
    EXPECT_EQ(3, machine.rA[5]);
}

TEST(TestMachineLoad, test_lda_4_to_4) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDA 2000(4:4)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(0, machine.rA[2]);
    EXPECT_EQ(0, machine.rA[3]);
    EXPECT_EQ(0, machine.rA[4]);
    EXPECT_EQ(5, machine.rA[5]);
}

TEST(TestMachineLoad, test_lda_0_to_0) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDA 2000(0:0)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(0, machine.rA[2]);
    EXPECT_EQ(0, machine.rA[3]);
    EXPECT_EQ(0, machine.rA[4]);
    EXPECT_EQ(0, machine.rA[5]);
}

TEST(TestMachineLoad, test_lda_1_to_1) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDA 2000(1:1)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(0, machine.rA[2]);
    EXPECT_EQ(0, machine.rA[3]);
    EXPECT_EQ(0, machine.rA[4]);
}

TEST(TestMachineLoad, test_lda_all_with_offset) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDA 2003,1", "", false);
    machine.rI1.negative = 1;
    machine.rI1.set(1, 0);
    machine.rI1.set(2, 3);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachineLoad, test_ld1) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LD1 2000(0:2)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rI1.negative);
    EXPECT_EQ(80, machine.rI1.bytes12());
    EXPECT_EQ(-80, machine.rI1.value());
}

TEST(TestMachineLoad, test_ld2) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LD2 2000(1:2)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rI2.negative);
    EXPECT_EQ(80, machine.rI2.bytes12());
    EXPECT_EQ(80, machine.rI2.value());
}

TEST(TestMachineLoad, test_ld3) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LD3 2000(3:4)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rI3.negative);
    EXPECT_EQ(3, machine.rI3[1]);
    EXPECT_EQ(5, machine.rI3[2]);
}

TEST(TestMachineLoad, test_ld4) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LD4 2000(4:5)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rI4.negative);
    EXPECT_EQ(5, machine.rI4[1]);
    EXPECT_EQ(4, machine.rI4[2]);
}

TEST(TestMachineLoad, test_ld5) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LD5 2000(4:4)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rI5.negative);
    EXPECT_EQ(0, machine.rI5[1]);
    EXPECT_EQ(5, machine.rI5[2]);
}

TEST(TestMachineLoad, test_ld6) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LD6 2000(0:0)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rI6.negative);
    EXPECT_EQ(0, machine.rI6[1]);
    EXPECT_EQ(0, machine.rI6[2]);
}

TEST(TestMachineLoad, test_ldx_all) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDX 2000", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rX.negative);
    EXPECT_EQ(80, machine.rX.bytes12());
    EXPECT_EQ(3, machine.rX[3]);
    EXPECT_EQ(5, machine.rX[4]);
    EXPECT_EQ(4, machine.rX[5]);
}

TEST(TestMachineLoad, test_ldan) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDAN 2000", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachineLoad, test_ld6n) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LD6N 2000(0:0)", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rI6.negative);
    EXPECT_EQ(0, machine.rI6[1]);
    EXPECT_EQ(0, machine.rI6[2]);
    machine.executeSingle(mixal::Parser::parseLine("LD5N 2000(0:0)", "", false).word);
    machine.executeSingle(mixal::Parser::parseLine("LD4N 2000(0:0)", "", false).word);
    machine.executeSingle(mixal::Parser::parseLine("LD3N 2000(0:0)", "", false).word);
    machine.executeSingle(mixal::Parser::parseLine("LD2N 2000(0:0)", "", false).word);
    machine.executeSingle(mixal::Parser::parseLine("LD1N 2000(0:0)", "", false).word);
}

TEST(TestMachineLoad, test_ldxn) {
    mixal::Computer machine;
    const auto result = mixal::Parser::parseLine("LDXN 2000", "", false);
    machine.memory[2000].set(true, 80, 3, 5, 4);;
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rX.negative);
    EXPECT_EQ(80, machine.rX.bytes12());
    EXPECT_EQ(3, machine.rX[3]);
    EXPECT_EQ(5, machine.rX[4]);
    EXPECT_EQ(4, machine.rX[5]);
}
