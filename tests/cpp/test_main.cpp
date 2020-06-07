#include "test.h"

using test::Framework;

int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->print();
    framework->finish();
    return framework->isAllPassed() ? 0 : -1;
}
