#include QMK_KEYBOARD_H

enum jian_layers {
  _QWERTY,
  _DVORAK,
  _COLEMAK,
  _WORKMAN,
  _LOWER,
  _RAISE,
  _ADJUST,
  _BCKLT_ADJ
};

enum jian_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  COLEMAK,
  WORKMAN
};

#define RAISE_T(kc) LT(_RAISE, kc)
#define LOWER_T(kc) LT(_LOWER, kc)

#ifdef SWAP_HANDS_ENABLE
#define SW_TG SH_TG
#else
#define SW_TG _______
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_LGUI, KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,         RGUI_T(KC_RBRC),
           KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
           KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RALT_T(KC_BSLS),
           RAISE_T(KC_TAB), LSFT_T(KC_SPC), LOWER_T(KC_ENT),       LOWER_T(KC_ESC), RSFT_T(KC_BSPC), RAISE_T(KC_DEL)
),

[_DVORAK] = LAYOUT(
  KC_LGUI, KC_GRV,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_LBRC,         RGUI_T(KC_RBRC),
           KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    RCTL_T(KC_SLSH),
           KC_LALT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    RALT_T(KC_BSLS),
           RAISE_T(KC_TAB), LSFT_T(KC_SPC), LOWER_T(KC_ENT),       LOWER_T(KC_ESC), RSFT_T(KC_BSPC), RAISE_T(KC_DEL)
),

[_COLEMAK] = LAYOUT(
  KC_LGUI, KC_GRV,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,      KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_LBRC,         RGUI_T(KC_RBRC),
           KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,      KC_H,    KC_N,    KC_E,    KC_I,   KC_O,    RCTL_T(KC_QUOT),
           KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_K,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, RALT_T(KC_BSLS),
           RAISE_T(KC_TAB), LSFT_T(KC_SPC), LOWER_T(KC_ENT),       LOWER_T(KC_ESC), RSFT_T(KC_BSPC), RAISE_T(KC_DEL)
),

[_WORKMAN] = LAYOUT(
  KC_LGUI, KC_GRV,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,      KC_J,    KC_F,    KC_U,    KC_P,   KC_SCLN, KC_LBRC,         RGUI_T(KC_RBRC),
           KC_LCTL, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,      KC_Y,    KC_N,    KC_E,    KC_O,   KC_I,    RCTL_T(KC_QUOT),
           KC_LALT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,      KC_K,    KC_L,    KC_COMM, KC_DOT, KC_SLSH, RALT_T(KC_BSLS),
                    RAISE_T(KC_TAB), LSFT_T(KC_SPC), LOWER_T(KC_ENT),      LOWER_T(KC_ESC), RSFT_T(KC_BSPC), RAISE_T(KC_DEL)
),

[_LOWER] = LAYOUT(
  _______, KC_UNDS,         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,          RGUI_T(KC_F12),
           LCTL_T(KC_EQL),  KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RCTL_T(KC_MINS),
           LALT_T(KC_PPLS), KC_1,    KC_2,  KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
                                            _______, _______, _______,      _______, _______, _______
),

[_RAISE] = LAYOUT(
  _______, KC_NUM,          KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,      KC_VOLU, KC_HOME, KC_PSCR, KC_PGUP, KC_SCRL, KC_CAPS,        _______,
           LCTL_T(KC_EQL),  KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,      KC_MUTE, KC_LEFT, KC_UP,   KC_RGHT, KC_INS,  RCTL_T(KC_APP),
           _______,         KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,      KC_VOLD, KC_END,  KC_DOWN, KC_PGDN, KC_PAUS, _______,
                                              _______, _______, _______,      _______, _______, _______
),

[_ADJUST] = LAYOUT_symmetric(
  QK_BOOT, DB_TOGG,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX,        WORKMAN, COLEMAK, DVORAK,  QWERTY,  XXXXXXX,
           TG(_BCKLT_ADJ), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             _______, SW_TG,   _______
),

#if defined(RGBLIGHT) || defined(BACKLIGHT_ENABLE)
[_BCKLT_ADJ] = LAYOUT_symmetric(
  XXXXXXX, XXXXXXX,        XXXXXXX, BL_INC,  RGB_VAI, RGB_HUD, RGB_HUI,
           XXXXXXX,        XXXXXXX, BL_DEC,  RGB_VAD, RGB_SAD, RGB_SAI,
           TG(_BCKLT_ADJ), BL_BRTG, BL_TOGG, RGB_TOG, RGB_RMOD,RGB_MOD,
                                             _______, _______, _______
)
#endif // defined(RGBLIGHT) || defined(BACKLIGHT_ENABLE)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
  }
  return true;
}
