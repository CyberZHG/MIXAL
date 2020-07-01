#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineStore : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineStore() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineStore, test_sta_all) {
    machine.rA.set(false, 6, 7, 8, 9, 0);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STA 2000", "", false);
    machine.executeSingle(&result);
    __ASSERT_EQ(0, machine.memory[2000].sign);
    __ASSERT_EQ(6, machine.memory[2000][1]);
    __ASSERT_EQ(7, machine.memory[2000][2]);
    __ASSERT_EQ(8, machine.memory[2000][3]);
    __ASSERT_EQ(9, machine.memory[2000][4]);
    __ASSERT_EQ(0, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_stx_1_to_5) {
    machine.rX.set(false, 6, 7, 8, 9, 0);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STX 2000(1:5)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.memory[2000].sign);
    __ASSERT_EQ(6, machine.memory[2000][1]);
    __ASSERT_EQ(7, machine.memory[2000][2]);
    __ASSERT_EQ(8, machine.memory[2000][3]);
    __ASSERT_EQ(9, machine.memory[2000][4]);
    __ASSERT_EQ(0, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_sta_5_to_5) {
    machine.rA.set(false, 6, 7, 8, 9, 0);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STA 2000(5:5)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.memory[2000].sign);
    __ASSERT_EQ(1, machine.memory[2000][1]);
    __ASSERT_EQ(2, machine.memory[2000][2]);
    __ASSERT_EQ(3, machine.memory[2000][3]);
    __ASSERT_EQ(4, machine.memory[2000][4]);
    __ASSERT_EQ(0, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_stx_2_to_2) {
    machine.rX.set(false, 6, 7, 8, 9, 0);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STX 2000(2:2)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.memory[2000].sign);
    __ASSERT_EQ(1, machine.memory[2000][1]);
    __ASSERT_EQ(0, machine.memory[2000][2]);
    __ASSERT_EQ(3, machine.memory[2000][3]);
    __ASSERT_EQ(4, machine.memory[2000][4]);
    __ASSERT_EQ(5, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_sta_2_to_3) {
    machine.rA.set(false, 6, 7, 8, 9, 0);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STA 2000(2:3)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.memory[2000].sign);
    __ASSERT_EQ(1, machine.memory[2000][1]);
    __ASSERT_EQ(9, machine.memory[2000][2]);
    __ASSERT_EQ(0, machine.memory[2000][3]);
    __ASSERT_EQ(4, machine.memory[2000][4]);
    __ASSERT_EQ(5, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_stx_0_to_1) {
    machine.rX.set(false, 6, 7, 8, 9, 0);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STX 2000(0:1)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.memory[2000].sign);
    __ASSERT_EQ(0, machine.memory[2000][1]);
    __ASSERT_EQ(2, machine.memory[2000][2]);
    __ASSERT_EQ(3, machine.memory[2000][3]);
    __ASSERT_EQ(4, machine.memory[2000][4]);
    __ASSERT_EQ(5, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_st1_0_to_1) {
    machine.rI1.set(false, 6, 7);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("ST1 2000(0:1)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.memory[2000].sign);
    __ASSERT_EQ(7, machine.memory[2000][1]);
    __ASSERT_EQ(2, machine.memory[2000][2]);
    __ASSERT_EQ(3, machine.memory[2000][3]);
    __ASSERT_EQ(4, machine.memory[2000][4]);
    __ASSERT_EQ(5, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_st2_1_to_2) {
    machine.rI2.set(false, 6, 7);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("ST2 2000(1:2)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.memory[2000].sign);
    __ASSERT_EQ(6, machine.memory[2000][1]);
    __ASSERT_EQ(7, machine.memory[2000][2]);
    __ASSERT_EQ(3, machine.memory[2000][3]);
    __ASSERT_EQ(4, machine.memory[2000][4]);
    __ASSERT_EQ(5, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_st3_2_to_3) {
    machine.rI3.set(false, 6, 7);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("ST3 2000(2:3)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.memory[2000].sign);
    __ASSERT_EQ(1, machine.memory[2000][1]);
    __ASSERT_EQ(6, machine.memory[2000][2]);
    __ASSERT_EQ(7, machine.memory[2000][3]);
    __ASSERT_EQ(4, machine.memory[2000][4]);
    __ASSERT_EQ(5, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_st4_3_to_4) {
    machine.rI4.set(false, 6, 7);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("ST4 2000(3:4)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.memory[2000].sign);
    __ASSERT_EQ(1, machine.memory[2000][1]);
    __ASSERT_EQ(2, machine.memory[2000][2]);
    __ASSERT_EQ(6, machine.memory[2000][3]);
    __ASSERT_EQ(7, machine.memory[2000][4]);
    __ASSERT_EQ(5, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_st5_4_to_5) {
    machine.rI5.set(false, 6, 7);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("ST5 2000(4:5)", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(1, machine.memory[2000].sign);
    __ASSERT_EQ(1, machine.memory[2000][1]);
    __ASSERT_EQ(2, machine.memory[2000][2]);
    __ASSERT_EQ(3, machine.memory[2000][3]);
    __ASSERT_EQ(6, machine.memory[2000][4]);
    __ASSERT_EQ(7, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_st6_all) {
    machine.rI6.set(false, 6, 7);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("ST6 2000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.memory[2000].sign);
    __ASSERT_EQ(0, machine.memory[2000][1]);
    __ASSERT_EQ(0, machine.memory[2000][2]);
    __ASSERT_EQ(0, machine.memory[2000][3]);
    __ASSERT_EQ(6, machine.memory[2000][4]);
    __ASSERT_EQ(7, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_stj_all) {
    machine.rJ.set(true, 6, 7);
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STJ 2000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.memory[2000].sign);
    __ASSERT_EQ(6, machine.memory[2000][1]);
    __ASSERT_EQ(7, machine.memory[2000][2]);
    __ASSERT_EQ(3, machine.memory[2000][3]);
    __ASSERT_EQ(4, machine.memory[2000][4]);
    __ASSERT_EQ(5, machine.memory[2000][5]);
}

__TEST_U(TestMachineStore, test_stz_all) {
    machine.memory[2000].set(true, 1, 2, 3, 4, 5);
    auto result = mixal::Parser::parseLine("STZ 2000", "", false);
    machine.executeSingle(result.word);
    __ASSERT_EQ(0, machine.memory[2000].sign);
    __ASSERT_EQ(0, machine.memory[2000][1]);
    __ASSERT_EQ(0, machine.memory[2000][2]);
    __ASSERT_EQ(0, machine.memory[2000][3]);
    __ASSERT_EQ(0, machine.memory[2000][4]);
    __ASSERT_EQ(0, machine.memory[2000][5]);
}

}  // namespace test
