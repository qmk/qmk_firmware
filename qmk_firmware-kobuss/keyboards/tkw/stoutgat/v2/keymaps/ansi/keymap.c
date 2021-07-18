#include QMK_KEYBOARD_H

enum layers {
    _BL,
    _FL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_65_ansi_blocker(
      KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_GRV,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,  KC_DEL,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,            KC_PGUP,
      KC_LSFT,          KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT,             MO(1), KC_LEFT, KC_DOWN,  KC_RIGHT),

  [1] = LAYOUT_65_ansi_blocker(
     /* esc      1        2        3        4       5       6       7       8       9         0        -         =     bkspc       `~  */
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,   RESET,
     /*  tab      Q       W        E        R        T      Y        U      I        O        P        [         ]        \      delete*/
      RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI, RESET,  KC_TRNS,KC_TRNS,KC_TRNS,KC_INS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_PAUS, KC_TRNS,  KC_TRNS,
     /*  caps     A       S        D        F        G      H        J      K        L        ;        '        enter             pg up*/
      RGB_TOG, RGB_VAD, RGB_SAD, RGB_HUD, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_INS,            KC_HOME,
     /* shift             Z         X        C       V       B       N      M        ,        .        /        shift     up      pg dn*/
      KC_LSFT,          KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS,  KC_RSFT, KC_VOLU,  KC_END,
     /* ctrl     win      alt                              space                    alt      fn       ctrl      left     down     right*/
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_TRNS,                KC_RALT,           KC_TRNS,  KC_TRNS, KC_VOLD,  KC_TRNS)
};

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise){

    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _BL:
                // Move whole words. Hold shift to select while moving.
                if (clockwise) {
                    tap_code16(C(KC_RGHT));
                } else {
                    tap_code16(C(KC_LEFT));
                }
                break;
            default:
                // History scrubbing. For Adobe products, hold shift while moving
                // backward to go forward instead.
                if (clockwise) {
                    tap_code16(C(KC_Z));
                } else {
                    tap_code16(C(KC_Y));
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _BL:
                // Scrolling with PageUp and PgDn.
                if (clockwise) {
                    tap_code16(KC_PGDN);
                } else {
                    tap_code16(KC_PGUP);
                }
                break;
            default:
                if (clockwise) {
                    tap_code16(A(KC_TAB));
                } else {
                    tap_code16(A(S(KC_TAB)));
                }
                break;
        }
    }
}
#endif
