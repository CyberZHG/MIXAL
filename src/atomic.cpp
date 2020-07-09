#include <iostream>
#include "expression.h"

namespace mixal {

Atomic::Atomic(AtomicType _type, bool _negative) :
        type(_type), negative(_negative), integer(), symbol() {}

Atomic::Atomic(AtomicType _type, int32_t _value, bool _negative) :
    type(_type), negative(_negative), integer(_value), symbol() {}

Atomic::Atomic(AtomicType _type, const std::string& _value, bool _negative) :
    type(_type), negative(_negative), integer(), symbol(_value) {}

Atomic::Atomic(const Atomic& atomic) :
    type(atomic.type), negative(atomic.negative), integer(), symbol() {
    if (type == AtomicType::INTEGER) {
        integer = atomic.integer;
    } else {
        symbol = atomic.symbol;
    }
}

bool Atomic::operator==(const Atomic& atomic) {
    if (type != atomic.type || negative != atomic.negative) {
        return false;
    }
    return type == AtomicType::INTEGER ? integer == atomic.integer : symbol == atomic.symbol;
}

bool Atomic::operator!=(const Atomic& atomic) {
    return !((*this) == atomic);
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

AtomicValue::AtomicValue() : negative(), value() {}

AtomicValue::AtomicValue(int32_t _value) : negative(), value(_value) {
    negative = _value < 0;
}

AtomicValue::AtomicValue(const AtomicValue& atomicValue) :
    negative(atomicValue.negative), value(atomicValue.value) {
}

AtomicValue& AtomicValue::operator=(const AtomicValue& atomicValue) {
    negative = atomicValue.negative;
    value = atomicValue.value;
    return *this;
}

};  // namespace mixal
