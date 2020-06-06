#include "test.h"
#include "instructions.h"

namespace test {

class TestInstructions : public UnitTest {};

__TEST_U(TestInstructions, test_word_length) {
    __ASSERT_EQ(6U, sizeof(mixal::InstructionWord));
}

__TEST_U(TestInstructions, test_get_invalid_instruction) {
    __ASSERT_EQ(mixal::Instructions::Codes::INVALID, mixal::Instructions::getInstruction(""));
    __ASSERT_EQ(mixal::Instructions::Codes::INVALID, mixal::Instructions::getInstruction("LD"));
    __ASSERT_EQ(mixal::Instructions::Codes::INVALID, mixal::Instructions::getInstruction("LDP"));
}

__TEST_U(TestInstructions, test_get_instructions) {
    __ASSERT_EQ(mixal::Instructions::Codes::NOP, mixal::Instructions::getInstruction("NOP"));
    __ASSERT_EQ(mixal::Instructions::Codes::LDA, mixal::Instructions::getInstruction("LDA"));
}

}  // namespace test
