#include QMK_KEYBOARD_H

enum custom_keycodes {
    KC_HELLO = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_HELLO)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_HELLO:
            if (record->event.pressed) {
                println("Hello world!");
            }
            return false;
    }
    return true;
}
