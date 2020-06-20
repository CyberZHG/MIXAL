#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <cstdint>

namespace mixal {

class Instructions;

struct ComputerWord {
    bool sign;
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
    uint8_t byte4;
    uint8_t byte5;

    ComputerWord() : sign(), byte1(), byte2(), byte3(), byte4(), byte5() {}
    explicit ComputerWord(int32_t value) : sign(), byte1(), byte2(), byte3(), byte4(), byte5() { set(value); }
    ComputerWord(bool _negative, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5) :
        sign(_negative), byte1(_byte1), byte2(_byte2), byte3(_byte3), byte4(_byte4), byte5(_byte5) {}
    ComputerWord(bool _negative, uint16_t bytes12, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5) :
        sign(_negative), byte1(bytes12 / 64), byte2(bytes12 % 64), byte3(_byte3), byte4(_byte4), byte5(_byte5) {}

    inline void reset() {
        sign = false;
        byte1 = byte2 = byte3 = byte4 = byte5 = 0;
    }

    bool operator==(const ComputerWord& word) const;
    friend std::ostream& operator<<(std::ostream& out, const ComputerWord& word);

    uint8_t operator[](int index) const;
    uint8_t& operator[](int index);
    uint16_t bytes2(int index1, int index2) const;
    uint16_t bytes12() const;
    uint16_t bytes23() const;
    uint16_t bytes34() const;
    uint16_t bytes45() const;
    int32_t value() const;

    int16_t addressValue() const;
    inline uint32_t address() const { return bytes12(); }
    inline uint8_t index() const { return byte3; }
    inline uint8_t field() const { return byte4; }
    inline uint8_t operation() const { return byte5; }

    void setAddress(int16_t address);
    void setAddress(bool negative, uint16_t address);
    inline void setIndex(uint8_t index) { byte3 = index; }
    inline void setField(uint8_t field) { byte4 = field; }
    inline void setOperation(uint8_t operation) { byte5 = operation; }

    void set(int32_t value);
    void set(int index, uint8_t val);
    void set(bool negative, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5);
    void set(bool negative, uint16_t bytes12, uint8_t byte3, uint8_t byte4, uint8_t byte5);
};

};  // namespace mixal


#endif  // INCLUDE_MEMORY_H_
