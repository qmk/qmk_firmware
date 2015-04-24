#include "test_env.h"

namespace {
    bool mbed_main_called = false;
}

extern "C" void mbed_main() {
    printf("MBED: mbed_main() call before main()\r\n");
    mbed_main_called = true;
}

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(Call function mbed_main before main);
    MBED_HOSTTEST_START("MBED_A21");

    printf("MBED: main() starts now!\r\n");

    MBED_HOSTTEST_RESULT(mbed_main_called);
}
