#include <iostream>
#include <set>
#include <tuple>
#include <sstream>
#include <cassert>
#include "machine.h"
#include "parser.h"

namespace mixal {

Computer::Computer() : rA(), rX(), rI1(), rI2(), rI3(), rI4(), rI5(), rI6(), rJ(),
      overflow(false), comparison(ComparisonIndicator::EQUAL), memory(),
      devices(NUM_IO_DEVICE, nullptr),
      _pesudoVarIndex(), _lineOffset(), _elapsed(), _constants() {}

Register2& Computer::rI(int index) {
    switch (index) {
    case 1: return rI1;
    case 2: return rI2;
    case 3: return rI3;
    case 4: return rI4;
    case 5: return rI5;
    case 6: return rI6;
    }
    throw RuntimeError(_lineOffset, "Invalid offset for index register: " + std::to_string(index));
}

const ComputerWord& Computer::memoryAt(int16_t index) const {
    return memory[index];
}

ComputerWord& Computer::memoryAt(int16_t index) {
    return memory[index];
}

void Computer::reset() {
    rA.reset();
    rX.reset();
    for (int i = 1; i <= NUM_INDEX_REGISTER; ++i) {
        rI(i).reset();
    }
    rJ.reset();
    overflow = false;
    comparison = ComparisonIndicator::EQUAL;
    for (int i = 0; i < NUM_MEMORY; ++i) {
        memory[i].reset();
    }
    for (size_t i = 0; i < NUM_IO_DEVICE; ++i) {
        devices[i] = nullptr;
    }
    _pesudoVarIndex = 0;
    _lineOffset = 0;
    _elapsed = 0;
    _constants.clear();
}

std::string Computer::getSingleLineSymbol() {
    std::string symbolName = getPesudoSymbolname();
    _constants[symbolName] = AtomicValue(_lineOffset);
    return symbolName;
}

void Computer::executeSingle() {
    executeSingle(memory[_lineOffset]);
}

void Computer::executeUntilSelfLoop() {
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
    waitDevices();
}

void Computer::executeUntilHalt() {
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
    waitDevices();
}

void Computer::executeSingle(ParsedResult* instruction) {
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

void Computer::executeSingle(const InstructionWord& instruction) {
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
    }
    ++_lineOffset;
    _elapsed += Instructions::getCost(static_cast<Instructions::Code>(instruction.operation()),
                                      instruction.field());
}

void Computer::executeSinglePesudo(ParsedResult* instruction) {
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
    }
}

void Computer::loadCodes(const std::vector<std::string>& codes, bool addHalt) {
    this->reset();
    // Parse and save all the results and intermediate expressions
    std::vector<ParsedResult> results(codes.size());
    std::unordered_map<std::string, AtomicValue> evaluated;
    std::unordered_map<std::string, Expression*> expressions;
    std::vector<std::tuple<std::string, Expression, Expression>> constants;  // (name, address, value)
    std::string lineBase = getPesudoSymbolname();
    evaluated[lineBase] = AtomicValue(0);
    int32_t lineOffset = 0, endIndex = -1;
    for (size_t codeIndex = 0; codeIndex < codes.size(); ++codeIndex) {
        auto code = codes[codeIndex];
        auto& result = results[codeIndex];
        auto lineSymbol = getPesudoSymbolname();
        result = Parser::parseLine(code, lineSymbol, true);
        if (result.parsedType == ParsedType::PSEUDO) {
            int32_t operation = result.word.operation() + Instructions::PSEUDO;
            switch (operation) {
            case Instructions::EQU:
                expressions[result.rawLocation] = &result.address;
                break;
            case Instructions::ORIG:
                lineBase = getPesudoSymbolname();
                expressions[lineBase] = &result.address;
                lineOffset = 0;
                break;
            case Instructions::CON:
            case Instructions::ALF:
                if (!result.rawLocation.empty()) {
                    lineSymbol = result.rawLocation;
                }
                constants.push_back(std::make_tuple(
                    lineSymbol,
                    Expression::getConstOffsetExpression(lineBase, lineOffset++),
                    result.address));
                break;
            case Instructions::END:
                endIndex = codeIndex;
                break;
            }
        } else if (result.parsedType == ParsedType::INSTRUCTION) {
            bool usedLineSymbol = !result.rawLocation.empty() ||
                                (!result.rawAddress.empty() && result.address.depends().count(lineSymbol)) ||
                                (!result.rawIndex.empty() && result.index.depends().count(lineSymbol)) ||
                                (!result.rawField.empty() && result.field.depends().count(lineSymbol));
            result.location = Expression::getConstOffsetExpression(lineBase, lineOffset);
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
    // Add halt
    if (addHalt) {
        auto lineSymbol = getPesudoSymbolname();
        auto haltCommand = Parser::parseLine("HLT", lineSymbol, false);
        constants.push_back(std::make_tuple(
            lineSymbol,
             Expression::getConstOffsetExpression(lineBase, lineOffset++),
             Expression::getConstExpression(AtomicValue(haltCommand.word.value()))));
    }
    // Add expressions and literal constants
    for (auto& result : results) {
        if (!result.rawAddress.empty()) {
            if (result.address.literalConstant()) {
                auto lineSymbol = getPesudoSymbolname();
                constants.push_back(std::make_tuple(
                    lineSymbol,
                    Expression::getConstOffsetExpression(lineBase, lineOffset++),
                    result.address));
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
    if (endIndex != -1) {
        auto lineSymbol = results[endIndex].rawLocation.empty() ? getPesudoSymbolname() : results[endIndex].rawLocation;
        constants.push_back(std::make_tuple(
            lineSymbol,
            Expression::getConstOffsetExpression(lineBase, lineOffset++),
            results[endIndex].address));
    }
    // Add collected constants to expressions
    for (auto& it : constants) {
        expressions[std::get<0>(it)] = &std::get<1>(it);
        expressions[getPesudoSymbolname()] = &std::get<2>(it);
    }
    // Try to solve all the expressions
    std::unordered_map<std::string, int> dependNums;
    std::unordered_map<std::string, std::unordered_set<std::string>> solves;
    std::set<std::pair<int, std::string>> tasks;
    for (auto& it : expressions) {
        dependNums[it.first] = static_cast<int>(it.second->depends().size());
        for (auto& depend : it.second->depends()) {
            solves[depend].insert(it.first);
            if (evaluated.find(depend) != evaluated.end()) {
                --dependNums[it.first];
            }
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
        int32_t location = std::get<1>(it).result().value;
        if (location < 0 || location >= NUM_MEMORY) {
            throw RuntimeError(location, "Location of the code is invalid: " + std::to_string(location));
        }
        memory[location].set(std::get<2>(it).result().value);
    }
    // Load results to memory
    _lineOffset = -1;
    for (auto& result : results) {
        if (result.parsedType == ParsedType::INSTRUCTION) {
            result.evaluate(evaluated);
            int32_t location = result.location.result().value;
            if (location < 0 || location >= NUM_MEMORY) {
                throw RuntimeError(location, "Location of the code is invalid: " + std::to_string(location));
            }
            if (_lineOffset == -1) {
                _lineOffset = location;
            }
            memory[location].set(result.word.negative,
                                 result.word.address(),
                                 result.word.index(),
                                 result.word.field(),
                                 result.word.operation());
        }
    }
    if (endIndex != -1) {
        results[endIndex].address.evaluate(evaluated);
        _lineOffset = results[endIndex].address.result().value;
    } else if (_lineOffset == -1) {
        _lineOffset = 0;
    }
}

std::string Computer::getPesudoSymbolname() {
    return "#" + std::to_string(_pesudoVarIndex++);
}

int32_t Computer::getIndexedAddress(const InstructionWord& instruction, bool checkRange) {
    int32_t offset = 0;
    if (instruction.index() != 0) {
        auto& rIi = rI(instruction.index());
        offset = static_cast<int32_t>(rIi.value());
    }
    int32_t address = static_cast<int32_t>(instruction.addressValue()) + offset;
    if (checkRange && !(0 <= address && address < NUM_MEMORY)) {
        throw RuntimeError(_lineOffset, "Invalid address in instruction '" + instruction.getBytesString() +
                                        "': " + std::to_string(address));
    }
    return address;
}

void Computer::copyToRegister5(const InstructionWord& instruction, const ComputerWord& word, Register5* reg) {
    int start = instruction.field() / 8;
    int stop = instruction.field() % 8;
    reg->reset();
    if (start == 0) {
        reg->negative = word.negative;
        ++start;
    }
    for (int i = stop, j = 5; i >= start; --i, --j) {
        reg->set(j, word[i]);
    }
}

void Computer::copyFromRegister5(const InstructionWord& instruction, const Register5& reg, ComputerWord* word) {
    int start = instruction.field() / 8;
    int stop = instruction.field() % 8;
    if (start == 0) {
        word->negative = reg.negative;
        ++start;
    }
    for (int i = stop, j = 5; i >= start; --i, --j) {
        word->set(i, reg[j]);
    }
}

void Computer::copyToRegister2(const InstructionWord& instruction, const ComputerWord& word, Register2* reg) {
    int start = instruction.field() / 8;
    int stop = instruction.field() % 8;
    reg->reset();
    if (start == 0) {
        reg->negative = word.negative;
        ++start;
    }
    for (int i = stop, j = 2; i >= start && j > 0; --i, --j) {
        reg->set(j, word[i]);
    }
}

/** Check whether the given value can be fitted into the given number of bytes.
 * 
 * Overflow will be triggered if it the value can not be fitted into 5 bytes.
 * (Which means rI will not trigger overflow.)
 */
int32_t Computer::checkRange(int32_t value, int bytes) {
    int32_t range = 1 << (6 * bytes);
    if (std::abs(value) >= range) {
        if (bytes == 5) {
            overflow = true;
        }
        value %= range;
    }
    return value;
}

uint8_t Computer::getAX(int index) const {
    assert(1 <= index && index <= 10);
    return index <= 5 ? rA[index] : rX[index - 5];
}

void Computer::setAX(int index, uint8_t value) {
    assert(1 <= index && index <= 10);
    if (index <= 5) {
        rA[index] = value;
    } else {
        rX[index - 5] = value;
    }
}

};  // namespace mixal
