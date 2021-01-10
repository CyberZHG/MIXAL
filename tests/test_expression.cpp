#include <iostream>
#include <gtest/gtest.h>
#include "expression.h"

TEST(TestExpression, test_parse_integer_100) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("100", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(100, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_neg_100) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("-100", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(-100, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_neg_0) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("-0", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(0, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_neg_0_plus_0) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("-0+0", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(0, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_neg_0_plus_1_sub_1) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("-0+1-1", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(0, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_add) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("1+2", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(3, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_sub) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("1-2", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(-1, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_mul) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("22*33", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(726, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_mul_neg) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("-22*-33", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(726, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_mul_pos) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("+22*+33", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(726, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_floor_div) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("13/3", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(4, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_integer_field) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("2*3:7", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(55, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_symbol) {
    auto expression = mixal::Expression();
    std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("SYMBOL", "");
    EXPECT_FALSE(expression.evaluate(environment));
    environment["SYMBOL"] = mixal::AtomicValue(42);
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(42, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_symbol_neg) {
    auto expression = mixal::Expression();
    std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("-SYMBOL", "");
    EXPECT_FALSE(expression.evaluate(environment));
    environment["SYMBOL"] = mixal::AtomicValue(42);
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(-42, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}

TEST(TestExpression, test_parse_symbol_ops) {
    auto expression = mixal::Expression();
    std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("A+B*C/D:E", "");
    EXPECT_FALSE(expression.evaluate(environment));
    environment["A"] = mixal::AtomicValue(3);
    environment["B"] = mixal::AtomicValue(4);
    environment["C"] = mixal::AtomicValue(5);
    environment["D"] = mixal::AtomicValue(2);
    environment["E"] = mixal::AtomicValue(1);
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(137, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_asterisk) {
    auto expression = mixal::Expression();
    std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("*", "ORIG");
    EXPECT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(-13);
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(-13, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}

TEST(TestExpression, test_parse_asterisk_neg) {
    auto expression = mixal::Expression();
    std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("-*", "ORIG");
    EXPECT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(0);
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(0, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}

TEST(TestExpression, test_parse_asterisk_pos) {
    auto expression = mixal::Expression();
    std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("+*", "ORIG");
    EXPECT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(0);
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(0, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_asterisk_mul) {
    auto expression = mixal::Expression();
    std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("***", "ORIG");
    EXPECT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(-2);
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_TRUE(expression.evaluated());
    EXPECT_EQ(4, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_asterisk_mul_symbol) {
    auto expression = mixal::Expression();
    std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("**X**", "ORIG");
    EXPECT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(-2);
    EXPECT_FALSE(expression.evaluate(environment));
    environment["X"] = mixal::AtomicValue(3);
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(12, expression.result().value);
    EXPECT_EQ(false, expression.result().negative);
}

TEST(TestExpression, test_parse_invalid_empty) {
    auto expression = mixal::Expression();
    EXPECT_THROW(expression.parse("", ""), mixal::ExpressionError);
    EXPECT_THROW(expression.parse("+", ""), mixal::ExpressionError);
    EXPECT_THROW(expression.parse("-", ""), mixal::ExpressionError);
}

TEST(TestExpression, test_parse_invalid_begin) {
    auto expression = mixal::Expression();
    EXPECT_THROW(expression.parse("&", ""), mixal::ExpressionError);
}

TEST(TestExpression, test_parse_invalid_missing_atomic) {
    auto expression = mixal::Expression();
    EXPECT_THROW(expression.parse("**", ""), mixal::ExpressionError);
    EXPECT_THROW(expression.parse("+**", ""), mixal::ExpressionError);
    EXPECT_THROW(expression.parse("-**", ""), mixal::ExpressionError);
}

TEST(TestExpression, test_parse_invalid_operator) {
    auto expression = mixal::Expression();
    EXPECT_THROW(expression.parse("1&2", ""), mixal::ExpressionError);
    EXPECT_THROW(expression.parse("1///2", ""), mixal::ExpressionError);
    EXPECT_THROW(expression.parse("*&*", ""), mixal::ExpressionError);
    EXPECT_THROW(expression.parse("*///*", ""), mixal::ExpressionError);
}

TEST(TestExpression, test_parse_invalid_symbol_character) {
    auto expression = mixal::Expression();
    EXPECT_THROW(expression.parse("1+WHAT_", ""), mixal::ExpressionError);
}

TEST(TestExpression, test_const_expression) {
    auto expression = mixal::Expression();
    expression = mixal::Expression::getConstExpression(mixal::AtomicValue(-128));
    EXPECT_TRUE(expression.evaluated());
    EXPECT_EQ(-128, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}

TEST(TestExpression, test_expression_invalid_large_integer) {
    auto expression = mixal::Expression();
    EXPECT_THROW(expression.parse("12345678901234", ""), mixal::ExpressionError);
}

TEST(TestExpression, test_expression_evaluate_before_parse) {
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    EXPECT_FALSE(mixal::Expression().evaluate(environment));
}

TEST(TestExpression, test_expression_equal) {
    EXPECT_TRUE(mixal::Expression("1+2") == mixal::Expression("+1++2"));
    EXPECT_TRUE(mixal::Expression("*") != mixal::Expression("*-***"));
    EXPECT_TRUE(mixal::Expression("+0") == mixal::Expression("-0"));
    EXPECT_TRUE(mixal::Expression("1/2") != mixal::Expression("1:2"));
}

TEST(TestExpression, test_expression_end_char) {
    auto expression = mixal::Expression();
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    expression.parse("-12#456", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(-12, expression.result().value);
    EXPECT_EQ(true, expression.result().negative);
}
