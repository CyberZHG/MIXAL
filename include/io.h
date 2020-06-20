#ifndef INCLUDE_IO_H_
#define INCLUDE_IO_H_

#include <cstdint>
#include <vector>
#include "memory.h"

namespace mixal {

extern uint16_t CHAR_CODES[];

enum class IODeviceType {
    TAPE,          // 100 words
    DISK,          // 100 words
    CARD_READER,   // 16 words
    CARD_PUNCH,    // 16 words
    LINE_PRINTER,  // 24 words
    TYPEWRITER,    // 14 words
    PAPER_TAPE,    // 14 words
};

enum class IODeviceStatus {
    READY,
    BUSY_READ,
    BUSY_WRITE,
};

class IODevice {
 public:
    IODevice(int32_t blockSize, bool allowRead, bool allowWrite) : _type(IODeviceType::TAPE),
        _blockSize(blockSize), _allowRead(allowRead), _allowWrite(allowWrite),
        _timestamp(), _readyRate(1.0) {}
    virtual ~IODevice() {}

    inline IODeviceType type() const { return _type; }
    inline int blockSize() const { return _blockSize; }
    inline bool allowRead() const { return _allowRead; }
    inline bool allowWrite() const { return _allowWrite; }

    virtual bool ready(int32_t elapsed);
    virtual void control(int32_t operation) = 0;
    virtual void read(ComputerWord* memory, int32_t address) = 0;
    virtual void write(const ComputerWord* memory, int32_t address) = 0;

 protected:
    IODeviceType _type;
    int32_t _blockSize;
    bool _allowRead;
    bool _allowWrite;
    int32_t _timestamp;
    double _readyRate;

    virtual void doRead() = 0;
    virtual void doWrite() = 0;
};

class IODeviceStorage : public IODevice {
 public:
    explicit IODeviceStorage(int32_t storageSize = 4096) : IODevice(100, true, true),
        _status(IODeviceStatus::READY), _address(0), _locator(0), _memory(nullptr),
        _buffer(100), _storage(storageSize) {}
    IODeviceStorage(const IODeviceStorage&) = default;
    IODeviceStorage& operator=(const IODeviceStorage&) = default;

    bool ready(int32_t elapsed) override;
    void read(ComputerWord* memory, int32_t address) override;
    void write(const ComputerWord* memory, int32_t address) override;
 protected:
    IODeviceStatus _status;
    int32_t _address, _locator;
    ComputerWord* _memory;
    std::vector<ComputerWord> _buffer;
    std::vector<ComputerWord> _storage;

    void doRead() override;
    void doWrite() override;
};

class IODeviceTape : public IODeviceStorage {
 public:
     explicit IODeviceTape(int32_t storageSize = 4096) : IODeviceStorage(storageSize) {
        _type = IODeviceType::TAPE;
        _readyRate = 0.1;
    }
    void control(int32_t operation) final;

 private:
    void doRead() final;
    void doWrite() final;
};

class IODeviceDisk : public IODeviceStorage {
 public:
    explicit IODeviceDisk(int32_t storageSize = 4096) : IODeviceStorage(storageSize) {
        _type = IODeviceType::DISK;
        _readyRate = 0.5;
    }
    void control(int32_t operation) final;
};

};  // namespace mixal


#endif  // INCLUDE_IO_H_
