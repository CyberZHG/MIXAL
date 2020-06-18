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
        int32_t address = getIndexedAddress(instruction);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
        overflow = false;
    }
}

void Machine::executeJNOV(const InstructionWord& instruction) {
    if (overflow) {
        overflow = false;
    } else {
        int32_t address = getIndexedAddress(instruction);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
    }
}

void Machine::executeJL(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::LESS) {
        int32_t address = getIndexedAddress(instruction);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
    }
}

void Machine::executeJE(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::EQUAL) {
        int32_t address = getIndexedAddress(instruction);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
    }
}

void Machine::executeJG(const InstructionWord& instruction) {
    if (comparison == ComparisonIndicator::GREATER) {
        int32_t address = getIndexedAddress(instruction);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
    }
}

void Machine::executeJGE(const InstructionWord& instruction) {
    if (comparison != ComparisonIndicator::LESS) {
        int32_t address = getIndexedAddress(instruction);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
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
        int32_t address = getIndexedAddress(instruction);
        rJ.set(_lineOffset + 1);
        _lineOffset = address - 1;
    }
}


};  // namespace mixal
