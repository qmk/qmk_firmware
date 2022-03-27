
#include "blacktyl.h"

void keyboard_post_init_user(void) {
    // rgblight_enable();
    // rgblight_sethsv_cyan();
    // rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
    // debug_config.enable = true;
    // debug_config.matrix = true;
    // debug_config.keyboard = true;
    // debug_config.mouse    = true;

    if (is_keyboard_left()) {
        dprintln("I'm left!");
    } else {
        dprintln("I'm right!");
    }
}

void housekeeping_task_user(void) {
    static uint16_t start = 0;
    if (timer_elapsed(start) > 1000) {
        start = timer_read();
        dprintf("Fresh into eeprom %d\n", (uint8_t)start);
        eeconfig_update_debug((uint8_t)start);
        dprintf("Fresh from eeprom %d\n", (uint8_t)eeconfig_read_debug());
    }
}
