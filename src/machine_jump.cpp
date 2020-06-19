#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::executeJMP(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction);
    rJ.set(_lineOffset + 1);
    _lineOffset = address - 1;
}

void Machine::executeJSJ(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction);
    _lineOffset = address - 1;
}

void Machine::executeJOV(const InstructionWord& instruction) {
    if (overflow) {
        this->executeJMP(instruction);
        overflow = false;
    }
}

void Machine::executeJNOV(const InstructionWord& instruction) {
    if (overflow) {
        overflow = false;
    } else {
        this->executeJMP(instruction);
    }
}

void Machine::executeJL(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::LESS) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJE(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::EQUAL) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJG(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::GREATER) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJGE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::LESS) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJNE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::EQUAL) {
        int32_t address = getIndexedAddress(instruction);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
    }
}

void Machine::executeJLE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::GREATER) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJN(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() < 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJZ(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() == 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJP(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() > 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJNN(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() >= 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJNZ(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() != 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJNP(const InstructionWord& instruction, Register5* reg) {
    if (reg->value() <= 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJiN(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N;
    auto& rIi = rI[registerIndex];
    if (rIi.value() < 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJiZ(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N;
    auto& rIi = rI[registerIndex];
    if (rIi.value() == 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJiP(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N;
    auto& rIi = rI[registerIndex];
    if (rIi.value() > 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJiNN(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N;
    auto& rIi = rI[registerIndex];
    if (rIi.value() >= 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJiNZ(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N;
    auto& rIi = rI[registerIndex];
    if (rIi.value() != 0) {
        this->executeJMP(instruction);
    }
}

void Machine::executeJiNP(const InstructionWord& instruction) {
    int registerIndex = instruction.operation() - Instructions::J1N;
    auto& rIi = rI[registerIndex];
    if (rIi.value() <= 0) {
        this->executeJMP(instruction);
    }
}

};  // namespace mixal
