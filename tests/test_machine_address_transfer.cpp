#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachineAddressTransfer, test_inca) {
    mixal::Computer machine;
    machine.rA.set(-12345);
    auto result = mixal::Parser::parseLine("INCA 47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12298, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_inca_with_index) {
    mixal::Computer machine;
    machine.rA.set(-12345);
    machine.rI2.set(47);
    auto result = mixal::Parser::parseLine("INCA 0,2", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12298, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_inca_overflow) {
    mixal::Computer machine;
    machine.rA.set(1073741814);
    const auto result = mixal::Parser::parseLine("INCA 47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(37, machine.rA.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_deca) {
    mixal::Computer machine;
    machine.rA.set(-12345);
    const auto result = mixal::Parser::parseLine("DECA -47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12298, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_deca_with_index) {
    mixal::Computer machine;
    machine.rA.set(-12345);
    machine.rI3.set(-47);
    const auto result = mixal::Parser::parseLine("DECA 0,3", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12298, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_deca_overflow) {
    mixal::Computer machine;
    machine.rA.set(-1073741814);
    const auto result = mixal::Parser::parseLine("DECA 47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-37, machine.rA.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_enta) {
    mixal::Computer machine;
    machine.rA.set(-1073741814);
    const auto result = mixal::Parser::parseLine("ENTA 0", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_enta_with_index) {
    mixal::Computer machine;
    machine.rA.set(1073741814);
    machine.rI4.set(5);
    const auto result = mixal::Parser::parseLine("ENTA -5,4", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(true, machine.rA.negative);
    EXPECT_EQ(0, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_enna) {
    mixal::Computer machine;
    machine.rA.set(-1073741814);
    const auto result = mixal::Parser::parseLine("ENNA 0", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(true, machine.rA.negative);
    EXPECT_EQ(0, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_enna_with_index) {
    mixal::Computer machine;
    machine.rA.set(1073741814);
    machine.rI5.set(5);
    const auto result = mixal::Parser::parseLine("ENNA -5,5", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(false, machine.rA.negative);
    EXPECT_EQ(0, machine.rA.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_incx) {
    mixal::Computer machine;
    machine.rX.set(-12345);
    const auto result = mixal::Parser::parseLine("INCX 47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12298, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_incx_with_index) {
    mixal::Computer machine;
    machine.rX.set(-12345);
    machine.rI2.set(47);
    const auto result = mixal::Parser::parseLine("INCX 0,2", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12298, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_incx_overflow) {
    mixal::Computer machine;
    machine.rX.set(1073741814);
    const auto result = mixal::Parser::parseLine("INCX 47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(37, machine.rX.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_decx) {
    mixal::Computer machine;
    machine.rX.set(-12345);
    const auto result = mixal::Parser::parseLine("DECX -47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12298, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_decx_with_index) {
    mixal::Computer machine;
    machine.rX.set(-12345);
    machine.rI3.set(-47);
    const auto result = mixal::Parser::parseLine("DECX 0,3", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-12298, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_decx_overflow) {
    mixal::Computer machine;
    machine.rX.set(-1073741814);
    const auto result = mixal::Parser::parseLine("DECX 47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-37, machine.rX.value());
    EXPECT_TRUE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_entx) {
    mixal::Computer machine;
    machine.rX.set(-1073741814);
    const auto result = mixal::Parser::parseLine("ENTX 0", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_entx_with_index) {
    mixal::Computer machine;
    machine.rX.set(1073741814);
    machine.rI4.set(5);
    const auto result = mixal::Parser::parseLine("ENTX -5,4", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(true, machine.rX.negative);
    EXPECT_EQ(0, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_ennx) {
    mixal::Computer machine;
    machine.rX.set(-1073741814);
    const auto result = mixal::Parser::parseLine("ENNX 0", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(true, machine.rX.negative);
    EXPECT_EQ(0, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_ennx_with_index) {
    mixal::Computer machine;
    machine.rX.set(1073741814);
    machine.rI5.set(5);
    const auto result = mixal::Parser::parseLine("ENNX -5,5", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(false, machine.rX.negative);
    EXPECT_EQ(0, machine.rX.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_inc1) {
    mixal::Computer machine;
    machine.rI1.set(-12);
    const auto result = mixal::Parser::parseLine("INC1 47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(35, machine.rI1.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_inc2_with_index) {
    mixal::Computer machine;
    machine.rI2.set(47);
    const auto result = mixal::Parser::parseLine("INC2 0,2", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(94, machine.rI2.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_inc3_overflow) {
    mixal::Computer machine;
    machine.rI3.set(4000);
    const auto result = mixal::Parser::parseLine("INC3 100", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(4, machine.rI3.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_inc3_double) {
    mixal::Computer machine;
    machine.rI3.set(-256);
    const auto result = mixal::Parser::parseLine("INC3 0,3", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-512, machine.rI3.value());
}

TEST(TestMachineAddressTransfer, test_dec4) {
    mixal::Computer machine;
    machine.rI4.set(-12);
    const auto result = mixal::Parser::parseLine("DEC4 -47", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(35, machine.rI4.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_dec5_with_index) {
    mixal::Computer machine;
    machine.rI5.set(-12);
    machine.rI3.set(-11);
    const auto result = mixal::Parser::parseLine("DEC5 0,3", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-1, machine.rI5.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_dec6_overflow) {
    mixal::Computer machine;
    machine.rI6.set(-4000);
    const auto result = mixal::Parser::parseLine("DEC6 100", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(-4, machine.rI6.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_ent1) {
    mixal::Computer machine;
    machine.rI1.set(-4000);
    const auto result = mixal::Parser::parseLine("ENT1 0", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(0, machine.rI1.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_ent2_with_index) {
    mixal::Computer machine;
    machine.rI2.set(4000);
    machine.rI4.set(5);
    const auto result = mixal::Parser::parseLine("ENT2 -5,4", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(true, machine.rI2.negative);
    EXPECT_EQ(0, machine.rI2.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_enn3) {
    mixal::Computer machine;
    machine.rI3.set(-4000);
    const auto result = mixal::Parser::parseLine("ENN3 0", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(true, machine.rI3.negative);
    EXPECT_EQ(0, machine.rI3.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_ent5_with_index_and_overflow) {
    mixal::Computer machine;
    machine.rI5.set(4000);
    machine.rI4.set(4000);
    const auto result = mixal::Parser::parseLine("ENT5 100,4", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(false, machine.rI5.negative);
    EXPECT_EQ(4, machine.rI5.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_enn4_with_index) {
    mixal::Computer machine;
    machine.rI4.set(4000);
    machine.rI5.set(5);
    const auto result = mixal::Parser::parseLine("ENN4 -5,5", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(false, machine.rI4.negative);
    EXPECT_EQ(0, machine.rI4.value());
    EXPECT_FALSE(machine.overflow);
}

TEST(TestMachineAddressTransfer, test_enn6_with_index_and_overflow) {
    mixal::Computer machine;
    machine.rI6.set(4000);
    machine.rI5.set(4000);
    const auto result = mixal::Parser::parseLine("ENN6 100,5", "", false);
    machine.executeSingle(result.word);
    EXPECT_EQ(true, machine.rI6.negative);
    EXPECT_EQ(-4, machine.rI6.value());
    EXPECT_FALSE(machine.overflow);
}
