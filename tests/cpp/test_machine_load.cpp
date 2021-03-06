#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineLoad : public UnitTest {
 public:
    mixal::Computer machine;

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
    auto result = mixal::Parser::parseLine("LDA 2000", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.negative);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_1_to_5) {
    auto result = mixal::Parser::parseLine("LDA 2000(1:5)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_3_to_5) {
    auto result = mixal::Parser::parseLine("LDA 2000(3:5)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_0_to_3) {
    auto result = mixal::Parser::parseLine("LDA 2000(0:3)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(80, machine.rA.bytes34());
    __ASSERT_EQ(3, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_4_to_4) {
    auto result = mixal::Parser::parseLine("LDA 2000(4:4)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
    __ASSERT_EQ(5, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_0_to_0) {
    auto result = mixal::Parser::parseLine("LDA 2000(0:0)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
    __ASSERT_EQ(0, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_lda_1_to_1) {
    auto result = mixal::Parser::parseLine("LDA 2000(1:1)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(0, machine.rA[1]);
    __ASSERT_EQ(0, machine.rA[2]);
    __ASSERT_EQ(0, machine.rA[3]);
    __ASSERT_EQ(0, machine.rA[4]);
}

__TEST_U(TestMachineLoad, test_lda_all_with_offset) {
    auto result = mixal::Parser::parseLine("LDA 2003,1", "", false);
    machine.rI1.negative = 1;
    machine.rI1.set(1, 0);
    machine.rI1.set(2, 3);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rA.negative);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_ld1) {
    auto result = mixal::Parser::parseLine("LD1 2000(0:2)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rI1.negative);
    __ASSERT_EQ(80, machine.rI1.bytes12());
    __ASSERT_EQ(-80, machine.rI1.value());
}

__TEST_U(TestMachineLoad, test_ld2) {
    auto result = mixal::Parser::parseLine("LD2 2000(1:2)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rI2.negative);
    __ASSERT_EQ(80, machine.rI2.bytes12());
    __ASSERT_EQ(80, machine.rI2.value());
}

__TEST_U(TestMachineLoad, test_ld3) {
    auto result = mixal::Parser::parseLine("LD3 2000(3:4)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rI3.negative);
    __ASSERT_EQ(3, machine.rI3[1]);
    __ASSERT_EQ(5, machine.rI3[2]);
}

__TEST_U(TestMachineLoad, test_ld4) {
    auto result = mixal::Parser::parseLine("LD4 2000(4:5)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rI4.negative);
    __ASSERT_EQ(5, machine.rI4[1]);
    __ASSERT_EQ(4, machine.rI4[2]);
}

__TEST_U(TestMachineLoad, test_ld5) {
    auto result = mixal::Parser::parseLine("LD5 2000(4:4)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rI5.negative);
    __ASSERT_EQ(0, machine.rI5[1]);
    __ASSERT_EQ(5, machine.rI5[2]);
}

__TEST_U(TestMachineLoad, test_ld6) {
    auto result = mixal::Parser::parseLine("LD6 2000(0:0)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rI6.negative);
    __ASSERT_EQ(0, machine.rI6[1]);
    __ASSERT_EQ(0, machine.rI6[2]);
}

__TEST_U(TestMachineLoad, test_ldx_all) {
    auto result = mixal::Parser::parseLine("LDX 2000", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.rX.negative);
    __ASSERT_EQ(80, machine.rX.bytes12());
    __ASSERT_EQ(3, machine.rX[3]);
    __ASSERT_EQ(5, machine.rX[4]);
    __ASSERT_EQ(4, machine.rX[5]);
}

__TEST_U(TestMachineLoad, test_ldan) {
    auto result = mixal::Parser::parseLine("LDAN 2000", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rA.negative);
    __ASSERT_EQ(80, machine.rA.bytes12());
    __ASSERT_EQ(3, machine.rA[3]);
    __ASSERT_EQ(5, machine.rA[4]);
    __ASSERT_EQ(4, machine.rA[5]);
}

__TEST_U(TestMachineLoad, test_ld6n) {
    auto result = mixal::Parser::parseLine("LD6N 2000(0:0)", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rI6.negative);
    __ASSERT_EQ(0, machine.rI6[1]);
    __ASSERT_EQ(0, machine.rI6[2]);
    machine.executeSingle(mixal::Parser::parseLine("LD5N 2000(0:0)", "", false).word);
    machine.executeSingle(mixal::Parser::parseLine("LD4N 2000(0:0)", "", false).word);
    machine.executeSingle(mixal::Parser::parseLine("LD3N 2000(0:0)", "", false).word);
    machine.executeSingle(mixal::Parser::parseLine("LD2N 2000(0:0)", "", false).word);
    machine.executeSingle(mixal::Parser::parseLine("LD1N 2000(0:0)", "", false).word);
}

__TEST_U(TestMachineLoad, test_ldxn) {
    auto result = mixal::Parser::parseLine("LDXN 2000", "", false);
    initMemory2000();
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.rX.negative);
    __ASSERT_EQ(80, machine.rX.bytes12());
    __ASSERT_EQ(3, machine.rX[3]);
    __ASSERT_EQ(5, machine.rX[4]);
    __ASSERT_EQ(4, machine.rX[5]);
}

}  // namespace test
