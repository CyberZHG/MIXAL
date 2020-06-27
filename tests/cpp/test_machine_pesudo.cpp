#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachinePesudo : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachinePesudo() : machine() {}

    void setUpEach() final {
        machine.reset();
    }

    void initMemory2000() {
        machine.memory[2000].set(
            true,
            static_cast<int16_t>(80),
            static_cast<int8_t>(3),
            static_cast<int8_t>(5),
            static_cast<int8_t>(4));
    }
};

__TEST_U(TestMachinePesudo, test_equ) {
    initMemory2000();
    auto result = mixal::Parser::parseLine("X EQU 1000", "", true);
    __ASSERT_EQ(mixal::ParsedType::PSEUDO, result.parsedType);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("  LDA X+X", "", true);
    machine.executeSingle(&result);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachinePesudo, test_equ_with_symbol) {
    initMemory2000();
    auto result = mixal::Parser::parseLine("X EQU 1000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("Y EQU X*2", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("  LDA Y", "", true);
    machine.executeSingle(&result);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachinePesudo, test_equ_with_unknown_symbol) {
    initMemory2000();
    auto result = mixal::Parser::parseLine("X EQU X-X", "", true);
    __ASSERT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

__TEST_U(TestMachinePesudo, test_orig) {
    initMemory2000();
    auto result = mixal::Parser::parseLine(" ORIG 3000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA *-1000", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachinePesudo, test_orig_with_location) {
    initMemory2000();
    auto result = mixal::Parser::parseLine("LOC ORIG 3000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA *-1000", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachinePesudo, test_orig_with_equ) {
    initMemory2000();
    auto result = mixal::Parser::parseLine("X EQU 1500", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" ORIG X+X", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA *-1000", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachinePesudo, test_orig_with_undefined_symbol) {
    initMemory2000();
    auto result = mixal::Parser::parseLine(" ORIG X+X", "", true);
    __ASSERT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

__TEST_U(TestMachinePesudo, test_con_load) {
    auto result = mixal::Parser::parseLine(" ORIG 2000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine("LOC CON 20*30*50", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA LOC", "", true);
    machine.executeSingle(&result);
    __ASSERT_EQ(30000, machine.rA.value());
}

__TEST_U(TestMachinePesudo, test_con_load_relative) {
    auto result = mixal::Parser::parseLine(" ORIG 2000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" CON 20*30*50", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" LDA *-1", machine.getSingleLineSymbol(), true);
    machine.executeSingle(&result);
    __ASSERT_EQ(30000, machine.rA.value());
}

__TEST_U(TestMachinePesudo, test_con_with_unknown_symbol) {
    auto result = mixal::Parser::parseLine(" ORIG 2000", "", true);
    machine.executeSingle(&result);
    result = mixal::Parser::parseLine(" CON A", "", true);
    __ASSERT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

__TEST_U(TestMachinePesudo, test_con_with_literal_constant) {
    auto result = mixal::Parser::parseLine(" LDA =123=", "", true);
    __ASSERT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

__TEST_U(TestMachinePesudo, test_alf) {
    machine.loadCodes({
        "     ORIG 3000",
        "     OUT  VAL(17)",
        "LOOP JBUS LOOP(17)",
        "     HLT",
        "VAL  ALF  PRIME",
    });
    machine.executeUntilHalt();
    __ASSERT_EQ("PRIME", machine.getDevice(17)->wordAt(0).getCharacters());
}

}  // namespace test
