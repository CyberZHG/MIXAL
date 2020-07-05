#ifndef INCLUDE_REGISTERS_H_
#define INCLUDE_REGISTERS_H_

#include <cstdint>
#include "memory.h"

/**
 * @file
 * @brief The definition of registers.
 */

namespace mixal {

/** The register with 5 bytes (rA, rX) is basically the same as a computer word. */
using Register5 = ComputerWord;

/** The register with 2 bytes (rI, rJ).
 *
 * The 2 bytes registers are used to represent locations and offsets.
 * It contains a sign indicator (`+` or `-`) and 2 bytes.
 * Each byte can represent at least [0, 64) integers.
 */
struct Register2 {
    bool negative;
    uint8_t byte1;
    uint8_t byte2;

    /** Initialize the register with zeros. */
    Register2() : negative(), byte1(), byte2() {}
    /** Initialize the register with an integer value.
     * 
     * @see set(int16_t)
     */
    explicit Register2(int16_t value) : negative(), byte1(), byte2() { set(value); }
    /** Initialize the register with all the specific values. */
    Register2(bool _negative, uint8_t _byte1, uint8_t _byte2) : negative(_negative), byte1(_byte1), byte2(_byte2) {}

    /** Reset the values in the register to 0. */
    inline void reset() {
        negative = false;
        byte1 = byte2 = 0;
    }

    /** Get the value with index in [1, 2].
     * 
     * @throw std::runtime_error when the index is not in [1, 2].
     */
    uint8_t operator[](int index) const;
    /** Get the absolution value of the register. */
    uint16_t bytes12() const;
    /** Get the value represented by the register. */
    int16_t value() const;

    /**
     * Set the register with an integer.
     * 
     * The sign will be set only when the input is non-zero.
     * Therefore to set the word to `-0` with this function,
     * one can set it with a negative value first, then set it to 0.
     * 
     * The least significant 12 bits will be saved to the word.
     * Each byte contains 6 bits. The byte2 will contain the least significant 6 bits. 
     */
    void set(int16_t value);
    /**
     * Set specific byte with the given index in [1, 2].
     * 
     * @param val The behavior is undefined if it is greater than 63.
     * 
     * @throw std::runtime_error when the index is not in [1, 2].
     */
    void set(int index, int8_t val);
    /** Set all the values. */
    void set(bool negative, uint8_t byte1, uint8_t byte2);
};

};  // namespace mixal


#endif  // INCLUDE_REGISTERS_H_
