#include "test.h"

using test::Framework;

int main() {
    Framework* framework = Framework::getInstance();
    framework->hidePassed();
    framework->runTests();
    framework->print();
    framework->finish();
    return framework->isAllPassed() ? 0 : -1;
}
