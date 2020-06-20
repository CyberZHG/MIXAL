#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::executeJBUS(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (!device->ready(this->_elapsed)) {
        this->executeJMP(instruction);
    }
}

void Machine::executeIOC(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    while (!device->ready(this->_elapsed)) {
        ++this->_elapsed;
    }
    if (device->type() == IODeviceType::DISK) {
        device->control(rX.value());
    } else {
        device->control(instruction.addressValue());
    }
}

void Machine::executeIN(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    device->read(memory, instruction.addressValue());
}

void Machine::executeOUT(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    device->write(memory, instruction.addressValue());
}

void Machine::executeJRED(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (device->ready(this->_elapsed)) {
        this->executeJMP(instruction);
    }
}

};  // namespace mixal
