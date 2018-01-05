#include "sweet16.h"

enum custom_keycodes {
  UP_URL = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,   KC_ASTR, 
        KC_4, KC_5,   KC_6,   KC_SLSH, 
        KC_1, KC_2,   KC_3,   KC_MINS, 
        KC_0, KC_ENT, KC_DOT, KC_EQL
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UP_URL:
            if (record->event.pressed) {
                SEND_STRING("http://1upkeyboads.com");
            }
            return false;
            break;
    }
    return true;
}