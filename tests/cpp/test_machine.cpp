#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachine : public UnitTest {
 public:
    mixal::Computer machine;

    friend mixal::Computer;

    TestMachine() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachine, test_get_invalid_index_register) {
    __ASSERT_THROW(machine.rI(0), mixal::RuntimeError);
}

__TEST_U(TestMachine, test_get_memory) {
    __ASSERT_EQ(0, machine.memoryAt(0).value());
}

__TEST_U(TestMachine, test_get_memory_const) {
    const auto& mac = machine;
    __ASSERT_EQ(0, mac.memoryAt(0).value());
}

__TEST_U(TestMachine, test_line_output_of_range_self_loop) {
    __ASSERT_THROW(machine.executeUntilSelfLoop(), mixal::RuntimeError);
}

__TEST_U(TestMachine, test_line_output_of_range_halt) {
    __ASSERT_THROW(machine.executeUntilHalt(), mixal::RuntimeError);
}

__TEST_U(TestMachine, test_invalid_field) {
    auto result = mixal::Parser::parseLine("LDA 2000(3:2)", "", false);
    __ASSERT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("LDX 2000(0:6)", "", false);
    __ASSERT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("STA 2000(3:2)", "", false);
    __ASSERT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("STX 2000(0:6)", "", false);
    __ASSERT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("LD1 2000(3:2)", "", false);
    __ASSERT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("LD2 2000(4:6)", "", false);
    __ASSERT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
}

}  // namespace test
