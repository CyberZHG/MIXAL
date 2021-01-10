#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachineConversion, test_num) {
    mixal::Computer machine;
    machine.rA.set(true, 0, 0, 31, 32, 39);
    machine.rX.set(false, 37, 57, 47, 30, 30);
    const auto result = mixal::Parser::parseLine("NUM", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12977700, machine.rA.value());
    EXPECT_EQ(mixal::ComputerWord(false, 37, 57, 47, 30, 30), machine.rX);
}

TEST(TestMachineConversion, test_num_overflow) {
    mixal::Computer machine;
    machine.rA.set(false, 39, 39, 31, 32, 39);
    machine.rX.set(false, 37, 57, 47, 30, 30);
    const auto result = mixal::Parser::parseLine("NUM", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(249301284, machine.rA.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineConversion, test_char) {
    mixal::Computer machine;
    machine.rA.set(-12977699);
    machine.rX.set(false, 37, 57, 47, 30, 30);
    const auto result = mixal::Parser::parseLine("CHAR", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComputerWord(true, 30, 30, 31, 32, 39), machine.rA);
    EXPECT_EQ(mixal::ComputerWord(false, 37, 37, 36, 39, 39), machine.rX);
}
