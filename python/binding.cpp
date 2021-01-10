#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <memory>
#include "machine.h"
#include "../include/memory.h"
using namespace std;
using namespace mixal;

namespace py = pybind11;

PYBIND11_MODULE(_core, m, py::mod_gil_not_used()) {
    py::class_<ComputerWord>(m, "ComputerWord")
        .def(py::init<>())
        .def_readwrite("negative", &ComputerWord::negative)
        .def_readwrite("byte1", &ComputerWord::byte1)
        .def_readwrite("byte2", &ComputerWord::byte2)
        .def_readwrite("byte3", &ComputerWord::byte3)
        .def_readwrite("byte4", &ComputerWord::byte4)
        .def_readwrite("byte5", &ComputerWord::byte5)
        .def("set", py::overload_cast<int32_t>(&ComputerWord::set), py::arg("value"))
        .def("set", py::overload_cast<const string&>(&ComputerWord::set), py::arg("value"))
        .def("set", py::overload_cast<int, uint8_t>(&ComputerWord::set), py::arg("index"), py::arg("value"))
        .def("set", py::overload_cast<bool, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>(&ComputerWord::set), py::arg("sign"), py::arg("byte1"), py::arg("byte2"), py::arg("byte3"), py::arg("byte4"), py::arg("byte5"))
        .def("set", py::overload_cast<bool, uint16_t, uint8_t, uint8_t, uint8_t>(&ComputerWord::set), py::arg("sign"), py::arg("byte12"), py::arg("byte3"), py::arg("byte4"), py::arg("byte5"))
        .def("value", &ComputerWord::value)
        .def("get_chars", &ComputerWord::getCharacters)
        .def("get_bytes_str", &ComputerWord::getBytesString)
    ;
    py::class_<Register2>(m, "Register2")
        .def(py::init<>())
        .def_readwrite("negative", &Register2::negative)
        .def_readwrite("byte1", &Register2::byte1)
        .def_readwrite("byte2", &Register2::byte2)
        .def("set", py::overload_cast<int16_t>(&Register2::set))
        .def("value", &Register2::value)
        .def("get_bytes_str", &Register2::getBytesString)
    ;
    py::class_<Computer>(m, "Computer")
        .def(py::init<>())
        .def_readwrite("rA", &Computer::rA)
        .def_readwrite("rX", &Computer::rX)
        .def_readwrite("rI1", &Computer::rI1)
        .def_readwrite("rI2", &Computer::rI2)
        .def_readwrite("rI3", &Computer::rI3)
        .def_readwrite("rI4", &Computer::rI4)
        .def_readwrite("rI5", &Computer::rI5)
        .def_readwrite("rI6", &Computer::rI6)
        .def_readwrite("rJ", &Computer::rJ)
        .def("reset", &Computer::reset)
        .def("load_codes", py::overload_cast<const string&, bool>(&Computer::loadCodes), py::arg("codes"), py::arg("add_halt") = true)
        .def("memory_at", static_cast<ComputerWord&(Computer::*)(int16_t)>(&Computer::memoryAt), py::return_value_policy::reference_internal)
        .def("execute_single", py::overload_cast<>(&Computer::executeSingle))
        .def("execute_until_self_loop", &Computer::executeUntilSelfLoop)
        .def("execute_until_halt", &Computer::executeUntilHalt)
        .def("execute_until_half_or_self_loop", &Computer::executeUntilHaltOrSelfLoop)
        .def("get_device_word_at", &Computer::getDeviceWordAt, py::arg("device"), py::arg("index"), py::return_value_policy::reference_internal)
        .def("line", &Computer::line)
        .def("elapsed", &Computer::elapsed)
    ;
}
