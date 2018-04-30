#include "v32u4.h"

// Define Layers
#define _BASE 0
#define _FNX  1
#define _MAC  2
#define _RGB  3
#define _OFF  4

// Define Macros
#define M_PRTS  M(0)
#define M_PRTA  M(1)
#define M_PRTSC M(2)
#define M_PRTAC M(3)
#define M_MSSN  M(4)
#define M_APPS  M(5)
#define M_SPOT  M(6)
#define M_LEFT  M(7)
#define M_RGHT  M(8)
#define RGB_WHT M(9)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base Layer
    [_BASE] = LAYOUT(
         KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,KC_BSLS, KC_GRV, KC_INS,
         KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_LBRC,KC_RBRC,        KC_BSPC, KC_DEL,
        KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,                 KC_ENT,KC_PGUP,
        KC_LSFT,  KC_NO,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,        KC_RSFT,  KC_UP,KC_PGDN,
          MO(1),KC_LALT,KC_LGUI,         KC_SPC, KC_SPC, KC_SPC,                        KC_RGUI,  KC_NO,KC_RALT,KC_LEFT,KC_DOWN,KC_RGHT
    ),
    // Fn Layer
    [_FNX] = LAYOUT(
        KC_TRNS,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,KC_TRNS,  TG(4),  TG(3),
        KC_CAPS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          TG(2),KC_VOLU,KC_MPLY,
        KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS,KC_TRNS,KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,KC_MRWD,KC_VOLD,KC_MFFD
    ),
    // Mac Layer
    [_MAC] = LAYOUT(
          TO(0), KC_F14, KC_F15, M_APPS, M_MSSN, KC_F11, KC_F12,KC_MRWD,KC_MPLY,KC_MFFD,KC_MUTE,KC_VOLD,KC_VOLU,KC_EJCT,  KC_NO,  KC_NO,
          KC_NO, M_PRTS, M_PRTA,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,        KC_BSPC,  KC_NO,
          KC_NO,M_PRTSC,M_PRTAC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                 KC_ENT,  KC_NO,
          KC_NO,  KC_NO,  KC_NO,   KC_X,   KC_C,   KC_V,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          TO(0), M_MSSN,  KC_NO,
          KC_NO,  KC_NO,KC_LGUI,         M_SPOT, M_SPOT, M_SPOT,                        KC_RGUI,  KC_NO,  KC_NO, M_LEFT, M_APPS, M_RGHT
    ),
    // RGB and BL Layer
    [_RGB] = LAYOUT(
          TO(0),  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  TO(0),
          KC_NO,RGB_HUD,RGB_HUI,RGB_WHT,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_NO,BL_TOGG,
          KC_NO,RGB_SAD,RGB_SAI,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                  KC_NO,RGB_TOG,
          KC_NO,  KC_NO,RGB_VAD,RGB_VAI, BL_DEC, BL_INC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,RGB_MOD,RGB_RMOD,         KC_NO,RGB_M_P,RGB_M_R,
          KC_NO,  KC_NO,  KC_NO,          KC_NO,  KC_NO,  KC_NO,                          KC_NO,  KC_NO,  KC_NO,  KC_NO,RGB_M_G,RGB_M_SW
    ),
    // Mash Layer
    [_OFF] = LAYOUT(
          TO(0),  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_NO,  KC_NO,
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                  KC_NO,  KC_NO,
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_NO,  KC_NO,  KC_NO,
          RESET,  KC_NO,  KC_NO,          KC_NO,  KC_NO,  KC_NO,                          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
    ),
};

// The Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LGUI), D(LSFT), T(3), U(LSFT), U(LGUI), END);                   // Mac print screen
            case 1:
                return MACRO(D(LGUI), D(LSFT), T(4), U(LSFT), U(LGUI), END);                   // Mac print area
            case 2:
                return MACRO(D(LCTL), D(LSFT), D(LGUI), T(3), D(LCTL), D(LSFT), D(LGUI), END); // Mac print screen to clipboard
            case 3:
                return MACRO(D(LCTL), D(LSFT), D(LGUI), T(4), D(LCTL), D(LSFT), D(LGUI), END); // Mac print area to clipboard
            case 4:
                return MACRO(D(LCTL), T(UP), U(LCTL), END);                                    // Mac mission control
            case 5:
                return MACRO(D(LCTL), T(DOWN), U(LCTL), END);                                  // Mac app windows
            case 6:
                return MACRO(D(LGUI), T(SPC), U(LGUI), END);                                   // Mac spotlight search
            case 7:
                return MACRO(D(LCTL), T(LEFT), U(LCTL), END);                                  // Mac mission left
            case 8:
                return MACRO(D(LCTL), T(RGHT), U(LCTL), END);                                  // Mac mission right
            case 9:
                rgblight_setrgb(0xff, 0xff, 0xff);                                             // White rgb shortcut
                break;
        }
    }
    return MACRO_NONE;
};
