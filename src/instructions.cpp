#include "instructions.h"

namespace mixal {

bool Instructions::hasArguments(const Code code) {
    return !(code == NOP || code == HLT);
}

Instructions::Code Instructions::getInstructionCode(const std::string& name) {
    auto charAt = [&name] (const size_t index) -> char {
        return index < name.length() ? static_cast<char>(std::toupper(name[index])) : '#';
    };
    switch (charAt(0)) {
    case 'A':
        switch (charAt(1)) {
        case 'D':
            switch (charAt(2)) {
            case 'D':
                switch (charAt(3)) {
                case '#':
                    return ADD;
                }
                break;
            }
            break;
        case 'L':
            switch (charAt(2)) {
            case 'F':
                switch (charAt(3)) {
                case '#':
                    return ALF;
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
                        return CHAR;
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
                        return CMP1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return CMP2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return CMP3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return CMP4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return CMP5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return CMP6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return CMPA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return CMPX;
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
                    return CON;
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
                        return DEC1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return DEC2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return DEC3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return DEC4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return DEC5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return DEC6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return DECA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return DECX;
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
                    return DIV;
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
            case 'D':
                switch (charAt(3)) {
                case '#':
                    return END;
                }
                break;
            case 'N':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return ENN1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return ENN2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return ENN3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return ENN4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return ENN5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return ENN6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return ENNA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return ENNX;
                    }
                    break;
                }
                break;
            case 'T':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return ENT1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return ENT2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return ENT3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return ENT4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return ENT5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return ENT6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return ENTA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return ENTX;
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
                    return EQU;
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
                        return FADD;
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
                        return FCMP;
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
                        return FDIV;
                    }
                    break;
                }
                break;
            }
            break;
        case 'I':
            switch (charAt(2)) {
            case 'X':
                switch (charAt(3)) {
                case '#':
                    return NUM;
                }
                break;
            }
            break;
        case 'L':
            switch (charAt(2)) {
            case 'O':
                switch (charAt(3)) {
                case 'T':
                    switch (charAt(4)) {
                    case '#':
                        return NUM;
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
                        return FMUL;
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
                        return FSUB;
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
                    return HLT;
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
                return IN;
            case 'C':
                switch (charAt(3)) {
                case '1':
                    switch (charAt(4)) {
                    case '#':
                        return INC1;
                    }
                    break;
                case '2':
                    switch (charAt(4)) {
                    case '#':
                        return INC2;
                    }
                    break;
                case '3':
                    switch (charAt(4)) {
                    case '#':
                        return INC3;
                    }
                    break;
                case '4':
                    switch (charAt(4)) {
                    case '#':
                        return INC4;
                    }
                    break;
                case '5':
                    switch (charAt(4)) {
                    case '#':
                        return INC5;
                    }
                    break;
                case '6':
                    switch (charAt(4)) {
                    case '#':
                        return INC6;
                    }
                    break;
                case 'A':
                    switch (charAt(4)) {
                    case '#':
                        return INCA;
                    }
                    break;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return INCX;
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
                    return IOC;
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
                    return J1N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return J1NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return J1NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return J1NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return J1P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return J1Z;
                }
                break;
            }
            break;
        case '2':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return J2N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return J2NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return J2NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return J2NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return J2P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return J2Z;
                }
                break;
            }
            break;
        case '3':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return J3N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return J3NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return J3NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return J3NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return J3P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return J3Z;
                }
                break;
            }
            break;
        case '4':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return J4N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return J4NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return J4NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return J4NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return J4P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return J4Z;
                }
                break;
            }
            break;
        case '5':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return J5N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return J5NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return J5NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return J5NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return J5P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return J5Z;
                }
                break;
            }
            break;
        case '6':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return J6N;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return J6NN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return J6NP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return J6NZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return J6P;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return J6Z;
                }
                break;
            }
            break;
        case 'A':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return JAN;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return JANN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return JANP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return JANZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return JAP;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return JAZ;
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
                        return JBUS;
                    }
                    break;
                }
                break;
            }
            break;
        case 'E':
            switch (charAt(2)) {
            case '#':
                return JE;
            }
            break;
        case 'G':
            switch (charAt(2)) {
            case '#':
                return JG;
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return JGE;
                }
                break;
            }
            break;
        case 'L':
            switch (charAt(2)) {
            case '#':
                return JL;
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return JLE;
                }
                break;
            }
            break;
        case 'M':
            switch (charAt(2)) {
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return JMP;
                }
                break;
            }
            break;
        case 'N':
            switch (charAt(2)) {
            case 'E':
                switch (charAt(3)) {
                case '#':
                    return JNE;
                }
                break;
            case 'O':
                switch (charAt(3)) {
                case 'V':
                    switch (charAt(4)) {
                    case '#':
                        return JNOV;
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
                    return JOV;
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
                        return JRED;
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
                    return JSJ;
                }
                break;
            }
            break;
        case 'X':
            switch (charAt(2)) {
            case 'N':
                switch (charAt(3)) {
                case '#':
                    return JXN;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return JXNN;
                    }
                    break;
                case 'P':
                    switch (charAt(4)) {
                    case '#':
                        return JXNP;
                    }
                    break;
                case 'Z':
                    switch (charAt(4)) {
                    case '#':
                        return JXNZ;
                    }
                    break;
                }
                break;
            case 'P':
                switch (charAt(3)) {
                case '#':
                    return JXP;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return JXZ;
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
                    return LD1;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return LD1N;
                    }
                    break;
                }
                break;
            case '2':
                switch (charAt(3)) {
                case '#':
                    return LD2;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return LD2N;
                    }
                    break;
                }
                break;
            case '3':
                switch (charAt(3)) {
                case '#':
                    return LD3;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return LD3N;
                    }
                    break;
                }
                break;
            case '4':
                switch (charAt(3)) {
                case '#':
                    return LD4;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return LD4N;
                    }
                    break;
                }
                break;
            case '5':
                switch (charAt(3)) {
                case '#':
                    return LD5;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return LD5N;
                    }
                    break;
                }
                break;
            case '6':
                switch (charAt(3)) {
                case '#':
                    return LD6;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return LD6N;
                    }
                    break;
                }
                break;
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return LDA;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return LDAN;
                    }
                    break;
                }
                break;
            case 'X':
                switch (charAt(3)) {
                case '#':
                    return LDX;
                case 'N':
                    switch (charAt(4)) {
                    case '#':
                        return LDXN;
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
                        return MOVE;
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
                    return MUL;
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
                    return NOP;
                }
                break;
            }
            break;
        case 'U':
            switch (charAt(2)) {
            case 'M':
                switch (charAt(3)) {
                case '#':
                    return NUM;
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
                        return ORIG;
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
                    return OUT;
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
                    return SLA;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return SLAX;
                    }
                    break;
                }
                break;
            case 'C':
                switch (charAt(3)) {
                case '#':
                    return SLC;
                }
                break;
            }
            break;
        case 'R':
            switch (charAt(2)) {
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return SRA;
                case 'X':
                    switch (charAt(4)) {
                    case '#':
                        return SRAX;
                    }
                    break;
                }
                break;
            case 'C':
                switch (charAt(3)) {
                case '#':
                    return SRC;
                }
                break;
            }
            break;
        case 'T':
            switch (charAt(2)) {
            case '1':
                switch (charAt(3)) {
                case '#':
                    return ST1;
                }
                break;
            case '2':
                switch (charAt(3)) {
                case '#':
                    return ST2;
                }
                break;
            case '3':
                switch (charAt(3)) {
                case '#':
                    return ST3;
                }
                break;
            case '4':
                switch (charAt(3)) {
                case '#':
                    return ST4;
                }
                break;
            case '5':
                switch (charAt(3)) {
                case '#':
                    return ST5;
                }
                break;
            case '6':
                switch (charAt(3)) {
                case '#':
                    return ST6;
                }
                break;
            case 'A':
                switch (charAt(3)) {
                case '#':
                    return STA;
                }
                break;
            case 'J':
                switch (charAt(3)) {
                case '#':
                    return STJ;
                }
                break;
            case 'X':
                switch (charAt(3)) {
                case '#':
                    return STX;
                }
                break;
            case 'Z':
                switch (charAt(3)) {
                case '#':
                    return STZ;
                }
                break;
            }
            break;
        case 'U':
            switch (charAt(2)) {
            case 'B':
                switch (charAt(3)) {
                case '#':
                    return SUB;
                }
                break;
            }
            break;
        }
        break;
    }
    return INVALID;
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
        case 'I':
            switch (charAt(2)) {
            case 'X':
                switch (charAt(3)) {
                case '#':
                    return 7;
                }
                break;
            }
            break;
        case 'L':
            switch (charAt(2)) {
            case 'O':
                switch (charAt(3)) {
                case 'T':
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

int Instructions::getCost(const Code code, const uint8_t field) {
    switch (code) {
    case NOP: return 1;
    case ADD: return 2;
    case SUB: return 2;
    case MUL: return 10;
    case DIV: return 12;
    case NUM: return 10;
    case SLA: return 2;
    case MOVE: return 1 + field * 2;

    case LDA: return 2;
    case LD1: return 2;
    case LD2: return 2;
    case LD3: return 2;
    case LD4: return 2;
    case LD5: return 2;
    case LD6: return 2;
    case LDX: return 2;

    case LDAN: return 2;
    case LD1N: return 2;
    case LD2N: return 2;
    case LD3N: return 2;
    case LD4N: return 2;
    case LD5N: return 2;
    case LD6N: return 2;
    case LDXN: return 2;

    case STA: return 2;
    case ST1: return 2;
    case ST2: return 2;
    case ST3: return 2;
    case ST4: return 2;
    case ST5: return 2;
    case ST6: return 2;
    case STX: return 2;

    case STJ: return 2;
    case STZ: return 2;
    case JBUS: return 1;
    case IOC: return 1;
    case IN: return 1;
    case OUT: return 1;
    case JRED: return 1;
    case JMP: return 1;

    case JAN: return 1;
    case J1N: return 1;
    case J2N: return 1;
    case J3N: return 1;
    case J4N: return 1;
    case J5N: return 1;
    case J6N: return 1;
    case JXN: return 1;

    case INCA: return 1;
    case INC1: return 1;
    case INC2: return 1;
    case INC3: return 1;
    case INC4: return 1;
    case INC5: return 1;
    case INC6: return 1;
    case INCX: return 1;

    case CMPA: return 2;
    case CMP1: return 2;
    case CMP2: return 2;
    case CMP3: return 2;
    case CMP4: return 2;
    case CMP5: return 2;
    case CMP6: return 2;
    case CMPX: return 2;
    default: return 0;
    }
}

}  // namespace mixal
