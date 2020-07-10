#include <iostream>
#include "machine.h"

/**
 * @file
 * @brief IO operations.
 */

namespace mixal {

std::shared_ptr<IODevice> Machine::getDevice(int32_t index) {
    if (devices[index] == nullptr) {
        switch (index) {
        case 0: case 1: case 2: case 3:
        case 4: case 5: case 6: case 7:
            devices[index] = std::shared_ptr<IODevice>(new IODeviceTape());
            break;
        case 8: case 9: case 10: case 11:
        case 12: case 13: case 14: case 15:
            devices[index] = std::shared_ptr<IODevice>(new IODeviceDisk());
            break;
        case 16:
            devices[index] = std::shared_ptr<IODevice>(new IODeviceCardReader());
            break;
        case 17:
            devices[index] = std::shared_ptr<IODevice>(new IODeviceCardPunch());
            break;
        case 18:
            devices[index] = std::shared_ptr<IODevice>(new IODeviceLinePrinter());
            break;
        case 19:
            devices[index] = std::shared_ptr<IODevice>(new IODeviceTypewriter());
            break;
        case 20:
            devices[index] = std::shared_ptr<IODevice>(new IODevicePaperTape());
            break;
        }
    }
    return devices[index];
}

void Machine::waitDevice(std::shared_ptr<IODevice> device) {
    while (!device->ready(this->_elapsed)) {
        ++this->_elapsed;
    }
}

void Machine::waitDevices() {
    for (int i = 0; i < NUM_IO_DEVICE; ++i) {
        if (devices[i] != nullptr) {
            waitDevice(devices[i]);
        }
    }
}

/** Jump when the device is busy.
 * 
 * The field value indicates the device.
 */
void Machine::executeJBUS(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (!device->ready(this->_elapsed)) {
        this->executeJMP(instruction);
    }
}

/** Execute special control signal.
 * 
 * The field value indicates the device.
 */
void Machine::executeIOC(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    waitDevice(device);
    if (device->type() == IODeviceType::DISK) {
        device->control(rX.value());
    } else {
        int32_t address = getIndexedAddress(instruction);
        device->control(address);
    }
}

/** Read a block from the device.
 * 
 * The field value indicates the device.
 * 
 * @throw mixal::Runtime When the device cannot be read.
 */
void Machine::executeIN(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (!device->allowRead()) {
        throw RuntimeError(_lineOffset, "Device does not support read: " + std::to_string(instruction.field()));
    }
    waitDevice(device);
    int32_t address = getIndexedAddress(instruction, true);
    device->read(memory, address);
}

/** Write a block to the device.
 * 
 * The field value indicates the device.
 * 
 * @throw mixal::Runtime When the device cannot be wrote.
 */
void Machine::executeOUT(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (!device->allowWrite()) {
        throw RuntimeError(_lineOffset, "Device does not support write: " + std::to_string(instruction.field()));
    }
    waitDevice(device);
    int32_t address = getIndexedAddress(instruction, true);
    device->write(memory, address);
}

/** Jump when the device is ready.
 * 
 * The field value indicates the device.
 */
void Machine::executeJRED(const InstructionWord& instruction) {
    auto device = getDevice(instruction.field());
    if (device->ready(this->_elapsed)) {
        this->executeJMP(instruction);
    }
}

};  // namespace mixal
