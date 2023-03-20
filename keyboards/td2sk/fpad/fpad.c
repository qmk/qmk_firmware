#include "i2c_master.h"

#include QMK_KEYBOARD_H

#include <stdbool.h>

#include "drivers/xl9555.h"
#include "gpio.h"

void additional_action_unregister(void) {}

static uint8_t prev_pressed             = 0;
static uint8_t additional_keys_map[][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {2, 4}, {4, 4}};

void additional_button_scan(void) {
    uint16_t pressed = XL9555_read() >> 10;
    if (readPin(B1)) {
        pressed |= 0b00100000;
    }
    uint8_t changed = prev_pressed ^ pressed;
    for (uint8_t i = 0; i < 6; ++i) {
        uint8_t mask = 1 << i;
        if (changed & mask) {
            action_exec(MAKE_KEYEVENT(additional_keys_map[i][0], additional_keys_map[i][1], (pressed >> i) & 1));
        }
    }
    prev_pressed = pressed;
}

void keyboard_post_init_user(void) {
    setPinInputHigh(B1);
    i2c_init();
    XL9555_set_polarity(0xFF, 0b10000011);
}

void matrix_scan_user(void) {
    additional_button_scan();
}

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {[0] = JOYSTICK_AXIS_IN(F7, 102, 512, 922), [1] = JOYSTICK_AXIS_IN(F6, 102, 512, 922)};
