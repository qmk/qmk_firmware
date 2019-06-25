#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layers {
  DEFAULT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = {
        { KC_END,  KC_UP,   KC__MUTE },
        { KC_LEFT, KC_DOWN, KC_RGHT  }
    }
};

void matrix_init_user(void) {
}

void encoder_one_update(bool clockwise) {
    if (clockwise) {
        tap_code(KC_PGDN);
    } else {
        tap_code(KC_PGUP);
    }
}

void encoder_two_update(bool clockwise) {
    if (clockwise) {
        tap_code(KC__VOLUP);
    } else {
        tap_code(KC__VOLDOWN);
    }
}
