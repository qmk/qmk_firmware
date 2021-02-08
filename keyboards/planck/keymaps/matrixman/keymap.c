#include QMK_KEYBOARD_H

// http://www.keyboard-layout-editor.com/#/gists/eb0696806831fc0d93c9

#define _PROSE 0
#define _SYMB_L 1
#define _SYMB_R 2
#define _NAV_L 3
#define _NAV_R 4
#define _NAV_ALT 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_PROSE] = LAYOUT_planck_grid(
   LT(_NAV_L,KC_Q), KC_W,  KC_E,      KC_R,        KC_T,         KC_DELETE, KC_BSPC,          KC_Y,       KC_U,    KC_I,     KC_O, LT(_NAV_R,KC_P)
  ,KC_A,            KC_S,  KC_D,      KC_F,        KC_G,     CTL_T(KC_ESC), CTL_T(KC_SCLN),   KC_H,       KC_J,    KC_K,     KC_L,     KC_QUOT
  ,SFT_T(KC_Z),     KC_X,  KC_C,      KC_V,        KC_B,     ALT_T(KC_TAB), ALT_T(KC_INS),    KC_N,       KC_M,    KC_COMM,  KC_DOT,   SFT_T(KC_SLSH)
  ,KC_LCTRL,     KC_LGUI,  LM(_NAV_ALT, MOD_LALT), KC_TAB, LT(_SYMB_L, KC_ESC), KC_LSFT,  KC_LSFT,  LT(_SYMB_R,KC_SPC), KC_BSPC, LM(_NAV_ALT, MOD_LALT), KC_RCTRL, KC_ENT
),
    // accessed via the left symb-layer key, includes a semicolon where the right symb-layer key was
[_SYMB_L] = LAYOUT_planck_grid(
   KC_GRV,         KC_TILD,    KC_ASTR,    KC_AMPR,          KC_SLSH,    LSFT(KC_COMM), LSFT(KC_DOT),  KC_BSLS,  KC_7,    KC_8,    KC_9,    KC_PIPE
  ,KC_UNDS,        KC_CIRC,    KC_PERC,    KC_DLR,           KC_LPRN,    KC_LBRC,       KC_RBRC,       KC_RPRN,  KC_4,    KC_5,    KC_6,    KC_MINS
  ,KC_EQL ,        KC_HASH,    KC_AT,      KC_EXLM,          KC_LCBR,    KC_TRNS,       KC_TRNS,       KC_RCBR,  KC_1,    KC_2,    KC_3,    KC_PLUS
  ,LSFT(KC_QUOT),  KC_TRNS,    KC_COMM,    LSFT(KC_SLSH),    KC_TRNS,    KC_TRNS,       KC_TRNS,       KC_SCLN,  KC_0,    KC_DOT,  KC_DOT,  KC_TRNS
),
    // accessed via the right symb-layer key, includes a colon where the left symb-layer key was
[_SYMB_R] = LAYOUT_planck_grid(
   KC_GRV,         KC_TILD,    KC_ASTR,    KC_AMPR,          KC_SLSH,    LSFT(KC_COMM), LSFT(KC_DOT), KC_BSLS,  KC_7,    KC_8,    KC_9,    KC_PIPE
  ,KC_UNDS,        KC_CIRC,    KC_PERC,    KC_DLR,           KC_LPRN,    KC_LBRC,       KC_RBRC,      KC_RPRN,  KC_4,    KC_5,    KC_6,    KC_MINS
  ,KC_EQL ,        KC_HASH,    KC_AT,      KC_EXLM,          KC_LCBR,    KC_TRNS,       KC_TRNS,      KC_RCBR,  KC_1,    KC_2,    KC_3,    KC_PLUS
  ,LSFT(KC_QUOT),  KC_TRNS,    KC_COMM,    LSFT(KC_SLSH),    KC_COLN,    KC_TRNS,       KC_TRNS,      KC_TRNS,  KC_0,    KC_DOT,  KC_TRNS, KC_TRNS
),
    // accessed via the left nav-layer key, includes a F10 where the right nav-layer key was
[_NAV_L] = LAYOUT_planck_grid(
   KC_TRNS,    KC_F2,    KC_F3,      KC_F4,         KC_F5,    RESET,      BL_STEP,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10
  ,KC_BTN1,  KC_MS_L,    KC_MS_U,    KC_MS_D,       KC_MS_R,  KC_PSCREEN, KC_PAUSE,   KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_F11
  ,KC_BTN2,  KC_BTN4,    KC_MS_WH_UP,KC_MS_WH_DOWN, KC_BTN5,  KC_TRNS,    KC_TRNS,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_F12
  ,KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,       KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
),
    // accessed via the right nav-layer key, includes a F1 where the left nav-layer key was
[_NAV_R] = LAYOUT_planck_grid(
   KC_F1,    KC_F2,      KC_F3,      KC_F4,         KC_F5,    RESET,      BL_STEP,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_TRNS
  ,KC_BTN1,  KC_MS_L,    KC_MS_U,    KC_MS_D,       KC_MS_R,  KC_PSCREEN, KC_PAUSE,   KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_F11
  ,KC_BTN2,  KC_BTN4,    KC_MS_WH_UP,KC_MS_WH_DOWN, KC_BTN5,  KC_TRNS,    KC_TRNS,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_F12
  ,KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,       KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
),
    // accessed via the lower alt keys, moves tab and delete to make alt+tab and ctrl+alt+del feel more standard
[_NAV_ALT] = LAYOUT_planck_grid(
   KC_F1,    KC_F2,      KC_F3,      KC_F4,         KC_F5,    RESET,      BL_STEP,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_DELETE
  ,KC_TAB,   KC_MS_L,    KC_MS_U,    KC_MS_D,       KC_MS_R,  KC_PSCREEN, KC_PAUSE,   KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_F11
  ,KC_BTN2,  KC_BTN4,    KC_MS_WH_UP,KC_MS_WH_DOWN, KC_BTN5,  KC_TRNS,    KC_TRNS,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_F12
  ,KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,       KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
)
};
