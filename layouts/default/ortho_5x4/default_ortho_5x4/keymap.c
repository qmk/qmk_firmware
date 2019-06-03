#include QMK_KEYBOARD_H

enum custom_keycodes {
    KC_P00 = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case KC_P00:
                // types Numpad 0 twice
                SEND_STRING(SS_TAP(X_KP_0) SS_TAP(X_KP_0));
                return false;
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_5x4(
    TG(1),   KC_PSLS, KC_PAST, KC_PMNS, \
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
    KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
    KC_P0,   KC_P00,  KC_PDOT, KC_PENT  \
  ),

  [1] = LAYOUT_ortho_5x4(
    _______, _______, _______, _______, \
    KC_HOME, KC_UP,   KC_PGUP, _______, \
    KC_LEFT, XXXXXXX, KC_RGHT, _______, \
    KC_END,  KC_DOWN, KC_PGDN, _______, \
    KC_INS,  XXXXXXX, KC_DEL,  _______  \
  ),
};
