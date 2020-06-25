#include "instructions.h"

namespace mixal {

Instructions::Code Instructions::getInstructionCode(const std::string& name) {
    auto charAt = [&name] (size_t index) -> char {
        return index < name.length() ? std::toupper(name[index]) : '#';
    };
    switch (charAt(0)) {
    case 'A':
        switch (charAt(1)) {
        case 'D':
            switch (charAt(2)) {
            case 'D':
                switch (charAt(3)) {
                case '#':
                    return Instructions::ADD;
                }
                break;
            }
            break;
        }
        break;
    case 'C':
        switch (charAt(1)) {
        case 'H':
            switch (charAt(2)) {
            case 'A':
                switch (charAt(3)) {
                case 'R':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CHAR;
                    }
                    break;
                }
                break;
            }
            break;
        case 'M':
            switch (charAt(2)) {
            case 'P':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CMP1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CMP2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CMP3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CMP4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CMP5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CMP6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CMPA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::CMPX;
                    }
                    break;
                }
                break;
            }
            break;
        case 'O':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::CON;
                }
                break;
            }
            break;
        }
        break;
    case 'D':
        switch (charAt(1)) {
        case 'E':
            switch (charAt(2)) {
            case 'C':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::DEC1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::DEC2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::DEC3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::DEC4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::DEC5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::DEC6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::DECA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::DECX;
                    }
                    break;
                }
                break;
            }
            break;
        case 'I':
            switch (charAt(2)) {
            case 'V':
                switch (charAt(3)) {
                case '#':
                    return Instructions::DIV;
                }
                break;
            }
            break;
        }
        break;
    case 'E':
        switch (charAt(1)) {
        case 'N':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENN1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENN2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENN3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENN4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENN5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENN6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENNA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENNX;
                    }
                    break;
                }
                break;
            case 'T':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENT1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENT2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENT3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENT4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENT5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENT6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENTA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ENTX;
                    }
                    break;
                }
                break;
            }
            break;
        case 'Q':
            switch (charAt(2)) {
            case 'U':
                switch (charAt(3)) {
                case '#':
                    return Instructions::EQU;
                }
                break;
            }
            break;
        }
        break;
    case 'F':
        switch (charAt(1)) {
        case 'A':
            switch (charAt(2)) {
            case 'D':
                switch (charAt(3)) {
                case 'D':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::FADD;
                    }
                    break;
                }
                break;
            }
            break;
        case 'C':
            switch (charAt(2)) {
            case 'M':
                switch (charAt(3)) {
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::FCMP;
                    }
                    break;
                }
                break;
            }
            break;
        case 'D':
            switch (charAt(2)) {
            case 'I':
                switch (charAt(3)) {
                case 'V':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::FDIV;
                    }
                    break;
                }
                break;
            }
            break;
        case 'M':
            switch (charAt(2)) {
            case 'U':
                switch (charAt(3)) {
                case 'L':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::FMUL;
                    }
                    break;
                }
                break;
            }
            break;
        case 'S':
            switch (charAt(2)) {
            case 'U':
                switch (charAt(3)) {
                case 'B':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::FSUB;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 'H':
        switch (charAt(1)) {
        case 'L':
            switch (charAt(2)) {
            case 'T':
                switch (charAt(3)) {
                case '#':
                    return Instructions::HLT;
                }
                break;
            }
            break;
        }
        break;
    case 'I':
        switch (charAt(1)) {
        case 'N':
            switch (charAt(2)) {
            case '#':
                return Instructions::IN;
            case 'C':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::INC1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::INC2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::INC3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::INC4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::INC5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::INC6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::INCA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::INCX;
                    }
                    break;
                }
                break;
            }
            break;
        case 'O':
            switch (charAt(2)) {
            case 'C':
                switch (charAt(3)) {
                case '#':
                    return Instructions::IOC;
                }
                break;
            }
            break;
        }
        break;
    case 'J':
        switch (charAt(1)) {
        case '1':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J1N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J1NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J1NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J1NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J1P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J1Z;
                }
                break;
            }
            break;
        case '2':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J2N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J2NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J2NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J2NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J2P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J2Z;
                }
                break;
            }
            break;
        case '3':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J3N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J3NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J3NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J3NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J3P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J3Z;
                }
                break;
            }
            break;
        case '4':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J4N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J4NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J4NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J4NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J4P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J4Z;
                }
                break;
            }
            break;
        case '5':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J5N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J5NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J5NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J5NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J5P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J5Z;
                }
                break;
            }
            break;
        case '6':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J6N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J6NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J6NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::J6NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J6P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::J6Z;
                }
                break;
            }
            break;
        case 'A':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JAN;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JANN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JANP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JANZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JAP;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JAZ;
                }
                break;
            }
            break;
        case 'B':
            switch (charAt(2)) {
            case 'U':
                switch (charAt(3)) {
                case 'S':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JBUS;
                    }
                    break;
                }
                break;
            }
            break;
        case 'E':
            switch (charAt(2)) {
            case '#':
                return Instructions::JE;
            }
            break;
        case 'G':
            switch (charAt(2)) {
            case '#':
                return Instructions::JG;
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JGE;
                }
                break;
            }
            break;
        case 'L':
            switch (charAt(2)) {
            case '#':
                return Instructions::JL;
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JLE;
                }
                break;
            }
            break;
        case 'M':
            switch (charAt(2)) {
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JMP;
                }
                break;
            }
            break;
        case 'N':
            switch (charAt(2)) {
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JNE;
                }
                break;
            case 'O':
                switch (charAt(3)) {
                case 'V':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JNOV;
                    }
                    break;
                }
                break;
            }
            break;
        case 'O':
            switch (charAt(2)) {
            case 'V':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JOV;
                }
                break;
            }
            break;
        case 'R':
            switch (charAt(2)) {
            case 'E':
                switch (charAt(3)) {
                case 'D':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JRED;
                    }
                    break;
                }
                break;
            }
            break;
        case 'S':
            switch (charAt(2)) {
            case 'J':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JSJ;
                }
                break;
            }
            break;
        case 'X':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JXN;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JXNN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JXNP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::JXNZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JXP;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::JXZ;
                }
                break;
            }
            break;
        }
        break;
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
    case 'M':
        switch (charAt(1)) {
        case 'O':
            switch (charAt(2)) {
            case 'V':
                switch (charAt(3)) {
                case 'E':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::MOVE;
                    }
                    break;
                }
                break;
            }
            break;
        case 'U':
            switch (charAt(2)) {
            case 'L':
                switch (charAt(3)) {
                case '#':
                    return Instructions::MUL;
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
        case 'U':
            switch (charAt(2)) {
            case 'M':
                switch (charAt(3)) {
                case '#':
                    return Instructions::NUM;
                }
                break;
            }
            break;
        }
        break;
    case 'O':
        switch (charAt(1)) {
        case 'R':
            switch (charAt(2)) {
            case 'I':
                switch (charAt(3)) {
                case 'G':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::ORIG;
                    }
                    break;
                }
                break;
            }
            break;
        case 'U':
            switch (charAt(2)) {
            case 'T':
                switch (charAt(3)) {
                case '#':
                    return Instructions::OUT;
                }
                break;
            }
            break;
        }
        break;
    case 'S':
        switch (charAt(1)) {
        case 'L':
            switch (charAt(2)) {
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return Instructions::SLA;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::SLAX;
                    }
                    break;
                }
                break;
            case 'C':
                switch (charAt(3)) {
                case '#':
                    return Instructions::SLC;
                }
                break;
            }
            break;
        case 'R':
            switch (charAt(2)) {
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return Instructions::SRA;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return Instructions::SRAX;
                    }
                    break;
                }
                break;
            case 'C':
                switch (charAt(3)) {
                case '#':
                    return Instructions::SRC;
                }
                break;
            }
            break;
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
            case 'J':
                switch (charAt(3)) {
                case '#':
                    return Instructions::STJ;
                }
                break;
            case 'X':
                switch (charAt(3)) {
                case '#':
                    return Instructions::STX;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return Instructions::STZ;
                }
                break;
            }
            break;
        case 'U':
            switch (charAt(2)) {
            case 'B':
                switch (charAt(3)) {
                case '#':
                    return Instructions::SUB;
                }
                break;
            }
            break;
        }
        break;
    }
    return Instructions::INVALID;
}

int Instructions::getDefaultField(const std::string& name) {
    auto charAt = [&name] (size_t index) -> char {
        return index < name.length() ? std::toupper(name[index]) : '#';
    };
    switch (charAt(0)) {
    case 'C':
        switch (charAt(1)) {
        case 'H':
            switch (charAt(2)) {
            case 'A':
                switch (charAt(3)) {
                case 'R':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 'D':
        switch (charAt(1)) {
        case 'E':
            switch (charAt(2)) {
            case 'C':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return 1;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 'E':
        switch (charAt(1)) {
        case 'N':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                }
                break;
            case 'T':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 'F':
        switch (charAt(1)) {
        case 'A':
            switch (charAt(2)) {
            case 'D':
                switch (charAt(3)) {
                case 'D':
                    switch (charAt(4)) {
                    case '#':
                        return 6;
                    }
                    break;
                }
                break;
            }
            break;
        case 'C':
            switch (charAt(2)) {
            case 'M':
                switch (charAt(3)) {
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 6;
                    }
                    break;
                }
                break;
            }
            break;
        case 'D':
            switch (charAt(2)) {
            case 'I':
                switch (charAt(3)) {
                case 'V':
                    switch (charAt(4)) {
                    case '#':
                        return 6;
                    }
                    break;
                }
                break;
            }
            break;
        case 'M':
            switch (charAt(2)) {
            case 'U':
                switch (charAt(3)) {
                case 'L':
                    switch (charAt(4)) {
                    case '#':
                        return 6;
                    }
                    break;
                }
                break;
            }
            break;
        case 'S':
            switch (charAt(2)) {
            case 'U':
                switch (charAt(3)) {
                case 'B':
                    switch (charAt(4)) {
                    case '#':
                        return 6;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 'H':
        switch (charAt(1)) {
        case 'L':
            switch (charAt(2)) {
            case 'T':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            }
            break;
        }
        break;
    case 'I':
        switch (charAt(1)) {
        case 'N':
            switch (charAt(2)) {
            case 'C':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return 0;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return 0;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return 0;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return 0;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return 0;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return 0;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return 0;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return 0;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case 'J':
        switch (charAt(1)) {
        case '1':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 5;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return 4;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        case '2':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 5;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return 4;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        case '3':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 5;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return 4;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        case '4':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 5;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return 4;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        case '5':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 5;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return 4;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        case '6':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 5;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return 4;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        case 'A':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 5;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return 4;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        case 'E':
            switch (charAt(2)) {
            case '#':
                return 5;
            }
            break;
        case 'G':
            switch (charAt(2)) {
            case '#':
                return 6;
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return 7;
                }
                break;
            }
            break;
        case 'L':
            switch (charAt(2)) {
            case '#':
                return 4;
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return 9;
                }
                break;
            }
            break;
        case 'M':
            switch (charAt(2)) {
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 0;
                }
                break;
            }
            break;
        case 'N':
            switch (charAt(2)) {
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return 8;
                }
                break;
            case 'O':
                switch (charAt(3)) {
                case 'V':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                }
                break;
            }
            break;
        case 'O':
            switch (charAt(2)) {
            case 'V':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            }
            break;
        case 'S':
            switch (charAt(2)) {
            case 'J':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        case 'X':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return 5;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return 4;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return 1;
                }
                break;
            }
            break;
        }
        break;
    case 'N':
        switch (charAt(1)) {
        case 'U':
            switch (charAt(2)) {
            case 'M':
                switch (charAt(3)) {
                case '#':
                    return 0;
                }
                break;
            }
            break;
        }
        break;
    case 'S':
        switch (charAt(1)) {
        case 'L':
            switch (charAt(2)) {
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return 0;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return 2;
                    }
                    break;
                }
                break;
            case 'C':
                switch (charAt(3)) {
                case '#':
                    return 4;
                }
                break;
            }
            break;
        case 'R':
            switch (charAt(2)) {
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return 1;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return 3;
                    }
                    break;
                }
                break;
            case 'C':
                switch (charAt(3)) {
                case '#':
                    return 5;
                }
                break;
            }
            break;
        case 'T':
            switch (charAt(2)) {
            case 'J':
                switch (charAt(3)) {
                case '#':
                    return 2;
                }
                break;
            }
            break;
        }
        break;
    }
    return -1;
}

int Instructions::getCost(Instructions::Code code, uint8_t field) {
    switch (code) {
    case Instructions::NOP: return 1;
    case Instructions::ADD: return 2;
    case Instructions::SUB: return 2;
    case Instructions::MUL: return 10;
    case Instructions::DIV: return 12;
    case Instructions::NUM: return 10;
    case Instructions::SLA: return 2;
    case Instructions::MOVE: return 1 + field * 2;

    case Instructions::LDA: return 2;
    case Instructions::LD1: return 2;
    case Instructions::LD2: return 2;
    case Instructions::LD3: return 2;
    case Instructions::LD4: return 2;
    case Instructions::LD5: return 2;
    case Instructions::LD6: return 2;
    case Instructions::LDX: return 2;

    case Instructions::LDAN: return 2;
    case Instructions::LD1N: return 2;
    case Instructions::LD2N: return 2;
    case Instructions::LD3N: return 2;
    case Instructions::LD4N: return 2;
    case Instructions::LD5N: return 2;
    case Instructions::LD6N: return 2;
    case Instructions::LDXN: return 2;

    case Instructions::STA: return 2;
    case Instructions::ST1: return 2;
    case Instructions::ST2: return 2;
    case Instructions::ST3: return 2;
    case Instructions::ST4: return 2;
    case Instructions::ST5: return 2;
    case Instructions::ST6: return 2;
    case Instructions::STX: return 2;

    case Instructions::STJ: return 2;
    case Instructions::STZ: return 2;
    case Instructions::JBUS: return 1;
    case Instructions::IOC: return 1;
    case Instructions::IN: return 1;
    case Instructions::OUT: return 1;
    case Instructions::JRED: return 1;
    case Instructions::JMP: return 1;

    case Instructions::JAN: return 1;
    case Instructions::J1N: return 1;
    case Instructions::J2N: return 1;
    case Instructions::J3N: return 1;
    case Instructions::J4N: return 1;
    case Instructions::J5N: return 1;
    case Instructions::J6N: return 1;
    case Instructions::JXN: return 1;

    case Instructions::INCA: return 1;
    case Instructions::INC1: return 1;
    case Instructions::INC2: return 1;
    case Instructions::INC3: return 1;
    case Instructions::INC4: return 1;
    case Instructions::INC5: return 1;
    case Instructions::INC6: return 1;
    case Instructions::INCX: return 1;

    case Instructions::CMPA: return 2;
    case Instructions::CMP1: return 2;
    case Instructions::CMP2: return 2;
    case Instructions::CMP3: return 2;
    case Instructions::CMP4: return 2;
    case Instructions::CMP5: return 2;
    case Instructions::CMP6: return 2;
    case Instructions::CMPX: return 2;
    default: return 0;
    }
}

};  // namespace mixal
