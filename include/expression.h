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
    /** Whether two atomics are different. */
    bool operator!=(const Atomic& atomic);
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
    /** Initialize with another atomic value. */
    AtomicValue(const AtomicValue& atomicValue);
    /** The copy assign operation. */
    AtomicValue& operator=(const AtomicValue& atomicValue);
};

/** Types of operations in expressions. */
enum class Operation {
    ADD,            /**< `+` */
    SUBTRACT,       /**< `-` */
    MULTIPLY,       /**< `*` */
    FLOOR_DIV,      /**< `/` */
    // FLOAT_DIV,   /**< `//` */
    FIELD,          /**< `a:b`, a * 8 + b. */
};

/** Output the symbol of the operation. */
std::ostream& operator<<(std::ostream& out, Operation operation);

/** Parse and store expressions. */
class Expression {
 public:
    /** Initialize with zeros. */
    Expression();
    /** Initialize with parsing
     * 
     * @see parse(const std::string&, const std::string&)
     */
    explicit Expression(const std::string& expression, const std::string& lineSymbol = "");

    /** Get a constant expression based on a given atomic value. */
    static Expression getConstExpression(const AtomicValue& value);
    /** Get a constant expression based on a given symbol.
     * 
     * The evaluation will depend on the given symbol.
     */
    static Expression getConstExpression(const std::string& symbol);
    /** Get a constant expression based on a given symbol and an offset.
     * 
     * This is used for representing the offset from an address.
     */
    static Expression getConstOffsetExpression(const std::string& symbol, int32_t offset);
    /** Whether an expression can start with the given character.
     * 
     * The first character could be:
     * - `[0-9A-Z]`, for symbols.
     * - `*`, for current location.
     * - `[+-]`, for the sign of an atomic.
     * - `=`, for literal constant.
     */
    static bool isValidFirst(char ch);
    /** Whether a character is valid inside an expression.
     * 
     * Besides the valid characters at the beginning,
     * the rest characters in the operations are also valid: `/` and `:`.
     * 
     * @see isValidFirst(char)
     */
    static bool isValidChar(char ch);

    /** Whether the expression has been evaluated. */
    inline bool evaluated() const { return _evaluated; }
    /** Get the evaluated atomic value. */
    inline const AtomicValue& result() const { return _result; }

    /** Whether this is a literal constant, which is surrounded by `=`. */
    inline bool literalConstant() const { return _literalConstant; }

    /** Get the symbols that should be evaluated before evaluating this expression. */
    inline const std::unordered_set<std::string> depends() const { return _depends; }
    /** Get the atomics in the expression. */
    inline const std::vector<Atomic> atomics() const { return _atomics; }
    /** Get the operations in the expression. */
    inline const std::vector<Operation> operations() const { return _operations; }

    /** Try to parse an expression string.
     * 
     * @param expression A string containing only the expression.
     * @param lineSymbol The symbol representing the current location.
     *                   Used for `*` to point to the current location.
     * 
     * @throw ExpressionError When the input expression string is invalid.
     */
    void parse(const std::string& expression, const std::string& lineSymbol);
    /** Try to evaluate the parsed expression.
     * 
     * @param constants A dictionary that maps from symbol names to evaluated atomic values.
     * 
     * @return Return true if the expression can be evaluated with the given dictionary.
     */
    bool evaluate(const std::unordered_map<std::string, AtomicValue>& constants);

    /** Output the expression. */
    friend std::ostream& operator<<(std::ostream& out, const Expression& expression);

    /** Replace the symbols in the expression.
     * 
     * This is used for replacing local symbols.
     */
    void replaceSymbol(const std::unordered_map<std::string, std::string>& mapping);

    /** Clear the parsed results. */
    void reset();

    /** Whether two expressions are the same. */
    bool operator==(const Expression& expression);
    /** Whether two expressions are different. */
    bool operator!=(const Expression& expression);

 private:
    bool _evaluated;      /**< Whether the expression has been evaluated. */
    AtomicValue _result;  /**< The evaluated atomic value. */

    bool _literalConstant;  /**< Whether this is a literal constant. */

    std::unordered_set<std::string> _depends;  /**< The symbols in the expression. */
    std::vector<Atomic> _atomics;              /**< The atomics in the expression. */
    std::vector<Operation> _operations;        /**< The operations in the expression. */
};

};  // namespace mixal


#endif  // INCLUDE_EXPRESSION_H_
