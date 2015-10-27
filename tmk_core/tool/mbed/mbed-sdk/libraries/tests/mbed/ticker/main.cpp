#include "mbed.h"
#include "test_env.h"

void print_char(char c = '*')
{
    printf("%c", c);
    fflush(stdout);
}

Ticker flipper_1;
DigitalOut led1(LED1);

void flip_1() {
    static int led1_state = 0;
    if (led1_state) {
        led1 = 0; led1_state = 0;
    } else {
        led1 = 1; led1_state = 1;
    }
    print_char();
}

Ticker flipper_2;
DigitalOut led2(LED2);

void flip_2() {
    static int led2_state = 0;
    if (led2_state) {
        led2 = 0; led2_state = 0;
    } else {
        led2 = 1; led2_state = 1;
    }
}

int main() {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(wait_us_auto);
    MBED_HOSTTEST_DESCRIPTION(Ticker Int);
    MBED_HOSTTEST_START("MBED_11");

    led1 = 0;
    led2 = 0;
    flipper_1.attach(&flip_1, 1.0); // the address of the function to be attached (flip) and the interval (1 second)
    flipper_2.attach(&flip_2, 2.0); // the address of the function to be attached (flip) and the interval (2 seconds)

    while (true) {
        wait(1.0);
    }
}
