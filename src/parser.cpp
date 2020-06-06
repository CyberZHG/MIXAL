#include "parser.h"
#include "instructions.h"

namespace mixal {

enum class ParseStates {
    START,
    BEFORE_CODE,
    CODE,  // Instruction code
    AFTER_CODE,
};

InstructionWord Parser::getWordFromLine(const std::string& line) {
    const char END_CHAR = '#';
    InstructionWord instruction;
    auto state = ParseStates::START;
    for (size_t i = 0; i <= line.size(); ++i) {
        char ch = i < line.size() ? line[i] : END_CHAR;
        switch (state) {
        case ParseStates::START:
            if (ch == ' ') {
                state = ParseStates::BEFORE_CODE;
            } else {
                state = ParseStates::CODE;
            }
        case ParseStates::BEFORE_CODE:
            break;
        case ParseStates::CODE:
            break;
        case ParseStates::AFTER_CODE:
            break;
        }
    }
    return instruction;
}

};  // namespace mixal
