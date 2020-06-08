#include <cstring>
#include <iostream>
#include "machine.h"

namespace mixal {

void Machine::reset() {
    rA.reset();
    rX.reset();
    for (int i = 0; i < 6; ++i) {
        rI[i].reset();
    }
    rJ.reset();
    overflow = false;
    comparison = ComparisonIndicator::EQUAL;
    memset(memory, 0, sizeof(memory));
}

void Machine::executeSingle(const InstructionWord& instruction) {
    switch (instruction.operation) {
    case Instructions::NOP:
        break;
    case Instructions::LDA:
        executeLDA(instruction);
        break;
    case Instructions::LDX:
        executeLDX(instruction);
        break;
    default:
        break;
    }
}

int Machine::getIndexedAddress(const InstructionWord& instruction) {
    int offset = 0;
    if (instruction.index != 0) {
        offset = static_cast<int>(rI[instruction.index - 1].word);
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

void Machine::executeLDA(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], &rA);
}

void Machine::executeLDX(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], &rX);
}

};  // namespace mixal
