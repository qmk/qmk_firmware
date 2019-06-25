#include "pulse4k.h"
#include "rgblight.h"

enum combo_events {
    LED_ADJUST
};

const uint16_t PROGMEM led_adjust_combo[] = {KC_LEFT, KC_RGHT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [LED_ADJUST] = COMBO_ACTION(led_adjust_combo)
};

bool led_adjust_active = false;

void matrix_init_kb(void) {
    matrix_init_user();
}

void process_combo_event(uint8_t combo_index, bool pressed) {
    if (combo_index == LED_ADJUST) {
        led_adjust_active = pressed;
    }
}

void encoder_update_kb(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (led_adjust_active) {
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
        } else encoder_one_update(clockwise);
    } else if (index == 1) {
        if (led_adjust_active) {
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
        } else encoder_two_update(clockwise);
    }
}
