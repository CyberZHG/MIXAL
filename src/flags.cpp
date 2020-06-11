#include "flags.h"

namespace mixal {

std::ostream& operator<<(std::ostream& os, ComparisonIndicator c) {
    switch (c) {
    case ComparisonIndicator::LESS: os << "LESS"; break;
    case ComparisonIndicator::EQUAL: os << "EQUAL"; break;
    case ComparisonIndicator::GREATER: os << "GREATER"; break;
    }
    return os;
}

};  // namespace mixal
