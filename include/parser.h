#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <string>
#include <stdexcept>

namespace mixal {

struct InstructionWord;

class ParseError : public std::exception {
 public:
    explicit ParseError(const std::string message) : _message(message) {}

    const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    std::string _message;
};

class Parser {
    static InstructionWord getWordFromLine(const std::string& line);
};

};  // namespace mixal

#endif  // INCLUDE_PARSER_H_
