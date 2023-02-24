#include "promethium.h"
#include "analog.h"
#include "timer.h"
#include "matrix.h"
#include "bluefruit_le.h"

// cubic fit {3.3, 0}, {3.5, 2.9}, {3.6, 5}, {3.7, 8.6}, {3.8, 36},  {3.9, 62}, {4.0, 73}, {4.05, 83}, {4.1, 89}, {4.15, 94}, {4.2, 100}

uint8_t battery_level(void) {
    float voltage = bluefruit_le_read_battery_voltage() * 2 * 3.3 / 1024;
    if (voltage < MIN_VOLTAGE) return 0;
    if (voltage > MAX_VOLTAGE) return 255;
    return (voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE) * 255;
}

__attribute__ ((weak))
void battery_poll(uint8_t level) {
}

void matrix_scan_kb(void) {
    static uint16_t counter = BATTERY_POLL;
    counter++;

    if (counter > BATTERY_POLL) {
        counter = 0;
        battery_poll(battery_level());
    }

    matrix_scan_user();
}
