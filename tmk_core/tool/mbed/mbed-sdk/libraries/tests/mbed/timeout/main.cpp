#include "mbed.h"
#include "test_env.h"

Timeout timer;
DigitalOut led(LED1);

namespace {
    const int MS_INTERVALS = 1000;
}

void print_char(char c = '*') {
    printf("%c", c);
    fflush(stdout);
}

void toggleOff(void);

void toggleOn(void) {
    static int toggle_counter = 0;
    if (toggle_counter == MS_INTERVALS) {
        led = !led;
        print_char();
        toggle_counter = 0;
    }
    toggle_counter++;
    timer.attach_us(toggleOff, 500);
}

void toggleOff(void) {
    timer.attach_us(toggleOn, 500);
}

int main() {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(wait_us_auto);
    MBED_HOSTTEST_DESCRIPTION(Timeout Int us);
    MBED_HOSTTEST_START("MBED_24");

    toggleOn();

    while (1);
}
