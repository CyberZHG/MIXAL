#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::reset() {
    rA.reset();
    rX.reset();
    for (int i = 0; i < NUM_INDEX_REGISTER; ++i) {
        rI[i].reset();
    }
    rJ.reset();
    overflow = false;
    comparison = ComparisonIndicator::EQUAL;
    for (int i = 0; i < NUM_MEMORY; ++i) {
        memory[i].reset();
    }
}

void Machine::executeSingle(const InstructionWord& instruction) {
    switch (instruction.operation) {
    case Instructions::NOP:
        break;
    case Instructions::LDA:
        executeLDA(instruction);
        break;
    case Instructions::LD1:
    case Instructions::LD2:
    case Instructions::LD3:
    case Instructions::LD4:
    case Instructions::LD5:
    case Instructions::LD6:
        executeLDi(instruction);
        break;
    case Instructions::LDX:
        executeLDX(instruction);
        break;
    case Instructions::LDAN:
        executeLDAN(instruction);
        break;
    case Instructions::LD1N:
    case Instructions::LD2N:
    case Instructions::LD3N:
    case Instructions::LD4N:
    case Instructions::LD5N:
    case Instructions::LD6N:
        executeLDiN(instruction);
        break;
    case Instructions::LDXN:
        executeLDXN(instruction);
        break;
    case Instructions::STA:
        executeSTA(instruction);
        break;
    case Instructions::ST1:
    case Instructions::ST2:
    case Instructions::ST3:
    case Instructions::ST4:
    case Instructions::ST5:
    case Instructions::ST6:
        executeSTi(instruction);
        break;
    case Instructions::STX:
        executeSTX(instruction);
        break;
    case Instructions::STJ:
        executeSTJ(instruction);
        break;
    case Instructions::STZ:
        executeSTZ(instruction);
        break;
    default:
        break;
    }
}

int Machine::getIndexedAddress(const InstructionWord& instruction) {
    int offset = 0;
    if (instruction.index != 0) {
        auto& rIi = rI[instruction.index - 1];
        offset = static_cast<int>(rIi.value());
    }
    return static_cast<int>(instruction.address) + offset;
}

void Machine::copyToRegister5(const InstructionWord& instruction, const ComputerWord& word, Register5* reg) {
    int start = instruction.modification / 8;
    int stop = instruction.modification % 8;
    reg->reset();
    if (start == 0) {
        reg->sign = word.sign;
        ++start;
    }
    for (int i = stop, j = 5; i >= start; --i, --j) {
        reg->set(j, word[i]);
    }
}

void Machine::copyFromRegister5(const InstructionWord& instruction, const Register5& reg, ComputerWord* word) {
    int start = instruction.modification / 8;
    int stop = instruction.modification % 8;
    if (start == 0) {
        word->sign = reg.sign;
        ++start;
    }
    for (int i = stop, j = 5; i >= start; --i, --j) {
        word->set(i, reg[j]);
    }
}

void Machine::copyToRegister2(const InstructionWord& instruction, const ComputerWord& word, Register2* reg) {
    int start = instruction.modification / 8;
    int stop = instruction.modification % 8;
    reg->reset();
    if (start == 0) {
        reg->sign = word.sign;
        ++start;
    }
    for (int i = stop, j = 2; i >= start && j > 0; --i, --j) {
        reg->set(j, word[i]);
    }
}

void Machine::executeLDA(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], &rA);
}

void Machine::executeLDi(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    int registerIndex = instruction.operation - Instructions::LD1;
    auto& rIi = rI[registerIndex];
    copyToRegister2(instruction, memory[address], &rIi);
}

void Machine::executeLDX(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], &rX);
}

void Machine::executeLDAN(const InstructionWord& instruction) {
    executeLDA(instruction);
    rA.sign = 1 - rA.sign;
}

void Machine::executeLDiN(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    int registerIndex = instruction.operation - Instructions::LD1N;
    auto& rIi = rI[registerIndex];
    copyToRegister2(instruction, memory[address], &rIi);
    rIi.sign = 1 - rIi.sign;
}

void Machine::executeLDXN(const InstructionWord& instruction) {
    executeLDX(instruction);
    rX.sign = 1 - rX.sign;
}

void Machine::executeSTA(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    copyFromRegister5(instruction, rA, &memory[address]);
}

void Machine::executeSTi(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    int registerIndex = instruction.operation - Instructions::ST1;
    auto& rIi = rI[registerIndex];
    ComputerWord word;
    word.set(rIi.sign, 0, 0, 0, rIi[1], rIi[2]);
    copyFromRegister5(instruction, word, &memory[address]);
}

void Machine::executeSTX(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    copyFromRegister5(instruction, rX, &memory[address]);
}

void Machine::executeSTJ(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    ComputerWord word;
    word.set(0, 0, 0, 0, rJ[1], rJ[2]);
    copyFromRegister5(instruction, word, &memory[address]);
}

void Machine::executeSTZ(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    ComputerWord word;
    word.set(0, 0, 0, 0, 0, 0);
    copyFromRegister5(instruction, word, &memory[address]);
}

};  // namespace mixal
