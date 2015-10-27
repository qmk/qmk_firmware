#include "test_env.h"

int main()
{
    MBED_HOSTTEST_TIMEOUT(5);
    MBED_HOSTTEST_SELECT(hello_auto);
    MBED_HOSTTEST_DESCRIPTION(Hello World);
    MBED_HOSTTEST_START("MBED_10");

    printf("Hello World\r\n");

    while(1);
}
