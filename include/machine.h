#ifndef INCLUDE_MACHINE_H_
#define INCLUDE_MACHINE_H_

#include "registers.h"
#include "flags.h"
#include "memory.h"
#include "instructions.h"

namespace mixal {

class Machine {
 public:
    Register5 rA, rX;
    Register2 rI[6], rJ;

    bool overflow;
    ComparisonIndicator comparison;

    ComputerWord memory[4000];

    Machine() : rA(), rX(), rI(), rJ(), overflow(false), comparison(ComparisonIndicator::EQUAL), memory() {}

    inline Register2& rI1() { return rI[0]; }
    inline Register2& rI2() { return rI[1]; }
    inline Register2& rI3() { return rI[2]; }
    inline Register2& rI4() { return rI[3]; }
    inline Register2& rI5() { return rI[4]; }
    inline Register2& rI6() { return rI[5]; }

    inline const Register2& rI1() const { return rI[0]; }
    inline const Register2& rI2() const { return rI[1]; }
    inline const Register2& rI3() const { return rI[2]; }
    inline const Register2& rI4() const { return rI[3]; }
    inline const Register2& rI5() const { return rI[4]; }
    inline const Register2& rI6() const { return rI[5]; }

    void reset();

    void executeSingle(const InstructionWord& instruction);

 private:
    int getIndexedAddress(const InstructionWord& instruction);
    void copyToRegister5(const InstructionWord& instruction, const ComputerWord& word, Register5* reg);
    void copyFromRegister5(const InstructionWord& instruction, const Register5& reg, ComputerWord* word);
    void copyToRegister2(const InstructionWord& instruction, const ComputerWord& word, Register2* reg);

    void executeLDA(const InstructionWord& instruction);
    void executeLDi(const InstructionWord& instruction);
    void executeLDX(const InstructionWord& instruction);
    void executeLDAN(const InstructionWord& instruction);
    void executeLDiN(const InstructionWord& instruction);
    void executeLDXN(const InstructionWord& instruction);
    void executeSTA(const InstructionWord& instruction);
    void executeSTi(const InstructionWord& instruction);
    void executeSTX(const InstructionWord& instruction);
};

};  // namespace mixal


#endif  // INCLUDE_MACHINE_H_
