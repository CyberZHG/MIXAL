#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineEvaluate : public UnitTest {
 public:
    mixal::Computer machine;

    TestMachineEvaluate() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineEvaluate, test_unsolved_address) {
    auto result = mixal::Parser::parseLine("ADD ADDRESS", "", false);
    __ASSERT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

__TEST_U(TestMachineEvaluate, test_unsolved_index) {
    auto result = mixal::Parser::parseLine("ADD 1000,INDEX", "", false);
    __ASSERT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

__TEST_U(TestMachineEvaluate, test_unsolved_field) {
    auto result = mixal::Parser::parseLine("ADD 1000(FIELD)", "", false);
    __ASSERT_THROW(machine.executeSingle(&result), mixal::RuntimeError);
}

}  // namespace test
