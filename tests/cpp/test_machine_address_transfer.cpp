#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineAddressTransfer : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineAddressTransfer() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineAddressTransfer, test_inca) {
    machine.rA.set(-12345);
    auto result = mixal::Parser::parseLine("INCA 47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12298, machine.rA.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_inca_with_index) {
    machine.rA.set(-12345);
    machine.rI2.set(47);
    auto result = mixal::Parser::parseLine("INCA 0,2", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12298, machine.rA.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_inca_overflow) {
    machine.rA.set(1073741814);
    auto result = mixal::Parser::parseLine("INCA 47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(37, machine.rA.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_deca) {
    machine.rA.set(-12345);
    auto result = mixal::Parser::parseLine("DECA -47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12298, machine.rA.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_deca_with_index) {
    machine.rA.set(-12345);
    machine.rI3.set(-47);
    auto result = mixal::Parser::parseLine("DECA 0,3", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12298, machine.rA.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_deca_overflow) {
    machine.rA.set(-1073741814);
    auto result = mixal::Parser::parseLine("DECA 47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-37, machine.rA.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_enta) {
    machine.rA.set(-1073741814);
    auto result = mixal::Parser::parseLine("ENTA 0", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_enta_with_index) {
    machine.rA.set(1073741814);
    machine.rI4.set(5);
    auto result = mixal::Parser::parseLine("ENTA -5,4", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(true, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_enna) {
    machine.rA.set(-1073741814);
    auto result = mixal::Parser::parseLine("ENNA 0", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(true, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_enna_with_index) {
    machine.rA.set(1073741814);
    machine.rI5.set(5);
    auto result = mixal::Parser::parseLine("ENNA -5,5", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(false, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_incx) {
    machine.rX.set(-12345);
    auto result = mixal::Parser::parseLine("INCX 47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12298, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_incx_with_index) {
    machine.rX.set(-12345);
    machine.rI2.set(47);
    auto result = mixal::Parser::parseLine("INCX 0,2", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12298, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_incx_overflow) {
    machine.rX.set(1073741814);
    auto result = mixal::Parser::parseLine("INCX 47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(37, machine.rX.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_decx) {
    machine.rX.set(-12345);
    auto result = mixal::Parser::parseLine("DECX -47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12298, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_decx_with_index) {
    machine.rX.set(-12345);
    machine.rI3.set(-47);
    auto result = mixal::Parser::parseLine("DECX 0,3", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-12298, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_decx_overflow) {
    machine.rX.set(-1073741814);
    auto result = mixal::Parser::parseLine("DECX 47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-37, machine.rX.value());
    __ASSERT_TRUE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_entx) {
    machine.rX.set(-1073741814);
    auto result = mixal::Parser::parseLine("ENTX 0", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_entx_with_index) {
    machine.rX.set(1073741814);
    machine.rI4.set(5);
    auto result = mixal::Parser::parseLine("ENTX -5,4", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(true, machine.rX.negative);
    __ASSERT_EQ(0, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_ennx) {
    machine.rX.set(-1073741814);
    auto result = mixal::Parser::parseLine("ENNX 0", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(true, machine.rX.negative);
    __ASSERT_EQ(0, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_ennx_with_index) {
    machine.rX.set(1073741814);
    machine.rI5.set(5);
    auto result = mixal::Parser::parseLine("ENNX -5,5", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(false, machine.rX.negative);
    __ASSERT_EQ(0, machine.rX.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_inc1) {
    machine.rI1.set(-12);
    auto result = mixal::Parser::parseLine("INC1 47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(35, machine.rI1.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_inc2_with_index) {
    machine.rI2.set(47);
    auto result = mixal::Parser::parseLine("INC2 0,2", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(94, machine.rI2.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_inc3_overflow) {
    machine.rI3.set(4000);
    auto result = mixal::Parser::parseLine("INC3 100", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(4, machine.rI3.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_inc3_double) {
    machine.rI3.set(-256);
    auto result = mixal::Parser::parseLine("INC3 0,3", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-512, machine.rI3.value());
}

__TEST_U(TestMachineAddressTransfer, test_dec4) {
    machine.rI4.set(-12);
    auto result = mixal::Parser::parseLine("DEC4 -47", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(35, machine.rI4.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_dec5_with_index) {
    machine.rI5.set(-12);
    machine.rI3.set(-11);
    auto result = mixal::Parser::parseLine("DEC5 0,3", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-1, machine.rI5.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_dec6_overflow) {
    machine.rI6.set(-4000);
    auto result = mixal::Parser::parseLine("DEC6 100", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(-4, machine.rI6.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_ent1) {
    machine.rI1.set(-4000);
    auto result = mixal::Parser::parseLine("ENT1 0", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rI1.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_ent2_with_index) {
    machine.rI2.set(4000);
    machine.rI4.set(5);
    auto result = mixal::Parser::parseLine("ENT2 -5,4", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(true, machine.rI2.negative);
    __ASSERT_EQ(0, machine.rI2.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_enn3) {
    machine.rI3.set(-4000);
    auto result = mixal::Parser::parseLine("ENN3 0", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(true, machine.rI3.negative);
    __ASSERT_EQ(0, machine.rI3.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_ent5_with_index_and_overflow) {
    machine.rI5.set(4000);
    machine.rI4.set(4000);
    auto result = mixal::Parser::parseLine("ENT5 100,4", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(false, machine.rI5.negative);
    __ASSERT_EQ(4, machine.rI5.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_enn4_with_index) {
    machine.rI4.set(4000);
    machine.rI5.set(5);
    auto result = mixal::Parser::parseLine("ENN4 -5,5", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(false, machine.rI4.negative);
    __ASSERT_EQ(0, machine.rI4.value());
    __ASSERT_FALSE(machine.overflow);
}

__TEST_U(TestMachineAddressTransfer, test_enn6_with_index_and_overflow) {
    machine.rI6.set(4000);
    machine.rI5.set(4000);
    auto result = mixal::Parser::parseLine("ENN6 100,5", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(true, machine.rI6.negative);
    __ASSERT_EQ(-4, machine.rI6.value());
    __ASSERT_FALSE(machine.overflow);
}

}  // namespace test
