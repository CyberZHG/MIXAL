#ifndef INCLUDE_ERRORS_H_
#define INCLUDE_ERRORS_H_

#include <stdexcept>
#include <string>

/**
 * @file
 * @brief The definition of some errors.
 */

namespace mixal {

/** Errors encountered while parsing an expression. */
class ExpressionError final : public std::exception {
 public:
    /** Initialize error with offset and message. */
    explicit ExpressionError(int index, const std::string& message) : _index(index), _message(message) {}

    /** The offset in the expression string. */
    [[nodiscard]] int index() const { return _index; }

    /** The error information. */
    [[nodiscard]] const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _index;  /**< The offset in the expression string. */
    std::string _message;  /**< The error information. */
};

/** Errors encountered while parsing codes. */
class ParseError final : public std::exception {
 public:
    /** Initialize error with offset and message. */
    explicit ParseError(const int index, const std::string& message) : _index(index), _message(message) {}

    /** The offset in the string of code. */
    [[nodiscard]] int index() const { return _index; }

    /** The error information. */
    [[nodiscard]] const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _index;  /**< The offset in the string of code. */
    std::string _message;  /**< The error information. */
};

/** Errors encountered while executing the codes. */
class RuntimeError final : public std::exception {
 public:
    /** Initialize error with line number and message. */
    explicit RuntimeError(const int line, const std::string& message) : _line(line), _message(message) {}

    /** The location of memory that is executing. */
    [[nodiscard]] int line() const { return _line; }

    /** The error information. */
    [[nodiscard]] const char* what() const noexcept override {
        return _message.c_str();
    }
 private:
    int _line;  /**< The location of memory that is executing. */
    std::string _message;  /**< The error information. */
};

};  // namespace mixal


#endif  // INCLUDE_ERRORS_H_
