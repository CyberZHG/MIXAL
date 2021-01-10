#include <stdexcept>
#include <string>
#include "registers.h"

namespace mixal {

Register2::Register2() : negative(), byte1(), byte2() {
}

Register2::Register2(const int16_t value) : negative(), byte1(), byte2() {
    set(value);
}

Register2::Register2(const bool _negative, const uint8_t _byte1, const uint8_t _byte2) :
    negative(_negative), byte1(_byte1), byte2(_byte2) {
}

Register2::Register2(const char sign, const uint8_t _byte1, const uint8_t _byte2) :
    negative(sign == '-'), byte1(_byte1), byte2(_byte2) {
    if (sign != '+' && sign != '-') {
        throw std::runtime_error("Invalid sign: " + std::string(1, sign));
    }
}

uint8_t Register2::operator[](const int index) const {
    if (index == 1) {
        return byte1;
    }
    if (index == 2) {
        return byte2;
    }
    throw std::runtime_error("Invalid index for a two bytes register: " + std::to_string(index));
}

uint16_t Register2::bytes12() const {
    const int16_t high = static_cast<uint8_t>(byte1);
    const int16_t low = static_cast<uint8_t>(byte2);
    return high * 64 + low;
}

int16_t Register2::value() const {
    const int16_t val = static_cast<int16_t>(bytes12());
    return negative ? -val : val;
}

std::string Register2::getBytesString() const {
    std::string result;
    result += negative ? '-' : '+';
    for (int i = 1; i <= 2; ++i) {
        result += ' ';
        if ((*this)[i] < 10) {
            result += ' ';
        }
        result += std::to_string((*this)[i]);
    }
    return result;
}

void Register2::set(int16_t value) {
    if (value > 0) {
        negative = false;
    } else if (value < 0) {
        negative = true;
        value = -value;
    }
    byte1 = static_cast<uint8_t>(value / (1 << 6));
    byte2 = static_cast<uint8_t>(value % (1 << 6));
}

void Register2::set(const int index, const int8_t val) {
    if (index == 1) {
        byte1 = val;
    } else if (index == 2) {
        byte2 = val;
    } else {
        throw std::runtime_error("Invalid index for a two bytes register: " + std::to_string(index));
    }
}

void Register2::set(const bool _negative, const uint8_t _byte1, const uint8_t _byte2) {
    this->negative = _negative;
    this->byte1 = _byte1;
    this->byte2 = _byte2;
}

void Register2::set(const char sign, const uint8_t _byte1, const uint8_t _byte2) {
    if (sign != '+' && sign != '-') {
        throw std::runtime_error("Invalid sign: " + std::string(1, sign));
    }
    this->negative = sign == '-';
    this->byte1 = _byte1;
    this->byte2 = _byte2;
}

};  // namespace mixal
