#include "mbed.h"
#include "cmsis_os.h"

DigitalOut LEDs[4] = {
    DigitalOut(LED1), DigitalOut(LED2), DigitalOut(LED3), DigitalOut(LED4)
};

void blink(void const *n) {
    LEDs[(int)n] = !LEDs[(int)n];
}

osTimerDef(blink_0, blink);
osTimerDef(blink_1, blink);
osTimerDef(blink_2, blink);
osTimerDef(blink_3, blink);

int main(void) {
    osTimerId timer_0 = osTimerCreate(osTimer(blink_0), osTimerPeriodic, (void *)0);
    osTimerId timer_1 = osTimerCreate(osTimer(blink_1), osTimerPeriodic, (void *)1);
    osTimerId timer_2 = osTimerCreate(osTimer(blink_2), osTimerPeriodic, (void *)2);
    osTimerId timer_3 = osTimerCreate(osTimer(blink_3), osTimerPeriodic, (void *)3);

    osTimerStart(timer_0, 2000);
    osTimerStart(timer_1, 1000);
    osTimerStart(timer_2,  500);
    osTimerStart(timer_3,  250);

    osDelay(osWaitForever);
}
