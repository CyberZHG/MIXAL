#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <string>
#include <stdexcept>
#include "instructions.h"

namespace mixal {

class ParseError : public std::exception {
 public:
    explicit ParseError(int index, const std::string message) : _index(index), _message(message) {}

    inline int index() { return _index; }

    const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _index;
    std::string _message;
};

class Parser {
 public:
    enum ParsedType {
        EMPTY,
        INSTRUCTION,
    };

    struct ParsedResult {
        ParsedType parsedType;
        std::string location;
        std::string operation;
        std::string address;
        InstructionWord word;
        std::string comment;

        ParsedResult() : parsedType(EMPTY), location(), operation(), address(), word(), comment() {}
    };

    static ParsedResult parseLine(const std::string& line, bool hasLocation = true);
};

};  // namespace mixal

#endif  // INCLUDE_PARSER_H_
