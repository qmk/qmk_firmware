#include "promethium.h"
#include "analog.h"
#include "timer.h"
#include "matrix.h"

float battery_percentage(void) {
    float voltage = analogRead(BATTERY_PIN) * 2 * 3.3 / 1024;
    float percentage = (voltage - 3.5) * 143;
    if (percentage > 100) {
        return 100;
    } else if (percentage < 0) {
        return 0;
    } else {
        return percentage;
    }
}

__attribute__ ((weak))
void battery_poll(float percentage) {
}

void matrix_init_kb(void) {
	matrix_init_user();
}

void matrix_scan_kb(void) {
    static uint16_t counter = BATTERY_POLL;
    counter++;

    if (counter > BATTERY_POLL) {
        counter = 0;
        battery_poll(battery_percentage());
    }

    matrix_scan_user();
}


