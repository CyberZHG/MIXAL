#include <iostream>
#include <cmath>
#include "machine.h"

/**
 * @file
 * @brief Comparison operations.
 */

namespace mixal {

/** Compare the values in rA or rX and the word in memory.
 * 
 * @see comparison
 */
void Computer::executeCMP(const InstructionWord& instruction, Register5* reg) {
    ComputerWord a, b;
    const int32_t address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, *reg, &a);
    copyToRegister5(instruction, memory[address], &b);
    const int32_t aVal = a.value(), bVal = b.value();
    if (aVal < bVal) {
        comparison = ComparisonIndicator::LESS;
    } else if (aVal > bVal) {
        comparison = ComparisonIndicator::GREATER;
    } else {
        comparison = ComparisonIndicator::EQUAL;
    }
}

/** Compare the values in rI and the word in memory.
 *
 * @see comparison
 */
void Computer::executeCMPi(const InstructionWord& instruction) {
    const int registerIndex = instruction.operation() - Instructions::CMP1 + 1;
    const auto& rIi = rI(registerIndex);
    const ComputerWord t(rIi.negative, 0, 0, 0, rIi.byte1, rIi.byte2);
    ComputerWord a, b;
    const int32_t address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, t, &a);
    copyToRegister5(instruction, memory[address], &b);
    const int32_t aVal = a.value(), bVal = b.value();
    if (aVal < bVal) {
        comparison = ComparisonIndicator::LESS;
    } else if (aVal > bVal) {
        comparison = ComparisonIndicator::GREATER;
    } else {
        comparison = ComparisonIndicator::EQUAL;
    }
}

/** Compare the float values in rI and the word in memory.
 *
 * @see comparison
 */
void Computer::executeFCMP(const InstructionWord& instruction) {
    const double valueA = rA.floatValue();
    const int32_t address = getIndexedAddress(instruction, true);
    const double valueM = memory[address].floatValue();
    if (valueA < valueM) {
        comparison = ComparisonIndicator::LESS;
    } else if (valueA > valueM) {
        comparison = ComparisonIndicator::GREATER;
    } else {
        comparison = ComparisonIndicator::EQUAL;
    }
}

}  // namespace mixal
