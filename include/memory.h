#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include <cstdint>
#include <string>

/**
 * @file
 * @brief The definition of a computer word.
 */

namespace mixal {

class Instructions;

extern uint16_t CHAR_CODES[];       /**< The mapping from a byte to the characters. */
constexpr int32_t CHAR_CODES_NUM = 56;  /**< The maximum number of characters in the mapping. */

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

    /** Initialize with 0s. The default sign is '+'. */
    ComputerWord();
    /** Initialize with integer value.
     * 
     * @see set(int32_t)
     */
    explicit ComputerWord(int32_t value);
    /** Initialize with five characters.
     * 
     * @see set(const std::string&)
     */
    explicit ComputerWord(const std::string& chars);
    /** Initialize with full representation. */
    ComputerWord(bool _negative, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5);
    /** Initialize with full representation.
     * 
     * @throw std::runtime_error when the sign is neither '+' nor '-'.
     */
    ComputerWord(char sign, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5);
    /** Initialize with the first two bytes combined.
     * 
     * @see set(bool, uint16_t, uint8_t, uint8_t, uint8_t)
     */
    ComputerWord(bool _negative, uint16_t bytes12, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5);
    /** Initialize with the first two bytes combined.
     * 
     * @see set(sign, uint16_t, uint8_t, uint8_t, uint8_t)
     * 
     * @throw std::runtime_error when the sign is neither '+' nor '-'.
     */
    ComputerWord(char sign, uint16_t bytes12, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5);

    /** Set the sign to `+` and all the bytes to 0. */
    void reset();

    /** Whether two words are strictly equal.
     * 
     * `+0` does not equal to `-0`.
     */
    bool operator==(const ComputerWord& word) const;
    /** Output the word in the format like:
     * `+ 0 1 2 13 24`
     */
    friend std::ostream& operator<<(std::ostream& out, const ComputerWord& word);
    /** Get the string of bytes with padded spaces like:
     * `-  0 12  3 43 49`
     */
    [[nodiscard]] std::string getBytesString() const;

    /** Get the value with index in [1, 5].
     * 
     * @throw std::runtime_error when the index is not in [1, 5].
     */
    uint8_t operator[](int index) const;
    /** Get the reference with index in [1, 5].
     * 
     * @throw std::runtime_error when the index is not in [1, 5].
     */
    uint8_t& operator[](int index);
    /** Get the value that represented by the indices of two bytes.
     */
    [[nodiscard]] uint16_t bytes2(int index1, int index2) const;
    /** Get the value of the first two bytes.
     * 
     * @see bytes2(int, int)
     */
    [[nodiscard]] uint16_t bytes12() const;
    /** Get the value of the second and third bytes.
     * 
     * @see bytes2(int, int)
     */
    [[nodiscard]] uint16_t bytes23() const;
    /** Get the value of the third and fourth bytes.
     * 
     * @see bytes2(int, int)
     */
    [[nodiscard]] uint16_t bytes34() const;
    /** Get the value of the last two bytes.
     * 
     * @see bytes2(int, int)
     */
    [[nodiscard]] uint16_t bytes45() const;
    /** Get the value the word represents.
     * 
     * The range of the result should be [-1073741824, 1073741824].
     */
    [[nodiscard]] int32_t value() const;

    /** When representing an instruction,
     * the function returns the value represented by the first two bytes with the sign.
     * 
     * @see bytes12()
     * 
     * @return Note that `-0` can not be returned.
     */
    [[nodiscard]] int16_t addressValue() const;
    /** When representing an instruction,
     * the function returns the value represented by the first two bytes without the sign.
     * 
     * @see bytes12
     */
    [[nodiscard]] uint16_t address() const { return bytes12(); }
    /** When representing an instruction,
     * the function returns the index value of the instruction.
     * 
     * @return The value should be in [0, 6].
     */
    [[nodiscard]] uint8_t index() const { return byte3; }
    /** When representing an instruction,
     * the function returns the field value of the instruction.
     * 
     * @return The value should be in [0, 63].
     *         For most of the operations the default field value is 5.
     */
    [[nodiscard]] uint8_t field() const { return byte4; }
    /** When representing an instruction,
     * the function returns the type of operation of the instruction.
     * 
     * @return The value should be in [0, 63].
     */
    [[nodiscard]] uint8_t operation() const { return byte5; }

    /** When representing an instruction, set the address value. */
    void setAddress(int16_t address);
    /** When representing an instruction, set the address value. */
    void setAddress(bool _negative, uint16_t address);
    /** When representing an instruction, set the index value. */
    void setIndex(const uint8_t index) { byte3 = index; }
    /** When representing an instruction, set the field value. */
    void setField(const uint8_t field) { byte4 = field; }
    /** When representing an instruction, set the type of operation. */
    void setOperation(const uint8_t operation) { byte5 = operation; }

    /** Get the value with index in [1, 5].
     * 
     * @see operator[](int) const
     * 
     * @throw std::runtime_error when the index is not in [1, 5].
     */
    uint8_t getAt(const int32_t index) const { return (*this)[index]; }
    /** Get a UTF8 string represents the 5 characters in the word. */
    [[nodiscard]] std::string getCharacters() const;
    /**
     * Set the word with an integer.
     * 
     * The sign will be set only when the input is non-zero.
     * Therefore, to set the word to `-0` with this function,
     * one can set it with a negative value first, then set it to 0.
     * 
     * The least significant 30 bits will be saved to the word.
     * Each byte contains 6 bits. The byte5 will contain the least significant 6 bits. 
     */
    void set(int32_t value);
    /**
     * Set the word with a UTF8 string.
     * 
     * Only a subset of characters is allowed. The invalid characters with be replaced with spaces.
     * 
     * The sign will always be `+`.
     * 
     * @param chars UTF8 encoded string.
     * 
     * @throw std::runtime_error when the size of characters in the string is not 5.
     */
    void set(const std::string& chars);
    /**
     * Set specific byte with the given index in [1, 5].
     * 
     * @param index
     * @param val The behavior is undefined if it is greater than 63.
     * 
     * @throw std::runtime_error when the index is not in [1, 5].
     */
    void set(int index, uint8_t val);
    /** Set all the values. */
    void set(bool _negative, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5);
    /** Set all the values.
     * 
     * @throw std::runtime_error when the sign is neither '+' nor '-'.
     */
    void set(char sign, uint8_t _byte1, uint8_t _byte2, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5);
    /**
     *  Set all the values.
     * 
     * @param _negative
     * @param bytes12 Use the first two bytes to represent an integer within 4096.
     *                The behavior is undefined if the number can not be represented.
     * @param _byte3
     * @param _byte4
     * @param _byte5
     */
    void set(bool _negative, uint16_t bytes12, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5);
    /**
     *  Set all the values.
     * 
     * @param sign
     * @param bytes12 Use the first two bytes to represent an integer within 4096.
     *                The behavior is undefined if the number can not be represented.
     * @param _byte3
     * @param _byte4
     * @param _byte5
     *
     * @throw std::runtime_error when the sign is neither '+' nor '-'.
     */
    void set(char sign, uint16_t bytes12, uint8_t _byte3, uint8_t _byte4, uint8_t _byte5);
};

};  // namespace mixal


#endif  // INCLUDE_MEMORY_H_
