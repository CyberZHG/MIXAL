#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>
#include "io.h"

namespace mixal {

IODevice::IODevice(int32_t blockSize, bool allowRead, bool allowWrite) : _type(IODeviceType::TAPE),
        _blockSize(blockSize), _allowRead(allowRead), _allowWrite(allowWrite),
        _timestamp(), _readyRate(1.0) {}

bool IODevice::ready(int32_t timestamp) {
    int32_t elapsed = std::max(0, timestamp - _timestamp);
    _timestamp = timestamp;
    double r = static_cast<double>(rand()) / RAND_MAX;
    double successRate = 1.0 - pow(1.0 - _readyRate, elapsed);
    return r <= successRate;
}

IODeviceStorage::IODeviceStorage(int32_t storageSize) : IODevice(100, true, true),
        _status(IODeviceStatus::READY), _address(0), _locator(0), _memory(nullptr),
        _buffer(100), _storage(storageSize) {}

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
    ready(_timestamp);
}

void IODeviceStorage::write(const ComputerWord* memory, int32_t address) {
    _status = IODeviceStatus::BUSY_WRITE;
    for (int i = 0; i < _blockSize; ++i) {
        _buffer[i] = memory[address + i];
    }
    ready(_timestamp);
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

IODeviceTape::IODeviceTape(int32_t storageSize) : IODeviceStorage(storageSize) {
    _type = IODeviceType::TAPE;
    _readyRate = 0.1;
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

IODeviceDisk::IODeviceDisk(int32_t storageSize) : IODeviceStorage(storageSize) {
    _type = IODeviceType::DISK;
    _readyRate = 0.5;
}

void IODeviceDisk::control(int32_t operation) {
    _locator = operation;
}

IODeviceSeqReader::IODeviceSeqReader(int32_t storageSize) : IODeviceStorage(storageSize) {
    _allowWrite = false;
}

void IODeviceSeqReader::doRead() {
    IODeviceStorage::doRead();
    _locator += _blockSize;
}

IODeviceSeqWriter::IODeviceSeqWriter(int32_t storageSize) : IODeviceStorage(storageSize) {
    _allowRead = false;
}

void IODeviceSeqWriter::doWrite() {
    IODeviceStorage::doWrite();
    _locator += _blockSize;
}

IODeviceCardReader::IODeviceCardReader(int32_t storageSize) : IODeviceSeqReader(storageSize) {
    _type = IODeviceType::CARD_READER;
    _blockSize = 16;
    _readyRate = 0.2;
}

IODeviceCardPunch::IODeviceCardPunch(int32_t storageSize) : IODeviceSeqWriter(storageSize) {
    _type = IODeviceType::CARD_PUNCH;
    _blockSize = 16;
    _readyRate = 0.1;
}

IODeviceLinePrinter::IODeviceLinePrinter(int32_t storageSize, int32_t pageSize) :
    IODeviceSeqWriter(storageSize), _pageSize(pageSize) {
    _type = IODeviceType::LINE_PRINTER;
    _blockSize = 24;
    _readyRate = 0.1;
}

void IODeviceLinePrinter::control(int32_t) {
    _locator += (_pageSize - _locator / _blockSize % _pageSize) * _blockSize;
}

int32_t IODeviceLinePrinter::pageOffsetAt(int32_t index) const {
    return index * _pageSize * _blockSize;
}

std::string IODeviceLinePrinter::line(int32_t pageNum, int32_t lineNum) const {
    int32_t offset = pageOffsetAt(pageNum) + lineNum * _blockSize;
    std::ostringstream out;
    for (int i = 0; i < _blockSize; ++i) {
        out << _storage[offset + i].getCharacters();
    }
    return out.str();
}

IODeviceTypewriter::IODeviceTypewriter(int32_t storageSize) : IODeviceSeqReader(storageSize) {
    _type = IODeviceType::TYPEWRITER;
    _blockSize = 14;
    _readyRate = 0.2;
}

IODevicePaperTape::IODevicePaperTape(int32_t storageSize) : IODeviceSeqReader(storageSize) {
    _type = IODeviceType::PAPER_TAPE;
    _blockSize = 14;
    _readyRate = 0.2;
}

void IODevicePaperTape::control(int32_t) {
    _locator = 0;
}

};  // namespace mixal
