#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <cstdint>

namespace mixal {

union ComputerWord {
    struct {
        int32_t word;
    };
    struct {
        int16_t sign : 2;
        int8_t byte1 : 6;
        int8_t byte2 : 6;
        int8_t byte3 : 6;
        int8_t byte4 : 6;
        int8_t byte5 : 6;
    };

    ComputerWord() : word(0) {}

    inline void reset() { sign = byte1 = byte2 = byte3 = byte4 = byte5 = 0; }

    int8_t operator[](int index) const;
    int16_t bytes12() const;
    int16_t bytes34() const;

    void set(int index, int8_t val);
    void set(bool negative, int8_t byte1, int8_t byte2, int8_t byte3, int8_t byte4, int8_t byte5);
    void set(bool negative, int16_t bytes12, int8_t byte3, int8_t byte4, int8_t byte5);
};

};  // namespace mixal


#endif  // INCLUDE_MEMORY_H_
