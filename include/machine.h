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

/**
 * @file
 * @brief The virtual machine.
 */

namespace mixal {

using InstructionWord = ComputerWord;

class Computer {
 public:
    static const int NUM_INDEX_REGISTER = 6;  /**< Number of index registers. */
    static const int NUM_MEMORY = 4000;       /**< Number of words in memory. */
    static const int NUM_IO_DEVICE = 21;      /**< Number of IO devices. */

    Register5 rA, /**< Accumulator register. */ rX;  /**< Extension register. */
    Register2 rI1 /**< Index register. */, rI2, rI3, rI4, rI5, rI6, rJ;  /**< Jump address register. */

    bool overflow;  /**< Whether overflow has been triggered. */
    ComparisonIndicator comparison;  /**< The result of comparison operations. */

    ComputerWord memory[NUM_MEMORY];  /**< The memory in the machine. */
    std::vector<std::shared_ptr<IODevice>> devices;  /**< The IO devices. */

    /** Initialize the machine with zeros. */
    Computer();

    /** Get the index register given the index of the register. */
    Register2& rI(int index);
    /** Get a word from the memory. */
    const ComputerWord& memoryAt(int16_t index) const;
    /** Get a word from the memory. */
    ComputerWord& memoryAt(int16_t index);
    /** Get the device based on the index value. */
    std::shared_ptr<IODevice> getDevice(int32_t index);
    /** Wait the IO device to be ready. */
    void waitDevice(std::shared_ptr<IODevice> device);
    /** Wait all IO devices to be ready. */
    void waitDevices();

    /** Reset the machine to zeros. */
    void reset();
    /** Get the current executing line of the memory. */
    inline int line() const { return _lineOffset; }
    /** Get elapsed unit time after executing the codes. */
    inline int elapsed() const { return _elapsed; }

    /** Get a unique symbol name. */
    std::string getSingleLineSymbol();
    /** Execute a single instruction in the memory. */
    void executeSingle();
    /** Execute instructions until there is a self loop. */
    void executeUntilSelfLoop();
    /** Execute instructions until the HLT operation has been met. */
    void executeUntilHalt();
    /** Execute a single instruction based on the given instruction. */
    void executeSingle(ParsedResult* instruction);
    /** Execute a single instruction based on the given instruction. */
    void executeSingle(const InstructionWord& instruction);
    /** Execute a single pesudo instruction. */
    void executeSinglePesudo(ParsedResult* instruction);

    /** Parse and load codes to memory. */
    void loadCode(const std::string& codes, bool addHalt = true);
    /** Parse and load codes to memory. */
    void loadCodes(const std::vector<std::string>& codes, bool addHalt = true);

 private:
    int32_t _pesudoVarIndex;  /**< Used to generate unique symbol name. */
    int32_t _lineOffset;      /**< The line of memory that is currently executing. */
    int32_t _elapsed;         /**< The number of unit time that has been elapsed. */
    /** The constants after executing the single line codes. */
    std::unordered_map<std::string, AtomicValue> _constants;

    /** Get a unique symbol name. */
    std::string getPesudoSymbolname();

    /** Get the address based on the base address and the index register. */
    int32_t getIndexedAddress(const InstructionWord& instruction, bool checkRange = false);
    /** Copy values considered the field value. */
    void copyToRegister5(const InstructionWord& instruction, const ComputerWord& word, Register5* reg);
    /** Copy values considered the field value. */
    void copyFromRegister5(const InstructionWord& instruction, const Register5& reg, ComputerWord* word);
    /** Copy values considered the field value. */
    void copyToRegister2(const InstructionWord& instruction, const ComputerWord& word, Register2* reg);

    int32_t checkRange(int32_t value, int bytes = 5);

    /** Get one byte from the unit value of rA and rX. */
    uint8_t getAX(int index) const;
    /** Set one byte to the unit value of rA and rX. */
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
