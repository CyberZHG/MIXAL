#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::executeINC(const InstructionWord& instruction, Register5* reg) {
    int32_t value = reg->value();
    int32_t address = getIndexedAddress(instruction);
    value += address;
    reg->set(checkRange(value));
}

void Machine::executeDEC(const InstructionWord& instruction, Register5* reg) {
    int32_t value = reg->value();
    int32_t address = getIndexedAddress(instruction);
    value -= address;
    reg->set(checkRange(value));
}

void Machine::executeENT(const InstructionWord& instruction, Register5* reg) {
    int32_t address = getIndexedAddress(instruction);
    reg->set(address);
    if (address == 0) {
        reg->negative = instruction.negative;
    }
}

void Machine::executeENN(const InstructionWord& instruction, Register5* reg) {
    int32_t address = getIndexedAddress(instruction);
    reg->set(-address);
    if (address == 0) {
        reg->negative = !instruction.negative;
    }
}

void Machine::executeINCi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::INC1 + 1;
    auto& rIi = rI(registerIndex);
    int16_t value = rIi.value();
    int16_t address = getIndexedAddress(instruction);
    value += address;
    rIi.set(checkRange(value, 2));
}

void Machine::executeDECi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::INC1 + 1;
    auto& rIi = rI(registerIndex);
    int16_t value = rIi.value();
    int16_t address = getIndexedAddress(instruction);
    value -= address;
    rIi.set(checkRange(value, 2));
}

void Machine::executeENTi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::INC1 + 1;
    auto& rIi = rI(registerIndex);
    int16_t address = getIndexedAddress(instruction);
    rIi.set(checkRange(address, 2));
    if (address == 0) {
        rIi.negative = instruction.negative;
    }
}

void Machine::executeENNi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::INC1 + 1;
    auto& rIi = rI(registerIndex);
    int16_t address = getIndexedAddress(instruction);
    rIi.set(checkRange(-address, 2));
    if (address == 0) {
        rIi.negative = !instruction.negative;
    }
}

};  // namespace mixal
