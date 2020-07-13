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
void Computer::executeJMP(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction, true);
    rJ.set(_lineOffset + 1);
    _lineOffset = address - 1;
}

/** Jump without updating rJ. */
void Computer::executeJSJ(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction, true);
    _lineOffset = address - 1;
}

/** Jump when overflow.
 * 
 * The overflow flag will be cleared.
 * 
 * @see overflow.
 */
void Computer::executeJOV(const InstructionWord& instruction) {
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
void Computer::executeJNOV(const InstructionWord& instruction) {
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
void Computer::executeJL(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::LESS) {
        this->executeJMP(instruction);
    }
}

/** Jump when the comparison result is equal.
 * 
 * @see comparison
 */
void Computer::executeJE(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::EQUAL) {
        this->executeJMP(instruction);
    }
}

/** Jump when the comparison result is greater.
 * 
 * @see comparison
 */
void Computer::executeJG(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::GREATER) {
        this->executeJMP(instruction);
    }
}

/** Jump when the comparison result is greater or equal.
 * 
 * @see comparison
 */
void Computer::executeJGE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::LESS) {
        this->executeJMP(instruction);
    }
}
/** Jump when the comparison result is not equal.
 * 
 * @see comparison
 */
void Computer::executeJNE(const InstructionWord& instruction) {
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
void Computer::executeJLE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::GREATER) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is negative. */
void Computer::executeJN(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() < 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is zero. */
void Computer::executeJZ(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() == 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is positive. */
void Computer::executeJP(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() > 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is non-negative. */
void Computer::executeJNN(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() >= 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is not zero. */
void Computer::executeJNZ(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() != 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rA or rX is non-positive. */
void Computer::executeJNP(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() <= 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is negative. */
void Computer::executeJiN(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto rIi = rI(registerIndex);
    if (rIi.value() < 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is zero. */
void Computer::executeJiZ(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() == 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is positive. */
void Computer::executeJiP(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() > 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is non-negative. */
void Computer::executeJiNN(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() >= 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is not zero. */
void Computer::executeJiNZ(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() != 0) {
        this->executeJMP(instruction);
    }
}

/** Jump when rI is non-positive. */
void Computer::executeJiNP(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N + 1;
    auto& rIi = rI(registerIndex);
    if (rIi.value() <= 0) {
        this->executeJMP(instruction);
    }
}

};  // namespace mixal
