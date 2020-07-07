#ifndef INCLUDE_EXPRESSION_H_
#define INCLUDE_EXPRESSION_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "errors.h"

/**
 * @file
 * @brief To parse the expressions.
 */

namespace mixal {

/** Type of atomics. */
enum class AtomicType {
    INTEGER,   /**< A constant integer. */
    SYMBOL,    /**< A named symbol. */
    ASTERISK,  /**< The current location. */
};

/** Store the information about an atomic. */
struct Atomic {
    AtomicType type;     /**< The type of the atomic. */
    bool negative;       /**< The sign for the integer value. */
    int32_t integer;     /**< The absolute value part of the integer. */
    std::string symbol;  /**< The named symbol for the symbol and the current location. */

    /** Initialize the atomic with specific atomic type. */
    explicit Atomic(AtomicType _type = AtomicType::INTEGER, bool _negative = false);
    /** Initialize the atomic with an integer value. */
    Atomic(AtomicType _type, int32_t _value, bool _negative = false);
    /** Initialize the atomic with a symbol. */
    Atomic(AtomicType _type, const std::string& _value, bool _negative = false);
    /** Initialize the atomic with another atomic. */
    Atomic(const Atomic& atomic);

    /** Whether two atomics are the same. */
    bool operator==(const Atomic& atomic);
    /** Outputs the integer or the symbol based on the atomic type. */
    friend std::ostream& operator<<(std::ostream& out, const Atomic& atomic);

    /** Whether the symbol is a local symbol.
     * 
     * A local symbol has the form [0-9][HFB] (here, forward, backward).
     */
    static bool isLocalSymbol(const std::string& symbol);
    /**
     * Whether the atomic is a local symbol.
     * 
     * @see isLocalSymbol(const std::string&)
     */
    bool isLocalSymbol() const;
    /** Replace the symbol with the actual location.
     * 
     * If the symbol is `2B`, it should be replaced with the location of the nearest `2H`
     * before the current location.
     * 
     * If the symbol is `4F`, it should be replaced with the location of the nearest `4H`
     * after the current location.
     * 
     * @param symbol A temporary name representing the location that should be replaced to.
     */
    void replaceSymbol(const std::string& symbol);
};

/** The evaluated value of an atomic.
 * 
 * Note that the sign is only used to distinguish `+0` and `-0`.
 */
struct AtomicValue {
    bool negative;
    int32_t value;

    /** Initialize with `+0`. */
    AtomicValue();
    /** Initialize with an integer value. */
    explicit AtomicValue(int32_t _value);
    /** Initialize with an integer value and the sign. */
    AtomicValue(bool _negative, int32_t _value);
    /** Initialize with another atomic value. */
    AtomicValue(const AtomicValue& atomicValue);
    /** The copy assign operation. */
    AtomicValue& operator=(const AtomicValue& atomicValue);
};

enum class Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    FLOOR_DIV,
    // FLOAT_DIV,
    FIELD,
};

std::ostream& operator<<(std::ostream& out, Operation operation);

class Expression {
 public:
    Expression() : _evaluated(false), _result(), _literalConstant(false),
                   _depends(), _atomics(), _operations() {}

    static Expression getConstExpression(const AtomicValue& value);
    static Expression getConstExpression(const std::string& symbol);
    static Expression getConstOffsetExpression(const std::string& symbol, int32_t offset);
    static bool isValidFirst(char ch);
    static bool isValidChar(char ch);

    inline bool evaluated() const { return _evaluated; }
    inline const AtomicValue& result() const { return _result; }

    inline bool literalConstant() const { return _literalConstant; }

    inline const std::unordered_set<std::string> depends() const { return _depends; }
    inline const std::vector<Atomic> atomics() const { return _atomics; }
    inline const std::vector<Operation> operations() const { return _operations; }

    void parse(const std::string& expression, const std::string& lineSymbol);
    bool evaluate(const std::unordered_map<std::string, AtomicValue>& constants);

    friend std::ostream& operator<<(std::ostream& out, const Expression& expression);

    void replaceSymbol(const std::unordered_map<std::string, std::string>& mapping);

 private:
    bool _evaluated;
    AtomicValue _result;

    bool _literalConstant;

    std::unordered_set<std::string> _depends;
    std::vector<Atomic> _atomics;
    std::vector<Operation> _operations;
};

};  // namespace mixal


#endif  // INCLUDE_EXPRESSION_H_
