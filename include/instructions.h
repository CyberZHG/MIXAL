#ifndef INCLUDE_INSTRUCTIONS_H_
#define INCLUDE_INSTRUCTIONS_H_

#include <cstdint>
#include <string>

namespace mixal {

class Instructions {
 public:
    enum Code {
        INVALID = -1,
        NOP = 0,  // No operation
        LDA = 8,
        LD1 = 9,
        LD2 = 10,
        LD3 = 11,
        LD4 = 12,
        LD5 = 13,
        LD6 = 14,
        LDX = 15,
    };

    static Instructions::Code getInstructionCode(const std::string& name);
};

struct InstructionWord {
    /** Computer words used for instructions.
     * | 0 | 1 | 2 | 3 | 4 | 5 |
     * | +   A   A | I | F | C |
     */
    int16_t address : 14;
    uint8_t index : 6;
    uint8_t modification : 6;
    uint8_t operation : 6;

    InstructionWord() : address(0), index(0), modification(5), operation() {}
};

};  // namespace mixal


#endif  // INCLUDE_INSTRUCTIONS_H_
