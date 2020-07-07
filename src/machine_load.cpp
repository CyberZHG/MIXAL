#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::executeLD(const InstructionWord& instruction, Register5* reg) {
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], reg);
}

void Machine::executeLDi(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    int registerIndex = instruction.operation() - Instructions::LD1 + 1;
    auto& rIi = rI(registerIndex);
    copyToRegister2(instruction, memory[address], &rIi);
}

void Machine::executeLDN(const InstructionWord& instruction, Register5* reg) {
    executeLD(instruction, reg);
    reg->negative = !reg->negative;
}

void Machine::executeLDiN(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    int registerIndex = instruction.operation() - Instructions::LD1N + 1;
    auto& rIi = rI(registerIndex);
    copyToRegister2(instruction, memory[address], &rIi);
    rIi.negative = 1 - rIi.negative;
}

};  // namespace mixal