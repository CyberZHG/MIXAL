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
    case Instructions::ADD:
        executeADD(instruction);
        break;
    case Instructions::SUB:
        executeSUB(instruction);
        break;
    case Instructions::MUL:
        executeMUL(instruction);
        break;
    case Instructions::DIV:
        executeDIV(instruction);
        break;
    case Instructions::LDA:
        executeLD(instruction, &rA);
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
        executeLD(instruction, &rX);
        break;
    case Instructions::LDAN:
        executeLDN(instruction, &rA);
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
        executeLDN(instruction, &rX);
        break;
    case Instructions::STA:
        executeST(instruction, &rA);
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
        executeST(instruction, &rX);
        break;
    case Instructions::STJ:
        executeSTJ(instruction);
        break;
    case Instructions::STZ:
        executeSTZ(instruction);
        break;
    case Instructions::INCA:
        switch (instruction.field) {
        case 0: executeINC(instruction, &rA); break;
        case 1: executeDEC(instruction, &rA); break;
        case 2: executeENT(instruction, &rA); break;
        case 3: executeENN(instruction, &rA); break;
        }
        break;
    case Instructions::INC1:
    case Instructions::INC2:
    case Instructions::INC3:
    case Instructions::INC4:
    case Instructions::INC5:
    case Instructions::INC6:
        switch (instruction.field) {
        case 0: executeINCi(instruction); break;
        case 1: executeDECi(instruction); break;
        case 2: executeENTi(instruction); break;
        case 3: executeENNi(instruction); break;
        }
        break;
    case Instructions::INCX:
        switch (instruction.field) {
        case 0: executeINC(instruction, &rX); break;
        case 1: executeDEC(instruction, &rX); break;
        case 2: executeENT(instruction, &rX); break;
        case 3: executeENN(instruction, &rX); break;
        }
        break;
    case Instructions::CMPA:
        executeCMP(instruction, &rA);
        break;
    case Instructions::CMP1:
    case Instructions::CMP2:
    case Instructions::CMP3:
    case Instructions::CMP4:
    case Instructions::CMP5:
    case Instructions::CMP6:
        executeCMPi(instruction);
        break;
    case Instructions::CMPX:
        executeCMP(instruction, &rX);
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
    return static_cast<int>(instruction.addressValue()) + offset;
}

void Machine::copyToRegister5(const InstructionWord& instruction, const ComputerWord& word, Register5* reg) {
    int start = instruction.field / 8;
    int stop = instruction.field % 8;
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
    int start = instruction.field / 8;
    int stop = instruction.field % 8;
    if (start == 0) {
        word->sign = reg.sign;
        ++start;
    }
    for (int i = stop, j = 5; i >= start; --i, --j) {
        word->set(i, reg[j]);
    }
}

void Machine::copyToRegister2(const InstructionWord& instruction, const ComputerWord& word, Register2* reg) {
    int start = instruction.field / 8;
    int stop = instruction.field % 8;
    reg->reset();
    if (start == 0) {
        reg->sign = word.sign;
        ++start;
    }
    for (int i = stop, j = 2; i >= start && j > 0; --i, --j) {
        reg->set(j, word[i]);
    }
}

int32_t Machine::checkRange(int32_t value, int bytes) {
    int32_t range = 1 << (6 * bytes);
    if (abs(value) >= range) {
        overflow = true;
        value %= range;
    }
    return value;
}

void Machine::executeADD(const InstructionWord& instruction) {
    int32_t valueA = rA.value();
    ComputerWord word;
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], &word);
    int32_t valueM = word.value();
    int32_t result = valueA + valueM;
    rA.set(checkRange(result));
}

void Machine::executeSUB(const InstructionWord& instruction) {
    int32_t valueA = rA.value();
    ComputerWord word;
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], &word);
    word.sign = !word.sign;
    int32_t valueM = word.value();
    int32_t result = valueA + valueM;
    rA.set(checkRange(result));
}

void Machine::executeMUL(const InstructionWord& instruction) {
    int32_t valueA = rA.value();
    ComputerWord word;
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], &word);
    int32_t valueM = word.value();
    int64_t result = static_cast<int64_t>(valueA) * static_cast<int64_t>(valueM);
    rA.set(result / (1 << 30));
    rX.set(result % (1 << 30));
}

void Machine::executeDIV(const InstructionWord& instruction) {
    int32_t valueA = abs(rA.value());
    int32_t valueX = abs(rX.value());
    int64_t dividend = (static_cast<int64_t>(valueA) << 30) + static_cast<int64_t>(valueX);
    if (rA.sign) {
        dividend = -dividend;
    }
    ComputerWord word;
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], &word);
    int32_t divisor = word.value();
    int64_t quotient = dividend / divisor;
    if (abs(quotient) >= (1 << 30)) {
        overflow = true;
        quotient %= (1 << 30);
    }
    int32_t remainder = dividend % divisor;
    rA.set(static_cast<int32_t>(quotient));
    rX.set(remainder);
}

void Machine::executeLD(const InstructionWord& instruction, Register5* reg) {
    int address = getIndexedAddress(instruction);
    copyToRegister5(instruction, memory[address], reg);
}

void Machine::executeLDi(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    int registerIndex = instruction.operation - Instructions::LD1;
    auto& rIi = rI[registerIndex];
    copyToRegister2(instruction, memory[address], &rIi);
}

void Machine::executeLDN(const InstructionWord& instruction, Register5* reg) {
    executeLD(instruction, reg);
    reg->sign = !reg->sign;
}

void Machine::executeLDiN(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    int registerIndex = instruction.operation - Instructions::LD1N;
    auto& rIi = rI[registerIndex];
    copyToRegister2(instruction, memory[address], &rIi);
    rIi.sign = 1 - rIi.sign;
}

void Machine::executeST(const InstructionWord& instruction, Register5* reg) {
    int address = getIndexedAddress(instruction);
    copyFromRegister5(instruction, *reg, &memory[address]);
}

void Machine::executeSTi(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    int registerIndex = instruction.operation - Instructions::ST1;
    auto& rIi = rI[registerIndex];
    ComputerWord word(rIi.sign, 0, 0, 0, rIi[1], rIi[2]);
    copyFromRegister5(instruction, word, &memory[address]);
}

void Machine::executeSTJ(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    ComputerWord word(0, 0, 0, 0, rJ[1], rJ[2]);
    copyFromRegister5(instruction, word, &memory[address]);
}

void Machine::executeSTZ(const InstructionWord& instruction) {
    int address = getIndexedAddress(instruction);
    ComputerWord word(0, 0, 0, 0, 0, 0);
    copyFromRegister5(instruction, word, &memory[address]);
}

void Machine::executeINC(const InstructionWord& instruction, Register5* reg) {
    int32_t value = reg->value();
    int32_t address = getIndexedAddress(instruction);
    value += address;
    reg->set(checkRange(value));
}

void Machine::executeDEC(const InstructionWord& instruction, Register5* reg) {
    int32_t value = reg->value();
    int32_t address = getIndexedAddress(instruction);
    value -= address;
    reg->set(checkRange(value));
}

void Machine::executeENT(const InstructionWord& instruction, Register5* reg) {
    int32_t address = getIndexedAddress(instruction);
    reg->set(address);
    if (address == 0) {
        reg->sign = instruction.sign;
    }
}

void Machine::executeENN(const InstructionWord& instruction, Register5* reg) {
    int32_t address = getIndexedAddress(instruction);
    reg->set(-address);
    if (address == 0) {
        reg->sign = !instruction.sign;
    }
}

void Machine::executeINCi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation - Instructions::INC1;
    auto& rIi = rI[registerIndex];
    int16_t value = rIi.value();
    int16_t address = getIndexedAddress(instruction);
    value += address;
    rIi.set(checkRange(value, 2));
}

void Machine::executeDECi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation - Instructions::INC1;
    auto& rIi = rI[registerIndex];
    int16_t value = rIi.value();
    int16_t address = getIndexedAddress(instruction);
    value -= address;
    rIi.set(checkRange(value, 2));
}

void Machine::executeENTi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation - Instructions::INC1;
    auto& rIi = rI[registerIndex];
    int16_t address = getIndexedAddress(instruction);
    rIi.set(checkRange(address, 2));
    if (address == 0) {
        rIi.sign = instruction.sign;
    }
}

void Machine::executeENNi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation - Instructions::INC1;
    auto& rIi = rI[registerIndex];
    int16_t address = getIndexedAddress(instruction);
    rIi.set(checkRange(-address, 2));
    if (address == 0) {
        rIi.sign = !instruction.sign;
    }
}

void Machine::executeCMP(const InstructionWord& instruction, Register5* reg) {
    ComputerWord a, b;
    int32_t address = getIndexedAddress(instruction);
    copyToRegister5(instruction, *reg, &a);
    copyToRegister5(instruction, memory[address], &b);
    int32_t aVal = a.value(), bVal = b.value();
    if (aVal < bVal) {
        comparison = ComparisonIndicator::LESS;
    } else if (aVal > bVal) {
        comparison = ComparisonIndicator::GREATER;
    } else {
        comparison = ComparisonIndicator::EQUAL;
    }
}

void Machine::executeCMPi(const InstructionWord& instruction) {
    int registerIndex = instruction.operation - Instructions::CMP1;
    auto& rIi = rI[registerIndex];
    ComputerWord t(rIi.sign, 0, 0, 0, rIi.byte1, rIi.byte2), a, b;
    int32_t address = getIndexedAddress(instruction);
    copyToRegister5(instruction, t, &a);
    copyToRegister5(instruction, memory[address], &b);
    int32_t aVal = a.value(), bVal = b.value();
    if (aVal < bVal) {
        comparison = ComparisonIndicator::LESS;
    } else if (aVal > bVal) {
        comparison = ComparisonIndicator::GREATER;
    } else {
        comparison = ComparisonIndicator::EQUAL;
    }
}

};  // namespace mixal
