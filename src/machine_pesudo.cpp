#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::executeEQU(ParsedResult* instruction) {
    if (!instruction->address.evaluated()) {
        if (!instruction->address.evaluate(_constants)) {
            throw RuntimeError(_lineOffset, "Unresolved symbol found while parsing EQU: " + instruction->rawAddress);
        }
    }
    _constants[instruction->rawLocation] = AtomicValue(instruction->address.result().value);
}

void Machine::executeORIG(ParsedResult* instruction) {
    if (!instruction->address.evaluated()) {
        if (!instruction->address.evaluate(_constants)) {
            throw RuntimeError(_lineOffset, "Unresolved symbol found while parsing ORIG: " + instruction->rawAddress);
        }
    }
    _lineOffset = instruction->address.result().value;
    if (instruction->rawLocation.length() > 0) {
        _constants[instruction->rawLocation] = AtomicValue(instruction->address.result().value);
    } else {
        std::string symbol = getPesudoSymbolname();
        _constants[symbol] = AtomicValue(instruction->address.result().value);
    }
}

void Machine::executeCON(ParsedResult* instruction) {
    if (!instruction->address.evaluated()) {
        if (!instruction->address.evaluate(_constants)) {
            throw RuntimeError(_lineOffset, "Unresolved symbol found while parsing CON: " + instruction->rawAddress);
        }
    }
    memory[_lineOffset].set(instruction->address.result().value);
    if (!instruction->rawLocation.empty()) {
        _constants[instruction->rawLocation] = AtomicValue(_lineOffset);
    }
    ++_lineOffset;
}

};  // namespace mixal
