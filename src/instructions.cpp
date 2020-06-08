#include "instructions.h"

mixal::Instructions::Code mixal::Instructions::getInstructionCode(const std::string& name) {
    switch (std::toupper(name[0])) {
    case 'L':
        switch (std::toupper(name[1])) {
        case 'D':
            switch (std::toupper(name[2])) {
            case 'A':
                return Instructions::LDA;
            case 'X':
                return Instructions::LDX;
            }
            break;
        }
        break;
    case 'N':
        switch (std::toupper(name[1])) {
        case 'O':
            switch (std::toupper(name[2])) {
            case 'P':
                return Instructions::NOP;
            }
            break;
        }
        break;
    }
    return Instructions::INVALID;
}
