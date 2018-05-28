#include QMK_KEYBOARD_H
#include "dhertz.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_iso(
      KC_ESC, KC_1,  KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
      KC_TAB,  KC_Q,  KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_HOME,
      CTL_T(KC_F19),   KC_A,  KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT, KC_END,
      KC_LSFT, HSH_TLD, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
      CTL_T(KC_F18), KC_LALT, KC_FN0, LT(1, KC_SPC), KC_FN1, KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT
      ),
  [1] = LAYOUT_iso(
      KC_NUBS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F10, KC_F11, KC_TRNS, ISO_COUNTRY_CODE,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CMD_SFT_L, KC_TRNS, KC_TRNS, KC_NUBS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_NUBS, KC_TRNS, KC_TRNS, CMD_ALT_C, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDOWN, KC_END
      ),
};

void matrix_scan_keymap(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case 0:
            rgblight_setrgb_teal();
            break;
        case 1:
            rgblight_setrgb_magenta();
            break;
        default:
            // none
            break;
    }
};
