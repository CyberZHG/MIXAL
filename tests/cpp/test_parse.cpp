#include <iostream>
#include "test.h"
#include "parser.h"

namespace test {

class TestParse : public UnitTest {};

__TEST_U(TestParse, test_parse_line_basic_numeric_address_all_1) {
    auto result = mixal::Parser::parseLine("LDA 2000,2(0:3)", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("2", result.rawIndex);
    __ASSERT_EQ("0:3", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(2, result.word.index());
    __ASSERT_EQ(3, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_all_1_with_indent) {
    auto result = mixal::Parser::parseLine("  LDA   2000,2(0:3)  ", "", true);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("2", result.rawIndex);
    __ASSERT_EQ("0:3", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(2, result.word.index());
    __ASSERT_EQ(3, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_all_2) {
    auto result = mixal::Parser::parseLine("LDA 2000,2(1:3)", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("2", result.rawIndex);
    __ASSERT_EQ("1:3", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(2, result.word.index());
    __ASSERT_EQ(11, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_no_index) {
    auto result = mixal::Parser::parseLine("LDA 2000(1:3)", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("1:3", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(0, result.word.index());
    __ASSERT_EQ(11, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_no_index_with_indent) {
    auto result = mixal::Parser::parseLine("  LDA 2000(1:3)  ", "", true);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("1:3", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(0, result.word.index());
    __ASSERT_EQ(11, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_only_address) {
    auto result = mixal::Parser::parseLine("LDA 2000", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(0, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_only_address_with_indent) {
    auto result = mixal::Parser::parseLine("  LDA 2000  ", "", true);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(0, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_no_mod) {
    auto result = mixal::Parser::parseLine("LDA 2000,4", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("4", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(4, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_no_mod_with_indent) {
    auto result = mixal::Parser::parseLine("  LDA 2000,4  ", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("4", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.addressValue());
    __ASSERT_EQ(4, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_negative) {
    auto result = mixal::Parser::parseLine("LDA -2000,4", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("-2000", result.rawAddress);
    __ASSERT_EQ("4", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(-2000, result.word.addressValue());
    __ASSERT_EQ(4, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_with_expressions) {
    auto result = mixal::Parser::parseLine("LDA -2000+400*2,-1+2(-1:3+6)", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("-2000+400*2", result.rawAddress);
    __ASSERT_EQ("-1+2", result.rawIndex);
    __ASSERT_EQ("-1:3+6", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(-3200, result.word.addressValue());
    __ASSERT_EQ(1, result.word.index());
    __ASSERT_EQ(1, result.word.field());
    __ASSERT_EQ(8, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_only_op) {
    auto result = mixal::Parser::parseLine("NOP", "", false);
    __ASSERT_EQ(mixal::Instructions::Code::NOP, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("NOP", result.operation);
    __ASSERT_EQ("", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(0, result.word.addressValue());
    __ASSERT_EQ(0, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(0, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_only_op_with_indent) {
    auto result = mixal::Parser::parseLine("  NOP  ", "", true);
    __ASSERT_EQ(mixal::Instructions::Code::NOP, result.word.operation());
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("NOP", result.operation);
    __ASSERT_EQ("", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(0, result.word.addressValue());
    __ASSERT_EQ(0, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(0, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_empty) {
    auto result = mixal::Parser::parseLine("   ", "", false);
    __ASSERT_EQ(mixal::ParsedType::EMPTY, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("", result.operation);
    __ASSERT_EQ("", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(0, result.word.addressValue());
    __ASSERT_EQ(0, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(0, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_empty_with_indent) {
    auto result = mixal::Parser::parseLine("   ", "", true);
    __ASSERT_EQ(mixal::ParsedType::EMPTY, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("", result.operation);
    __ASSERT_EQ("", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(0, result.word.addressValue());
    __ASSERT_EQ(0, result.word.index());
    __ASSERT_EQ(5, result.word.field());
    __ASSERT_EQ(0, result.word.operation());
}

__TEST_U(TestParse, test_parse_line_single_line_comment) {
    auto result = mixal::Parser::parseLine("* EXAMPLE PROGRAM", "", true);
    __ASSERT_EQ(mixal::ParsedType::EMPTY, result.parsedType);
    __ASSERT_EQ("", result.rawLocation);
    __ASSERT_EQ("", result.operation);
    __ASSERT_EQ("", result.rawAddress);
    __ASSERT_EQ("", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("* EXAMPLE PROGRAM", result.comment);
}

__TEST_U(TestParse, test_parse_line_location_and_comment) {
    auto result = mixal::Parser::parseLine("4H LDA 2000,5 P10. Set up line. (Right to left)", "", true);
    __ASSERT_EQ(mixal::ParsedType::INSTRUCTION, result.parsedType);
    __ASSERT_EQ("4H", result.rawLocation);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.rawAddress);
    __ASSERT_EQ("5", result.rawIndex);
    __ASSERT_EQ("", result.rawField);
    __ASSERT_EQ("P10. Set up line. (Right to left)", result.comment);
}

__TEST_U(TestParse, test_parse_line_invalid_location_with_invalid_character) {
    __ASSERT_THROW(mixal::Parser::parseLine("-", "", true), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_location_without_operation) {
    __ASSERT_THROW(mixal::Parser::parseLine("H5", "", true), mixal::ParseError);
    __ASSERT_THROW(mixal::Parser::parseLine("H5  ", "", true), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_operation_with_invalid_begin) {
    __ASSERT_THROW(mixal::Parser::parseLine("-", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_operation_with_invalid_character) {
    __ASSERT_THROW(mixal::Parser::parseLine("L-", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_address_with_invalid_begin) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA %", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_address_with_only_negative_sign) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_address_with_multiple_negative_signs) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA --2000", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_address_with_too_long) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -20000", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_address_with_too_large) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA 5000", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_address_with_invalid_character) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -200%", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_index_with_no_index) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_index_with_invalid_index) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,%", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_index_with_invalid_register) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,7", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_index_with_invalid_character) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2%", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_index_with_invalid_expression) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2-", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_without_first) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_with_invalid_character_in_first) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(%", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_without_connection) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_without_second) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0:", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_with_invalid_connection) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0%", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_with_invalid_second) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0:%", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_without_closing) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0:3", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_with_invalid_expression) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0-)", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_with_invalid_value) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0:-3)", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_with_invalid_closing) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0:3%", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_with_invalid_suffix) {
    __ASSERT_THROW(mixal::Parser::parseLine("LDA -2000,2(0:3)%", "", false), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_with_get_index) {
    try {
        mixal::Parser::parseLine("LDA -2000,2(0:3)x", "", false);
    } catch (mixal::ParseError error) {
        __ASSERT_EQ(16, error.index());
        __ASSERT_EQ(std::string("Unexpected character encountered while parsing digital modification"),
                    std::string(error.what()));
    }
}

__TEST_U(TestParse, test_parse_line_invalid_loc_with_invalid_character) {
    __ASSERT_THROW(mixal::Parser::parseLine("LOC- LDA -2000,2(0:3)x", "", true), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_line_without_address) {
    __ASSERT_THROW(mixal::Parser::parseLine("LOC", "", true), mixal::ParseError);
}

__TEST_U(TestParse, test_parse_line_invalid_field_value) {
    __ASSERT_NO_THROW(mixal::Parser::parseLine("ENTA 0", "", false));
    __ASSERT_THROW(mixal::Parser::parseLine("ENTA 0(1:3)", "", false), mixal::ParseError);
}

}  // namespace test
