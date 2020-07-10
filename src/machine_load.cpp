#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief Load operations.
 */

namespace mixal {

/** Load the word from the address to rA or rX. */
void Machine::executeLD(const InstructionWord& instruction, Register5* reg) {
    int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], reg);
}

/** Load the word from the address to rI. */
void Machine::executeLDi(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction, true);
    int registerIndex = instruction.operation() - Instructions::LD1 + 1;
    auto& rIi = rI(registerIndex);
    copyToRegister2(instruction, memory[address], &rIi);
}

/** Load negative value of the word from the address to rA or rX. */
void Machine::executeLDN(const InstructionWord& instruction, Register5* reg) {
    executeLD(instruction, reg);
    reg->negative = !reg->negative;
}

/** Load negative value of the word from the address to rI. */
void Machine::executeLDiN(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction, true);
    int registerIndex = instruction.operation() - Instructions::LD1N + 1;
    auto& rIi = rI(registerIndex);
    copyToRegister2(instruction, memory[address], &rIi);
    rIi.negative = 1 - rIi.negative;
}

};  // namespace mixal
