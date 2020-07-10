#include <iostream>
#include "test.h"
#include "expression.h"

namespace test {

class TestExpression : public UnitTest {
 public:
    mixal::Expression expression;
    std::unordered_map<std::string, mixal::AtomicValue> environment;

    TestExpression() : expression(), environment() {}

    void setUpEach() final {
        expression = mixal::Expression();
        environment.clear();
    }
};

__TEST_U(TestExpression, test_parse_integer_100) {
    expression.parse("100", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(100, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_neg_100) {
    expression.parse("-100", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(-100, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_neg_0) {
    expression.parse("-0", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(0, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_neg_0_plus_0) {
    expression.parse("-0+0", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(0, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_neg_0_plus_1_sub_1) {
    expression.parse("-0+1-1", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(0, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_add) {
    expression.parse("1+2", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(3, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_sub) {
    expression.parse("1-2", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(-1, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_mul) {
    expression.parse("22*33", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(726, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_mul_neg) {
    expression.parse("-22*-33", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(726, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_mul_pos) {
    expression.parse("+22*+33", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(726, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_floor_div) {
    expression.parse("13/3", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(4, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_integer_field) {
    expression.parse("2*3:7", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(55, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_symbol) {
    expression.parse("SYMBOL", "");
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["SYMBOL"] = mixal::AtomicValue(42);
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(42, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_symbol_neg) {
    expression.parse("-SYMBOL", "");
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["SYMBOL"] = mixal::AtomicValue(42);
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(-42, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_symbol_ops) {
    expression.parse("A+B*C/D:E", "");
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["A"] = mixal::AtomicValue(3);
    environment["B"] = mixal::AtomicValue(4);
    environment["C"] = mixal::AtomicValue(5);
    environment["D"] = mixal::AtomicValue(2);
    environment["E"] = mixal::AtomicValue(1);
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(137, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_asterisk) {
    expression.parse("*", "ORIG");
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(-13);
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(-13, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_asterisk_neg) {
    expression.parse("-*", "ORIG");
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(0);
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(0, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_asterisk_pos) {
    expression.parse("+*", "ORIG");
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(0);
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(0, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_asterisk_mul) {
    expression.parse("***", "ORIG");
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(-2);
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_TRUE(expression.evaluated());
    __ASSERT_EQ(4, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_asterisk_mul_symbol) {
    expression.parse("**X**", "ORIG");
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["ORIG"] = mixal::AtomicValue(-2);
    __ASSERT_FALSE(expression.evaluate(environment));
    environment["X"] = mixal::AtomicValue(3);
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(12, expression.result().value);
    __ASSERT_EQ(false, expression.result().negative);
}

__TEST_U(TestExpression, test_parse_invalid_empty) {
    __ASSERT_THROW(expression.parse("", ""), mixal::ExpressionError);
    __ASSERT_THROW(expression.parse("+", ""), mixal::ExpressionError);
    __ASSERT_THROW(expression.parse("-", ""), mixal::ExpressionError);
}

__TEST_U(TestExpression, test_parse_invalid_begin) {
    __ASSERT_THROW(expression.parse("&", ""), mixal::ExpressionError);
}

__TEST_U(TestExpression, test_parse_invalid_missing_atomic) {
    __ASSERT_THROW(expression.parse("**", ""), mixal::ExpressionError);
    __ASSERT_THROW(expression.parse("+**", ""), mixal::ExpressionError);
    __ASSERT_THROW(expression.parse("-**", ""), mixal::ExpressionError);
}

__TEST_U(TestExpression, test_parse_invalid_operator) {
    __ASSERT_THROW(expression.parse("1&2", ""), mixal::ExpressionError);
    __ASSERT_THROW(expression.parse("1///2", ""), mixal::ExpressionError);
    __ASSERT_THROW(expression.parse("*&*", ""), mixal::ExpressionError);
    __ASSERT_THROW(expression.parse("*///*", ""), mixal::ExpressionError);
}

__TEST_U(TestExpression, test_parse_invalid_symbol_character) {
    __ASSERT_THROW(expression.parse("1+WHAT_", ""), mixal::ExpressionError);
}

__TEST_U(TestExpression, test_const_expression) {
    expression = mixal::Expression::getConstExpression(mixal::AtomicValue(-128));
    __ASSERT_TRUE(expression.evaluated());
    __ASSERT_EQ(-128, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

__TEST_U(TestExpression, test_expression_invalid_large_integer) {
    __ASSERT_THROW(expression.parse("12345678901234", ""), mixal::ExpressionError);
}

__TEST_U(TestExpression, test_expression_evaluate_before_parse) {
    __ASSERT_FALSE(mixal::Expression().evaluate(environment));
}

__TEST_U(TestExpression, test_expression_equal) {
    __ASSERT_EQ(mixal::Expression("1+2"), mixal::Expression("+1++2"));
    __ASSERT_NE(mixal::Expression("*"), mixal::Expression("*-***"));
    __ASSERT_NE(mixal::Expression("+0"), mixal::Expression("-0"));
    __ASSERT_NE(mixal::Expression("1/2"), mixal::Expression("1:2"));
}

__TEST_U(TestExpression, test_expression_end_char) {
    expression.parse("-12#456", "");
    __ASSERT_TRUE(expression.evaluate(environment));
    __ASSERT_EQ(-12, expression.result().value);
    __ASSERT_EQ(true, expression.result().negative);
}

}  // namespace test
