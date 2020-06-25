#ifndef INCLUDE_MACHINE_H_
#define INCLUDE_MACHINE_H_

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "registers.h"
#include "flags.h"
#include "memory.h"
#include "parser.h"
#include "instructions.h"
#include "io.h"
#include "errors.h"

namespace mixal {

using InstructionWord = ComputerWord;

class Machine {
 public:
    static const int NUM_INDEX_REGISTER = 6;
    static const int NUM_MEMORY = 4000;
    static const int NUM_DEVICE = 16;

    Register5 rA, rX;
    Register2 rI[NUM_INDEX_REGISTER], rJ;

    bool overflow;
    ComparisonIndicator comparison;

    ComputerWord memory[NUM_MEMORY];
    std::shared_ptr<IODevice> devices[16];

    Machine() : rA(), rX(), rI(), rJ(), overflow(false), comparison(ComparisonIndicator::EQUAL), memory(),
      devices(),
      _pesudoVarIndex(), _lineOffset(), _elapsed(), _constants(), _lineNumbers() {}

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

    const ComputerWord& memoryAt(int16_t index) const;
    ComputerWord& memoryAt(int16_t index);

    void reset();
    inline int line() const { return _lineOffset; }
    inline int elapsed() const { return _elapsed; }

    std::string getSingleLineSymbol();
    void executeSingle();
    void executeUntilSelfLoop();
    void executeUntilHalt();
    void executeSingle(ParsedResult* instruction);
    void executeSingle(const InstructionWord& instruction);
    void executeSinglePesudo(ParsedResult* instruction);

    void loadCodes(const std::vector<std::string>& codes);

 private:
    int32_t _pesudoVarIndex;
    int32_t _lineOffset;
    int32_t _elapsed;
    std::unordered_map<std::string, AtomicValue> _constants;
    std::vector<std::string> _lineNumbers;

    std::string getPesudoSymbolname();
    std::shared_ptr<IODevice> getDevice(int32_t index);

    int getIndexedAddress(const InstructionWord& instruction);
    void copyToRegister5(const InstructionWord& instruction, const ComputerWord& word, Register5* reg);
    void copyFromRegister5(const InstructionWord& instruction, const Register5& reg, ComputerWord* word);
    void copyToRegister2(const InstructionWord& instruction, const ComputerWord& word, Register2* reg);
    int32_t checkRange(int32_t value, int bytes = 5);

    uint8_t getAX(int index) const;
    void setAX(int index, uint8_t value);

    void executeADD(const InstructionWord& instruction);
    void executeSUB(const InstructionWord& instruction);
    void executeMUL(const InstructionWord& instruction);
    void executeDIV(const InstructionWord& instruction);

    void executeNUM();
    void executeCHAR();

    void executeSLA(const InstructionWord& instruction);
    void executeSRA(const InstructionWord& instruction);
    void executeSLAX(const InstructionWord& instruction);
    void executeSRAX(const InstructionWord& instruction);
    void executeSLC(const InstructionWord& instruction);
    void executeSRC(const InstructionWord& instruction);
    void executeMOVE(const InstructionWord& instruction);

    void executeLD(const InstructionWord& instruction, Register5* reg);
    void executeLDi(const InstructionWord& instruction);
    void executeLDN(const InstructionWord& instruction, Register5* reg);
    void executeLDiN(const InstructionWord& instruction);
    void executeST(const InstructionWord& instruction, Register5* reg);
    void executeSTi(const InstructionWord& instruction);
    void executeSTJ(const InstructionWord& instruction);
    void executeSTZ(const InstructionWord& instruction);

    void executeJBUS(const InstructionWord& instruction);
    void executeIOC(const InstructionWord& instruction);
    void executeIN(const InstructionWord& instruction);
    void executeOUT(const InstructionWord& instruction);
    void executeJRED(const InstructionWord& instruction);

    void executeJMP(const InstructionWord& instruction);
    void executeJSJ(const InstructionWord& instruction);
    void executeJOV(const InstructionWord& instruction);
    void executeJNOV(const InstructionWord& instruction);
    void executeJL(const InstructionWord& instruction);
    void executeJE(const InstructionWord& instruction);
    void executeJG(const InstructionWord& instruction);
    void executeJGE(const InstructionWord& instruction);
    void executeJNE(const InstructionWord& instruction);
    void executeJLE(const InstructionWord& instruction);
    void executeJN(const InstructionWord& instruction, Register5* reg);
    void executeJZ(const InstructionWord& instruction, Register5* reg);
    void executeJP(const InstructionWord& instruction, Register5* reg);
    void executeJNN(const InstructionWord& instruction, Register5* reg);
    void executeJNZ(const InstructionWord& instruction, Register5* reg);
    void executeJNP(const InstructionWord& instruction, Register5* reg);
    void executeJiN(const InstructionWord& instruction);
    void executeJiZ(const InstructionWord& instruction);
    void executeJiP(const InstructionWord& instruction);
    void executeJiNN(const InstructionWord& instruction);
    void executeJiNZ(const InstructionWord& instruction);
    void executeJiNP(const InstructionWord& instruction);

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

    void executeEQU(ParsedResult* instruction);
    void executeORIG(ParsedResult* instruction);
    void executeCON(ParsedResult* instruction);
};

};  // namespace mixal


#endif  // INCLUDE_MACHINE_H_
