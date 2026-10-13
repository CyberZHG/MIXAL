#include <cassert>
#include <cstdlib>
#include <limits>
#include <iostream>
#include "expression.h"

/**
 * @file
 * @brief The parsing and evaluation of expressions.
 */

namespace mixal {

Expression::Expression() : _evaluated(false), _literalConstant(false) {
}

Expression::Expression(const std::string& expression, const std::string& lineSymbol) :
    _evaluated(false), _literalConstant(false) {
    parse(expression, lineSymbol);
}

Expression Expression::getConstExpression(const AtomicValue& value) {
    auto expr = Expression();
    expr._evaluated = true;
    expr._result = value;
    expr._atomics.emplace_back(AtomicType::INTEGER, value.value);
    return expr;
}

Expression Expression::getConstExpression(const std::string& symbol) {
    auto expr = Expression();
    expr._atomics.emplace_back(AtomicType::SYMBOL, symbol);
    expr._depends.insert(symbol);
    return expr;
}

Expression Expression::getConstOffsetExpression(const std::string& symbol, int32_t offset) {
    auto expr = Expression();
    expr._atomics = {Atomic(AtomicType::SYMBOL, symbol), Atomic(AtomicType::INTEGER, offset)};
    expr._operations = {Operation::ADD};
    expr._depends.insert(symbol);
    return expr;
}

bool Expression::isValidFirst(char ch) {
    return isalnum(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '=';
}

bool Expression::isValidChar(char ch) {
    return isValidFirst(ch) || ch == '/' || ch == ':';
}

/** The states while parsing the expression.
 * 
 * ```
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
 * ```
 * 
 * However, multiple signs like `++` or `---` will be rejected as they are useless.
 */
enum class ExprParseState {
    START,      /**< The start state. */
    ATOMIC,     /**< Parsing the atomic. */
    OPERATION,  /**< Parsing the operation. */
    END,        /**< The end of parsing. */
};

/** Whether an operation can start with the given character. */
inline bool isOperationFirst(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ':';
}

void Expression::parse(const std::string& expression, const std::string& lineSymbol) {
    this->reset();
    const char END_CHAR = '#';  // The character that indicates the end of the input.
    constexpr int INIT_INDEX = -1;  // The uninitialized index value.
    auto state = ExprParseState::START;
    int lastAtomicStart = INIT_INDEX;     // The start index of the last atomic.
    int lastOperationStart = INIT_INDEX;  // The start index of the last operation.

    // Check whether this is a literal constant that starts and ends with a `=`.
    int start = 0;
    int exprLen = static_cast<int>(expression.size());
    if (exprLen > 2 && expression[0] == '=' && expression[exprLen - 1] == '=') {
        _literalConstant = true;
        start = 1;
        --exprLen;
    }
    if (expression.find_first_of(",(", start) < static_cast<size_t>(exprLen)) {
        parseWValue(expression.substr(start, exprLen - start), start, lineSymbol);
        return;
    }

    // Parsing the expression.
    for (int i = start; i <= exprLen; ++i) {
        char ch = i < exprLen ? expression[i] : END_CHAR;
        switch (state) {
        case ExprParseState::START:
            if (ch == '+' || ch == '-' || ch == '*' || isalnum(ch)) {
                state = ExprParseState::ATOMIC;
                lastAtomicStart = i;
            } else if (ch == END_CHAR) {
                throw ExpressionError(i, "The expression is empty.");
            } else {
                throw ExpressionError(i,
                    "Invalid character found at the start of the expression: " + std::string(1, ch));
            }
            break;

        case ExprParseState::ATOMIC:
            assert(lastAtomicStart != INIT_INDEX);
            if (expression[lastAtomicStart] == '*' ||
                (lastAtomicStart + 1 < i &&
                 (expression[lastAtomicStart] == '+' || expression[lastAtomicStart] == '-') &&
                 expression[lastAtomicStart + 1] == '*')) {
                // The atomic that matches `*`, `+*`, or `-*`.
                if (ch == END_CHAR) {
                    state = ExprParseState::END;
                } else if (isOperationFirst(ch)) {
                    state = ExprParseState::OPERATION;
                    lastOperationStart = i;
                } else {
                    throw ExpressionError(i,
                        "Invalid character found while trying to find an operation: " + std::string(1, ch));
                }
                const bool negative = expression[lastAtomicStart] == '-';
                _atomics.emplace_back(AtomicType::ASTERISK, lineSymbol, negative);
                _depends.insert(lineSymbol);
            } else if (isalnum(ch) ||
                ((expression[lastAtomicStart] == '+' || expression[lastAtomicStart] == '-') &&
                 lastAtomicStart + 1 == i && ch == '*')) {
            } else {
                if (ch == END_CHAR) {
                    state = ExprParseState::END;
                } else if (isOperationFirst(ch)) {
                    state = ExprParseState::OPERATION;
                    lastOperationStart = i;
                } else {
                    throw ExpressionError(i,
                        "Invalid character found while trying to find an operation: " + std::string(1, ch));
                }
                bool isInteger = true, negative = false;
                int32_t integerValue = 0;
                if (expression[lastAtomicStart] == '-') {
                    negative = true;
                    ++lastAtomicStart;
                } else if (expression[lastAtomicStart] == '+') {
                    ++lastAtomicStart;
                }
                if (lastAtomicStart == i) {
                    throw ExpressionError(i, "The atomic is empty: " +
                        std::to_string(expression[lastAtomicStart - 1]));
                }
                // Check the type of the atomic. Note that symbols can start with digits.
                for (int j = lastAtomicStart; j < i; ++j) {
                    if (isalpha(expression[j])) {
                        isInteger = false;
                        break;
                    }
                    const int32_t digit = expression[j] - '0';
                    if (integerValue > (std::numeric_limits<int32_t>::max() - digit) / 10) {
                        throw ExpressionError(i, "The integer value is too large: " +
                            expression.substr(lastAtomicStart, i - lastAtomicStart));
                    }
                    integerValue = integerValue * 10 + digit;
                }
                if (isInteger) {
                    _atomics.emplace_back(AtomicType::INTEGER, integerValue, negative);
                } else {
                    auto symbol = expression.substr(lastAtomicStart, i - lastAtomicStart);
                    _atomics.emplace_back(AtomicType::SYMBOL, symbol, negative);
                    _depends.insert(symbol);
                }
            }
            break;

        case ExprParseState::OPERATION:
            assert(lastOperationStart != INIT_INDEX);
            if (ch == '/') {
                // The `/` could be continuous for `//`.
            } else if (ch == END_CHAR) {
                throw ExpressionError(i, "No atomic found after the binary operator");
            } else {
                state = ExprParseState::ATOMIC;
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
                } else if (i - lastOperationStart == 2 && expression[lastOperationStart] == '/') {
                    _operations.emplace_back(Operation::FLOAT_DIV);
                } else {
                    throw ExpressionError(i, "Unknown binary operator found");
                }
            }
            break;

        case ExprParseState::END:
            break;
        }
    }
    // The parsing should always end with END state.
    assert(state == ExprParseState::END);
    // Since all the operations are binary, there should be exactly one more operations than atomics.
    assert(_atomics.size() == _operations.size() + 1);
}

void Expression::parseWValue(const std::string& expression, const int offset, const std::string& lineSymbol) {
    auto parsePart = [&](const std::string& part, const size_t partOffset) {
        try {
            return Expression(part, lineSymbol);
        } catch (const ExpressionError& e) {
            throw ExpressionError(offset + static_cast<int>(partOffset) + e.index(), e.what());
        }
    };
    size_t partStart = 0;
    while (partStart <= expression.size()) {
        size_t partEnd = expression.find(',', partStart);
        if (partEnd == std::string::npos) {
            partEnd = expression.size();
        }
        const std::string part = expression.substr(partStart, partEnd - partStart);
        const size_t open = part.find('(');
        if (open == std::string::npos) {
            _wValueExpressions.emplace_back(parsePart(part, partStart));
            _wValueFields.emplace_back(getConstExpression(AtomicValue(5)));
        } else {
            if (part.back() != ')' || part.find(')') != part.size() - 1) {
                throw ExpressionError(offset + static_cast<int>(partEnd), "Invalid field in W-value: " + part);
            }
            _wValueExpressions.emplace_back(parsePart(part.substr(0, open), partStart));
            _wValueFields.emplace_back(parsePart(part.substr(open + 1, part.size() - open - 2), partStart + open + 1));
        }
        _depends.insert(_wValueExpressions.back().depends().begin(), _wValueExpressions.back().depends().end());
        _depends.insert(_wValueFields.back().depends().begin(), _wValueFields.back().depends().end());
        partStart = partEnd + 1;
    }
}

bool Expression::evaluateWValue(const std::unordered_map<std::string, AtomicValue>& constants) {
    bool negative = false;
    int32_t bytes[6] = {};
    for (size_t i = 0; i < _wValueExpressions.size(); ++i) {
        auto& value = _wValueExpressions[i];
        auto& field = _wValueFields[i];
        if ((!value.evaluated() && !value.evaluate(constants)) || (!field.evaluated() && !field.evaluate(constants))) {
            return false;
        }
        const int32_t fieldValue = field.result().value;
        int32_t left = fieldValue / 8;
        const int32_t right = fieldValue % 8;
        if (fieldValue < 0 || left > right || right > 5) {
            throw ExpressionError(0, "Invalid field in W-value: " + std::to_string(fieldValue));
        }
        if (left == 0) {
            negative = value.result().negative;
            left = 1;
        }
        int32_t magnitude = std::abs(value.result().value);
        for (int32_t k = right; k >= left; --k) {
            bytes[k] = magnitude % 64;
            magnitude /= 64;
        }
    }
    int32_t magnitude = 0;
    for (int32_t k = 1; k <= 5; ++k) {
        magnitude = magnitude * 64 + bytes[k];
    }
    _result.negative = negative;
    _result.value = negative ? -magnitude : magnitude;
    _evaluated = true;
    return true;
}

bool Expression::evaluate(const std::unordered_map<std::string, AtomicValue>& constants) {
    if (isWValue()) {
        return evaluateWValue(constants);
    }
    if (_atomics.empty()) {
        return false;
    }
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
        case Operation::FLOAT_DIV:
            first.value = static_cast<int32_t>((static_cast<int64_t>(first.value) << 30) / second.value);
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

void Expression::replaceSymbol(const std::unordered_map<std::string, std::string>& mapping) {
    if (isWValue()) {
        _depends.clear();
        for (auto* parts : {&_wValueExpressions, &_wValueFields}) {
            for (auto& part : *parts) {
                part.replaceSymbol(mapping);
                _depends.insert(part.depends().begin(), part.depends().end());
            }
        }
        return;
    }
    for (auto& atomic : _atomics) {
        if (atomic.type == AtomicType::SYMBOL) {
            auto it = mapping.find(atomic.symbol);
            if (it != mapping.end()) {
                atomic.replaceSymbol(it->second);
                _depends.erase(it->first);
                _depends.insert(it->second);
            }
        }
    }
}

void Expression::reset() {
    _evaluated = false;
    _literalConstant = false;
    _depends.clear();
    _atomics.clear();
    _operations.clear();
    _wValueExpressions.clear();
    _wValueFields.clear();
}

bool Expression::operator==(const Expression& expression) const {
    if (_wValueExpressions != expression._wValueExpressions || _wValueFields != expression._wValueFields) {
        return false;
    }
    if (_atomics.size() != expression._atomics.size()) {
        return false;
    }
    for (size_t i = 0; i < _atomics.size(); ++i) {
        if (_atomics[i] != expression._atomics[i]) {
            return false;
        }
    }
    for (size_t i = 0; i < _operations.size(); ++i) {
        if (_operations[i] != expression._operations[i]) {
            return false;
        }
    }
    return true;
}

bool Expression::operator!=(const Expression& expression) const {
    return !((*this) == expression);
}

std::ostream& operator<<(std::ostream& out, Operation operation) {
    switch (operation) {
    case Operation::ADD: out << '+'; break;
    case Operation::SUBTRACT: out << '-'; break;
    case Operation::MULTIPLY: out << '*'; break;
    case Operation::FLOOR_DIV: out << '/'; break;
    case Operation::FLOAT_DIV: out << "//"; break;
    case Operation::FIELD: out << ':'; break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Expression& expression) {
    for (size_t i = 0; i < expression._wValueExpressions.size(); ++i) {
        if (i > 0) {
            out << ',';
        }
        out << expression._wValueExpressions[i] << '(' << expression._wValueFields[i] << ')';
    }
    if (!expression._atomics.empty()) {
        out << expression._atomics[0];
    }
    for (size_t i = 0; i < expression._operations.size(); ++i) {
        out << expression._operations[i];
        out << expression._atomics[i + 1];
    }
    return out;
}

}  // namespace mixal
