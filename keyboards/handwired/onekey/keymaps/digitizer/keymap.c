#include QMK_KEYBOARD_H

#include "digitizer.h"

#include "math.h"

#ifndef ADC_PIN
#    define ADC_PIN F6
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {LAYOUT_ortho_1x1(KC_A)};

uint32_t timer = 0;

void matrix_scan_user() {
    if (timer_elapsed32(timer) < 200) {
        return;
    }
    
    timer               = timer_read32();
    digitizer.x         = 0.5 - 0.2 * cos(timer_read() / 250. / 6.28);
    digitizer.y         = 0.5 - 0.2 * sin(timer_read() / 250. / 6.28);
    digitizer.tipswitch = 0;
    digitizer.inrange   = 1;
    digitizer.status |= DZ_UPDATED;
}
