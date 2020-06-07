#include <iostream>
#include "test.h"
#include "parser.h"

namespace test {

class TestParse : public UnitTest {};

__TEST_U(TestParse, test_parse_line_basic_numeric_address_all_1) {
    auto result = mixal::Parser::parseLine("LDA 2000,2(0:3)", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation);
    __ASSERT_EQ("", result.location);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000,2(0:3)", result.address);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.address);
    __ASSERT_EQ(2, result.word.index);
    __ASSERT_EQ(3, result.word.modification);
    __ASSERT_EQ(8, result.word.operation);
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_all_2) {
    auto result = mixal::Parser::parseLine("LDA 2000,2(1:3)", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation);
    __ASSERT_EQ("", result.location);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000,2(1:3)", result.address);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.address);
    __ASSERT_EQ(2, result.word.index);
    __ASSERT_EQ(11, result.word.modification);
    __ASSERT_EQ(8, result.word.operation);
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_no_index) {
    auto result = mixal::Parser::parseLine("LDA 2000(1:3)", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation);
    __ASSERT_EQ("", result.location);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000(1:3)", result.address);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.address);
    __ASSERT_EQ(0, result.word.index);
    __ASSERT_EQ(11, result.word.modification);
    __ASSERT_EQ(8, result.word.operation);
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_only_address) {
    auto result = mixal::Parser::parseLine("LDA 2000", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation);
    __ASSERT_EQ("", result.location);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000", result.address);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.address);
    __ASSERT_EQ(0, result.word.index);
    __ASSERT_EQ(5, result.word.modification);
    __ASSERT_EQ(8, result.word.operation);
}

__TEST_U(TestParse, test_parse_line_basic_numeric_address_no_mod) {
    auto result = mixal::Parser::parseLine("LDA 2000,4", false);
    __ASSERT_EQ(mixal::Instructions::Code::LDA, result.word.operation);
    __ASSERT_EQ("", result.location);
    __ASSERT_EQ("LDA", result.operation);
    __ASSERT_EQ("2000,4", result.address);
    __ASSERT_EQ("", result.comment);
    __ASSERT_EQ(2000, result.word.address);
    __ASSERT_EQ(4, result.word.index);
    __ASSERT_EQ(5, result.word.modification);
    __ASSERT_EQ(8, result.word.operation);
}

}  // namespace test
