#include <iostream>
#include <set>
#include <tuple>
#include <sstream>
#include "machine.h"
#include "parser.h"

namespace mixal {

std::shared_ptr<IODevice> Machine::getDevice(int32_t index) {
    if (devices[index] == nullptr) {
        switch (index) {
        case 0: case 1: case 2: case 3:
        case 4: case 5: case 6: case 7:
            devices[index] = std::unique_ptr<IODevice>(new IODeviceTape());
            break;
        case 8: case 9: case 10: case 11:
        case 12: case 13: case 14: case 15:
            devices[index] = std::unique_ptr<IODevice>(new IODeviceDisk());
            break;
        }
    }
    return devices[index];
}

const ComputerWord& Machine::memoryAt(int16_t index) const {
    return memory[index];
}

ComputerWord& Machine::memoryAt(int16_t index) {
    return memory[index];
}

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
    for (size_t i = 0; i < NUM_DEVICE; ++i) {
        devices[i] = nullptr;
    }
    _pesudoVarIndex = 0;
    _lineOffset = 0;
    _elapsed = 0;
    _constants.clear();
    _lineNumbers.clear();
}

std::string Machine::getSingleLineSymbol() {
    std::string symbolName = getPesudoSymbolname();
    _constants[symbolName] = AtomicValue(_lineOffset);
    return symbolName;
}

void Machine::executeSingle() {
    executeSingle(memory[_lineOffset]);
}

void Machine::executeUntilSelfLoop() {
    int32_t lastOffset = _lineOffset;
    while (true) {
        if (_lineOffset < 0 || NUM_MEMORY <= _lineOffset) {
            throw RuntimeError(_lineOffset, "Invalid code line: " + std::to_string(_lineOffset));
        }
        executeSingle(memory[_lineOffset]);
        if (lastOffset == _lineOffset) {
            break;
        }
        lastOffset = _lineOffset;
    }
}

void Machine::executeUntilHalt() {
    while (true) {
        if (_lineOffset < 0 || NUM_MEMORY <= _lineOffset) {
            throw RuntimeError(_lineOffset, "Invalid code line: " + std::to_string(_lineOffset));
        }
        if (memory[_lineOffset].operation() == Instructions::HLT &&
            memory[_lineOffset].field() == 2) {
            ++_lineOffset;
            break;
        }
        executeSingle(memory[_lineOffset]);
    }
}

void Machine::executeSingle(ParsedResult* instruction) {
    if (instruction->address.literalConstant() ||
        instruction->index.literalConstant() ||
        instruction->field.literalConstant()) {
        throw RuntimeError(_lineOffset, "Literal constant cannot be used in single execution");
    }
    if (instruction->parsedType == ParsedType::INSTRUCTION) {
        if (!instruction->evaluated()) {
            if (!instruction->evaluate(_constants)) {
                throw RuntimeError(_lineOffset, "Unresolved symbol found when trying to execute");
            }
        }
        executeSingle(instruction->word);
    } else if (instruction->parsedType == ParsedType::PSEUDO) {
        executeSinglePesudo(instruction);
    }
}

void Machine::executeSingle(const InstructionWord& instruction) {
    switch (instruction.operation()) {
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
    case Instructions::HLT:
        switch (instruction.field()) {
        case 0: executeNUM(); break;
        case 1: executeCHAR(); break;
        }
        break;
    case Instructions::SLA:
        switch (instruction.field()) {
        case 0: executeSLA(instruction); break;
        case 1: executeSRA(instruction); break;
        case 2: executeSLAX(instruction); break;
        case 3: executeSRAX(instruction); break;
        case 4: executeSLC(instruction); break;
        case 5: executeSRC(instruction); break;
        }
        break;
    case Instructions::MOVE:
        executeMOVE(instruction);
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
    case Instructions::JBUS:
        executeJBUS(instruction);
        break;
    case Instructions::IOC:
        executeIOC(instruction);
        break;
    case Instructions::IN:
        executeIN(instruction);
        break;
    case Instructions::OUT:
        executeOUT(instruction);
        break;
    case Instructions::JRED:
        executeJRED(instruction);
        break;
    case Instructions::JMP:
        switch (instruction.field()) {
        case 0: executeJMP(instruction); break;
        case 1: executeJSJ(instruction); break;
        case 2: executeJOV(instruction); break;
        case 3: executeJNOV(instruction); break;
        case 4: executeJL(instruction); break;
        case 5: executeJE(instruction); break;
        case 6: executeJG(instruction); break;
        case 7: executeJGE(instruction); break;
        case 8: executeJNE(instruction); break;
        case 9: executeJLE(instruction); break;
        }
        break;
    case Instructions::JAN:
        switch (instruction.field()) {
        case 0: executeJN(instruction, &rA); break;
        case 1: executeJZ(instruction, &rA); break;
        case 2: executeJP(instruction, &rA); break;
        case 3: executeJNN(instruction, &rA); break;
        case 4: executeJNZ(instruction, &rA); break;
        case 5: executeJNP(instruction, &rA); break;
        }
        break;
    case Instructions::J1N:
    case Instructions::J2N:
    case Instructions::J3N:
    case Instructions::J4N:
    case Instructions::J5N:
    case Instructions::J6N:
        switch (instruction.field()) {
        case 0: executeJiN(instruction); break;
        case 1: executeJiZ(instruction); break;
        case 2: executeJiP(instruction); break;
        case 3: executeJiNN(instruction); break;
        case 4: executeJiNZ(instruction); break;
        case 5: executeJiNP(instruction); break;
        }
        break;
    case Instructions::JXN:
        switch (instruction.field()) {
        case 0: executeJN(instruction, &rX); break;
        case 1: executeJZ(instruction, &rX); break;
        case 2: executeJP(instruction, &rX); break;
        case 3: executeJNN(instruction, &rX); break;
        case 4: executeJNZ(instruction, &rX); break;
        case 5: executeJNP(instruction, &rX); break;
        }
        break;
    case Instructions::INCA:
        switch (instruction.field()) {
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
        switch (instruction.field()) {
        case 0: executeINCi(instruction); break;
        case 1: executeDECi(instruction); break;
        case 2: executeENTi(instruction); break;
        case 3: executeENNi(instruction); break;
        }
        break;
    case Instructions::INCX:
        switch (instruction.field()) {
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
    ++_lineOffset;
    _elapsed += Instructions::getCost(static_cast<Instructions::Code>(instruction.operation()),
                                      instruction.field());
}

void Machine::executeSinglePesudo(ParsedResult* instruction) {
    switch (instruction->word.operation() + Instructions::PSEUDO) {
    case Instructions::EQU:
        executeEQU(instruction);
        break;
    case Instructions::ORIG:
        executeORIG(instruction);
        break;
    case Instructions::CON:
        executeCON(instruction);
        break;
    default:
        break;
    }
}

void Machine::loadCodes(const std::vector<std::string>& codes) {
    this->reset();
    // Parse and save all the results and intermediate expressions
    std::vector<ParsedResult> results(codes.size());
    std::unordered_map<std::string, Expression*> expressions;
    std::vector<std::tuple<std::string, Expression, Expression>> constants;
    std::string lineBase;
    int32_t lineOffset = 0;
    for (size_t codeIndex = 0; codeIndex < codes.size(); ++codeIndex) {
        auto code = codes[codeIndex];
        auto& result = results[codeIndex];
        auto lineSymbol = getPesudoSymbolname();
        result = Parser::parseLine(code, lineSymbol, true);
        if (result.parsedType == ParsedType::PSEUDO) {
            switch (result.word.operation() + Instructions::PSEUDO) {
            case Instructions::EQU:
                expressions[result.rawLocation] = &result.address;
                break;
            case Instructions::ORIG:
                lineBase = getPesudoSymbolname();
                expressions[lineBase] = &result.address;
                lineOffset = 0;
                break;
            case Instructions::CON:
                if (lineBase.empty()) {
                    constants.push_back({lineSymbol,
                                         Expression::getConstExpression(AtomicValue(lineOffset)),
                                         result.address});
                } else {
                    constants.push_back({lineSymbol,
                                         Expression::getConstOffsetExpression(lineBase, lineOffset),
                                         result.address});
                }
                ++lineOffset;
                break;
            default:
                break;
            }
        } else if (result.parsedType == ParsedType::INSTRUCTION) {
            bool usedLineSymbol = !result.rawLocation.empty() ||
                                (!result.rawAddress.empty() && result.address.depends().count(lineSymbol)) ||
                                (!result.rawIndex.empty() && result.index.depends().count(lineSymbol)) ||
                                (!result.rawField.empty() && result.field.depends().count(lineSymbol));
            if (lineBase.empty()) {
                result.location = Expression::getConstExpression(AtomicValue(lineOffset));
            } else {
                result.location = Expression::getConstOffsetExpression(lineBase, lineOffset);
            }
            if (!result.rawLocation.empty()) {
                if (!(Atomic::isLocalSymbol(result.rawLocation) && result.rawLocation[1] == 'H')) {
                    expressions[result.rawLocation] = &result.location;
                }
            } else if (usedLineSymbol) {
                result.rawLocation = lineSymbol;
            }
            expressions[lineSymbol] = &result.location;
            ++lineOffset;
        }
    }
    // Replace local symbols
    std::unordered_map<std::string, std::string> localSymbolMapping;
    for (auto& result : results) {
        if (!result.rawLocation.empty() && Atomic::isLocalSymbol(result.rawLocation) && result.rawLocation[1] == 'H') {
            auto lineSymbol = getPesudoSymbolname();
            result.rawLocation[1] = 'B';
            localSymbolMapping[result.rawLocation] = lineSymbol;
            result.rawLocation[1] = 'H';
            expressions[lineSymbol] = &result.location;
        }
        result.address.replaceSymbol(localSymbolMapping);
    }
    for (int i = static_cast<int>(results.size()) - 1; i >= 0; --i) {
        auto& result = results[i];
        if (!result.rawLocation.empty() && Atomic::isLocalSymbol(result.rawLocation) && result.rawLocation[1] == 'H') {
            auto lineSymbol = getPesudoSymbolname();
            result.rawLocation[1] = 'F';
            localSymbolMapping[result.rawLocation] = lineSymbol;
            result.rawLocation[1] = 'H';
            expressions[lineSymbol] = &result.location;
        }
        result.address.replaceSymbol(localSymbolMapping);
    }
    // Add expressions and literal constants
    for (auto& result : results) {
        if (!result.rawAddress.empty()) {
            if (result.address.literalConstant()) {
                auto lineSymbol = getPesudoSymbolname();
                constants.push_back({lineSymbol,
                                    Expression::getConstOffsetExpression(lineBase, lineOffset++),
                                    result.address});
                result.address = Expression::getConstExpression(lineSymbol);
            }
            expressions[getPesudoSymbolname()] = &result.address;
        }
        if (!result.rawIndex.empty()) {
            expressions[getPesudoSymbolname()] = &result.index;
        }
        if (!result.rawField.empty()) {
            expressions[getPesudoSymbolname()] = &result.field;
        }
    }
    // Add collected constants to expressions
    for (auto& it : constants) {
        expressions[std::get<0>(it)] = &std::get<1>(it);
        expressions[getPesudoSymbolname()] = &std::get<2>(it);
    }
    // Try to solve all the expressions
    std::unordered_map<std::string, int> dependNums;
    std::unordered_map<std::string, std::unordered_set<std::string>> solves;
    std::unordered_map<std::string, AtomicValue> evaluated;
    std::set<std::pair<int, std::string>> tasks;
    for (auto& it : expressions) {
        dependNums[it.first] = static_cast<int>(it.second->depends().size());
        for (auto& depend : it.second->depends()) {
            solves[depend].insert(it.first);
        }
        tasks.insert({dependNums[it.first], it.first});
    }
    while (!tasks.empty()) {
        auto& symbol = tasks.begin()->second;
        auto& expression = expressions[symbol];
        if (tasks.begin()->first != 0 || !expression->evaluate(evaluated)) {
            throw RuntimeError(0, "Unresolved symbol found while trying to calcuate: " +
                                  tasks.begin()->second);
        }
        evaluated[symbol] = expression->result();
        tasks.erase({0, symbol});
        for (auto& solve : solves[symbol]) {
            tasks.erase({dependNums[solve], solve});
            tasks.insert({--dependNums[solve], solve});
        }
    }
    // Load constants to memory
    for (auto& it : constants) {
        memory[std::get<1>(it).result().value].set(std::get<2>(it).result().value);
    }
    // Load results to memory
    _lineOffset = -1;
    for (auto& result : results) {
        if (result.parsedType == ParsedType::INSTRUCTION) {
            result.evaluate(evaluated);
            if (_lineOffset == -1) {
                _lineOffset = result.location.result().value;
            }
            memory[result.location.result().value].set(result.word.sign,
                                                       result.word.address(),
                                                       result.word.index(),
                                                       result.word.field(),
                                                       result.word.operation());
        }
    }
    if (_lineOffset == -1) {
        _lineOffset = 0;
    }
}

std::string Machine::getPesudoSymbolname() {
    return "#" + std::to_string(_pesudoVarIndex++);
}

int Machine::getIndexedAddress(const InstructionWord& instruction) {
    int offset = 0;
    if (instruction.index() != 0) {
        auto& rIi = rI[instruction.index() - 1];
        offset = static_cast<int>(rIi.value());
    }
    return static_cast<int>(instruction.addressValue()) + offset;
}

void Machine::copyToRegister5(const InstructionWord& instruction, const ComputerWord& word, Register5* reg) {
    int start = instruction.field() / 8;
    int stop = instruction.field() % 8;
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
    int start = instruction.field() / 8;
    int stop = instruction.field() % 8;
    if (start == 0) {
        word->sign = reg.sign;
        ++start;
    }
    for (int i = stop, j = 5; i >= start; --i, --j) {
        word->set(i, reg[j]);
    }
}

void Machine::copyToRegister2(const InstructionWord& instruction, const ComputerWord& word, Register2* reg) {
    int start = instruction.field() / 8;
    int stop = instruction.field() % 8;
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
        if (bytes == 5) {
            overflow = true;
        }
        value %= range;
    }
    return value;
}

uint8_t Machine::getAX(int index) const {
    if (index <= 0 || index > 10) {
        throw std::runtime_error("Invalid index for AX: " + std::to_string(index));
    }
    return index <= 5 ? rA[index] : rX[index - 5];
}

void Machine::setAX(int index, uint8_t value) {
    if (index <= 0 || index > 10) {
        throw std::runtime_error("Invalid index for AX: " + std::to_string(index));
    }
    if (index <= 5) {
        rA[index] = value;
    } else {
        rX[index - 5] = value;
    }
}

};  // namespace mixal
