#ifndef INCLUDE_IO_H_
#define INCLUDE_IO_H_

#include <cstdint>

namespace mixal {

extern uint16_t CHAR_CODES[];

enum class IOEquipment {
    TAPE_0, TAPE_1, TAPE_2, TAPE_3, TAPE_4, TYPE_5, TYPE_6, TYPE_7,  // 100 words
    DISK_0, DISK_1, DISK_2, DISK_3, DISK_4, DISK_5, DISK_6, DISK_7,  // 100 words
    CARD_READER,   // 16 words
    CARD_PUNCH,    // 16 words
    LINE_PRINTER,  // 24 words
    TYPEWRITER,    // 14 words
    PAPER_TAPE,    // 14 words
};

};  // namespace mixal


#endif  // INCLUDE_IO_H_
