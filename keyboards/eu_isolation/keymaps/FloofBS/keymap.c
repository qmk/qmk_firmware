#include "EU_ISO.h"

enum layers {
    _BASE = 0,
    _FN1,
    _FN2,
    _FN3
};

enum combos {
    AB_ESC = 0,
    JA_DEL,
    JR_VOLU,
    RB_VOLD,
};

enum custom_keycodes {
    WCSTR = SAFE_RANGE
};

const uint16_t PROGMEM ab_combo[] = { KC_F1, KC_F3, COMBO_END };
const uint16_t PROGMEM ja_combo[] = { KC_F2, KC_F4, COMBO_END };
const uint16_t PROGMEM jr_combo[] = { KC_F1, KC_F2, COMBO_END };
const uint16_t PROGMEM rb_combo[] = { KC_F3, KC_F4, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [AB_ESC] = COMBO(ab_combo, KC_ESC),
    [JA_DEL] = COMBO(ja_combo, KC_DEL),
    [JR_VOLU] = COMBO(jr_combo, KC_VOLU),
    [RB_VOLD] = COMBO(rb_combo, KC_VOLD),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_euiso_bigspace(
                         KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_F1,   KC_F2,  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_F3,   KC_F4,  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, LT(_FN1, KC_ENT),
                         MO(_FN3),KC_LALT,                        LT(_FN2, KC_SPC),                          KC_LGUI, KC_RCTL
    ),

    [_FN1] = LAYOUT_euiso_bigspace(
                          KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   KC_DEL,
          WCSTR, _______, KC_ESC , KC_PIPE, KC_DQUO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,  _______,
                          _______, _______,                         _______,                                        KC_VOLD,  KC_MNXT
    ),

    [_FN2] = LAYOUT_euiso_bigspace(
                          KC_GRV ,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL,
        _______, _______, KC_ESC , KC_BSLS, KC_QUOT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC,    KC_4,    KC_5,    KC_6, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_1,    KC_2,    KC_3, KC_VOLU,  _______,
                          _______, _______,                         _______,                                        KC_VOLD,  KC_MNXT
    ),

    [_FN3] = LAYOUT_euiso_bigspace(
                          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,    KC_F9,  KC_F10,  KC_F11, KC_F12,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT,  KC_DOWN,  KC_UP, KC_RGHT, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
                          _______,   RESET,                         _______,                                        _______,  _______
    )
};

// Update: The problem does not sit in this area. The function works quite well actually. So it has to do with QMK's comboing software
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WCSTR:
      if (record->event.pressed) {
        // when this shitpost is pressed
        SEND_STRING("HAPPY FEET!! WOMBO COMBO!!");
      } else {
	// The rest of the shitpost when released
        SEND_STRING("OH OH OH OH OH!!!!\n");
      }
      break;
  }
  return true;
};
