#ifndef INCLUDE_INSTRUCTIONS_H_
#define INCLUDE_INSTRUCTIONS_H_

#include <cstdint>

namespace mixal {

enum class Instructions {
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
};

};  // namespace mixal


#endif  // INCLUDE_INSTRUCTIONS_H_
