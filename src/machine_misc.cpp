#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief MISC operations.
 */

namespace mixal {

/** Shift left rA padded with zeros. */
void Computer::executeSLA(const InstructionWord& instruction) {
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

/** Shift right rA padded with zeros. */
void Computer::executeSRA(const InstructionWord& instruction) {
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

/** Shift left rA and rX padded with zeros. */
void Computer::executeSLAX(const InstructionWord& instruction) {
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

/** Shift right rA and rX padded with zeros. */
void Computer::executeSRAX(const InstructionWord& instruction) {
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

/** Shift left rA and rX circularly. */
void Computer::executeSLC(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction);
    int32_t shift = (address + 10000) % 10;
    if (shift) {
        auto swap = [&](int start, int stop) {
            int mid = start + (stop - start) / 2;
            for (int i = start; i < mid; ++i) {
                int oppsite = stop - 1 - (i - start);
                uint8_t temp = getAX(i);
                setAX(i, getAX(oppsite));
                setAX(oppsite, temp);
            }
        };
        swap(1, shift + 1);
        swap(shift + 1, 11);
        swap(1, 11);
    }
}

/** Shift right rA and rX circularly. */
void Computer::executeSRC(const InstructionWord& instruction) {
    int32_t address = getIndexedAddress(instruction);
    int32_t shift = (address + 10000) % 10;
    if (shift) {
        auto swap = [&](int start, int stop) {
            int mid = start + (stop - start) / 2;
            for (int i = start; i < mid; ++i) {
                int oppsite = stop - 1 - (i - start);
                uint8_t temp = getAX(i);
                setAX(i, getAX(oppsite));
                setAX(oppsite, temp);
            }
        };
        swap(1, 11 - shift);
        swap(11 - shift, 11);
        swap(1, 11);
    }
}

/** Move a batch of words based on address and rI1.
 *
 * The field value means the number of words to be moved.
 * Nothing happens if the address is out of range.
 */
void Computer::executeMOVE(const InstructionWord& instruction) {
    int32_t originAddress = getIndexedAddress(instruction);
    int32_t targetAddress = rI1.value();
    uint8_t amount = instruction.field();
    for (uint8_t i = 0; i < amount; ++i) {
        int32_t target = targetAddress + i;
        int32_t origin = originAddress + i;
        if (target < 0 || target >= NUM_MEMORY) {
            continue;
        }
        memory[target] = memory[origin];
    }
    rI1.set(targetAddress + amount);
}

};  // namespace mixal
