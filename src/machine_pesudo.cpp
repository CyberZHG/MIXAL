#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief Pesudo operations.
 */

namespace mixal {

/** Define a symbol and its corresponding value. */
void Computer::executeEQU(ParsedResult* instruction) {
    if (!instruction->address.evaluated()) {
        if (!instruction->address.evaluate(_constants)) {
            throw RuntimeError(_lineOffset, "Unresolved symbol found while parsing EQU: " + instruction->rawAddress);
        }
    }
    _constants[instruction->rawLocation] = AtomicValue(instruction->address.result().value);
}

/** Set the start line of the following codes. */
void Computer::executeORIG(ParsedResult* instruction) {
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

/** Store a constant to memory. */
void Computer::executeCON(ParsedResult* instruction) {
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
