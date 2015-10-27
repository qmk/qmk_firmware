#include "CommandLineTestRunner.h"
#include <stdio.h>
#include "mbed.h"
#include "testrunner.h"
#include "test_env.h"

/**
Object 'mbed_cpputest_console' is used to show prints on console.
It is declared in \cpputest\src\Platforms\armcc\UtestPlatform.cpp
*/
Serial mbed_cpputest_console(STDIO_UART_TX, STDIO_UART_RX);

int main(int ac, char** av) {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(Unit test);
    MBED_HOSTTEST_START("UT");

    unsigned failureCount = 0;
    {
        // Some compilers may not pass ac, av so we need to supply them ourselves
        int ac = 2;
        char* av[] = {__FILE__, "-v"};
        failureCount = CommandLineTestRunner::RunAllTests(ac, av);
    }

    MBED_HOSTTEST_RESULT(failureCount == 0);
    return failureCount;
}
