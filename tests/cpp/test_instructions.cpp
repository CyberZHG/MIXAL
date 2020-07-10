#include <string>
#include "test.h"
#include "instructions.h"

namespace test {

class TestInstructions : public UnitTest {
 public:
    char getValidChar(int index) const {
        if (index < 26) {
            return index + 'A';
        }
        index -= 26;
        if (index < 10) {
            return index + '0';
        }
        return '#';
    }
};

__TEST_U(TestInstructions, test_get_invalid_instruction) {
    __ASSERT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode(""));
    __ASSERT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode("LD"));
    __ASSERT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode("LDP"));
}

__TEST_U(TestInstructions, test_get_instructions) {
    __ASSERT_EQ(mixal::Instructions::Code::NOP, mixal::Instructions::getInstructionCode("NOP"));
    __ASSERT_EQ(mixal::Instructions::Code::LDA, mixal::Instructions::getInstructionCode("LDA"));
}

__TEST_U(TestInstructions, test_get_cost) {
    __ASSERT_EQ(1, mixal::Instructions::getCost(mixal::Instructions::NOP, 0));
    __ASSERT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP1, 0));
    __ASSERT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP2, 0));
    __ASSERT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP3, 0));
    __ASSERT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP4, 0));
    __ASSERT_EQ(2, mixal::Instructions::getCost(mixal::Instructions::CMP5, 0));
    __ASSERT_EQ(0, mixal::Instructions::getCost(mixal::Instructions::CON, 0));
}

__TEST_U(TestInstructions, test_get_instructions_coverage) {
    for (int i = 0; i < 37; ++i) {
        char a = getValidChar(i);
        for (int j = 0; j < 37; ++j) {
            char b = getValidChar(j);
            for (int k = 0; k < 37; ++k) {
                char c = getValidChar(k);
                for (int l = 0; l < 37; ++l) {
                    char d = getValidChar(l);
                    for (int m = 35; m < 37; ++m) {
                        char e = getValidChar(m);
                        std::string cand({a, b, c, d, e});
                        mixal::Instructions::getInstructionCode(cand);
                        mixal::Instructions::getDefaultField(cand);
                    }
                }
            }
        }
    }
}

}  // namespace test
