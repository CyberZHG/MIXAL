#include <cassert>
#include <iostream>
#include "parser.h"
#include "instructions.h"

namespace mixal {

enum class ParseState {
    // LOC OP ADDRESS,I(F)
    START,
    LOC,
    BEFORE_OP,
    OP,
    BEFORE_ADDRESS,
    NUMERICAL_ADDRESS_NEGATIVE,
    NUMERICAL_ADDRESS,
    BEFORE_INDEX,
    INDEX,
    MOD_OPEN,
    MOD_FIRST,
    MOD_CONNECTION,
    MOD_SECOND,
    MOD_CLOSE,
    BEFORE_COMMENT,
    COMMENT,
    END,
};

#ifdef __DEBUG__
std::ostream& operator<<(std::ostream& os, ParseState c) {
    switch (c) {
    case ParseState::START: os << "START"; break;
    case ParseState::LOC: os << "LOC"; break;
    case ParseState::BEFORE_OP: os << "BEFORE_OP"; break;
    case ParseState::OP: os << "OP"; break;
    case ParseState::BEFORE_ADDRESS: os << "BEFORE_ADDRESS"; break;
    case ParseState::NUMERICAL_ADDRESS_NEGATIVE: os << "NUMERICAL_ADDRESS_NEGATIVE"; break;
    case ParseState::NUMERICAL_ADDRESS: os << "NUMERICAL_ADDRESS"; break;
    case ParseState::BEFORE_INDEX: os << "BEFORE_INDEX"; break;
    case ParseState::INDEX: os << "INDEX"; break;
    case ParseState::MOD_OPEN: os << "MOD_OPEN"; break;
    case ParseState::MOD_FIRST: os << "MOD_FIRST"; break;
    case ParseState::MOD_CONNECTION: os << "MOD_CONNECTION"; break;
    case ParseState::MOD_SECOND: os << "MOD_SECOND"; break;
    case ParseState::MOD_CLOSE: os << "MOD_CLOSE"; break;
    case ParseState::BEFORE_COMMENT: os << "BEFORE_COMMENT"; break;
    case ParseState::COMMENT: os << "COMMENT"; break;
    case ParseState::END: os << "END"; break;
    }
    return os;
}
#endif  // __DEBUG__

inline bool isDigit(char ch) {
    return ('0' <= ch && ch <= '9');
}

inline bool isAlpha(char ch) {
    return ('A' <= ch && ch <= 'Z') || isDigit(ch);
}

int subStr2Decimal(const std::string& s, int start, int stop) {
    int decimal = 0;
    bool negative = false;
    if (s[start] == '-') {
        negative = true;
        ++start;
    }
    for (int i = start; i < stop; ++i) {
        decimal = decimal * 10 + static_cast<int>(s[i] - '0');
    }
    return negative ? -decimal : decimal;
}

Parser::ParsedResult Parser::parseLine(const std::string& line, bool hasLocation) {
    const char END_CHAR = '#';
    const int INIT_INDEX = -1;
    ParsedResult result;
    result.parsedType = ParsedType::INSTRUCTION;
    auto state = hasLocation ? ParseState::START : ParseState::BEFORE_OP;
    int locationStart = INIT_INDEX,
        operationStart = INIT_INDEX,
        addressStart = INIT_INDEX,
        indexStart = INIT_INDEX,
        modFirst = INIT_INDEX, modSecond = INIT_INDEX,
        commentStart = INIT_INDEX;
    for (int i = 0; i <= static_cast<int>(line.size()); ++i) {
        char ch = i < static_cast<int>(line.size()) ? line[i] : END_CHAR;
        switch (state) {
        case ParseState::START:
            if (ch == ' ') {
                state = ParseState::BEFORE_OP;
            } else if (ch == '*') {
                state = ParseState::COMMENT;
                result.parsedType = ParsedType::EMPTY;
                commentStart = i;
            } else {
                state = ParseState::LOC;
                locationStart = i;
            }
            break;
        case ParseState::LOC:
            if (ch == ' ') {
                state = ParseState::BEFORE_OP;
                result.location = line.substr(locationStart, i - locationStart);
            } else if (!isAlpha(ch)) {
                throw ParseError(i, "Unexpected character encountered while parsing location");
            }
            break;
        case ParseState::BEFORE_OP:
            if (ch == ' ') {
                continue;
            } else if (ch == END_CHAR) {
                if (locationStart != INIT_INDEX) {
                    throw ParseError(i, "No operation found after location");
                }
                state = ParseState::END;
                result.parsedType = ParsedType::EMPTY;
            } else if (isAlpha(ch)) {
                state = ParseState::OP;
                operationStart = i;
            } else {
                throw ParseError(i, "Unexpected character encountered while finding operation");
            }
            break;
        case ParseState::OP:
            if (ch == ' ' || ch == END_CHAR) {
                if (ch == ' ') {
                    state = ParseState::BEFORE_ADDRESS;
                } else {
                    state = ParseState::END;
                }
                result.operation = line.substr(operationStart, i - operationStart);
                result.word.operation = static_cast<int>(Instructions::getInstructionCode(result.operation));
            } else if (!isAlpha(ch)) {
                throw ParseError(i, "Unexpected character encountered while parsing operation");
            }
            break;
        case ParseState::BEFORE_ADDRESS:
            if (ch == ' ') {
                continue;
            } else if (ch == END_CHAR) {
                state = ParseState::END;
            } else if (isDigit(ch)) {
                state = ParseState::NUMERICAL_ADDRESS;
                addressStart = i;
            } else if (ch == '-') {
                state = ParseState::NUMERICAL_ADDRESS_NEGATIVE;
                addressStart = i;
            } else {
                throw ParseError(i, "Unexpected character encountered while finding address");
            }
            break;
        case ParseState::NUMERICAL_ADDRESS_NEGATIVE:
            if (ch == END_CHAR) {
                throw ParseError(i, "No valid address found after operation");
            } else if (isDigit(ch)) {
                state = ParseState::NUMERICAL_ADDRESS;
            } else {
                throw ParseError(i, "Unexpected character encountered while parsing address");
            }
            break;
        case ParseState::NUMERICAL_ADDRESS:
            if (ch == ' ' || ch == ',' || ch == '(' || ch == END_CHAR) {
                if (ch == ' ') {
                    state = ParseState::BEFORE_COMMENT;
                } else if (ch == ',') {
                    state = ParseState::BEFORE_INDEX;
                } else if (ch == '(') {
                    state = ParseState::MOD_OPEN;
                } else {
                    state = ParseState::END;
                }
                if (ch == ' ' || ch == END_CHAR) {
                    result.address = line.substr(addressStart, i - addressStart);
                }
                result.word.address = subStr2Decimal(line, addressStart, i);
            } else if (!isDigit(ch)) {
                throw ParseError(i, "Unexpected character encountered while parsing numeric address");
            }
            break;
        case ParseState::BEFORE_INDEX:
            if (isDigit(ch)) {
                state = ParseState::INDEX;
                indexStart = i;
            } else if (ch == END_CHAR) {
                throw ParseError(i, "No index found after comma");
            } else {
                throw ParseError(i, "Unexpected character encountered while finding index");
            }
            break;
        case ParseState::INDEX:
            if (ch == ' ' || ch == '(' || ch == END_CHAR) {
                if (ch == ' ') {
                    state = ParseState::BEFORE_COMMENT;
                } else if (ch == '(') {
                    state = ParseState::MOD_OPEN;
                } else {
                    state = ParseState::END;
                }
                if (ch == ' ' || ch == END_CHAR) {
                    result.address = line.substr(addressStart, i - addressStart);
                }
                result.word.index = subStr2Decimal(line, indexStart, i);
            } else if (!isDigit(ch)) {
                throw ParseError(i, "Unexpected character encountered while parsing index");
            }
            break;
        case ParseState::MOD_OPEN:
            if (isDigit(ch)) {
                state = ParseState::MOD_FIRST;
                modFirst = static_cast<int>(ch - '0');
            } else {
                throw ParseError(i, "Unexpected character encountered while parsing modification");
            }
            break;
        case ParseState::MOD_FIRST:
            if (ch == ':') {
                state = ParseState::MOD_CONNECTION;
            } else {
                throw ParseError(i, "Unexpected character encountered while parsing modification");
            }
            break;
        case ParseState::MOD_CONNECTION:
            if (isDigit(ch)) {
                state = ParseState::MOD_SECOND;
                modSecond = static_cast<int>(ch - '0');
                result.word.modification = modFirst * 8 + modSecond;
            } else {
                throw ParseError(i, "Unexpected character encountered while parsing modification");
            }
            break;
        case ParseState::MOD_SECOND:
            if (ch == ')') {
                state = ParseState::MOD_CLOSE;
            } else {
                throw ParseError(i, "Unexpected character encountered while parsing modification");
            }
            break;
        case ParseState::MOD_CLOSE:
            if (ch == ' ' || ch == END_CHAR) {
                if (ch == ' ') {
                    state = ParseState::BEFORE_COMMENT;
                } else {
                    state = ParseState::END;
                }
                result.address = line.substr(addressStart, i - addressStart);
            } else {
                throw ParseError(i, "Unexpected character encountered while parsing digital modification");
            }
            break;
        case ParseState::BEFORE_COMMENT:
            if (ch == END_CHAR) {
                state = ParseState::END;
            } else if (ch != ' ') {
                state = ParseState::COMMENT;
                commentStart = i;
            }
            break;
        case ParseState::COMMENT:
            if (ch == END_CHAR) {
                state = ParseState::END;
                result.comment = line.substr(commentStart, i - commentStart);
            }
            break;
        case ParseState::END:
            assert(false);
        }
    }
    assert(state == ParseState::END);
    return result;
}

};  // namespace mixal
