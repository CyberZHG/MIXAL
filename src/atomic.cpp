#include <iostream>
#include "expression.h"

namespace mixal {

Atomic::Atomic(const AtomicType _type, const bool _negative) :
        type(_type), negative(_negative), integer() {}

Atomic::Atomic(const AtomicType _type, const int32_t _value, const bool _negative) :
    type(_type), negative(_negative), integer(_value) {}

Atomic::Atomic(const AtomicType _type, const std::string& _value, const bool _negative) :
    type(_type), negative(_negative), integer(), symbol(_value) {}

bool Atomic::operator==(const Atomic& atomic) const {
    if (type != atomic.type) {
        return false;
    }
    if (type == AtomicType::INTEGER) {
        return integer == atomic.integer;
    }
    return negative == atomic.negative && symbol == atomic.symbol;
}

bool Atomic::operator!=(const Atomic& atomic) const {
    return !((*this) == atomic);
}

std::ostream& operator<<(std::ostream& out, const Atomic& atomic) {
    switch (atomic.type) {
    case AtomicType::INTEGER:
        out << atomic.integer;
        break;
    case AtomicType::SYMBOL:
    case AtomicType::ASTERISK:
        out << atomic.symbol;
        break;
    }
    return out;
}

bool Atomic::isLocalSymbol(const std::string& symbol) {
    return symbol.size() == 2 &&
           ('0' <= symbol[0] && symbol[0] <= '9') &&
           (symbol[1] == 'H' || symbol[1] == 'F' || symbol[1] == 'B');
}

bool Atomic::isLocalSymbol() const {
    return type == AtomicType::SYMBOL && isLocalSymbol(symbol);
}

void Atomic::replaceSymbol(const std::string& _symbol) {
    symbol = _symbol;
}

AtomicValue::AtomicValue() : negative(), value() {}

AtomicValue::AtomicValue(const int32_t _value) : negative(), value(_value) {
    negative = _value < 0;
}

AtomicValue::AtomicValue(const AtomicValue& atomicValue) = default;

AtomicValue& AtomicValue::operator=(const AtomicValue& atomicValue) = default;

};  // namespace mixal
