#ifndef INCLUDE_REGISTERS_H_
#define INCLUDE_REGISTERS_H_

#include <cstdint>
#include "memory.h"

namespace mixal {

enum class Registers {
    A,  // Accumulator
    X,  // Extension
    I1, I2, I3, I4, I5, I6,  // Index registers
    J,  // Jump address
};

using Register5 = ComputerWord;

union Register2 {
    struct {
        int16_t word;
    };
    struct {
        int16_t sign : 2;
        int8_t byte1 : 6;
        int8_t byte2 : 6;
    };

    Register2() : word() {}

    inline void reset() {
        word = 0;
    }
};

};  // namespace mixal


#endif  // INCLUDE_REGISTERS_H_
