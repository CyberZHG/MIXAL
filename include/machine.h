#ifndef INCLUDE_MACHINE_H_
#define INCLUDE_MACHINE_H_

#include <map>
#include <string>
#include <unordered_map>
#include "registers.h"
#include "flags.h"
#include "memory.h"
#include "parser.h"
#include "instructions.h"
#include "errors.h"

namespace mixal {

class Machine {
 public:
    static const int NUM_INDEX_REGISTER = 6;
    static const int NUM_MEMORY = 4000;

    Register5 rA, rX;
    Register2 rI[NUM_INDEX_REGISTER], rJ;

    bool overflow;
    ComparisonIndicator comparison;

    ComputerWord memory[NUM_MEMORY];

    Machine() : rA(), rX(), rI(), rJ(), overflow(false), comparison(ComparisonIndicator::EQUAL), memory(),
      _lineBase(), _lineOffset(), _constants() {}

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

    void executeSingle(ParsedResult* instruction);
    void executeSingle(const InstructionWord& instruction);

 private:
    std::string _lineBase;
    int32_t _lineOffset;
    std::unordered_map<std::string, AtomicValue> _constants;

    int getIndexedAddress(const InstructionWord& instruction);
    void copyToRegister5(const InstructionWord& instruction, const ComputerWord& word, Register5* reg);
    void copyFromRegister5(const InstructionWord& instruction, const Register5& reg, ComputerWord* word);
    void copyToRegister2(const InstructionWord& instruction, const ComputerWord& word, Register2* reg);
    int32_t checkRange(int32_t value, int bytes = 5);

    void executeADD(const InstructionWord& instruction);
    void executeSUB(const InstructionWord& instruction);
    void executeMUL(const InstructionWord& instruction);
    void executeDIV(const InstructionWord& instruction);
    void executeLD(const InstructionWord& instruction, Register5* reg);
    void executeLDi(const InstructionWord& instruction);
    void executeLDN(const InstructionWord& instruction, Register5* reg);
    void executeLDiN(const InstructionWord& instruction);
    void executeST(const InstructionWord& instruction, Register5* reg);
    void executeSTi(const InstructionWord& instruction);
    void executeSTJ(const InstructionWord& instruction);
    void executeSTZ(const InstructionWord& instruction);
    void executeINC(const InstructionWord& instruction, Register5* reg);
    void executeDEC(const InstructionWord& instruction, Register5* reg);
    void executeENT(const InstructionWord& instruction, Register5* reg);
    void executeENN(const InstructionWord& instruction, Register5* reg);
    void executeINCi(const InstructionWord& instruction);
    void executeDECi(const InstructionWord& instruction);
    void executeENTi(const InstructionWord& instruction);
    void executeENNi(const InstructionWord& instruction);
    void executeCMP(const InstructionWord& instruction, Register5* reg);
    void executeCMPi(const InstructionWord& instruction);
};

};  // namespace mixal


#endif  // INCLUDE_MACHINE_H_
