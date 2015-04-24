#include "mbed.h"
#include "test_env.h"

int main() {
    MBED_HOSTTEST_TIMEOUT(10);
    MBED_HOSTTEST_SELECT(detect_auto);
    MBED_HOSTTEST_DESCRIPTION(Simple detect test);
    MBED_HOSTTEST_START("DTCT_1");

    notify_start();
    printf("MBED: Target '%s'\r\n", TEST_SUITE_TARGET_NAME);
    printf("MBED: Test ID '%s'\r\n", TEST_SUITE_TEST_ID);
    printf("MBED: UUID '%s'\r\n", TEST_SUITE_UUID);
    MBED_HOSTTEST_RESULT(true);
}
