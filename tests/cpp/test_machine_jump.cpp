#include <iostream>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineJump : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineJump() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineJump, test_jump) {
    machine.loadCodes({
        "     ORIG 3000",
        "     ENTA -40",
        "     JMP  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(-40, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jump_save_j) {
    machine.loadCodes({
        "     ORIG 3000",
        "     ENTA -40",
        "     JSJ  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeSingle();
    machine.executeSingle();
    __ASSERT_EQ(-40, machine.rA.value());
    __ASSERT_EQ(0, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jov_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1073741814=",
        "     ADD  =1073741814=",
        "     JOV  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(1073741804, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jov_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1073741814=",
        "     ADD  =1=",
        "     JOV  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jnov_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1073741814=",
        "     ADD  =1073741814=",
        "     JNOV EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jnov_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1073741814=",
        "     ADD  =1=",
        "     JNOV EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(1073741815, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

}  // namespace test
