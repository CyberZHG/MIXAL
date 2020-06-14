#ifndef INCLUDE_ERRORS_H_
#define INCLUDE_ERRORS_H_

#include <stdexcept>
#include <string>

namespace mixal {

class ExpressionError : public std::exception {
 public:
    explicit ExpressionError(int index, const std::string& message) : _index(index), _message(message) {}

    inline int index() const { return _index; }

    const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _index;
    std::string _message;
};

class ParseError : public std::exception {
 public:
    explicit ParseError(int index, const std::string& message) : _index(index), _message(message) {}

    inline int index() const { return _index; }

    const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _index;
    std::string _message;
};

class RuntimeError : public std::exception {
 public:
    explicit RuntimeError(int line, const std::string& message) : _line(line), _message(message) {}

    inline int line() const { return _line; }

    const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _line;
    std::string _message;
};

};  // namespace mixal


#endif  // INCLUDE_ERRORS_H_
