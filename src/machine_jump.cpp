#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief Jump operations.
 */

namespace mixal {

/** Unconditional jump.
 * 
 * rJ will be set to the next instruction if the jump has not been occured.
 */
void Machine::executeJMP(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction, true);
    rJ.set(_lineOffset + 1);
    _lineOffset = address - 1;
}

/** Jump without updating rJ. */
void Machine::executeJSJ(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction, true);
    _lineOffset = address - 1;
}

/** Jump when overflow.
 * 
 * The overflow flag will be cleared.
 * 
 * @see overflow.
 */
void Machine::executeJOV(const InstructionWord& instruction) {
    if (overflow) {
        this->executeJMP(instruction);
        overflow = false;
    }
}

/** Jump when not overflow.
 * 
 * The overflow flag will be cleared.
 * 
 * @see overflow.
 */
void Machine::executeJNOV(const InstructionWord& instruction) {
    if (overflow) {
        overflow = false;
    } else {
        this->executeJMP(instruction);
    }
}

/** Jump when the comparison result is less.
 * 
 * @see comparison
 */
void Machine::executeJL(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::LESS) {
        this->executeJMP(instruction);
    }
}

/** Jump when the comparison result is equal.
 * 
 * @see comparison
 */
void Machine::executeJE(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::EQUAL) {
        this->executeJMP(instruction);
    }
}

/** Jump when the comparison result is greater.
 * 
 * @see comparison
 */
void Machine::executeJG(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::GREATER) {
        this->executeJMP(instruction);
    }
}

/** Jump when the comparison result is greater or equal.
 * 
 * @see comparison
 */
void Machine::executeJGE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::LESS) {
        this->executeJMP(instruction);
    }
}
/** Jump when the comparison result is not equal.
 * 
 * @see comparison
 */
void Machine::executeJNE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::EQUAL) {
        int32_t address = getIndexedAddress(instruction, true);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
    }
}

/** Jump when the comparison result is less or equal.
 * 
 * @see comparison
 */
void Machine::executeJLE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::GREATER) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is negative. */
void Machine::executeJN(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() < 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is zero. */
void Machine::executeJZ(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() == 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is positive. */
void Machine::executeJP(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() > 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is non-negative. */
void Machine::executeJNN(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() >= 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is not zero. */
void Machine::executeJNZ(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() != 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is non-positive. */
void Machine::executeJNP(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() <= 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is negative. */
void Machine::executeJiN(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto rIi = rI(registerIndex);
    if (rIi.value() < 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is zero. */
void Machine::executeJiZ(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() == 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is positive. */
void Machine::executeJiP(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() > 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is non-negative. */
void Machine::executeJiNN(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() >= 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is not zero. */
void Machine::executeJiNZ(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() != 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is non-positive. */
void Machine::executeJiNP(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() <= 0) {
        this->executeJMP(instruction);
    }
}

};  // namespace mixal
