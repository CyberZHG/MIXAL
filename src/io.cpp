#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "io.h"

namespace mixal {

uint16_t CHAR_CODES[] = {
    ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    0xb4, 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    0x2da, 0x2dd, 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '.', ',', '(', ')', '+', '-', '*', '/', '=', '$',
    '<', '>', '@', ';', ':', 0x201a
};

bool IODevice::ready(int32_t timestamp) {
    int32_t elapsed = std::max(0, timestamp - _timestamp);
    _timestamp = timestamp;
    double r = static_cast<double>(rand()) / RAND_MAX;
    double successRate = 1.0 - pow(1.0 - _readyRate, elapsed);
    return r <= successRate;
}

bool IODeviceStorage::ready(int32_t elapsed) {
    bool state = IODevice::ready(elapsed);
    if (state) {
        if (_status == IODeviceStatus::BUSY_READ) {
            doRead();
        } else if (_status == IODeviceStatus::BUSY_WRITE) {
            doWrite();
        }
    }
    return state;
}

void IODeviceStorage::read(ComputerWord* memory, int32_t address) {
    _status = IODeviceStatus::BUSY_READ;
    _address = address;
    _memory = memory;
    for (int i = 0; i < _blockSize; ++i) {
        _buffer[i] = _storage[_locator + i];
    }
}

void IODeviceStorage::write(const ComputerWord* memory, int32_t address) {
    _status = IODeviceStatus::BUSY_WRITE;
    for (int i = 0; i < _blockSize; ++i) {
        _buffer[i] = memory[address + i];
    }
}

void IODeviceStorage::doRead() {
    for (int i = 0; i < _blockSize; ++i) {
        _memory[_address + i] = _buffer[i];
    }
    _status = IODeviceStatus::READY;
}

void IODeviceStorage::doWrite() {
    for (int i = 0; i < _blockSize; ++i) {
        _storage[_locator + i] = _buffer[i];
    }
    _status = IODeviceStatus::READY;
}

void IODeviceTape::control(int32_t operation) {
    if (operation == 0) {
        _locator = 0;
    } else {
        _locator += operation * _blockSize;
        _locator = std::max(0, _locator);
    }
}

void IODeviceTape::doRead() {
    IODeviceStorage::doRead();
    _locator += _blockSize;
}

void IODeviceTape::doWrite() {
    IODeviceStorage::doWrite();
    _locator += _blockSize;
}

void IODeviceDisk::control(int32_t operation) {
    _locator = operation;
}

};  // namespace mixal
