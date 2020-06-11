#ifndef INCLUDE_FLAGS_H_
#define INCLUDE_FLAGS_H_

#include <iostream>

namespace mixal {

enum class ComparisonIndicator {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1,
};

std::ostream& operator<<(std::ostream& os, ComparisonIndicator c);

};  // namespace mixal


#endif  // INCLUDE_FLAGS_H_
