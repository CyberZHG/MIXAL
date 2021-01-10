#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"
#include "parser.h"

TEST(TestMachineEvaluate, test_unsolved_address) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine("ADD ADDRESS", "", false);
    EXPECT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

TEST(TestMachineEvaluate, test_unsolved_index) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine("ADD 1000,INDEX", "", false);
    EXPECT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

TEST(TestMachineEvaluate, test_unsolved_field) {
    mixal::Computer machine;
    auto result = mixal::Parser::parseLine("ADD 1000(FIELD)", "", false);
    EXPECT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}
