#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachineArithmetic, test_add_all_ra_bytes) {
    mixal::Computer machine;
    machine.rA.set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STA 2000", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("LDA 2000(5:5)", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(4:4)", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(3:3)", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(2:2)", "", false);
    machine.executeSingle(result.word);
    result = mixal::Parser::parseLine("ADD 2000(1:1)", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(0, machine.rA[2]);
    EXPECT_EQ(0, machine.rA[3]);
    EXPECT_EQ(0, machine.rA[4]);
    EXPECT_EQ(15, machine.rA[5]);
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineArithmetic, test_add_packed) {
    mixal::Computer machine;
    machine.rA.set(false, 1234, 1, 150 / 64, 150 % 64);
    machine.memory[1000].set(false, 100, 5, 0, 50);
    const auto result = mixal::Parser::parseLine("ADD 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(1334, machine.rA.bytes12());
    EXPECT_EQ(6, machine.rA[3]);
    EXPECT_EQ(200, machine.rA.bytes45());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineArithmetic, test_add_negative_zero) {
    mixal::Computer machine;
    machine.rA.set(-123);
    machine.memory[1000].set(123);
    const auto result = mixal::Parser::parseLine("ADD 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(0, machine.rA[2]);
    EXPECT_EQ(0, machine.rA[3]);
    EXPECT_EQ(0, machine.rA[4]);
    EXPECT_EQ(0, machine.rA[5]);
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineArithmetic, test_add_overflow_positive) {
    mixal::Computer machine;
    machine.rA.set(1000000000);
    machine.memory[1000].set(1000000000);
    const auto result = mixal::Parser::parseLine("ADD 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(926258176, machine.rA.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineArithmetic, test_add_overflow_negative) {
    mixal::Computer machine;
    machine.rA.set(-1000000000);
    machine.memory[1000].set(-1000000000);
    const auto result = mixal::Parser::parseLine("ADD 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(-926258176, machine.rA.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineArithmetic, test_sub_packed) {
    mixal::Computer machine;
    machine.rA.set(true, 1234, 0, 0, 9);
    machine.memory[1000].set(true, 2000, 150 / 64, 150 % 64, 0);
    const auto result = mixal::Parser::parseLine("SUB 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(766, machine.rA.bytes12());
    EXPECT_EQ(149, machine.rA.bytes34());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineArithmetic, test_sub_overflow) {
    mixal::Computer machine;
    machine.rA.set(true, 0, 0, 0, 0, 1);
    machine.memory[1000].set(false, 63, 63, 63, 63, 63);
    const auto result = mixal::Parser::parseLine("SUB 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(true, machine.rA.negative);
    EXPECT_EQ(0, machine.rA.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineArithmetic, test_mul_all) {
    mixal::Computer machine;
    machine.rA.set(false, 1, 1, 1, 1, 1);
    machine.memory[1000].set(false, 1, 1, 1, 1, 1);
    const auto result = mixal::Parser::parseLine("MUL 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(1, machine.rA[2]);
    EXPECT_EQ(2, machine.rA[3]);
    EXPECT_EQ(3, machine.rA[4]);
    EXPECT_EQ(4, machine.rA[5]);
    EXPECT_EQ(0, machine.rX.negative);
    EXPECT_EQ(5, machine.rX[1]);
    EXPECT_EQ(4, machine.rX[2]);
    EXPECT_EQ(3, machine.rX[3]);
    EXPECT_EQ(2, machine.rX[4]);
    EXPECT_EQ(1, machine.rX[5]);
}

TEST(TestMachineArithmetic, test_mul_one_byte) {
    mixal::Computer machine;
    machine.rA.set(-112);
    machine.memory[1000].set(true, 2, 3, 4, 5, 6);
    const auto result = mixal::Parser::parseLine("MUL 1000(1:1)", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(1, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(0, machine.rA[2]);
    EXPECT_EQ(0, machine.rA[3]);
    EXPECT_EQ(0, machine.rA[4]);
    EXPECT_EQ(0, machine.rA[5]);
    EXPECT_EQ(1, machine.rX.negative);
    EXPECT_EQ(-224, machine.rX.value());
}

TEST(TestMachineArithmetic, test_mul_packed) {
    mixal::Computer machine;
    machine.rA.set(true, 50, 0, 112 / 64, 112 % 64, 4);
    machine.memory[1000].set(true, 2, 0, 0, 0, 0);
    const auto result = mixal::Parser::parseLine("MUL 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(100, machine.rA.bytes12());
    EXPECT_EQ(0, machine.rA[3]);
    EXPECT_EQ(224, machine.rA.bytes45());
    EXPECT_EQ(0, machine.rX.negative);
    EXPECT_EQ(8, machine.rX[1]);
    EXPECT_EQ(0, machine.rX[2]);
    EXPECT_EQ(0, machine.rX[3]);
    EXPECT_EQ(0, machine.rX[4]);
    EXPECT_EQ(0, machine.rX[5]);
}

TEST(TestMachineArithmetic, test_div_all) {
    mixal::Computer machine;
    machine.rA.set(0);
    machine.rX.set(17);
    machine.memory[1000].set(3);
    const auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(5, machine.rA.value());
    EXPECT_EQ(0, machine.rX.negative);
    EXPECT_EQ(2, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineArithmetic, test_div_all_negative_rx) {
    mixal::Computer machine;
    machine.rA.set(0);
    machine.rX.set(-17);
    machine.memory[1000].set(3);
    const auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(5, machine.rA.value());
    EXPECT_EQ(0, machine.rX.negative);
    EXPECT_EQ(2, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineArithmetic, test_div_packed) {
    mixal::Computer machine;
    machine.rA.set(true, 0, 0, 0, 0, 0);
    machine.rX.set(false, 1235, 0, 3, 1);
    machine.memory[1000].set(true, 0, 0, 0, 2, 0);
    const auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.negative);
    EXPECT_EQ(0, machine.rA[1]);
    EXPECT_EQ(617, machine.rA.bytes23());
    EXPECT_EQ(1, machine.rX.negative);
    EXPECT_EQ(0, machine.rX[1]);
    EXPECT_EQ(0, machine.rX[2]);
    EXPECT_EQ(0, machine.rX[3]);
    EXPECT_EQ(1, machine.rX[5]);
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineArithmetic, test_div_overflow) {
    mixal::Computer machine;
    machine.rA.set(true, 64, 0, 0, 0, 0);
    machine.rX.set(false, 0, 0, 0, 0);
    machine.memory[1000].set(false, 0, 0, 0, 0, 3);
    const auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-357913941, machine.rA.value());
    EXPECT_EQ(-1, machine.rX.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineArithmetic, test_div_zero) {
    mixal::Computer machine;
    machine.rA.set(true, 64, 0, 0, 0, 0);
    machine.rX.set(false, 0, 0, 0, 0);
    machine.memory[1000].set(false, 0, 0, 0, 0, 0);
    const auto result = mixal::Parser::parseLine("DIV 1000", "", false);
    EXPECT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    try {
        machine.executeSingle(result.word);
    } catch (mixal::RuntimeError& error) {
        EXPECT_EQ(std::string("Divisor cannot be 0"), std::string(error.what()));
    }
}
