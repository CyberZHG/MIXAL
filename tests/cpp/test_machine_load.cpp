#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineLoad : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineLoad() : machine() {}

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

__TEST_U(TestMachineLoad, test_lda_all) {
    auto result = mixal::Parser::parseLine("LDA 2000", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_1_to_5) {
    auto result = mixal::Parser::parseLine("LDA 2000(1:5)", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.sign);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_3_to_5) {
    auto result = mixal::Parser::parseLine("LDA 2000(3:5)", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.sign);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_0_to_3) {
    auto result = mixal::Parser::parseLine("LDA 2000(0:3)", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(80, machine.rA.bytes34());
    __ASSERT_EQ(3, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_4_to_4) {
    auto result = mixal::Parser::parseLine("LDA 2000(4:4)", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.sign);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
    __ASSERT_EQ(5, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_0_to_0) {
    auto result = mixal::Parser::parseLine("LDA 2000(0:0)", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
    __ASSERT_EQ(0, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_1_to_1) {
    auto result = mixal::Parser::parseLine("LDA 2000(1:1)", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.sign);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
}

__TEST_U(TestMachineLoad, test_lda_all_with_offset) {
    auto result = mixal::Parser::parseLine("LDA 2003,1", false);
    machine.rI1().word = -3;
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.sign);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

}  // namespace test
