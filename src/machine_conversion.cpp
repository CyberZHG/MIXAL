#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief Conversion operations.
 */

namespace mixal {

/** Convert chars in rA and rX to number, and save the result to rA.
 * 
 * @see overflow
 */
void Computer::executeNUM() {
    int64_t num = 0;
    for (int i = 1; i <= 5; ++i) {
        num = num * 10 + rA[i] % 10;
    }
    for (int i = 1; i <= 5; ++i) {
        num = num * 10 + rX[i] % 10;
    }
    bool negative = rA.negative;
    if (num >= (1 << 30)) {
        overflow = true;
        num %= (1 << 30);
    }
    rA.set(num);
    rA.negative = negative;
}

/** Convert number in rA to chars, and save the result to rA and rX. */
void Computer::executeCHAR() {
    int32_t num = std::abs(rA.value());
    for (int i = 5; i >= 1; --i) {
        rX[i] = 30 + num % 10;
        num /= 10;
    }
    for (int i = 5; i >= 1; --i) {
        rA[i] = 30 + num % 10;
        num /= 10;
    }
}

};  // namespace mixal
