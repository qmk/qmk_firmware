#include QMK_KEYBOARD_H
#include "quantum.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _FN,
    _ADJ
};

#define FN_ESC   LT(_FN, KC_ESC)
#define FN_CAPS  LT(_FN, KC_CAPS)
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK)


#define _LAYOUT( \
/*       0    1    2    3    4    5    6    7    8    9    10   11     12 */\
/* 0 */  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11,   K12, \
/* 1 */  K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24,        \
/* 2 */  K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37,        \
/* 3 */  K38, K39, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49,   K50, \
/* 4 */  K51, K52, K53, K54, K55, K56, K57, K58, K59, K60, K61, K62         \
  ) { \
/* 0 */{ K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11,   K12   }, \
/* 1 */{ K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24,   KC_NO }, \
/* 2 */{ K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37,   KC_NO }, \
/* 3 */{ K38, K39, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49,   K50   }, \
/* 4 */{ K51, K52, K53, K54, K55, K56, K57, K58, K59, K60, K61, KC_NO, K62   }  \
  }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = _LAYOUT( \
        GRAVE_ESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_DEL, \
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,         \
        FN_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,          \
        KC_LSFT,   KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,\
        KC_LCTL,   KC_LGUI, KC_LALT, RGB_TOG, MO(_ADJ),KC_SPC, KC_SPC, MO(_FN), KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT         \
    ),

    [_COLEMAK] = _LAYOUT( \
        GRAVE_ESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_DEL, \
        KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,   KC_J,   KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,         \
        FN_ESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,   KC_H,   KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,          \
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_ENT, \
        KC_LCTL,   KC_LGUI, KC_LALT, RGB_TOG, MO(_ADJ),KC_SPC, KC_SPC, MO(_FN), KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT         \
    ),

    [_FN] = _LAYOUT( \
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_PSCR, \
        _______, KC_PGDN, KC_UP,   KC_PGUP, _______, _______, _______, KC_PGDN, KC_UP,   KC_PGUP, KC_PSCR, KC_HOME,         \
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,  KC_END,          \
        _______, _______, _______, _______, _______, _______, _______, KC_LBRC, _______, KC_RBRC, _______, _______, _______,\
        _______, _______, _______, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______          \
    ),

    [_ADJ] = _LAYOUT( \
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_PSCR, \
        _______, RGB_SAD, RGB_VAI, RGB_SAI, RESET,   _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,         \
        _______, RGB_HUD, RGB_VAD, RGB_HUI, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______,         \
        _______, RGB_SPD, _______, RGB_SPI, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______,\
        _______, _______, _______, RGB_MOD, _______, _______, _______, KC_P0,   KC_PDOT, KC_NLCK, _QWERTY, _COLEMAK           \
    )
};

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_P(PSTR("The PAN Keyboard     "), false);
    oled_write_P(PSTR("By RGBKB"), false);
}
#endif