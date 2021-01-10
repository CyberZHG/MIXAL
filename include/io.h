#ifndef INCLUDE_IO_H_
#define INCLUDE_IO_H_

#include <cstdint>
#include <vector>
#include <string>
#include "memory.h"

/**
 * @file
 * @brief IO Devices.
 */

namespace mixal {

/** Type of IO device. */
enum class IODeviceType {
    TAPE,          // 100 words
    DISK,          // 100 words
    CARD_READER,   // 16 words
    CARD_PUNCH,    // 16 words
    LINE_PRINTER,  // 24 words
    TYPEWRITER,    // 14 words
    PAPER_TAPE,    // 14 words
};

/** Status of an IO device. */
enum class IODeviceStatus {
    READY,       /**< The device is ready for reading or writing. */
    BUSY_READ,   /**< The device is reading. */
    BUSY_WRITE,  /**< The device is writing. */
};

/** The IO device.
 * 
 * Once read or write, the device will not be ready immediately.
 * The reading or writing operation is saved,
 * the actual reading or writing is performed only when the device is explicitly being queried.
 */
class IODevice {
 public:
    /** Initialize an IO device.
     * 
     * @param blockSize The number of bytes in one reading or writing.
     * @param allowRead Whether the device can be read.
     * @param allowWrite Whether the device can be wrote.
     */
    IODevice(int32_t blockSize, bool allowRead, bool allowWrite);
    virtual ~IODevice() = default;

    /** Get the type of the IO device. */
    [[nodiscard]] IODeviceType type() const { return _type; }
    /** The number of bytes in one reading or writing. */
    [[nodiscard]] int blockSize() const { return _blockSize; }
    /** Whether the device can be read. */
    [[nodiscard]] bool allowRead() const { return _allowRead; }
    /** Whether the device can be wrote. */
    [[nodiscard]] bool allowWrite() const { return _allowWrite; }

    /** Whether the device is ready for reading or writing. */
    virtual bool ready(int32_t elapsed);
    /** Special control of the device. */
    virtual void control(int32_t) {}
    /** Read one block from the device. */
    virtual void read(ComputerWord* memory, int32_t address) = 0;
    /** Write one block to the device. */
    virtual void write(const ComputerWord* memory, int32_t address) = 0;

    /** Get a word from the storage of the device. */
    virtual ComputerWord& wordAt(int32_t index) = 0;

 protected:
    IODeviceType _type;  /**< The type of the IO device. */
    int32_t _blockSize;  /**< The number of bytes in one reading or writing. */
    bool _allowRead;     /**< Whether the device can be read. */
    bool _allowWrite;    /**< Whether the device can be wrote. */
    int32_t _timestamp;  /**< The latest time that the device being triggered. */
    double _readyRate;   /**< The rate that the device could be ready in one unit time. */

    /** Perform the actual reading. */
    virtual void doRead() = 0;
    /** Perform the actual writing. */
    virtual void doWrite() = 0;
};

/** Device with a storage. */
class IODeviceStorage : public IODevice {
 public:
    explicit IODeviceStorage(int32_t storageSize = 4096);
    IODeviceStorage(const IODeviceStorage&) = default;
    IODeviceStorage& operator=(const IODeviceStorage&) = default;

    bool ready(int32_t elapsed) override;
    void read(ComputerWord* memory, int32_t address) override;
    void write(const ComputerWord* memory, int32_t address) override;

    ComputerWord& wordAt(const int32_t index) override { return _storage[index]; }
 protected:
    IODeviceStatus _status;
    int32_t _address, _locator;
    ComputerWord* _memory;
    std::vector<ComputerWord> _buffer;
    std::vector<ComputerWord> _storage;

    void doRead() override;
    void doWrite() override;
};

/** Magnetic tape. */
class IODeviceTape final : public IODeviceStorage {
 public:
     explicit IODeviceTape(int32_t storageSize = 4096);
    /** If M = 0, the tape is rewound.
     * If M < 0 the tape is skipped backward −M blocks, or to the beginning of the tape.
     * If M > 0, the tape is skipped forward;
     */
    void control(int32_t operation) override;

 private:
    void doRead() override;
    void doWrite() override;
};

/** Disk or drum.
 * 
 * @warning The documentation of the device is unclear yet.
 */
class IODeviceDisk final : public IODeviceStorage {
 public:
    explicit IODeviceDisk(int32_t storageSize = 4096);
    /** Position the device according to the given value (rX). */
    void control(int32_t operation) override;
};

/** Read sequentially. */
class IODeviceSeqReader : public IODeviceStorage {
 public:
    explicit IODeviceSeqReader(int32_t storageSize = 4096);

 private:
    void doRead() override;
};

/** Write sequentially. */
class IODeviceSeqWriter : public IODeviceStorage {
 public:
    explicit IODeviceSeqWriter(int32_t storageSize = 4096);

 private:
    void doWrite() override;
};

/** Card reader. */
class IODeviceCardReader final : public IODeviceSeqReader {
 public:
    explicit IODeviceCardReader(int32_t storageSize = 4096);
};

/** Card punch. */
class IODeviceCardPunch final : public IODeviceSeqWriter {
 public:
    explicit IODeviceCardPunch(int32_t storageSize = 4096);
};

/** Line printer. */
class IODeviceLinePrinter final : public IODeviceSeqWriter {
 public:
    static constexpr int NUM_CHARACTERS_PER_LINE = 80;
    static constexpr int NUM_WORDS_PER_LINE = NUM_CHARACTERS_PER_LINE / 5;

    explicit IODeviceLinePrinter(int32_t storageSize = 4096, int32_t numLinesPerPage = 60);
    /** Skip the printer to the top of the following page. */
    void control(int32_t operation) override;
    /** Get the printed line with the given page number and line number in the page. */
    [[nodiscard]] std::string line(int32_t pageNum, int32_t lineNum) const;

    [[nodiscard]] int32_t numLinesPerPage() const { return _numLinesPerPage; }
 private:
    int32_t _numLinesPerPage;  /**< Number of lines in one page. */
};

/** Typewriter. */
class IODeviceTypewriter final : public IODeviceSeqReader {
 public:
    explicit IODeviceTypewriter(int32_t storageSize = 4096);
};

/** Paper tape. */
class IODevicePaperTape final : public IODeviceSeqReader {
 public:
    explicit IODevicePaperTape(int32_t storageSize = 4096);
    /** Rewind the tape. */
    void control(int32_t operation) override;
};

};  // namespace mixal

#endif  // INCLUDE_IO_H_
