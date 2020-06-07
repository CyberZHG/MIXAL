#include "test.h"
#include "instructions.h"

namespace test {

class TestInstructions : public UnitTest {};

__TEST_U(TestInstructions, test_word_length) {
    __ASSERT_EQ(6U, sizeof(mixal::InstructionWord));
}

__TEST_U(TestInstructions, test_get_invalid_instruction) {
    __ASSERT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode(""));
    __ASSERT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode("LD"));
    __ASSERT_EQ(mixal::Instructions::Code::INVALID, mixal::Instructions::getInstructionCode("LDP"));
}

__TEST_U(TestInstructions, test_get_instructions) {
    __ASSERT_EQ(mixal::Instructions::Code::NOP, mixal::Instructions::getInstructionCode("NOP"));
    __ASSERT_EQ(mixal::Instructions::Code::LDA, mixal::Instructions::getInstructionCode("LDA"));
}

}  // namespace test
