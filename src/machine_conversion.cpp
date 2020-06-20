#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::executeNUM() {
    int64_t num = 0;
    for (int i = 1; i <= 5; ++i) {
        num = num * 10 + rA[i] % 10;
    }
    for (int i = 1; i <= 5; ++i) {
        num = num * 10 + rX[i] % 10;
    }
    bool negative = rA.sign;
    if (num >= (1 << 30)) {
        overflow = true;
        num %= (1 << 30);
    }
    rA.set(num);
    rA.sign = negative;
}

void Machine::executeCHAR() {
    int32_t num = abs(rA.value());
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
