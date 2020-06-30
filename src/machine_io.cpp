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
        int32_t address = getIndexedAddress(instruction);
        device->control(address);
    }
}

void Machine::executeIN(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (!device->allowRead()) {
        throw RuntimeError(_lineOffset, "Device does not support read: " + std::to_string(instruction.field()));
    }
    int32_t address = getIndexedAddress(instruction);
    device->read(memory, address);
}

void Machine::executeOUT(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (!device->allowWrite()) {
        throw RuntimeError(_lineOffset, "Device does not support write: " + std::to_string(instruction.field()));
    }
    int32_t address = getIndexedAddress(instruction);
    device->write(memory, address);
}

void Machine::executeJRED(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (device->ready(this->_elapsed)) {
        this->executeJMP(instruction);
    }
}

};  // namespace mixal
