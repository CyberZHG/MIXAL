#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachinePseudo, test_equ) {
    mixal::Computer machine;
    machine.memory[2000].set(true, 80, 3, 5, 4);
    auto result = mixal::Parser::parseLine("X EQU 1000", "", true);
    EXPECT_EQ(mixal::ParsedType::PSEUDO, result.parsedType);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("  LDA X+X", "", true);
    machine.executeSingle(&result);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachinePseudo, test_equ_with_symbol) {
    mixal::Computer machine;
    machine.memory[2000].set(true, 80, 3, 5, 4);
    auto result = mixal::Parser::parseLine("X EQU 1000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("Y EQU X*2", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("  LDA Y", "", true);
    machine.executeSingle(&result);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachinePseudo, test_equ_with_unknown_symbol) {
    mixal::Computer machine;
    machine.memory[2000].set(true, 80, 3, 5, 4);
    auto result = mixal::Parser::parseLine("X EQU X-X", "", true);
    EXPECT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

TEST(TestMachinePseudo, test_orig) {
    mixal::Computer machine;
    machine.memory[2000].set(true, 80, 3, 5, 4);
    auto result = mixal::Parser::parseLine(" ORIG 3000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA *-1000", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachinePseudo, test_orig_with_location) {
    mixal::Computer machine;
    machine.memory[2000].set(true, 80, 3, 5, 4);
    auto result = mixal::Parser::parseLine("LOC ORIG 3000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA *-1000", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachinePseudo, test_orig_with_equ) {
    mixal::Computer machine;
    machine.memory[2000].set(true, 80, 3, 5, 4);
    auto result = mixal::Parser::parseLine("X EQU 1500", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" ORIG X+X", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA *-1000", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(80, machine.rA.bytes12());
    EXPECT_EQ(3, machine.rA[3]);
    EXPECT_EQ(5, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
}

TEST(TestMachinePseudo, test_orig_with_undefined_symbol) {
    mixal::Computer machine;
    machine.memory[2000].set(true, 80, 3, 5, 4);
    auto result = mixal::Parser::parseLine(" ORIG X+X", "", true);
    EXPECT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

TEST(TestMachinePseudo, test_orig_with_asterisk) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine("FOO ORIG 1500", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("BUF ORIG *+100", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" CON BUF", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA 1600", "", true);
    machine.executeSingle(&result);
    EXPECT_EQ(1500, machine.rA.value());
}

TEST(TestMachinePseudo, test_orig_with_asterisk_loadCodes) {
    mixal::Computer machine;
    machine.loadCodes({
        "BAR  ORIG 1500",
        "BUF  ORIG *+200",
        "     CON  BUF",
        "     LDA  1700",
        "     HLT",
    });
    machine.executeUntilHalt();
    EXPECT_EQ(1500, machine.rA.value());
}

TEST(TestMachinePseudo, test_con_load) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine(" ORIG 2000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("LOC CON 20*30*50", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA LOC", "", true);
    machine.executeSingle(&result);
    EXPECT_EQ(30000, machine.rA.value());
}

TEST(TestMachinePseudo, test_con_load_relative) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine(" ORIG 2000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" CON 20*30*50", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA *-1", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    EXPECT_EQ(30000, machine.rA.value());
}

TEST(TestMachinePseudo, test_con_with_unknown_symbol) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine(" ORIG 2000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" CON A", "", true);
    EXPECT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

TEST(TestMachinePseudo, test_con_with_literal_constant) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine(" LDA =123=", "", true);
    EXPECT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

TEST(TestMachinePseudo, test_alf) {
    mixal::Computer machine;
    machine.loadCodes({
        "     ORIG 3000",
        "     OUT  VAL(17)",
        "LOOP JBUS LOOP(17)",
        "     HLT",
        "VAL  ALF  PRIME",
    });
    machine.executeUntilHalt();
    EXPECT_EQ("PRIME", machine.getDevice(17)->wordAt(0).getCharacters());
}

TEST(TestMachinePseudo, test_alf_short) {
    mixal::Computer machine;
    machine.loadCodes({
        "     ORIG 3000",
        "     OUT  VAL(17)",
        "LOOP JBUS LOOP(17)",
        "     HLT",
        "VAL  ALF  PRIM",
    });
    machine.executeUntilHalt();
    EXPECT_EQ("PRIM ", machine.getDevice(17)->wordAt(0).getCharacters());
}

TEST(TestMachinePseudo, test_alf_none) {
    mixal::Computer machine;
    machine.loadCodes({
        "     ORIG 3000",
        "     OUT  VAL(17)",
        "LOOP JBUS LOOP(17)",
        "     HLT",
        "VAL  ALF",
    });
    machine.executeUntilHalt();
    EXPECT_EQ("     ", machine.getDevice(17)->wordAt(0).getCharacters());
}

TEST(TestMachinePseudo, test_alf_long) {
    mixal::Computer machine;
    machine.loadCodes({
        "     ORIG 3000",
        "     OUT  VAL(17)",
        "LOOP JBUS LOOP(17)",
        "     HLT",
        "VAL  ALF  PRIME with comments",
    });
    machine.executeUntilHalt();
    EXPECT_EQ("PRIME", machine.getDevice(17)->wordAt(0).getCharacters());
}

TEST(TestMachinePseudo, test_end) {
    mixal::Computer machine;
    machine.loadCodes({
        "       ORIG 3000",
        "       ENTA 1000",
        "START  ADD  =100=",
        "EXIT   END  START",
    });
    EXPECT_EQ(3001, machine.line());
    machine.executeUntilHalt();
    EXPECT_EQ(100, machine.rA.value());
}
