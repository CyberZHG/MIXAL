#include <stdexcept>
#include <string>
#include "registers.h"

namespace mixal {

int8_t Register2::operator[](int index) const {
    if (index == 1) {
        return byte1;
    }
    if (index == 2) {
        return byte2;
    }
    throw std::runtime_error("Invalid index for a two bytes register: " + std::to_string(index));
}

int16_t Register2::bytes12() const {
    int16_t high = static_cast<int16_t>(static_cast<uint8_t>(byte1));
    int16_t low = static_cast<int16_t>(static_cast<uint8_t>(byte2));
    return high * 64 + low;
}

int16_t Register2::value() const {
    auto val = bytes12();
    return sign ? -val : val;
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

};  // namespace mixal
