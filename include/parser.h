#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <string>
#include <stdexcept>
#include <unordered_map>
#include "instructions.h"
#include "expression.h"
#include "memory.h"
#include "errors.h"

namespace mixal {

enum class ParsedType {
    EMPTY,
    INSTRUCTION,
    PSEUDO,
};

std::ostream& operator<<(std::ostream& os, ParsedType c);

class Parser;

class ParsedResult {
 public:
    ParsedType parsedType;
    std::string rawLocation;
    Expression location;
    std::string operation;
    std::string rawAddress;
    Expression address;
    std::string rawIndex;
    Expression index;
    std::string rawField;
    Expression field;
    ComputerWord word;
    std::string comment;

    ParsedResult() : parsedType(ParsedType::EMPTY),
        rawLocation(), location(),
        operation(),
        rawAddress(), address(),
        rawIndex(), index(),
        rawField(), field(),
        word(), comment() {}

    bool evaluate(const std::unordered_map<std::string, AtomicValue>& constants);
    bool evaluated() const;

    friend Parser;
    friend std::ostream& operator<<(std::ostream& out, const ParsedResult& result);

 private:
    bool evaluateAddress(const std::unordered_map<std::string, AtomicValue>& constants, int32_t index = 0);
    bool evaluateIndex(const std::unordered_map<std::string, AtomicValue>& constants, int32_t index = 0);
    bool evaluateField(const std::unordered_map<std::string, AtomicValue>& constants, int32_t index = 0);
};

class Parser {
 public:
    static ParsedResult parseLine(const std::string& line, const std::string& lineSymbol, bool hasLocation = true);
};

};  // namespace mixal

#endif  // INCLUDE_PARSER_H_
