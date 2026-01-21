#include <iostream>
#include <cmath>
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
void Computer::executeADD(const InstructionWord& instruction) {
    const int32_t valueA = rA.value();
    ComputerWord word;
    const int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], &word);
    const int32_t valueM = word.value();
    const int32_t result = valueA + valueM;
    rA.set(checkRange(result));
}

/** Subtract the values of rA and the word in the memory into rA.
 * 
 * @see overflow
 */
void Computer::executeSUB(const InstructionWord& instruction) {
    const int32_t valueA = rA.value();
    ComputerWord word;
    const int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], &word);
    word.negative = !word.negative;
    const int32_t valueM = word.value();
    const int32_t result = valueA + valueM;
    rA.set(checkRange(result));
}

/** Multiply the values of rA and the word in the memory into rA and rX.
 * 
 * Note that overflow will never be triggered.
 */
void Computer::executeMUL(const InstructionWord& instruction) {
    const int32_t valueA = rA.value();
    ComputerWord word;
    const int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], &word);
    const int32_t valueM = word.value();
    const int64_t result = static_cast<int64_t>(valueA) * static_cast<int64_t>(valueM);
    rA.set(static_cast<int32_t>(result / (1 << 30)));
    rX.set(static_cast<int32_t>(result % (1 << 30)));
}

/** Divide the value of rA and rX with the value of the word in the memory.
 * 
 * The quotient will be placed in rA and the remainder will be placed in rX.
 * 
 * @see overflow
 * 
 * @throw mixal::RuntimeError When the divisor is 0.
 */
void Computer::executeDIV(const InstructionWord& instruction) {
    const int32_t valueA = std::abs(rA.value());
    const int32_t valueX = std::abs(rX.value());
    int64_t dividend = (static_cast<int64_t>(valueA) << 30) + static_cast<int64_t>(valueX);
    if (rA.negative) {
        dividend = -dividend;
    }
    ComputerWord word;
    const int address = getIndexedAddress(instruction, true);
    copyToRegister5(instruction, memory[address], &word);
    const int32_t divisor = word.value();
    if (divisor == 0) {
        throw RuntimeError(_lineOffset, "Divisor cannot be 0");
    }
    int64_t quotient = dividend / divisor;
    if (std::abs(quotient) >= (1 << 30)) {
        overflow = true;
        quotient %= (1 << 30);
    }
    const int32_t remainder = dividend % divisor;
    rA.set(static_cast<int32_t>(quotient));
    rX.set(remainder);
}

/** Add the float values of rA and the word in the memory into rA.
 *
 * @see overflow
 */
void Computer::executeFADD(const InstructionWord& instruction) {
    const double valueA = rA.floatValue();
    const int address = getIndexedAddress(instruction, true);
    const double valueM = memory[address].floatValue();
    const double result = valueA + valueM;
    if (rA.set(result)) {
        overflow = true;
    }
}

/** Subtract the float values of rA and the word in the memory into rA.
 *
 * @see overflow
 */
void Computer::executeFSUB(const InstructionWord& instruction) {
    const double valueA = rA.floatValue();
    const int address = getIndexedAddress(instruction, true);
    const double valueM = memory[address].floatValue();
    const double result = valueA - valueM;
    if (rA.set(result)) {
        overflow = true;
    }
}

/** Multiply the float values of rA and the word in the memory into rA and rX.
 *
 * @see overflow
 */
void Computer::executeFMUL(const InstructionWord& instruction) {
    const double valueA = rA.floatValue();
    const int address = getIndexedAddress(instruction, true);
    const double valueM = memory[address].floatValue();
    const double result = valueA * valueM;
    if (rA.set(result)) {
        overflow = true;
    }
}

/** Divide the float values of rA and rX with the value of the word in the memory.
 *
 * The quotient will be placed in rA and the remainder will be placed in rX.
 *
 * @see overflow
 *
 * @throw mixal::RuntimeError When the divisor is 0.
 */
void Computer::executeFDIV(const InstructionWord& instruction) {
    const double valueA = rA.floatValue();
    const int address = getIndexedAddress(instruction, true);
    const double valueM = memory[address].floatValue();
    if (valueM == 0.0) {
        throw RuntimeError(_lineOffset, "Floating-point divisor cannot be 0");
    }
    const double result = valueA / valueM;
    if (rA.set(result)) {
        overflow = true;
    }
}

}  // namespace mixal
