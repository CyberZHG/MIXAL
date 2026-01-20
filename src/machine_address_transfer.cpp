#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief Address transfer operations.
 */

namespace mixal {

/** Increase rA or rX by the address value.
 * 
 * @see overflow
 */
void Computer::executeINC(const InstructionWord& instruction, Register5* reg) {
    const int32_t value = reg->value();
    const int32_t address = getIndexedAddress(instruction);
    reg->set(checkRange(value + address));
}

/** Decrease rA or rX by the address value.
 *
 * @see overflow
 */
void Computer::executeDEC(const InstructionWord& instruction, Register5* reg) {
    const int32_t value = reg->value();
    const int32_t address = getIndexedAddress(instruction);
    reg->set(checkRange(value - address));
}

/** Enter the immediate address value to rA or rX. */
void Computer::executeENT(const InstructionWord& instruction, Register5* reg) {
    const int32_t address = getIndexedAddress(instruction);
    reg->set(address);
    if (address == 0) {
        reg->negative = instruction.negative;
    }
}

/** Enter the negative immediate address value to rA or rX. */
void Computer::executeENN(const InstructionWord& instruction, Register5* reg) {
    const int32_t address = getIndexedAddress(instruction);
    reg->set(-address);
    if (address == 0) {
        reg->negative = !instruction.negative;
    }
}

/** Increase rI by the address value. */
void Computer::executeINCi(const InstructionWord& instruction) {
    const int registerIndex = instruction.operation() - Instructions::INC1 + 1;
    auto& rIi = rI(registerIndex);
    const int16_t value = rIi.value();
    const int16_t address = getIndexedAddress(instruction);
    rIi.set(checkRange(value + address, 2));
}

/** Decrease rI by the address value. */
void Computer::executeDECi(const InstructionWord& instruction) {
    const int registerIndex = instruction.operation() - Instructions::INC1 + 1;
    auto& rIi = rI(registerIndex);
    const int16_t value = rIi.value();
    const int16_t address = getIndexedAddress(instruction);
    rIi.set(checkRange(value - address, 2));
}

/** Enter address value to rI. */
void Computer::executeENTi(const InstructionWord& instruction) {
    const int registerIndex = instruction.operation() - Instructions::INC1 + 1;
    auto& rIi = rI(registerIndex);
    const int16_t address = getIndexedAddress(instruction);
    rIi.set(checkRange(address, 2));
    if (address == 0) {
        rIi.negative = instruction.negative;
    }
}

/** Enter negative address value to rI. */
void Computer::executeENNi(const InstructionWord& instruction) {
    const int registerIndex = instruction.operation() - Instructions::INC1 + 1;
    auto& rIi = rI(registerIndex);
    const int16_t address = getIndexedAddress(instruction);
    rIi.set(checkRange(-address, 2));
    if (address == 0) {
        rIi.negative = !instruction.negative;
    }
}

}  // namespace mixal
