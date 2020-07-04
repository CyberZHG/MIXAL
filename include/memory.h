#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <cstdint>
#include <string>

namespace mixal {

class Instructions;

extern uint16_t CHAR_CODES[];       /**< The mapping from a byte to the characters. */
const int32_t CHAR_CODES_NUM = 56;  /**< The maximum number of characters in the mapping. */

/**
 * Basic definition of a word.
 * 
 * A word contains a sign indicator (`+` or `-`) and 5 bytes.
 * Each byte can represent at least [0, 64) integers.
 */
struct ComputerWord {
    bool negative;
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
    uint8_t byte4;
    uint8_t byte5;

    /**
     * Initialize with 0s. The default sign is '+'.
     */
    ComputerWord() : negative(), byte1(), byte2(), byte3(), byte4(), byte5() {}
    /**
     * Initialize with integer value.
     * 
     * @see set(int32_t)
     */
    explicit ComputerWord(int32_t value) : negative(), byte1(), byte2(), byte3(), byte4(), byte5() { set(value); }
    explicit ComputerWord(const std::string& chars) :
        negative(), byte1(), byte2(), byte3(), byte4(), byte5() { set(chars); }
    ComputerWord(bool _negative, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5) :
        negative(_negative), byte1(_byte1), byte2(_byte2), byte3(_byte3), byte4(_byte4), byte5(_byte5) {}
    ComputerWord(bool _negative, uint16_t bytes12, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5) :
        negative(_negative), byte1(bytes12 / 64), byte2(bytes12 % 64), byte3(_byte3), byte4(_byte4), byte5(_byte5) {}

    inline void reset() {
        negative = false;
        byte1 = byte2 = byte3 = byte4 = byte5 = 0;
    }

    bool operator==(const ComputerWord& word) const;
    friend std::ostream& operator<<(std::ostream& out, const ComputerWord& word);
    std::string getBytesString() const;

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

    uint8_t getAt(int32_t index) const { return (*this)[index]; }
    std::string getCharacters() const;
    /**
     * Set the word with an integer.
     * 
     * The sign will be set only when the input is non-zero.
     * Therefore to set the word to `-0` with this function,
     * one can set it with a negative value first, then set it to 0.
     * 
     * The least significant 30 bits will be saved to the word.
     * Each byte contains 6 bits. The byte5 will contain the least significant 5 bits. 
     */
    void set(int32_t value);
    void set(const std::string& chars);
    void set(int index, uint8_t val);
    void set(bool negative, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5);
    void set(bool negative, uint16_t bytes12, uint8_t byte3, uint8_t byte4, uint8_t byte5);
};

};  // namespace mixal


#endif  // INCLUDE_MEMORY_H_
