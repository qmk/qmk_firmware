/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "keymap_steno.h"

enum {
    BASE = 0, // default layer
    FUN,      // macros/motion #
    NUM,      // numbers
    PLV       // steno
};

#define DYNAMIC_MACRO_SIZE 256
#define DYNAMIC_MACRO_RANGE SAFE_RANGE
#include "dynamic_macro.h"

#define M_RECD1 DYN_REC_START1
#define M_STOP1 DYN_REC_STOP
#define M_PLAY1 DYN_MACRO_PLAY1

void matrix_init_user() {
    steno_set_mode(STENO_MODE_GEMINI);  // or STENO_MODE_BOLT
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_dynamic_macro(keycode, record);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Keymap 0: Base layer
[BASE] = LAYOUT_gergo(
KC_GRAVE,              KC_Q,  KC_W,   KC_F,   KC_P, KC_B,                  /**/                   KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, KC_EQL,
LT(NUM, KC_PGUP),      KC_A,  KC_R,   KC_S,   KC_T, KC_G, KC_TAB,          /**/          KC_ENT,  KC_M, KC_N, KC_E,    KC_I,   KC_O,    KC_QUOT,
MT(MOD_LSFT, KC_PGDN), KC_Z,  KC_X,   KC_C,   KC_D, KC_V, KC_ESC, KC_LBRC, /**/ KC_RBRC, KC_BSLS, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,

                       KC_LCTL,  KC_LALT,  KC_LCMD, MT(MOD_LSFT, KC_CAPS), /**/ KC_BSPC, KC_RSFT,  LT(FUN, KC_SPC),  MT(MOD_RCTL, KC_DEL)
),

// Keymap 1: Fn layer
[FUN] = LAYOUT_gergo(
TG(PLV), M_RECD1, M_STOP1, M_PLAY1, KC_TRNS, KC_TRNS,                   /**/                   KC_MNXT, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_TRNS,
KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          /**/          KC_MPLY, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /**/ KC_TRNS, KC_MPRV, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_BSLS, KC_PIPE,

                                  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, /**/ KC_TRNS, KC_TRNS,  _______,  RESET
),
// Keymap 2: Numpad/F-key layer
[NUM] = LAYOUT_gergo(
KC_TRNS, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_TRNS,                   /**/                   KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS, KC_TRNS,
_______, KC_TRNS, KC_F4, KC_F5, KC_F6, KC_TRNS, KC_TRNS,          /**/          KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_TRNS, KC_TRNS, KC_TRNS, /**/ KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS,

                            KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, /**/ KC_DEL, KC_TRNS,  KC_0,  KC_DOT
),

[PLV] = LAYOUT_gergo(
STN_N1,  STN_N2,  STN_N3, STN_N4, STN_N5, STN_N6,                   /**/                   STN_N7, STN_N8, STN_N9, STN_NA, STN_NB, STN_NC,
XXXXXXX, XXXXXXX, STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,          /**/          STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR, XXXXXXX,
XXXXXXX, XXXXXXX, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2, TG(PLV), /**/ XXXXXXX, STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR, XXXXXXX,

                                  XXXXXXX,  XXXXXXX,  STN_A, STN_O, /**/ STN_E, STN_U,  KC_TRNS,  XXXXXXX
)
};
