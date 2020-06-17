#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineLoadCodes : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineLoadCodes() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineLoadCodes, test_load_sample) {
    std::vector<std::string> codes = {
        "X       EQU  1000",
        "        ORIG 3000",
        "MAXIMUM STJ  EXIT",
        "INIT    ENT3 0,1",
        "        JMP  CHANGEM",
        "LOOP    CMPA X,3",
        "        JGE  *+3",
        "CHANGEM ENT2 0,3",
        "        LDA  X,3",
        "        DEC3 1",
        "        J3P  LOOP",
        "EXIT    JMP  *",
    };
    machine.loadCodes(codes);
    __ASSERT_EQ(mixal::ComputerWord(false, 3009, 0, 2, 32), machine.memory[3000]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 1, 2, 51), machine.memory[3001]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3005, 0, 0, 39), machine.memory[3002]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1000, 3, 5, 56), machine.memory[3003]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3007, 0, 7, 39), machine.memory[3004]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 3, 2, 50), machine.memory[3005]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1000, 3, 5,  8), machine.memory[3006]);
    __ASSERT_EQ(mixal::ComputerWord(false,    1, 0, 1, 51), machine.memory[3007]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3003, 0, 2, 43), machine.memory[3008]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3009, 0, 0, 39), machine.memory[3009]);
}

__TEST_U(TestMachineLoadCodes, test_load_constant) {
    std::vector<std::string> codes = {
        " CON  100000",
        " ORIG 3000",
        " CON  1000000",
    };
    machine.loadCodes(codes);
    __ASSERT_EQ(100000, machine.memory[0].value());
    __ASSERT_EQ(1000000, machine.memory[3000].value());
}

__TEST_U(TestMachineLoadCodes, test_load_literal_constant) {
    std::vector<std::string> codes = {
        " ORIG 3000",
        " LDA  =10-23=,0+0(2+3)",
    };
    machine.loadCodes(codes);
    __ASSERT_EQ(mixal::ComputerWord(false, 3001, 0, 5, 8), machine.memory[3000]);
    __ASSERT_EQ(-13, machine.memory[3001].value());
}

__TEST_U(TestMachineLoadCodes, test_load_sample_with_local_symbols) {
    std::vector<std::string> codes = {
        "X       EQU  1000",
        "        ORIG 3000",
        "MAXIMUM STJ  2F",
        "INIT    ENT3 0,1",
        "        JMP  6F",
        "4H      CMPA X,3",
        "        JGE  *+3",
        "6H      ENT2 0,3",
        "        LDA  X,3",
        "        DEC3 1",
        "        J3P  4B",
        "2H      JMP  *",
    };
    machine.loadCodes(codes);
    __ASSERT_EQ(mixal::ComputerWord(false, 3009, 0, 2, 32), machine.memory[3000]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 1, 2, 51), machine.memory[3001]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3005, 0, 0, 39), machine.memory[3002]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1000, 3, 5, 56), machine.memory[3003]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3007, 0, 7, 39), machine.memory[3004]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 3, 2, 50), machine.memory[3005]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1000, 3, 5,  8), machine.memory[3006]);
    __ASSERT_EQ(mixal::ComputerWord(false,    1, 0, 1, 51), machine.memory[3007]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3003, 0, 2, 43), machine.memory[3008]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3009, 0, 0, 39), machine.memory[3009]);
}

}  // namespace test
