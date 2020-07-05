#include <iostream>
#include "expression.h"

namespace mixal {

bool Atomic::operator==(const Atomic& atomic) {
    if (type != atomic.type || negative != atomic.negative) {
        return false;
    }
    return type == AtomicType::INTEGER ? integer == atomic.integer : symbol == atomic.symbol;
}

std::ostream& operator<<(std::ostream& out, const Atomic& atomic) {
    switch (atomic.type) {
    case AtomicType::INTEGER: out << atomic.integer; break;
    case AtomicType::SYMBOL: out << atomic.symbol; break;
    case AtomicType::ASTERISK: out << atomic.symbol; break;
    }
    return out;
}

bool Atomic::isLocalSymbol(const std::string& symbol) {
    return symbol.size() == 2 &&
           ('0' <= symbol[0] && symbol[0] <= '9') &&
           (symbol[1] == 'H' || symbol[1] == 'F' || symbol[1] == 'B');
}

bool Atomic::isLocalSymbol() const {
    return type == AtomicType::SYMBOL && Atomic::isLocalSymbol(symbol);
}

void Atomic::replaceSymbol(const std::string& symbol) {
    this->symbol = symbol;
}

};  // namespace mixal
