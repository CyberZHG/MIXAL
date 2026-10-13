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

TEST(TestExpression, test_expression_w_value) {
    const std::unordered_map<std::string, mixal::AtomicValue> environment = {{"B", mixal::AtomicValue(100)}};
    auto expression = mixal::Expression("1,-1000(0:2)", "");
    EXPECT_TRUE(expression.isWValue());
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(-((1000 << 18) + 1), expression.result().value);
    EXPECT_TRUE(expression.result().negative);

    expression.parse("-1000(0:2),1", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(1, expression.result().value);
    EXPECT_FALSE(expression.result().negative);

    expression.parse("2(1:1),1(3:3),B(4:5)", "");
    EXPECT_EQ(1u, expression.depends().size());
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ((2 << 24) + (1 << 12) + 100, expression.result().value);

    expression.parse("-0(0:0)", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(0, expression.result().value);
    EXPECT_TRUE(expression.result().negative);

    expression.parse("=1(1:1)=", "");
    EXPECT_TRUE(expression.literalConstant());
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(1 << 24, expression.result().value);
}

TEST(TestExpression, test_expression_w_value_invalid) {
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    EXPECT_THROW(mixal::Expression("1,", ""), mixal::ExpressionError);
    EXPECT_THROW(mixal::Expression("1(1:1", ""), mixal::ExpressionError);
    auto expression = mixal::Expression("1(3:2)", "");
    EXPECT_THROW(expression.evaluate(environment), mixal::ExpressionError);
}

TEST(TestExpression, test_expression_float_div) {
    const std::unordered_map<std::string, mixal::AtomicValue> environment;
    auto expression = mixal::Expression("1//2", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(1 << 29, expression.result().value);
    expression.parse("1//3+1", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ((1 << 30) / 3 + 1, expression.result().value);
    expression.parse("-1//4", "");
    EXPECT_TRUE(expression.evaluate(environment));
    EXPECT_EQ(-(1 << 28), expression.result().value);
    EXPECT_THROW(expression.parse("1///2", ""), mixal::ExpressionError);
}
