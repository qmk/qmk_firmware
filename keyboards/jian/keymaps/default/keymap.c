#include QMK_KEYBOARD_H
#include "action_layer.h"

extern keymap_config_t keymap_config;

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
  WORKMAN,
  EXT_RGB,
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define TG_ISO  TG(_ISO)
#define TG_THMB TG(_THUMB_ALT)
#define BL_ADJ  TG(_BCKLT_ADJ)

#define F12_RGU MT(MOD_RGUI, KC_F12)
#define PLS_LCT MT(MOD_LCTL, KC_PPLS)
#define EQL_LCT MT(MOD_LCTL, KC_PEQL)
#define APP_RCT MT(MOD_RCTL, KC_APP)
#define MIN_RCT MT(MOD_RCTL, KC_MINS)
#define EQL_LAL MT(MOD_LALT, KC_EQL)
#define BSL_RAL MT(MOD_RALT, KC_BSLS)

#define BSP_LSH MT(MOD_LSFT, KC_BSPC)
#define BSP_RSH MT(MOD_RSFT, KC_BSPC)
#define SPC_LSH MT(MOD_LSFT, KC_SPC)
#define SPC_RSH MT(MOD_RSFT, KC_SPC)
#define DEL_RSE LT(_RAISE, KC_DEL)
#define TAB_RSE LT(_RAISE, KC_TAB)
#define ENT_LWR LT(_LOWER, KC_ENT)
#define ESC_LWR LT(_LOWER, KC_ESC)

#define RGU_RBR RGUI_T(KC_RBRC)
#define RCT_QUO RCTL_T(KC_QUOT)

#define LAYOUT_base( \
    GRV, Q, W, E, R, T, Y, U, I,    O,   P,    LBRC, RBRC, \
         A, S, D, F, G, H, J, K,    L,   SCLN, QUOT, \
         Z, X, C, V, B, N, M, COMM, DOT, SLSH \
  ) \
  LAYOUT( \
  KC_LGUI, GRV,     Q,       W,       E,       R,       T,            Y,       U,       I,       O,       P,       LBRC,    RGU_RBR, \
           KC_LCTL, A,       S,       D,       F,       G,            H,       J,       K,       L,       SCLN,    RCT_QUO, \
           KC_LALT, Z,       X,       C,       V,       B,            N,       M,       COMM,    DOT,     SLSH,    BSL_RAL, \
                                      TAB_RSE, SPC_LSH, ENT_LWR,      ESC_LWR, BSP_RSH, DEL_RSE \
  )
#define LAYOUT_base_wrapper(...) LAYOUT_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_base_wrapper(QWERTY_base),
[_DVORAK] = LAYOUT_base_wrapper(DVORAK_base),
[_COLEMAK] = LAYOUT_base_wrapper(COLEMAK_base),
[_WORKMAN] = LAYOUT_base_wrapper(WORKMAN_base),

[_LOWER] = LAYOUT(\
  _______, KC_UNDS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  F12_RGU, \
           PLS_LCT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, MIN_RCT, \
           EQL_LAL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
                                      _______, _______, _______,      _______,  _______, _______\
),

[_RAISE] = LAYOUT(\
  _______, KC_NLCK, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,      KC_VOLU, KC_HOME, KC_PSCR, KC_PGUP, KC_SLCK, KC_CAPS, _______, \
           EQL_LCT, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,      KC_MUTE, KC_LEFT, KC_UP,   KC_RGHT, KC_INS,  APP_RCT, \
           _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,      KC_VOLD, KC_END,  KC_DOWN, KC_PGDN, KC_PAUS, _______, \
                                      _______, _______, _______,      _______, _______, _______\
),

[_ADJUST] = SYMM_LAYOUT(\
  RESET,   DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
           XXXXXXX, WORKMAN, COLEMAK, DVORAK,  QWERTY,  XXXXXXX, \
           BL_ADJ,  XXXXXXX, XXXXXXX, XXXXXXX, TG_ISO,  TG_THMB, \
                                      _______, SH_TG,   _______  \
),
#if defined(RGBLIGHT) | defined(BACKLIGHT_ENABLE)
[_BCKLT_ADJ] = SYMM_LAYOUT(\
  XXXXXXX, XXXXXXX, XXXXXXX, BL_INC,  RGB_VAI, RGB_HUD, RGB_HUI, \
           XXXXXXX, XXXXXXX, BL_DEC,  RGB_VAD, RGB_SAD, RGB_SAI, \
           BL_ADJ,  XXXXXXX, XXXXXXX, RGB_TOG, RGB_RMOD,RGB_MOD, \
                                      _______, _______, _______  \
),
#endif // defined(RGBLIGHT) | defined(BACKLIGHT_ENABLE)

[_THUMB_ALT] = LAYOUT(\
  _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, \
           _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, \
           _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, \
                                      DEL_RSE, BSP_LSH, ESC_LWR,      ENT_LWR, SPC_RSH, TAB_RSE \
),

[_ISO] = LAYOUT(\
  _______, _______,         _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, \
           LCTL_T(KC_NUBS), _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, \
           LALT_T(KC_NUHS), _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, KC_RALT, \
                                              _______, _______, _______,      _______, _______, _______\
),

};

uint32_t layer_state_set_user(uint32_t state) {
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
