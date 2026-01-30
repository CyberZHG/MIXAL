#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <cstdint>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include "instructions.h"
#include "expression.h"
#include "memory.h"
#include "errors.h"

/**
 * @file
 * @brief Parse one line of code.
 */

namespace mixal {

/** Type of the parsed instruction. */
enum class ParsedType {
    EMPTY,         /**< No instruction, empty or comment only. */
    INSTRUCTION,   /**< Actual instruction that can be interpreted as a computer word. */
    PSEUDO,        /**< Pseudo instruction that can not be converted to a operation field. */
};

/** A span representing a token's position in the source line. */
struct TokenSpan {
    int32_t start;  /**< Start index (inclusive). -1 if not present. */
    int32_t end;    /**< End index (exclusive). -1 if not present. */

    TokenSpan() : start(-1), end(-1) {}
    TokenSpan(const int32_t s, const int32_t e) : start(s), end(e) {}

    /** Whether this span is valid (token exists). */
    [[nodiscard]] bool valid() const { return start >= 0 && end >= 0; }
};

/** Output the name of a parsed type. */
std::ostream& operator<<(std::ostream& os, ParsedType c);

class Parser;

/** The parsed result. */
class ParsedResult {
 public:
    ParsedType parsedType;    /**< Type of the parsed result. */
    std::string rawLocation;  /**< Raw string of the location name. */
    Expression location;      /**< The location expression. */
    std::string operation;    /**< Raw string of the operation name. */
    std::string rawAddress;   /**< Raw string of the base address. */
    Expression address;       /**< The parsed base address expression. */
    std::string rawIndex;     /**< Raw string of the index. */
    Expression index;         /**< The parsed index expression. */
    std::string rawField;     /**< Raw string of the field. */
    Expression field;         /**< The parsed field expression. */
    ComputerWord word;        /**< The converted computer word that represents the instruction. */
    std::string comment;      /**< The comments. */

    // Token spans for syntax highlighting
    TokenSpan locationSpan;   /**< Span of the location token. */
    TokenSpan operationSpan;  /**< Span of the operation token. */
    TokenSpan addressSpan;    /**< Span of the address token. */
    TokenSpan indexSpan;      /**< Span of the index token. */
    TokenSpan fieldSpan;      /**< Span of the field token (including parentheses). */
    TokenSpan commentSpan;    /**< Span of the comment. */

    /** Initialize the parsed result with empties. */
    ParsedResult() : parsedType(ParsedType::EMPTY) {}

    /** Evaluate base address, index, and field expressions. */
    bool evaluate(const std::unordered_map<std::string, AtomicValue>& constants);
    /** Whether the instruction has been evaluated. */
    [[nodiscard]] bool evaluated() const;

    friend Parser;
    /** Output the instruction. */
    friend std::ostream& operator<<(std::ostream& out, const ParsedResult& result);

 private:
    /** Evaluate the base address expression. */
    bool evaluateAddress(const std::unordered_map<std::string, AtomicValue>& constants, int32_t _index = 0);
    /** Evaluate the index expression. */
    bool evaluateIndex(const std::unordered_map<std::string, AtomicValue>& constants, int32_t _index = 0);
    /** Evaluate the field expression. */
    bool evaluateField(const std::unordered_map<std::string, AtomicValue>& constants, int32_t _index = 0);
};

class Parser {
 public:
    /** Parse one line of code.
     * 
     * @param line The code.
     * @param lineSymbol @see mixal::Expression
     * @param hasLocation Whether the code should have the location part.
     */
    static ParsedResult parseLine(const std::string& line, const std::string& lineSymbol, bool hasLocation = true);
};

}  // namespace mixal

#endif  // INCLUDE_PARSER_H_
