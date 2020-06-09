#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <cstdint>

namespace mixal {

struct ComputerWord {
    bool sign;
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
    uint8_t byte4;
    uint8_t byte5;

    ComputerWord() : sign(), byte1(), byte2(), byte3(), byte4(), byte5() {}

    inline void reset() {
        sign = false;
        byte1 = byte2 = byte3 = byte4 = byte5 = 0;
    }

    uint8_t operator[](int index) const;
    uint16_t bytes2(int index1, int index2) const;
    uint16_t bytes12() const;
    uint16_t bytes23() const;
    uint16_t bytes34() const;
    uint16_t bytes45() const;
    int32_t value() const;

    void set(int32_t value);
    void set(int index, uint8_t val);
    void set(bool negative, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5);
    void set(bool negative, uint16_t bytes12, uint8_t byte3, uint8_t byte4, uint8_t byte5);
};

};  // namespace mixal


#endif  // INCLUDE_MEMORY_H_
