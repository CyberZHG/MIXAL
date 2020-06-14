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

__TEST_U(TestMachineLoadCodes, test_unsolved_address) {
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
    __ASSERT_TRUE(mixal::ComputerWord(false, 3009 / 64, 3009 % 64, 0, 2, 32) == machine.memory[3000]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 0, 0, 1, 2, 51) == machine.memory[3001]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 3005 / 64, 3005 % 64, 0, 0, 39) == machine.memory[3002]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 1000 / 64, 1000 % 64, 3, 5, 56) == machine.memory[3003]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 3007 / 64, 3007 % 64, 0, 7, 39) == machine.memory[3004]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 0, 0, 3, 2, 50) == machine.memory[3005]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 1000 / 64, 1000 % 64, 3, 5, 8) == machine.memory[3006]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 0, 1, 0, 1, 51) == machine.memory[3007]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 3003 / 64, 3003 % 64, 0, 2, 43) == machine.memory[3008]);
    __ASSERT_TRUE(mixal::ComputerWord(false, 3009 / 64, 3009 % 64, 0, 0, 39) == machine.memory[3009]);
}

}  // namespace test
