#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _EXTEND 1
#define _NUMBERS 2

#define LAY_EXT MO(_EXTEND)
#define LAY_NUM MO(_NUMBERS)

#define C_A LCTL_T(KC_A)
#define A_R LALT_T(KC_R)
#define G_S LGUI_T(KC_S)
#define S_T LSFT_T(KC_T)
#define S_N RSFT_T(KC_N)
#define G_E RGUI_T(KC_E)
#define A_I RALT_T(KC_I)
#define C_O RCTL_T(KC_O)

#define S_P4 RSFT_T(KC_P4)
#define G_P5 RGUI_T(KC_P5)
#define A_P6 RALT_T(KC_P6)
#define C_PLS RCTL_T(KC_PPLS)

#define SFT_SPC SFT_T(KC_SPC)
#define EXT_SPC LT(_EXTEND, KC_SPC)
#define CTL_ESC LCTL_T(KC_ESC)

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SFT_SPC:
    case EXT_SPC:
    case CTL_ESC:
      return true;
    default:
      return false;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
   //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_MINS,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      CTL_ESC, C_A,     A_R,     G_S,     S_T,     KC_G,                               KC_M,    S_N,     G_E,     A_I,     C_O,     KC_QUOT,
   //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_BSPC,          KC_BSPC, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,
   //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_LGUI, EXT_SPC, LAY_NUM,                   KC_ENT,  SFT_SPC,  KC_RALT
                                 // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      ),

  [_EXTEND] = LAYOUT(
   //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      XXXXXXX, KC_BRID, KC_BRIU, RGB_TOG, RGB_VAD, RGB_VAI,                            KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, XXXXXXX,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_PGUP, KC_HOME, KC_END,  XXXXXXX, KC_DEL,  XXXXXXX,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, XXXXXXX,
   //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      _______, KC_LT,   KC_LBRC, KC_LCBR, KC_LPRN, XXXXXXX, _______,          _______, KC_PGDN, KC_RPRN, KC_RCBR, KC_RBRC, KC_GT,   XXXXXXX,
   //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, _______, _______
                                 // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      ),

  [_NUMBERS] = LAYOUT(
   //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_PAST, KC_PSLS,
   //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                            XXXXXXX, S_P4,    G_P5,    A_P6,    C_PLS,   KC_PMNS,
   //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   XXXXXXX, KC_PEQL,
   //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______, _______, _______,                   _______, KC_P0,   _______
                                 // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
      )
};

