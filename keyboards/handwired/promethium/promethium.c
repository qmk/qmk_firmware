#include "keyboard.h"
#include "timer.h"
#include "battery.h"

#ifndef BATTERY_POLL
#    define BATTERY_POLL 30000
#endif

uint8_t battery_level(void) {
    // maintain legacy behaviour and scale 0-100 percent to 0-255
    uint16_t percent = battery_get_percent();
    return  (percent * 255) / 100;
}

__attribute__ ((weak))
void battery_poll(uint8_t level) {
}

void housekeeping_task_kb(void) {
    static uint16_t counter = BATTERY_POLL;
    counter++;

    if (counter > BATTERY_POLL) {
        counter = 0;
        battery_poll(battery_level());
    }
}
