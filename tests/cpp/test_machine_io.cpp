#include <iostream>
#include "test.h"
#include "machine.h"

namespace test {

class TestMachineIO : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineIO() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineIO, test_get_devices) {
    for (int i = 0; i < machine.NUM_IO_DEVICE; ++i) {
        machine.getDevice(i)->control(0);
    }
}

__TEST_U(TestMachineIO, test_io_tape) {
    machine.loadCodes({
        "     ORIG 3000",
        "     OUT  1000(3)",
        "     IOC  -1(3)",
        "     IN   2000(3)",
        "LOOP JRED EXIT(3)",
        "     JMP  LOOP",
        "EXIT JMP  EXIT",
    });
    machine.memory[1000].set(1000);
    machine.memory[1001].set(1001);
    machine.memory[1002].set(1002);
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(1000, machine.memory[2000].value());
    __ASSERT_EQ(1001, machine.memory[2001].value());
    __ASSERT_EQ(1002, machine.memory[2002].value());
}

__TEST_U(TestMachineIO, test_io_tape_rewind) {
    machine.loadCodes({
        "     ORIG 3000",
        "     OUT  1000(3)",
        "     IOC  0(3)",
        "     IN   2000(3)",
        "LOOP JBUS LOOP(3)",
        "EXIT HLT",
    });
    machine.memory[1000].set(1000);
    machine.memory[1001].set(1001);
    machine.memory[1002].set(1002);
    machine.executeUntilHalt();
    __ASSERT_EQ(1000, machine.memory[2000].value());
    __ASSERT_EQ(1001, machine.memory[2001].value());
    __ASSERT_EQ(1002, machine.memory[2002].value());
}

__TEST_U(TestMachineIO, test_io_disk) {
    machine.loadCodes({
        "     ORIG 3000",
        "     IOC  100(14)",
        "     OUT  1000(14)",
        "2H   JBUS 2B(14)",
        "     IN   2000(14)",
        "2H   JBUS 2B(14)",
        "EXIT HLT",
    });
    machine.memory[1000].set(1000);
    machine.memory[1001].set(1001);
    machine.memory[1002].set(1002);
    machine.executeUntilHalt();
    __ASSERT_EQ(1000, machine.memory[2000].value());
    __ASSERT_EQ(1001, machine.memory[2001].value());
    __ASSERT_EQ(1002, machine.memory[2002].value());
}

__TEST_U(TestMachineIO, test_io_chars) {
    machine.loadCodes({
        "     ORIG 3000",
        "     IN   100(16)",
        "LIN  JBUS LIN(16)",
        "     OUT  100(17)",
        "LOUT JBUS LOUT(17)",
    });
    machine.getDevice(16)->wordAt(0).set("PRIME");
    machine.executeUntilHalt();
    __ASSERT_EQ("PRIME", machine.getDevice(17)->wordAt(0).getCharacters());
}

}  // namespace test
