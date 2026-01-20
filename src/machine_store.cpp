#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief Store operations.
 */

namespace mixal {

/** Store the value in rA or rX to memory. */
void Computer::executeST(const InstructionWord& instruction, Register5* reg) {
    const int address = getIndexedAddress(instruction, true);
    copyFromRegister5(instruction, *reg, &memory[address]);
}

/** Store the value in rI to memory. */
void Computer::executeSTi(const InstructionWord& instruction) {
    const int address = getIndexedAddress(instruction, true);
    const int registerIndex = instruction.operation() - Instructions::ST1 + 1;
    const auto& rIi = rI(registerIndex);
    const ComputerWord word(rIi.negative, 0, 0, 0, rIi[1], rIi[2]);
    copyFromRegister5(instruction, word, &memory[address]);
}

/** Store the value in rJ to memory. */
void Computer::executeSTJ(const InstructionWord& instruction) {
    const int address = getIndexedAddress(instruction, true);
    const ComputerWord word('+', 0, 0, 0, rJ[1], rJ[2]);
    copyFromRegister5(instruction, word, &memory[address]);
}

/** Store zeros to memory. */
void Computer::executeSTZ(const InstructionWord& instruction) {
    const int address = getIndexedAddress(instruction, true);
    const ComputerWord word('+', 0, 0, 0, 0, 0);
    copyFromRegister5(instruction, word, &memory[address]);
}

}  // namespace mixal
