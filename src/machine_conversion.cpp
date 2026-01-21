#include <iostream>
#include <cmath>
#include <limits>
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
    const bool negative = rA.negative;
    if (num >= (1 << 30)) {
        overflow = true;
        num %= (1 << 30);
    }
    rA.set(static_cast<int32_t>(num));
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

void Computer::executeFLOT() {
    rA.set(static_cast<double>(rA.value()));
}

void Computer::executeFIX() {
    const double value = rA.floatValue();
    if (value < static_cast<double>(std::numeric_limits<int32_t>::min())) {
        overflow = true;
        rA.set('+', 63, 63, 63, 63, 63);
        return;
    }
    if (value > static_cast<double>(std::numeric_limits<int32_t>::max())) {
        overflow = true;
        rA.set('-', 63, 63, 63, 63, 63);
        return;
    }
    rA.set(static_cast<int32_t>(round(rA.floatValue())));
    checkRange(rA.value());
}

}  // namespace mixal
