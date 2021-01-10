#include <functional>

#include "machine.h"
#include <string>
#include <emscripten/bind.h>
using namespace std;
using namespace emscripten;
using namespace mixal;

EMSCRIPTEN_BINDINGS(MixalWASM) {
    class_<ComputerWord>("ComputerWord")
        .constructor<>()
        .function("set", select_overload<void(int32_t)>(&ComputerWord::set))
        .function("setCharacters", select_overload<void(const string&)>(&ComputerWord::set))
        .function("setByteAt", select_overload<void(int, uint8_t)>(&ComputerWord::set))
        .function("setBytes", select_overload<void(bool, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)>(&ComputerWord::set))
        .function("setMergedBytes", select_overload<void(bool, uint16_t, uint8_t, uint8_t, uint8_t)>(&ComputerWord::set))
        .function("value", &ComputerWord::value)
        .function("getCharacters", &ComputerWord::getCharacters)
        .function("getBytesString", &ComputerWord::getBytesString)
    ;
    class_<Register2>("Register2")
        .constructor<>()
        .function("set", select_overload<void(int16_t)>(&Register2::set))
        .function("value", &Register2::value)
    ;
    class_<Computer>("Computer")
        .constructor<>()
        .function("registerA", &Computer::registerA, return_value_policy::reference())
        .function("registerX", &Computer::registerX, return_value_policy::reference())
        .function("registerI1", &Computer::registerI1, return_value_policy::reference())
        .function("registerI2", &Computer::registerI2, return_value_policy::reference())
        .function("registerI3", &Computer::registerI3, return_value_policy::reference())
        .function("registerI4", &Computer::registerI4, return_value_policy::reference())
        .function("registerI5", &Computer::registerI5, return_value_policy::reference())
        .function("registerI6", &Computer::registerI6, return_value_policy::reference())
        .function("registerJ", &Computer::registerJ, return_value_policy::reference())
        .function("reset", &Computer::reset)
        .function("_loadCodes", select_overload<void(const string&, bool)>(&Computer::loadCodes))
        .function("memoryAt", static_cast<ComputerWord&(Computer::*)(int16_t)>(&Computer::memoryAt), return_value_policy::reference())
        .function("executeSingle", select_overload<void()>(&Computer::executeSingle))
        .function("executeUntilSelfLoop", &Computer::executeUntilSelfLoop)
        .function("executeUntilHalt", &Computer::executeUntilHalt)
        .function("getDeviceWordAt", &Computer::getDeviceWordAt, return_value_policy::reference())
        .function("line", &Computer::line)
        .function("elapsed", &Computer::elapsed)
    ;
}
