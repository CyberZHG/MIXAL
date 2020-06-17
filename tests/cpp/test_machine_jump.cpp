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

}  // namespace test
