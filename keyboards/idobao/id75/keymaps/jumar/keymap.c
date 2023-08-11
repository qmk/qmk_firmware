#include QMK_KEYBOARD_H
#include "jumar.h"

#define LAYOUT LAYOUT_ortho_5x15

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_0_QWERTY] = LAYOUT_wrapper(
                                   ROW5_LEFT_BASE, KC_CUT  , TG(5), KC_PSCR, ROW5_RIGHT_BASE,
                                   ROW4_LEFT_BASE, KC_COPY , TG(4), XXXXXXX, ROW4_RIGHT_BASE,
                                   ROW3_LEFT_BASE, KC_PASTE, TG(3), XXXXXXX, ROW3_RIGHT_BASE,
                                   ROW2_LEFT_BASE, KC_APP  , TG(2), KC_INS , ROW2_RIGHT_BASE,
        XXXXXXX, XXXXXXX, XXXXXXX, ROW1_LEFT_BASE, KC_BSPC , TG(1), KC_DEL , ROW1_RIGHT_BASE, XXXXXXX, XXXXXXX, XXXXXXX
    ),
	[_1_SYMBOLS_NUMPAD] = LAYOUT_wrapper(
                    ROW5_LEFT_SYMB_NUMPAD, _______, XXXXXXX, _______, ROW5_RIGHT_SYMB_NUMPAD,
                    ROW4_LEFT_SYMB_NUMPAD, _______, XXXXXXX, _______, ROW4_RIGHT_SYMB_NUMPAD,
                    ROW3_LEFT_SYMB_NUMPAD, _______, XXXXXXX, _______, ROW3_RIGHT_SYMB_NUMPAD,
                    ROW2_LEFT_SYMB_NUMPAD, _______, XXXXXXX, _______, ROW2_RIGHT_SYMB_NUMPAD,
        THREE_TRNS, ROW1_LEFT_SYMB_NUMPAD, _______, _______, _______, ROW1_RIGHT_SYMB_NUMPAD, THREE_TRNS
    ),
	[_2_MOUSE_MEDIA] = LAYOUT_wrapper(
                    ROW5_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, ROW5_RIGHT_MOUSE_MEDIA,
                    ROW4_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, ROW4_RIGHT_MOUSE_MEDIA,
                    ROW3_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, ROW3_RIGHT_MOUSE_MEDIA,
                    ROW2_LEFT_MOUSE_MEDIA, XXXXXXX, _______, XXXXXXX, ROW2_RIGHT_MOUSE_MEDIA,
        THREE_TRNS, ROW1_LEFT_MOUSE_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, ROW1_RIGHT_MOUSE_MEDIA, THREE_TRNS
    ),
	[_3_NAV] = LAYOUT_wrapper(
                    ROW5_LEFT_NAV_CPY_PASTA, _______, XXXXXXX, _______, ROW5_RIGHT_NAV_CPY_PASTA,
                    ROW4_LEFT_NAV_CPY_PASTA, _______, XXXXXXX, _______, ROW4_RIGHT_NAV_CPY_PASTA,
                    ROW3_LEFT_NAV_CPY_PASTA, _______, _______, _______, ROW3_RIGHT_NAV_CPY_PASTA,
                    ROW2_LEFT_NAV_CPY_PASTA, _______, XXXXXXX, _______, ROW2_RIGHT_NAV_CPY_PASTA,
        THREE_TRNS, ROW1_LEFT_NAV_CPY_PASTA, _______, XXXXXXX, _______, ROW1_RIGHT_NAV_CPY_PASTA, THREE_TRNS
    ),
	[_4_GAM] = LAYOUT_ortho_5x15(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, XXXXXXX, _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______, _______, KC_PGUP, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_CAPS, KC_A   , LSFT_S , KC_D   , LCTL_F , KC_G   , _______, XXXXXXX, KC_PGDN, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______, XXXXXXX, _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_ESC ,
        KC_LCTL, _______, KC_LGUI, _______, KC_LALT, KC_SPC , KC_BSPC, XXXXXXX, KC_DEL , KC_ENT , KC_SLSH, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
   [_5_RGB] = LAYOUT_wrapper(
                    ROW5_LEFT_RGB, XXXXXXX, _______, XXXXXXX, ROW5_RIGHT_RGB,
                    ROW4_LEFT_RGB, XXXXXXX, XXXXXXX, XXXXXXX, ROW4_RIGHT_RGB,
                    ROW3_LEFT_RGB, XXXXXXX, XXXXXXX, XXXXXXX, ROW3_RIGHT_RGB,
                    ROW2_LEFT_RGB, XXXXXXX, XXXXXXX, XXXXXXX, ROW2_RIGHT_RGB,
        THREE_TRNS, ROW1_LEFT_RGB, XXXXXXX, XXXXXXX, XXXXXXX, ROW1_RIGHT_RGB, THREE_TRNS
    ),
};

void matrix_init_user(void) {
    matrix_init_user_RGB_LYR();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  process_record_user_RGB(keycode, record);
  return true;
}
