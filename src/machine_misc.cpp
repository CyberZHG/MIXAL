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

void Machine::executeSLAX(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction);
    int32_t shift = (address + 10000) % 10;
    if (shift) {
        for (int i = 1; i <= (10 - shift); ++i) {
            setAX(i, getAX(i + shift));
        }
        for (int i = 11 - shift; i <= 10; ++i) {
            setAX(i, 0);
        }
    }
}

void Machine::executeSRAX(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction);
    int32_t shift = (address + 10000) % 10;
    if (shift) {
        for (int i = 10; i > shift; --i) {
            setAX(i, getAX(i - shift));
        }
        for (int i = shift; i > 0; --i) {
            setAX(i, 0);
        }
    }
}

};  // namespace mixal
