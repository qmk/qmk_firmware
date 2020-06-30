#include <stdint.h>
#include "annepro2.h"

enum anne_pro_layers {
  _BASE_LAYER,
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE_LAYER] = KEYMAP( /* Base */
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,   KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,  KC_BSLS,
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,         KC_ENT,
    KC_LSFT,KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    KC_LCTL,KC_LGUI, KC_LALT,      KC_SPC,             KC_RALT,  KC_RGUI,  KC_RGUI, KC_RCTL
  )
};

const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    return layer;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
