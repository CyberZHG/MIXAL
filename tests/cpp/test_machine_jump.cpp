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

__TEST_U(TestMachineJump, test_jl_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =-1=",
        "     CMPA =1=",
        "     JL   EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(-1, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jl_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1=",
        "     CMPA =1=",
        "     JL   EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_je_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1=",
        "     CMPA =1=",
        "     JE   EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(1, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_je_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1=",
        "     CMPA =-1=",
        "     JE   EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jg_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =3=",
        "     CMPA =1=",
        "     JG   EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(3, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jg_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =3=",
        "     CMPA =4=",
        "     JG   EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jge_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1=",
        "     CMPA =1=",
        "     JGE  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(1, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jge_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1=",
        "     CMPA =2=",
        "     JGE  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jne_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =1=",
        "     CMPA =-1=",
        "     JNE  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(1, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jne_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =-1=",
        "     CMPA =-1=",
        "     JNE  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jle_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =3=",
        "     CMPA =3=",
        "     JLE  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(3, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jle_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =5=",
        "     CMPA =4=",
        "     JLE  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3005, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jan_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =-5=",
        "     JAN  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(-5, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jan_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =5=",
        "     JAN  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jaz_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =-0=",
        "     JAZ  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(0, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jaz_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =5=",
        "     JAZ  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jap_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =7=",
        "     JAP  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(7, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jap_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =-5=",
        "     JAP  EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jann_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =-5=",
        "     JANN EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jann_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =5=",
        "     JANN EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(5, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_janz_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =-0=",
        "     JANZ EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_janz_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =5=",
        "     JANZ EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(5, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_janp_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =7=",
        "     JANP EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_janp_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDA  =-5=",
        "     JANP EXIT",
        "     ENTA 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(-5, machine.rA.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxn_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =-5=",
        "     JXN  EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(-5, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxn_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =5=",
        "     JXN  EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxz_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =-0=",
        "     JXZ  EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(0, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxz_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =5=",
        "     JXZ  EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxp_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =7=",
        "     JXP  EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(7, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxp_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =-5=",
        "     JXP  EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxnn_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =-5=",
        "     JXNN EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxnn_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =5=",
        "     JXNN EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(5, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxnz_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =-0=",
        "     JXNZ EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxnz_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =5=",
        "     JXNZ EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(5, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxnp_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =7=",
        "     JXNP EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_jxnp_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LDX  =-5=",
        "     JXNP EXIT",
        "     ENTX 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(-5, machine.rX.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j1n_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD1  =-5=",
        "     J1N  EXIT",
        "     ENT1 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(-5, machine.rI1.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j2n_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD2  =5=",
        "     J2N  EXIT",
        "     ENT2 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rI2.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j3z_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD3  =-0=",
        "     J3Z  EXIT",
        "     ENT3 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(0, machine.rI3.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j4z_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD4  =5=",
        "     J4Z  EXIT",
        "     ENT4 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rI4.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j5p_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD5  =7=",
        "     J5P  EXIT",
        "     ENT5 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(7, machine.rI5.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j6p_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD6  =-5=",
        "     J6P  EXIT",
        "     ENT6 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rI6.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j1nn_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD1  =-5=",
        "     J1NN EXIT",
        "     ENT1 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rI1.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j2nn_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD2  =5=",
        "     J2NN EXIT",
        "     ENT2 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(5, machine.rI2.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j3nz_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD3  =-0=",
        "     J3NZ EXIT",
        "     ENT3 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rI3.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j4nz_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD4  =5=",
        "     J4NZ EXIT",
        "     ENT4 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(5, machine.rI4.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j5np_off) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD5  =7=",
        "     J5NP EXIT",
        "     ENT5 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(35, machine.rI5.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

__TEST_U(TestMachineJump, test_j6np_on) {
    machine.loadCodes({
        "     ORIG 3000",
        "     LD6  =-5=",
        "     J6NP EXIT",
        "     ENT6 35",
        "EXIT JMP  EXIT",
    });
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(-5, machine.rI6.value());
    __ASSERT_EQ(3004, machine.rJ.value());
}

}  // namespace test
