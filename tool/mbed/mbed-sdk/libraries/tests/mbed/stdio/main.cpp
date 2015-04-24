#include "mbed.h"
#include "test_env.h"

/* This test purpose is to verify the behaviour when the program does not link
 * any symbol from the mbed library.
 * In the past we had an issue where the stdio retargeting was not linked in.
 */

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(stdio_auto);
    MBED_HOSTTEST_DESCRIPTION(stdio);
    MBED_HOSTTEST_START("MBED_2");

    DigitalOut led1(LED1);
    DigitalOut led2(LED2);

    int value_int;
    

    notify_start(); // Just to sync with host test supervisor

    const char* PRINT_PATTERN = "MBED: Your value was: %d\r\n";

    while (true) {
        // SCANF PRINTF family
        value_int = 0;
        led1 = 1;
        scanf("%d", &value_int);
        printf(PRINT_PATTERN, value_int);
        led1 = 0;

        // FSCANF, FPRINTF family
        value_int = 0;
        led2 = 1;
        fscanf(stdin, "%d", &value_int);
        fprintf(stdout, PRINT_PATTERN, value_int);
        led2 = 0;
    }
}
