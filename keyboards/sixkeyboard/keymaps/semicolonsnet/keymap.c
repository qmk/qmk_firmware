#include QMK_KEYBOARD_H


enum custom_keycodes {
    QMKPASS = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKPASS:
        if (record->event.pressed) {
            // when keycode QMKPASS is pressed
            SEND_STRING("Sample string");
        } else {
            // when keycode QMKPASS is released
        }
        break;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_ESC, SGUI(KC_R), SGUI(KC_S), QMKPASS, SGUI(KC_A), SGUI(KC_V))
};

