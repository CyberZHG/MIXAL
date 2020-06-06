#ifndef INCLUDE_REGISTERS_H_
#define INCLUDE_REGISTERS_H_

namespace mixal {

enum class Registers {
    A,  // Accumulator
    X,  // Extension
    I1, I2, I3, I4, I5, I6,  // Index registers
    J,  // Jump address
};

class Register {
};

};  // namespace mixal


#endif  // INCLUDE_REGISTERS_H_
