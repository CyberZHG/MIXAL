#ifndef INCLUDE_FLAGS_H_
#define INCLUDE_FLAGS_H_

#include <iostream>

/**
 * @file
 * @brief The definition of special flags.
 */

namespace mixal {

/** The result of a comparision. */
enum class ComparisonIndicator {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1,
};

/** Output the name of comparision. */
std::ostream& operator<<(std::ostream& os, ComparisonIndicator c);

};  // namespace mixal


#endif  // INCLUDE_FLAGS_H_
