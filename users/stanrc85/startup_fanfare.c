#include "stanrc85.h"

static uint8_t top = 0;
static uint8_t middle = 0;
static uint8_t bottom = 0;

static bool is_enabled = true;
static bool is_rgblight_startup = true;
static uint16_t rgblight_startup_loop_timer;

void matrix_scan_user(void) {
    // Boot up "fanfare"
    if (is_rgblight_startup && is_keyboard_master()) {
        if (timer_elapsed(rgblight_startup_loop_timer) > 10) {
            static uint8_t counter;
            counter++;
            if (counter == 1) {
                top = 1;
                writePin(INDICATOR_PIN_0, top);
                wait_ms(300);
                top = 0;
                writePin(INDICATOR_PIN_0, top);
            }
            if (counter == 2) {
                middle = 1;
                writePin(INDICATOR_PIN_1, middle);
                wait_ms(300);
                middle = 0;
                writePin(INDICATOR_PIN_1, middle);
            }
            if (counter == 3) {
                bottom = 1;
                writePin(INDICATOR_PIN_2, bottom);
                wait_ms(300);
                bottom = 0;
                writePin(INDICATOR_PIN_2, bottom);
            }
            if (counter == 4) {
                is_enabled = is_rgblight_startup = false;
            }
        }
    }
}
