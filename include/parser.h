#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

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

    /** Initialize the parsed result with empties. */
    ParsedResult() : parsedType(ParsedType::EMPTY),
        rawLocation(), location(),
        operation(),
        rawAddress(), address(),
        rawIndex(), index(),
        rawField(), field(),
        word(), comment() {}

    /** Evaluate base address, index, and field expressions. */
    bool evaluate(const std::unordered_map<std::string, AtomicValue>& constants);
    /** Whether the instruction has been evaluated. */
    bool evaluated() const;

    friend Parser;
    /** Output the instruction. */
    friend std::ostream& operator<<(std::ostream& out, const ParsedResult& result);

 private:
    /** Evaluate the base address expression. */
    bool evaluateAddress(const std::unordered_map<std::string, AtomicValue>& constants, int32_t index = 0);
    /** Evaluate the index expression. */
    bool evaluateIndex(const std::unordered_map<std::string, AtomicValue>& constants, int32_t index = 0);
    /** Evaluate the field expression. */
    bool evaluateField(const std::unordered_map<std::string, AtomicValue>& constants, int32_t index = 0);
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

};  // namespace mixal

#endif  // INCLUDE_PARSER_H_
