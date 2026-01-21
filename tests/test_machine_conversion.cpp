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

TEST(TestMachineConversion, test_flot) {
    mixal::Computer machine;
    machine.rA.set(123);
    const auto result = mixal::Parser::parseLine("FLOT", "", false);
    machine.executeSingle(result.word);
    EXPECT_NEAR(123.0, machine.rA.floatValue(), 1e-5);
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineConversion, test_fix) {
    mixal::Computer machine;
    machine.rA.set(123.4);
    const auto result = mixal::Parser::parseLine("FIX", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(123, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineConversion, test_overflow) {
    mixal::Computer machine;
    machine.rA.set(2e10);
    const auto result = mixal::Parser::parseLine("FIX", "", false);
    machine.executeSingle(result.word);
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineConversion, test_overflow_int_max) {
    mixal::Computer machine;
    machine.rA.set(1e300);
    const auto result = mixal::Parser::parseLine("FIX", "", false);
    machine.executeSingle(result.word);
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineConversion, test_overflow_int_min) {
    mixal::Computer machine;
    machine.rA.set(-1e300);
    const auto result = mixal::Parser::parseLine("FIX", "", false);
    machine.executeSingle(result.word);
    EXPECT_TRUE(machine.overflow);
}