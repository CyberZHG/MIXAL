#include <stdexcept>
#include <string>
#include "registers.h"

namespace mixal {

uint8_t Register2::operator[](int index) const {
    if (index == 1) {
        return byte1;
    }
    if (index == 2) {
        return byte2;
    }
    throw std::runtime_error("Invalid index for a two bytes register: " + std::to_string(index));
}

uint16_t Register2::bytes12() const {
    int16_t high = static_cast<int16_t>(static_cast<uint8_t>(byte1));
    int16_t low = static_cast<int16_t>(static_cast<uint8_t>(byte2));
    return high * 64 + low;
}

int16_t Register2::value() const {
    int16_t val = static_cast<int16_t>(bytes12());
    return sign ? -val : val;
}

void Register2::set(int16_t value) {
    if (value > 0) {
        sign = 0;
    } else if (value < 0) {
        sign = 1;
        value = -value;
    }
    byte1 = static_cast<uint8_t>(value / (1 << 6));
    byte2 = static_cast<uint8_t>(value % (1 << 6));
}

void Register2::set(int index, int8_t val) {
    if (index == 1) {
        byte1 = val;
    } else if (index == 2) {
        byte2 = val;
    } else {
        throw std::runtime_error("Invalid index for a two bytes register: " + std::to_string(index));
    }
}

void Register2::set(bool negative, uint8_t byte1, uint8_t byte2) {
    this->sign = negative;
    this->byte1 = byte1;
    this->byte2 = byte2;
}

};  // namespace mixal
