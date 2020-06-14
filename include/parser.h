#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <string>
#include <stdexcept>
#include "instructions.h"
#include "expression.h"

namespace mixal {

class ParseError : public std::exception {
 public:
    explicit ParseError(int index, const std::string message) : _index(index), _message(message) {}

    inline int index() const { return _index; }

    const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _index;
    std::string _message;
};

enum class ParsedType {
    EMPTY,
    INSTRUCTION,
};

std::ostream& operator<<(std::ostream& os, ParsedType c);

struct ParsedResult {
    ParsedType parsedType;
    std::string location;
    std::string operation;
    std::string rawAddress;
    Expression address;
    std::string rawIndex;
    Expression index;
    std::string rawField;
    Expression field;
    InstructionWord word;
    std::string comment;

    ParsedResult() : parsedType(ParsedType::EMPTY), location(), operation(),
        rawAddress(), address(),
        rawIndex(), index(),
        rawField(), field(),
        word(), comment() {}
};

class Parser {
 public:
    static ParsedResult parseLine(const std::string& line, const std::string& lineSymbol, bool hasLocation = true);
};

};  // namespace mixal

#endif  // INCLUDE_PARSER_H_
