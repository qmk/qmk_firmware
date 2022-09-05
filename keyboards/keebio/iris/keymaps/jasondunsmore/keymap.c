#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layers
#define _QWERTY 0 // Base layer
#define _NAVI   1 // Navigation layer

// Keys
#define KC_AGRV LALT_T(KC_GRAVE)
#define KC_AQUO RALT_T(KC_QUOTE)
#define KC_GUIE LGUI_T(KC_ESC)
#define KC_ECTL RCTL_T(KC_EQL)
#define KC_MCTL LCTL_T(KC_MINS)
#define KC_NAVI MO(_NAVI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_GUIE, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                        KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_DEL,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_TAB,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                        KC_J,   KC_L,   KC_U,   KC_Y,  KC_SCLN,KC_BSPC,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_LALT, KC_A,   KC_R,   KC_S,   KC_T,   KC_G,                        KC_M,   KC_N,   KC_E,   KC_I,   KC_O,  KC_AQUO,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,  KC_GRV,      KC_BSLS, KC_K,   KC_H,  KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
  //`-------+-------+-------+--+----+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                   KC_NAVI,KC_MCTL, KC_SPC,         KC_ENT, KC_ECTL,KC_NAVI
  //                              `-------+-------+-------'        `-------+-------+-------'
   ),

  [_NAVI] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_TRNS, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                       KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
      KC_NO, DM_RSTP,KC_MUTE,KC_VOLU, KC_NO,  KC_NO,                      KC_PGUP,KC_HOME, KC_UP, KC_END,  KC_NO, KC_F12,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_TRNS,DM_REC1,KC_BRID,KC_VOLD,KC_BRIU,KC_TRNS,                     KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT, KC_NO, KC_TRNS,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     KC_TRNS,DM_PLY1, KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_INS,       KC_NO, KC_LCBR,KC_RCBR,KC_LBRC,KC_RBRC, KC_NO, KC_TRNS,
  //`-------+-------+-------+--+----+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                    KC_NO, KC_TRNS, KC_NO,           KC_NO, KC_TRNS, KC_NO
  //                              `-------+-------+-------'        `-------+-------+-------'
     )
};
