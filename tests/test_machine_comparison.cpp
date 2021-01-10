#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachineComparison, test_cmpa) {
    mixal::Computer machine;
    machine.rA.set(-12345);
    machine.memory[1000].set(12345);
    auto result = mixal::Parser::parseLine("CMPA 1000(1:5)", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComparisonIndicator::EQUAL, machine.comparison);
    result = mixal::Parser::parseLine("CMPA 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComparisonIndicator::LESS, machine.comparison);
}

TEST(TestMachineComparison, test_cmpx) {
    mixal::Computer machine;
    machine.rA.set(0);
    machine.rI6.set(-1);
    machine.memory[1000].set(-12345);
    auto result = mixal::Parser::parseLine("CMPX 1000,6", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComparisonIndicator::EQUAL, machine.comparison);
    result = mixal::Parser::parseLine("CMPX 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComparisonIndicator::GREATER, machine.comparison);
}

TEST(TestMachineComparison, test_cmpi) {
    mixal::Computer machine;
    machine.rI6.set(false, 6, 5);
    machine.memory[1000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("CMP6 1000(1:2)", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComparisonIndicator::LESS, machine.comparison);
    result = mixal::Parser::parseLine("CMP6 1000(4:4)", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComparisonIndicator::GREATER, machine.comparison);
    result = mixal::Parser::parseLine("CMP6 1000(5:5)", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComparisonIndicator::EQUAL, machine.comparison);
    result = mixal::Parser::parseLine("CMP6 1000(0:0)", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(mixal::ComparisonIndicator::EQUAL, machine.comparison);
}
