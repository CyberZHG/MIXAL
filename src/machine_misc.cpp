#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::executeSLA(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction);
    int32_t shift = (address + 10000) % 5;
    if (shift) {
        for (int i = 1; i <= (5 - shift); ++i) {
            rA[i] = rA[i + shift];
        }
        for (int i = 6 - shift; i <=5; ++i) {
            rA[i] = 0;
        }
    }
}

void Machine::executeSRA(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction);
    int32_t shift = (address + 10000) % 5;
    if (shift) {
        for (int i = 5; i > shift; --i) {
            rA[i] = rA[i - shift];
        }
        for (int i = shift; i > 0; --i) {
            rA[i] = 0;
        }
    }
}

};  // namespace mixal
