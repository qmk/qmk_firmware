#include QMK_KEYBOARD_H

#define _DVORAK 0 // Base Dvorak layer
#define _MEDIA 1  // Media layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DVORAK] = LAYOUT(
        // left hand
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5, KC_F6, KC_F7, KC_F8,
        KC_EQL,   KC_1,    KC_2,    KC_3,    KC_4,   KC_5,
        KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,   KC_Y,
        KC_CAPS,  KC_A,    KC_O,    KC_E,    KC_U,   KC_I,
        KC_LSFT,  KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,
                  KC_GRV,  KC_INS, KC_LEFT, KC_RIGHT,
        // left thumb
                            KC_LCTL, KC_LALT,
                                     KC_HOME,
                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
        KC_F9,  KC_F10,   KC_F11,   KC_F12,   KC_PSCR, KC_SLCK, KC_PAUS, KC_FN0, KC_1,
        KC_6,   KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,
        KC_F,   KC_G,     KC_C,     KC_R,     KC_L,    KC_SLSH,
        KC_D,   KC_H,     KC_T,     KC_N,     KC_S,    KC_BSLS,
        KC_B,   KC_M,     KC_W,     KC_V,     KC_Z,    KC_RSFT,
                          KC_UP,  KC_DOWN, KC_LBRC, KC_RBRC,
        // right thumb
        KC_RGUI,    KC_RCTL,
        KC_PGUP,
        KC_PGDN, KC_ENT, KC_SPC
    ),

[_MEDIA] = LAYOUT(
       // left hand
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO,   KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO,
       KC_NO,   KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,
                KC_NO,   KC_NO,   KC_MS_D, KC_MS_U,
        // left thumb
                                           KC_NO,   KC_NO,
                                                    KC_NO,
                                  KC_NO,   KC_NO,   KC_TRNS,
       // right hand
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_POWER,
       KC_NO,   KC_VOLU, KC_MS_U, KC_VOLD, KC_NO,   KC_NO,
       KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,   KC_NO,
       KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,
                KC_MS_L, KC_MS_R, KC_NO,   KC_NO,
       // right thumb
       KC_NO, KC_NO,
       KC_NO,
       KC_TRNS, KC_ENT, KC_NO
)
};
