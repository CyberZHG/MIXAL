#include <cassert>
#include <iostream>
#include "expression.h"

namespace mixal {

Expression Expression::getConstExpression(const AtomicValue& value) {
    auto expr = Expression();
    expr._evaluated = true;
    expr._result = value;
    expr._atomics.emplace_back(Atomic(AtomicType::INTEGER, value.value));
    return expr;
}

enum class ParseState {
    /**
     * EXPRESSION -> + EXPRESSION
     *             | - EXPRESSION
     *             | EXPRESSION OPERATOR EXPRESSION
     *             | ATOMIC
     * OPERATOR -> + | - | * | / | // | :
     * ATOMIC -> INTEGER
     *         | SYMBOL
     *         | *
     * INTEGER -> DIGIT
     *          | DIGIT INTEGER
     * SYMBOL -> ALPHA
     *         | DIGIT
     *         | ALPHS SYMBOL
     *         | DIGIT SYMBOL
     * DIGIT -> [0-9]
     * ALPHA -> [A-Z]
     */
    START,
    ATOMIC,
    OPERATION,
    END,
};

inline bool isOperationFirst(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ':';
}

void Expression::parse(const std::string& expression, const std::string& lineSymbol) {
    const char END_CHAR = '#';
    const int INIT_INDEX = -1;
    ParseState state = ParseState::START;
    int lastAtomicStart = INIT_INDEX;
    int lastOperationStart = INIT_INDEX;
    _depends.clear();
    _atomics.clear();
    _operations.clear();
    for (int i = 0; i <= static_cast<int>(expression.size()); ++i) {
        char ch = i < static_cast<int>(expression.size()) ? expression[i] : END_CHAR;
        switch (state) {
        case ParseState::START:
            if (ch == '+' || ch == '-' || ch == '*' || isalnum(ch)) {
                state = ParseState::ATOMIC;
                lastAtomicStart = i;
            } else if (ch == END_CHAR) {
                throw ExpressionError(i, "Empty expression");
            } else {
                throw ExpressionError(i, "Invalid character found at the start of the expression");
            }
            break;
        case ParseState::ATOMIC:
            assert(lastAtomicStart != INIT_INDEX);
            if (expression[lastAtomicStart] == '*' ||
                (lastAtomicStart + 1 < i &&
                 (expression[lastAtomicStart] == '+' || expression[lastAtomicStart] == '-') &&
                 expression[lastAtomicStart + 1] == '*')) {
                if (ch == END_CHAR) {
                    state = ParseState::END;
                } else if (isOperationFirst(ch)) {
                    state = ParseState::OPERATION;
                    lastOperationStart = i;
                } else {
                    throw ExpressionError(i, "Invalid character found while finding operation");
                }
                bool negative = expression[lastAtomicStart] == '-';
                _atomics.emplace_back(Atomic(AtomicType::ASTERISK, lineSymbol, negative));
                _depends.insert(lineSymbol);
            } else if (isalnum(ch) ||
                ((expression[lastAtomicStart] == '+' || expression[lastAtomicStart] == '-') &&
                 lastAtomicStart + 1 == i && ch == '*')) {
            } else {
                if (ch == END_CHAR) {
                    state = ParseState::END;
                } else if (isOperationFirst(ch)) {
                    state = ParseState::OPERATION;
                    lastOperationStart = i;
                } else {
                    throw ExpressionError(i, "Invalid character found while finding operation");
                }
                bool isInteger = true, negative = false;
                int integerValue = 0;
                if (expression[lastAtomicStart] == '-') {
                    negative = true;
                    ++lastAtomicStart;
                } else if (expression[lastAtomicStart] == '+') {
                    ++lastAtomicStart;
                }
                if (lastAtomicStart == i) {
                    throw ExpressionError(i, "The atomic is empty");
                }
                for (int j = lastAtomicStart; j < i; ++j) {
                    if (isalpha(expression[j])) {
                        isInteger = false;
                        break;
                    }
                    integerValue = integerValue * 10 + (expression[j] - '0');
                }
                if (isInteger) {
                    _atomics.emplace_back(Atomic(AtomicType::INTEGER, integerValue, negative));
                } else {
                    auto symbol = expression.substr(lastAtomicStart, i - lastAtomicStart);
                    _atomics.emplace_back(Atomic(AtomicType::SYMBOL, symbol, negative));
                    _depends.insert(symbol);
                }
            }
            break;
        case ParseState::OPERATION:
            assert(lastOperationStart != INIT_INDEX);
            if (ch == '/') {
            } else if (ch == END_CHAR) {
                throw ExpressionError(i, "No atomic found after the binary operator");
            } else {
                state = ParseState::ATOMIC;
                lastAtomicStart = i;
                if (i - lastOperationStart == 1) {
                    switch (expression[lastOperationStart]) {
                    case '+':
                        _operations.emplace_back(Operation::ADD);
                        break;
                    case '-':
                        _operations.emplace_back(Operation::SUBTRACT);
                        break;
                    case '*':
                        _operations.emplace_back(Operation::MULTIPLY);
                        break;
                    case '/':
                        _operations.emplace_back(Operation::FLOOR_DIV);
                        break;
                    case ':':
                        _operations.emplace_back(Operation::FIELD);
                        break;
                    }
                } else {
                    throw ExpressionError(i, "Unknown binary operator found");
                }
            }
            break;
        case ParseState::END:
            assert(false);
        }
    }
    assert(state == ParseState::END);
    assert(_atomics.size() == _operations.size() + 1);
}

bool Expression::evaluate(const std::unordered_map<std::string, AtomicValue>& constants) {
    auto evalAtomic = [&constants](const Atomic& atomic, AtomicValue* result) -> bool {
        if (atomic.type == AtomicType::INTEGER) {
            result->negative = atomic.negative;
            result->value = atomic.integer;
            if (atomic.negative) {
                result->value = -result->value;
            }
        } else {
            auto it = constants.find(atomic.symbol);
            if (it == constants.end()) {
                return false;
            }
            *result = it->second;
            if (atomic.negative) {
                result->negative = !result->negative;
                result->value = -result->value;
            }
        }
        return true;
    };
    AtomicValue first, second;
    if (!evalAtomic(_atomics[0], &first)) {
        return false;
    }
    for (size_t i = 0; i < _operations.size(); ++i) {
        if (!evalAtomic(_atomics[i + 1], &second)) {
            return false;
        }
        switch (_operations[i]) {
        case Operation::ADD:
            first.value += second.value;
            break;
        case Operation::SUBTRACT:
            first.value -= second.value;
            break;
        case Operation::MULTIPLY:
            first.value *= second.value;
            break;
        case Operation::FLOOR_DIV:
            first.value /= second.value;
            break;
        case Operation::FIELD:
            first.value = first.value * 8 + second.value;
            break;
        }
        if (first.value > 0) {
            first.negative = false;
        } else if (first.value < 0) {
            first.negative = true;
        }
    }
    _evaluated = true;
    _result = first;
    return true;
}

};  // namespace mixal
