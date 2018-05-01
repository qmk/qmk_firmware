#include "tada68.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define LCTL_MA LCTL_T(KC_UP)
#define LSFT_MA LSFT_T(KC_DOWN)
#define RSFT_MA SFT_T(KC_UP)
#define TABS_MA LT(1,KC_TAB)
#define SPCE_MA LT(2,KC_SPC)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP_ANSI(
 KC_GESC,KC_1   ,KC_2   ,KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_NUBS,\
 TABS_MA,KC_Q   ,KC_W   ,KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,_______,\
 LCTL_MA,KC_A   ,KC_S   ,KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT ,_______,\
 LSFT_MA,KC_Z   ,KC_X   ,KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,        RSFT_MA,MO(1)  ,_______,\
 KC_LCTL,KC_LALT,KC_LGUI,                SPCE_MA,                        KC_RGUI,KC_RALT,_______,_______,_______,_______),

[1] = KEYMAP_ANSI(
 KC_PSCR,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_INS ,_______,\
 _______,_______,_______,KC_PGUP,KC_PGDN,KC_HOME,KC_END ,KC_PGDN,KC_PGUP,_______,_______,_______,_______,KC_DEL ,_______,\
 KC_CAPS,KC_NUBS,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,        _______,_______,\
 _______,_______,BL_TOGG,BL_INC ,BL_DEC ,_______,_______,KC_VOLD,KC_VOLU,KC_MUTE,_______,        _______,_______,_______,\
 _______,_______,_______,                _______,                        _______,_______,_______,_______,_______,_______),

[2] = KEYMAP_ANSI(
 _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
 KC_BTN5,KC_BTN4,KC_BTN3,KC_BTN2,KC_BTN1,KC_HOME,KC_END ,_______,_______,_______,_______,_______,_______,_______,_______,\
 _______,_______,KC_WH_L,KC_WH_U,KC_WH_D,KC_WH_R,KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,_______,        _______,_______,\
 _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,\
 _______,_______,_______,                _______,                        _______,_______,_______,_______,_______,_______),


};
