#include <string>
#include <gtest/gtest.h>
#include "instructions.h"

char getValidChar(int index) {
    if (index < 26) {
        return static_cast<char>(index + 'A');
    }
    index -= 26;
    if (index < 10) {
        return static_cast<char>(index + '0');
    }
    return '#';
}

TEST(TestInstructions, test_get_invalid_instruction) {
    EXPECT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode(""));
    EXPECT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode("LD"));
    EXPECT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode("LDP"));
}

TEST(TestInstructions, test_get_instructions) {
    EXPECT_EQ(mixal::Instructions::Code::NOP, mixal::Instructions::getInstructionCode("NOP"));
    EXPECT_EQ(mixal::Instructions::Code::LDA, mixal::Instructions::getInstructionCode("LDA"));
}

TEST(TestInstructions, test_get_cost) {
    EXPECT_EQ(1, mixal::Instructions::getCost(mixal::Instructions::NOP, 0));
    EXPECT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP1, 0));
    EXPECT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP2, 0));
    EXPECT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP3, 0));
    EXPECT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP4, 0));
    EXPECT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP5, 0));
    EXPECT_EQ(0, mixal::Instructions::getCost(mixal::Instructions::CON, 0));
}

TEST(TestInstructions, test_get_instructions_coverage) {
    for (int i = 0; i < 37; ++i) {
        const char a = getValidChar(i);
        for (int j = 0; j < 37; ++j) {
            const char b = getValidChar(j);
            for (int k = 0; k < 37; ++k) {
                const char c = getValidChar(k);
                for (int l = 0; l < 37; ++l) {
                    const char d = getValidChar(l);
                    for (int m = 35; m < 37; ++m) {
                        const char e = getValidChar(m);
                        std::string cand({a, b, c, d, e});
                        mixal::Instructions::getInstructionCode(cand);
                        mixal::Instructions::getDefaultField(cand);
                    }
                }
            }
        }
    }
}
