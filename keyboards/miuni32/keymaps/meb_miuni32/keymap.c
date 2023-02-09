#include QMK_KEYBOARD_H

enum layers {
    STARCRAFT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [STARCRAFT] = LAYOUT_ortho_3x11(
        KC_ESC ,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10    , KC_F11 ,   KC_F12 ,   KC_PGUP,   KC_PSCR,
        KC_LSFT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6     , KC_F7  ,   KC_F8  ,   KC_PGDN,   KC_INS ,
        KC_LCTL,   KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 ,   KC_LALT   , KC_VOLD,   KC_VOLU,   KC_NO  ,   KC_MPLY
    )

};
