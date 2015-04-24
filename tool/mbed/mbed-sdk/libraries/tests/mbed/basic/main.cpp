#include "test_env.h"

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(Basic);
    MBED_HOSTTEST_START("MBED_A1");
    MBED_HOSTTEST_RESULT(true);
}
