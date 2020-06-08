#include "instructions.h"

mixal::Instructions::Code mixal::Instructions::getInstructionCode(const std::string& name) {
    auto charAt = [&name] (size_t index) -> char {
        return index < name.length() ? std::toupper(name[index]) : '#';
    };
    switch (charAt(0)) {
    case 'L':
        switch (charAt(1)) {
        case 'D':
            switch (charAt(2)) {
            case '1':
                switch (charAt(3)) {
                case '#':
                    return Instructions::LD1;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::LD1N;
                    }
                    break;
                }
                break;
            case '2':
                switch (charAt(3)) {
                case '#':
                    return Instructions::LD2;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::LD2N;
                    }
                    break;
                }
                break;
            case '3':
                switch (charAt(3)) {
                case '#':
                    return Instructions::LD3;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::LD3N;
                    }
                    break;
                }
                break;
            case '4':
                switch (charAt(3)) {
                case '#':
                    return Instructions::LD4;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::LD4N;
                    }
                    break;
                }
                break;
            case '5':
                switch (charAt(3)) {
                case '#':
                    return Instructions::LD5;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::LD5N;
                    }
                    break;
                }
                break;
            case '6':
                switch (charAt(3)) {
                case '#':
                    return Instructions::LD6;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::LD6N;
                    }
                    break;
                }
                break;
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return Instructions::LDA;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::LDAN;
                    }
                    break;
                }
                break;
            case 'X':
                switch (charAt(3)) {
                case '#':
                    return Instructions::LDX;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::LDXN;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 'N':
        switch (charAt(1)) {
        case 'O':
            switch (charAt(2)) {
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::NOP;
                }
                break;
            }
            break;
        }
        break;
    case 'S':
        switch (charAt(1)) {
        case 'T':
            switch (charAt(2)) {
            case '1':
                switch (charAt(3)) {
                case '#':
                    return Instructions::ST1;
                }
                break;
            case '2':
                switch (charAt(3)) {
                case '#':
                    return Instructions::ST2;
                }
                break;
            case '3':
                switch (charAt(3)) {
                case '#':
                    return Instructions::ST3;
                }
                break;
            case '4':
                switch (charAt(3)) {
                case '#':
                    return Instructions::ST4;
                }
                break;
            case '5':
                switch (charAt(3)) {
                case '#':
                    return Instructions::ST5;
                }
                break;
            case '6':
                switch (charAt(3)) {
                case '#':
                    return Instructions::ST6;
                }
                break;
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return Instructions::STA;
                }
                break;
            case 'X':
                switch (charAt(3)) {
                case '#':
                    return Instructions::STX;
                }
                break;
            }
            break;
        }
        break;
    }
    return Instructions::INVALID;
}
