#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachine, test_get_invalid_index_register) {
    mixal::Computer machine;
    EXPECT_THROW(machine.rI(0), mixal::RuntimeError);
}

TEST(TestMachine, test_get_memory) {
    mixal::Computer machine;
    EXPECT_EQ(0, machine.memoryAt(0).value());
}

TEST(TestMachine, test_get_memory_const) {
    const mixal::Computer machine;
    const auto& mac = machine;
    EXPECT_EQ(0, mac.memoryAt(0).value());
}

TEST(TestMachine, test_line_output_of_range_self_loop) {
    mixal::Computer machine;
    EXPECT_THROW(machine.executeUntilSelfLoop(), mixal::RuntimeError);
}

TEST(TestMachine, test_line_output_of_range_halt) {
    mixal::Computer machine;
    EXPECT_THROW(machine.executeUntilHalt(), mixal::RuntimeError);
}

TEST(TestMachine, test_invalid_field) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine("LDA 2000(3:2)", "", false);
    EXPECT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("LDX 2000(0:6)", "", false);
    EXPECT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("STA 2000(3:2)", "", false);
    EXPECT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("STX 2000(0:6)", "", false);
    EXPECT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("LD1 2000(3:2)", "", false);
    EXPECT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
    result = mixal::Parser::parseLine("LD2 2000(4:6)", "", false);
    EXPECT_THROW(machine.executeSingle(result.word), mixal::RuntimeError);
}
