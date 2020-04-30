#include QMK_KEYBOARD_H

enum jian_layers {
  _QWERTY,
  _DVORAK,
  _COLEMAK,
  _WORKMAN,
  _ISO,
  _LOWER,
  _RAISE,
  _ADJUST,
  _BCKLT_ADJ,
  _THUMB_ALT,
};

enum jian_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  COLEMAK,
  WORKMAN
};

#define RAISE_T(kc) LT(_RAISE, kc)
#define LOWER_T(kc) LT(_LOWER, kc)

#define LAYOUT_base( \
    GRV, Q, W, E, R, T, Y, U, I,    O,   P,    LBRC, RBRC, \
         A, S, D, F, G, H, J, K,    L,   SCLN, QUOT, \
         Z, X, C, V, B, N, M, COMM, DOT, SLSH \
  ) \
  LAYOUT( \
  KC_LGUI, GRV,     Q, W, E,               R,              T,                    Y,               U,               I,              O,   P,    LBRC,            RGUI_T(KC_RBRC), \
           KC_LCTL, A, S, D,               F,              G,                    H,               J,               K,              L,   SCLN, RCTL_T(KC_QUOT), \
           KC_LALT, Z, X, C,               V,              B,                    N,               M,               COMM,           DOT, SLSH, RALT_T(KC_BSLS), \
                          RAISE_T(KC_TAB), LSFT_T(KC_SPC), LOWER_T(KC_ENT),      LOWER_T(KC_ESC), RSFT_T(KC_BSPC), RAISE_T(KC_DEL) \
  )
#define LAYOUT_base_wrapper(...) LAYOUT_base(__VA_ARGS__)

#ifdef SWAP_HANDS_ENABLE
#define SW_TG SH_TG
#else
#define SW_TG _______
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_base_wrapper(QWERTY_base),
[_DVORAK] = LAYOUT_base_wrapper(DVORAK_base),
[_COLEMAK] = LAYOUT_base_wrapper(COLEMAK_base),
[_WORKMAN] = LAYOUT_base_wrapper(WORKMAN_base),

[_LOWER] = LAYOUT(\
  _______, KC_UNDS,         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,          RGUI_T(KC_F12), \
           LCTL_T(KC_EQL),  KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RCTL_T(KC_MINS), \
           LALT_T(KC_PPLS), KC_1,    KC_2,  KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
                                            _______, _______, _______,      _______, _______, _______\
),

[_RAISE] = LAYOUT(\
  _______, KC_NLCK,         KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,      KC_VOLU, KC_HOME, KC_PSCR, KC_PGUP, KC_SLCK, KC_CAPS,        _______, \
           LCTL_T(KC_EQL),  KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,      KC_MUTE, KC_LEFT, KC_UP,   KC_RGHT, KC_INS,  RCTL_T(KC_APP), \
           _______,         KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,      KC_VOLD, KC_END,  KC_DOWN, KC_PGDN, KC_PAUS, _______, \
                                              _______, _______, _______,      _______, _______, _______\
),

[_ADJUST] = SYMM_LAYOUT(\
  RESET,   DEBUG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
           XXXXXXX,        WORKMAN, COLEMAK, DVORAK,  QWERTY,  XXXXXXX, \
           TG(_BCKLT_ADJ), XXXXXXX, XXXXXXX, XXXXXXX, TG(_ISO),TG(_THUMB_ALT), \
                                             _______, SW_TG,   _______  \
),
#if defined(RGBLIGHT) | defined(BACKLIGHT_ENABLE)
[_BCKLT_ADJ] = SYMM_LAYOUT(\
  XXXXXXX, XXXXXXX,        XXXXXXX, BL_INC,  RGB_VAI, RGB_HUD, RGB_HUI, \
           XXXXXXX,        XXXXXXX, BL_DEC,  RGB_VAD, RGB_SAD, RGB_SAI, \
           TG(_BCKLT_ADJ), BL_BRTG, BL_TOGG, RGB_TOG, RGB_RMOD,RGB_MOD, \
                                             _______, _______, _______  \
),
#endif // defined(RGBLIGHT) | defined(BACKLIGHT_ENABLE)

[_THUMB_ALT] = LAYOUT(\
  _______, _______, _______, _______, _______,         _______,         _______,              _______,         _______,        _______, _______, _______, _______, _______, \
           _______, _______, _______, _______,         _______,         _______,              _______,         _______,        _______, _______, _______, _______, \
           _______, _______, _______, _______,         _______,         _______,              _______,         _______,        _______, _______, _______, _______, \
                                      RAISE_T(KC_DEL), LSFT_T(KC_BSPC), LOWER_T(KC_ESC),      LOWER_T(KC_ENT), RSFT_T(KC_SPC), RAISE_T(KC_TAB) \
),

[_ISO] = LAYOUT(\
  _______, _______,         _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, \
           LCTL_T(KC_NUBS), _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, \
           LALT_T(KC_NUHS), _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, KC_RALT, \
                                              _______, _______, _______,      _______, _______, _______\
),

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
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
      break;
  }
  return true;
}
