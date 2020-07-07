#include <iostream>
#include "test.h"
#include "expression.h"

namespace test {

class TestAtomic : public UnitTest {
};

__TEST_U(TestAtomic, test_equal) {
    __ASSERT_EQ(mixal::Atomic(mixal::AtomicType::INTEGER, 12, true),
                mixal::Atomic(mixal::AtomicType::INTEGER, 12, true));
    __ASSERT_EQ(mixal::Atomic(mixal::AtomicType::SYMBOL, "sym"),
                mixal::Atomic(mixal::AtomicType::SYMBOL, "sym"));
    __ASSERT_EQ(mixal::Atomic(mixal::AtomicType::ASTERISK, "sym"),
                mixal::Atomic(mixal::AtomicType::ASTERISK, "sym"));
    __ASSERT_NE(mixal::Atomic(mixal::AtomicType::SYMBOL, "sym"),
                mixal::Atomic(mixal::AtomicType::ASTERISK, "sym"));
}

__TEST_U(TestAtomic, test_is_local_symbol) {
    __ASSERT_FALSE(mixal::Atomic(mixal::AtomicType::INTEGER, 12, true).isLocalSymbol());
}

}  // namespace test
