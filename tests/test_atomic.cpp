#include <iostream>
#include <gtest/gtest.h>
#include "expression.h"

TEST(TestAtomic, test_equal) {
    EXPECT_EQ(mixal::Atomic(mixal::AtomicType::INTEGER, 12, true),
                mixal::Atomic(mixal::AtomicType::INTEGER, 12, true));
    EXPECT_EQ(mixal::Atomic(mixal::AtomicType::SYMBOL, "sym"),
                mixal::Atomic(mixal::AtomicType::SYMBOL, "sym"));
    EXPECT_EQ(mixal::Atomic(mixal::AtomicType::ASTERISK, "sym"),
                mixal::Atomic(mixal::AtomicType::ASTERISK, "sym"));
    EXPECT_NE(mixal::Atomic(mixal::AtomicType::SYMBOL, "sym"),
                mixal::Atomic(mixal::AtomicType::ASTERISK, "sym"));
}

TEST(TestAtomic, test_is_local_symbol) {
    EXPECT_FALSE(mixal::Atomic(mixal::AtomicType::INTEGER, 12, true).isLocalSymbol());
}
