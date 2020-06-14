#ifndef INCLUDE_EXPRESSION_H_
#define INCLUDE_EXPRESSION_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace mixal {

class ExpressionError : public std::exception {
 public:
    explicit ExpressionError(int index, const std::string message) : _index(index), _message(message) {}

    inline int index() { return _index; }

    const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _index;
    std::string _message;
};

enum class AtomicType {
    INTEGER,
    SYMBOL,
    ASTERISK,
};

struct Atomic {
    AtomicType type;
    bool negative;
    int32_t integer;
    std::string symbol;

    Atomic() : type(AtomicType::INTEGER), negative(false), integer(), symbol() {}
    explicit Atomic(AtomicType _type, bool _negative = false) :
        type(_type), negative(_negative), integer(), symbol() {}
    Atomic(AtomicType _type, int32_t _value, bool _negative = false) :
        type(_type), negative(_negative), integer(_value), symbol() {}
    Atomic(AtomicType _type, const std::string& _value, bool _negative = false) :
        type(_type), negative(_negative), integer(), symbol(_value) {}
    Atomic(const Atomic& atomic) : type(atomic.type), negative(atomic.negative), integer(), symbol() {
        if (type == AtomicType::INTEGER) {
            integer = atomic.integer;
        } else {
            symbol = atomic.symbol;
        }
    }
    Atomic& operator=(const Atomic& atomic) {
        type = atomic.type;
        negative = atomic.negative;
        if (type == AtomicType::INTEGER) {
            integer = atomic.integer;
        } else {
            symbol = atomic.symbol;
        }
        return *this;
    }
};

struct AtomicValue {
    bool negative;
    int32_t value;

    AtomicValue() : negative(), value() {}
    explicit AtomicValue(int32_t _value) : negative(), value(_value) { negative = _value < 0; }
    AtomicValue(bool _negative, int32_t _value) : negative(_negative), value(_value) {}
    AtomicValue(const AtomicValue& atomicValue) : negative(atomicValue.negative), value(atomicValue.value) {}
    AtomicValue& operator=(const AtomicValue& atomicValue) {
        negative = atomicValue.negative;
        value = atomicValue.value;
        return *this;
    }
};

enum class Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    FLOOR_DIV,
    // FLOAT_DIV,
    FIELD,
};

class Expression {
 public:
    Expression() : _evaluated(false), _result(), _depends(), _atomics(), _operations() {}

    static Expression getConstExpression(const AtomicValue& value);

    inline bool evaluated() const { return _evaluated; }
    inline const AtomicValue& result() const { return _result; }

    inline const std::unordered_set<std::string> depends() const { return _depends; }
    inline const std::vector<Atomic> atomics() const { return _atomics; }
    inline const std::vector<Operation> operations() const { return _operations; }

    void parse(const std::string& expression, const std::string& lineSymbol);
    bool evaluate(const std::unordered_map<std::string, AtomicValue>& constants);

 private:
    bool _evaluated;
    AtomicValue _result;

    std::unordered_set<std::string> _depends;
    std::vector<Atomic> _atomics;
    std::vector<Operation> _operations;
};

};  // namespace mixal


#endif  // INCLUDE_EXPRESSION_H_
