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

struct Register2 {
    bool sign;
    uint8_t byte1;
    uint8_t byte2;

    Register2() : sign(), byte1(), byte2() {}
    explicit Register2(int16_t value) : sign(), byte1(), byte2() { set(value); }
    Register2(bool _negative, uint8_t _byte1, uint8_t _byte2) : sign(_negative), byte1(_byte1), byte2(_byte2) {}

    inline void reset() {
        sign = false;
        byte1 = byte2 = 0;
    }

    uint8_t operator[](int index) const;
    uint16_t bytes12() const;
    int16_t value() const;

    void set(int16_t value);
    void set(int index, int8_t val);
    void set(bool negative, uint8_t byte1, uint8_t byte2);
};

};  // namespace mixal


#endif  // INCLUDE_REGISTERS_H_
