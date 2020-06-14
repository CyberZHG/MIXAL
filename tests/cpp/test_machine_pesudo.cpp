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

}  // namespace test
