#ifndef INCLUDE_INSTRUCTIONS_H_
#define INCLUDE_INSTRUCTIONS_H_

#include <cstdint>
#include <string>

namespace mixal {

class Instructions {
 public:
    enum Code {
        INVALID = -1,
        NOP = 0,    // no operation
        ADD = 1,    // add
        FADD = 1,   // float add (6)
        SUB = 2,    // subtract
        FSUB = 2,   // float subtract (6)
        MUL = 3,    // multiply
        FMUL = 3,   // float multiply (6)
        DIV = 4,    // divide
        FDIV = 4,   // float divide (6)
        NUM = 5,    // convert to numeric (0)
        CHAR = 5,   // convert to characters (1)
        HLT = 5,    // halt (2)
        SLA = 6,    // shift left A (0)
        SRA = 6,    // shift right A (1)
        SLAX = 6,   // shift left AX (2)
        SRAX = 6,   // shift right AX (3)
        SLC = 6,    // shift left AX circularly (4)
        SRC = 6,    // shift right AX circularly (5)
        MOVE = 7,   // move
        LDA = 8,    // load A
        LD1 = 9,    // load I1
        LD2 = 10,   // load I2
        LD3 = 11,   // load I3
        LD4 = 12,   // load I4
        LD5 = 13,   // load I5
        LD6 = 14,   // load I6
        LDX = 15,   // load X
        LDAN = 16,  // load A negative
        LD1N = 17,  // load I1 negative
        LD2N = 18,  // load I2 negative
        LD3N = 19,  // load I3 negative
        LD4N = 20,  // load I4 negative
        LD5N = 21,  // load I5 negative
        LD6N = 22,  // load I6 negative
        LDXN = 23,  // load X
        STA = 24,   // store A
        ST1 = 25,   // store I1
        ST2 = 26,   // store I2
        ST3 = 27,   // store I3
        ST4 = 28,   // store I4
        ST5 = 29,   // store I5
        ST6 = 30,   // store I6
        STX = 31,   // store X
        STJ = 32,   // store J
        STZ = 33,   // store zero
        JBUS = 34,  // jump busy
        IOC = 35,   // input-output control
        IN = 36,    // input
        OUT = 37,   // output
        JRED = 38,  // jump ready
        JMP = 39,   // jump (0)
        JSJ = 39,   // jump, save J (1)
        JOV = 39,   // jump on overflow (2)
        JNOV = 39,  // jump on no overflow (3)
        JL = 39,    // jump on less (4)
        JE = 39,    // jump on equal (5)
        JG = 39,    // jump on greater (6)
        JGE = 39,   // jump on greater-or-equal (7)
        JNE = 39,   // jump on unequal (8)
        JLE = 39,   // jump on less-or-equal (9)
        JAN = 40,   // jump A negative (0)
        JAZ = 40,   // jump A zero (1)
        JAP = 40,   // jump A positive (2)
        JANN = 40,  // jump A nonnegative (3)
        JANZ = 40,  // jump A nonzero (4)
        JANP = 40,  // jump A nonpositive (5)
        J1N = 41,   // jump I1 negative (0)
        J1Z = 41,   // jump I1 zero (1)
        J1P = 41,   // jump I1 positive (2)
        J1NN = 41,  // jump I1 nonnegative (3)
        J1NZ = 41,  // jump I1 nonzero (4)
        J1NP = 41,  // jump I1 nonpositive (5)
        J2N = 42,   // jump I2 negative (0)
        J2Z = 42,   // jump I2 zero (1)
        J2P = 42,   // jump I2 positive (2)
        J2NN = 42,  // jump I2 nonnegative (3)
        J2NZ = 42,  // jump I2 nonzero (4)
        J2NP = 42,  // jump I2 nonpositive (5)
        J3N = 43,   // jump I3 negative (0)
        J3Z = 43,   // jump I3 zero (1)
        J3P = 43,   // jump I3 positive (2)
        J3NN = 43,  // jump I3 nonnegative (3)
        J3NZ = 43,  // jump I3 nonzero (4)
        J3NP = 43,  // jump I3 nonpositive (5)
        J4N = 44,   // jump I4 negative (0)
        J4Z = 44,   // jump I4 zero (1)
        J4P = 44,   // jump I4 positive (2)
        J4NN = 44,  // jump I4 nonnegative (3)
        J4NZ = 44,  // jump I4 nonzero (4)
        J4NP = 44,  // jump I4 nonpositive (5)
        J5N = 45,   // jump I5 negative (0)
        J5Z = 45,   // jump I5 zero (1)
        J5P = 45,   // jump I5 positive (2)
        J5NN = 45,  // jump I5 nonnegative (3)
        J5NZ = 45,  // jump I5 nonzero (4)
        J5NP = 45,  // jump I5 nonpositive (5)
        J6N = 46,   // jump I6 negative (0)
        J6Z = 46,   // jump I6 zero (1)
        J6P = 46,   // jump I6 positive (2)
        J6NN = 46,  // jump I6 nonnegative (3)
        J6NZ = 46,  // jump I6 nonzero (4)
        J6NP = 46,  // jump I6 nonpositive (5)
        JXN = 47,   // jump X negative (0)
        JXZ = 47,   // jump X zero (1)
        JXP = 47,   // jump X positive (2)
        JXNN = 47,  // jump X nonnegative (3)
        JXNZ = 47,  // jump X nonzero (4)
        JXNP = 47,  // jump X nonpositive (5)
        INCA = 48,  // increase A (0)
        DECA = 48,  // decrease A (1)
        ENTA = 48,  // enter A (2)
        ENNA = 48,  // enter negative A (3)
        INC1 = 49,  // increase I1 (0)
        DEC1 = 49,  // decrease I1 (1)
        ENT1 = 49,  // enter I1 (2)
        ENN1 = 49,  // enter negative I1 (3)
        INC2 = 50,  // increase I2 (0)
        DEC2 = 50,  // decrease I2 (1)
        ENT2 = 50,  // enter I2 (2)
        ENN2 = 50,  // enter negative I2 (3)
        INC3 = 51,  // increase I3 (0)
        DEC3 = 51,  // decrease I3 (1)
        ENT3 = 51,  // enter I3 (2)
        ENN3 = 51,  // enter negative I3 (3)
        INC4 = 52,  // increase I4 (0)
        DEC4 = 52,  // decrease I4 (1)
        ENT4 = 52,  // enter I4 (2)
        ENN4 = 52,  // enter negative I4 (3)
        INC5 = 53,  // increase I5 (0)
        DEC5 = 53,  // decrease I5 (1)
        ENT5 = 53,  // enter I5 (2)
        ENN5 = 53,  // enter negative I5 (3)
        INC6 = 54,  // increase I6 (0)
        DEC6 = 54,  // decrease I6 (1)
        ENT6 = 54,  // enter I6 (2)
        ENN6 = 54,  // enter negative I6 (3)
        INCX = 55,  // increase X (0)
        DECX = 55,  // decrease X (1)
        ENTX = 55,  // enter X (2)
        ENNX = 55,  // enter negative X (3)
        CMPA = 56,  // compare A
        FCMP = 56,  // float compare A (6)
        CMP1 = 57,  // compare I1
        CMP2 = 58,  // compare I2
        CMP3 = 59,  // compare I3
        CMP4 = 60,  // compare I4
        CMP5 = 61,  // compare I5
        CMP6 = 62,  // compare I6
        CMPX = 63,  // compare IX
        LAST = 63,  // last operation
        PSEUDO = 100,  // pseudo-operation: begin index
        EQU = 100,   // pseudo-operation: equivalent
        ORIG = 101,  // pseudo-operation: originate
        CON = 102,   // pseudo-operation: constant
    };

    static Instructions::Code getInstructionCode(const std::string& name);
    static int getDefaultField(const std::string& name);
    static int getCost(Instructions::Code code, uint8_t field = 0);
};

};  // namespace mixal


#endif  // INCLUDE_INSTRUCTIONS_H_
