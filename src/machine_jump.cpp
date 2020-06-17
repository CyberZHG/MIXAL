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

};  // namespace mixal
