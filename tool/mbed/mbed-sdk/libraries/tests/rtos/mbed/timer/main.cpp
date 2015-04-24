#include "mbed.h"
#include "test_env.h"
#include "rtos.h"

DigitalOut LEDs[4] = {
    DigitalOut(LED1), DigitalOut(LED2), DigitalOut(LED3), DigitalOut(LED4)
};

void print_char(char c = '*')
{
    printf("%c", c);
    fflush(stdout);
}

void blink(void const *n) {
    static int counter = 0;
    const int led_id = int(n);
    LEDs[led_id] = !LEDs[led_id];
    if (++counter == 75) {
        print_char();
        counter = 0;
    }
}

int main(void) {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(wait_us_auto);
    MBED_HOSTTEST_DESCRIPTION(Timer);
    MBED_HOSTTEST_START("RTOS_7");

    RtosTimer led_1_timer(blink, osTimerPeriodic, (void *)0);
    RtosTimer led_2_timer(blink, osTimerPeriodic, (void *)1);
    RtosTimer led_3_timer(blink, osTimerPeriodic, (void *)2);
    RtosTimer led_4_timer(blink, osTimerPeriodic, (void *)3);

    led_1_timer.start(200);
    led_2_timer.start(100);
    led_3_timer.start(50);
    led_4_timer.start(25);

    Thread::wait(osWaitForever);
}
