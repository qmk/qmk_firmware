#include QMK_KEYBOARD_H

// lshift split, backspace split, full ANSI enter, full right shift
#define KEYMAP_BZIO(                                                         \
               K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K49, \
               K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
               K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
               K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, \
               K40, K41, K42,           K45,                K4A, K4B, K4C, K4D \
                ) {                                                     \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, KC_NO, K2D }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, KC_NO, K3D }, \
    { K40, K41, K42, KC_NO,    KC_NO,    K45, KC_NO,    KC_NO,    KC_NO,    K49, K4A, K4B, K4C, K4D } \
  }


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: HHKB with hyper key where ctrl used to be, and right half of left
       shift used as a key lock */
    KEYMAP_BZIO(
        KC_ESC,           KC_1,    KC_2,    KC_3,  KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, \
        KC_TAB,           KC_Q,    KC_W,    KC_E,  KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,\
        KC_LCTL,          KC_A,    KC_S,    KC_D,  KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,\
        KC_LSFT, KC_LOCK, KC_Z,    KC_X,    KC_C,  KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, \
        KC_HYPR, KC_LGUI, KC_LALT, LT(1, KC_SPC),                                           KC_RALT, KC_RGUI, KC_APP,  KC_RCTL),

    /* 1: spacefn with WASD arrows/navigation block and extra space key for
       realignment of source code, plus IJKL mouse arrows, volume up/down in <>,
       and caps lock where it used to be */
    KEYMAP_BZIO(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,     KC_F4,      KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, \
        KC_TRNS,          KC_PGUP, KC_UP,   KC_PGDOWN, KC_INSERT,  KC_MS_BTN2, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   \
        KC_TRNS,          KC_LEFT, KC_DOWN, KC_RGHT,   KC_DELETE,  KC_MS_BTN1, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_HOME, KC_SPC,  KC_END,    KC_PSCREEN, KC_TRNS,    KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
