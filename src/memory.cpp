#include <stdexcept>
#include <string>
#include <iostream>
#include "memory.h"

namespace mixal {

int8_t ComputerWord::operator[](int index) const {
    if (index <= 0 || index > 5) {
        throw std::runtime_error("Invalid index for a word: " + std::to_string(index));
    }
    switch (index) {
    case 1: return byte1;
    case 2: return byte2;
    case 3: return byte3;
    case 4: return byte4;
    default: return byte5;
    }
}

int16_t ComputerWord::bytes12() const {
    int16_t high = static_cast<int16_t>(static_cast<uint8_t>(byte1));
    int16_t low = static_cast<int16_t>(static_cast<uint8_t>(byte2));
    return high * 64 + low;
}

int16_t ComputerWord::bytes34() const {
    int16_t high = static_cast<int16_t>(static_cast<uint8_t>(byte3));
    int16_t low = static_cast<int16_t>(static_cast<uint8_t>(byte4));
    return high * 64 + low;
}

void ComputerWord::set(int index, int8_t val) {
    if (index <= 0 || index > 5) {
        throw std::runtime_error("Invalid index for a word: " + std::to_string(index));
    }
    switch (index) {
    case 1: byte1 = val; break;
    case 2: byte2 = val; break;
    case 3: byte3 = val; break;
    case 4: byte4 = val; break;
    default: byte5 = val;
    }
}

void ComputerWord::set(bool negative, int8_t byte1, int8_t byte2, int8_t byte3, int8_t byte4, int8_t byte5) {
    this->sign = static_cast<int>(negative);
    this->byte1 = byte1;
    this->byte2 = byte2;
    this->byte3 = byte3;
    this->byte4 = byte4;
    this->byte5 = byte5;
}

void ComputerWord::set(bool negative, int16_t bytes12, int8_t byte3, int8_t byte4, int8_t byte5) {
    this->sign = static_cast<int>(negative);
    this->byte1 = static_cast<int8_t>(bytes12 / 64);
    this->byte2 = static_cast<int8_t>(bytes12 % 64);
    this->byte3 = byte3;
    this->byte4 = byte4;
    this->byte5 = byte5;
}

};  // namespace mixal
