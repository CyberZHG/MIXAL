#include <iostream>
#include <gtest/gtest.h>
#include "machine.h"

TEST(TestMachineIO, test_get_devices) {
    mixal::Computer machine;
    for (int i = 0; i < mixal::Computer::NUM_IO_DEVICE; ++i) {
        machine.getDevice(i)->control(0);
    }
}

TEST(TestMachineIO, test_io_tape) {
    mixal::Computer machine;
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
    EXPECT_EQ(1000, machine.memory[2000].value());
    EXPECT_EQ(1001, machine.memory[2001].value());
    EXPECT_EQ(1002, machine.memory[2002].value());
}

TEST(TestMachineIO, test_io_tape_rewind) {
    mixal::Computer machine;
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
    EXPECT_EQ(1000, machine.memory[2000].value());
    EXPECT_EQ(1001, machine.memory[2001].value());
    EXPECT_EQ(1002, machine.memory[2002].value());
}

TEST(TestMachineIO, test_io_disk) {
    mixal::Computer machine;
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
    EXPECT_EQ(1000, machine.memory[2000].value());
    EXPECT_EQ(1001, machine.memory[2001].value());
    EXPECT_EQ(1002, machine.memory[2002].value());
}

TEST(TestMachineIO, test_io_chars) {
    mixal::Computer machine;
    machine.loadCodes({
        "     ORIG 3000",
        "     IN   100(16)",
        "LIN  JBUS LIN(16)",
        "     OUT  100(17)",
        "LOUT JBUS LOUT(17)",
    });
    machine.getDevice(16)->wordAt(0).set("PRIME");
    machine.executeUntilHalt();
    EXPECT_EQ("PRIME", machine.getDevice(17)->wordAt(0).getCharacters());
}

TEST(TestMachineIO, test_io_chars_with_wrap) {
    mixal::Computer machine;
    machine.loadCodes({
        "     ORIG 3000",
        "     IN   100(16)",
        "LIN  JBUS LIN(16)",
        "     OUT  100(17)",
        "LOUT JBUS LOUT(17)",
    });
    machine.getDeviceWordAt(16, 0).set("PRIME");
    machine.executeUntilHalt();
    EXPECT_EQ("PRIME", machine.getDeviceWordAt(17, 0).getCharacters());
}

TEST(TestMachineIO, test_io_invalid_in) {
    mixal::Computer machine;
    machine.loadCodes(std::vector<std::string>({
        "     ORIG 3000",
        "     IN   100(17)",
    }));
    EXPECT_THROW(machine.executeUntilHalt(), mixal::RuntimeError);
}

TEST(TestMachineIO, test_io_invalid_out) {
    mixal::Computer machine;
    machine.loadCodes(std::vector<std::string>({
        "     ORIG 3000",
        "     OUT  100(16)",
    }));
    EXPECT_THROW(machine.executeUntilHalt(), mixal::RuntimeError);
}

TEST(TestMachineIO, test_io_invalid_address) {
    mixal::Computer machine;
    machine.loadCodes(std::vector<std::string>({
        "     ORIG 3000",
        "     OUT  -100(17)",
    }));
    EXPECT_THROW(machine.executeUntilHalt(), mixal::RuntimeError);
}
