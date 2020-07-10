#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief Arithmetic operations.
 */

namespace mixal {

/** Add the values of rA and the word in the memory into rA.
 * 
 * @see overflow
 */
void Machine::executeADD(const InstructionWord& instruction) {
    int32_t valueA = rA.value();
    ComputerWord word;
    int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], &word);
    int32_t valueM = word.value();
    int32_t result = valueA + valueM;
    rA.set(checkRange(result));
}

/** Subtract the values of rA and the word in the memory into rA.
 * 
 * @see overflow
 */
void Machine::executeSUB(const InstructionWord& instruction) {
    int32_t valueA = rA.value();
    ComputerWord word;
    int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], &word);
    word.negative = !word.negative;
    int32_t valueM = word.value();
    int32_t result = valueA + valueM;
    rA.set(checkRange(result));
}

/** Multiply the values of rA and the word in the memory into rA and rX.
 * 
 * Note that overflow will never be triggered.
 */
void Machine::executeMUL(const InstructionWord& instruction) {
    int32_t valueA = rA.value();
    ComputerWord word;
    int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], &word);
    int32_t valueM = word.value();
    int64_t result = static_cast<int64_t>(valueA) * static_cast<int64_t>(valueM);
    rA.set(result / (1 << 30));
    rX.set(result % (1 << 30));
}

/** Divide the value of rA and rX with the value of the word in the memory.
 * 
 * The quotient will be placed in rA and the remainder will be placed in rX.
 * 
 * @see overflow
 * 
 * @throw mixal::RuntimeError When the divisor is 0.
 */
void Machine::executeDIV(const InstructionWord& instruction) {
    int32_t valueA = std::abs(rA.value());
    int32_t valueX = std::abs(rX.value());
    int64_t dividend = (static_cast<int64_t>(valueA) << 30) + static_cast<int64_t>(valueX);
    if (rA.negative) {
        dividend = -dividend;
    }
    ComputerWord word;
    int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], &word);
    int32_t divisor = word.value();
    if (divisor == 0) {
        throw RuntimeError(_lineOffset, "Divisor cannot be 0");
    }
    int64_t quotient = dividend / divisor;
    if (std::abs(quotient) >= (1 << 30)) {
        overflow = true;
        quotient %= (1 << 30);
    }
    int32_t remainder = dividend % divisor;
    rA.set(static_cast<int32_t>(quotient));
    rX.set(remainder);
}

};  // namespace mixal
