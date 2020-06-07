#include "test.h"

using test::Framework;

int main() {
    Framework* framework = Framework::getInstance();
    framework->runTests();
    framework->print();
    framework->finish();
    if (framework->isTestFailed()) {
        return -1;
    }
    return 0;
}
