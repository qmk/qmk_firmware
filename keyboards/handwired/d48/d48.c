#include "d48.h"
#include "smoothled.h"
#include "dmc12.h"

#ifdef LIGHTMODE_ENABLE

/* Light modes switcher */

uint8_t light_mode = SMOOTHLED;

void set_light_mode(light_mode_t value, uint32_t color) {
    light_mode = value;
    if (light_mode == SMOOTHLED) {
        smoothled_set(color);
    } else {
        dmc12_start(color, true);
    }
}

void process_light_mode(void) {
    if (light_mode == SMOOTHLED) {
        smoothled_process();
    } else {
        dmc12_process();
    }
}

void update_light_mode(uint32_t color) {
    if (light_mode == SMOOTHLED) {
        smoothled_set(color);
    } else {
        dmc12_start(color, false);
    }
}

void next_light_mode(uint32_t color) {
    light_mode = (light_mode + 1) % LIGHT_MODE_SIZE;
    set_light_mode(light_mode, color);
}

void matrix_scan_kb(void) {
    process_light_mode();
    matrix_scan_user();
}

#endif
