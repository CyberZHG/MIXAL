#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <cstdint>

namespace mixal {

union ComputerWord {
    struct {
        int32_t word;
    } word;
    struct {
        int16_t sign : 2;
        int8_t byte1 : 6;
        int8_t byte2 : 6;
        int8_t byte3 : 6;
        int8_t byte4 : 6;
        int8_t byte5 : 6;
    } bytes;
};

extern ComputerWord memory[4000];

};  // namespace mixal


#endif  // INCLUDE_MEMORY_H_
