#include "planck.h"
#include "action_layer.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define SP_NOPE LALT(KC_F4) //alt+f4
#define SP_LESS LSFT(KC_COMMA)
#define SP_MORE LSFT(KC_DOT)
#define SP_SPC  MT(MOD_LSFT, KC_SPC)
#define SP_PSCR KC_PSCREEN

#define _MEDIA MO(_MEDIA)

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _CUSTOM,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MEDIA
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  CUSTOM,
  GAMING,
  LOWER,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* qwerty
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ esc │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │ bsp │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ tab │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │ ent │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ bsp │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │ up  │ del │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ctrl │ os  │media│ alt │lower│   raise   │space│ alt │left │down │right│
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_QWERTY] = {
    {KC_ESC,  KC_Q,    KC_W,   KC_E,    KC_R,  KC_T,  KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_TAB,  KC_A,    KC_S,   KC_D,    KC_F,  KC_G,  KC_H,  KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT},
    {KC_BSPC, KC_Z,    KC_X,   KC_C,    KC_V,  KC_B,  KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_UP,   KC_DEL },
    {KC_LCTL, KC_LGUI, _MEDIA, KC_LALT, LOWER, RAISE, RAISE, SP_SPC, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT}
  },

  /* custom
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ esc │  G  │  M  │  D  │  L  │  V  │  H  │  U  │  C  │  P  │  B  │ bsp │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ tab │  T  │  N  │  I  │  E  │  ,  │  .  │  A  │  S  │  R  │  O  │ ent │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ bsp │  ;  │  W  │  J  │  F  │  X  │  Y  │  Q  │  K  │  Z  │ up  │ del │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ctrl │ os  │media│ alt │lower│   raise   │space│ alt │left │down │right│
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_CUSTOM] = {
    {KC_ESC,  KC_G,    KC_M,   KC_D,    KC_L,  KC_V,    KC_H,   KC_U,   KC_C,    KC_P,    KC_B,    KC_BSPC},
    {KC_TAB,  KC_T,    KC_N,   KC_I,    KC_E,  KC_COMM, KC_DOT, KC_A,   KC_S,    KC_R,    KC_O,    KC_ENT},
    {KC_BSPC, KC_SCLN, KC_W,   KC_J,    KC_F,  KC_X,    KC_Y,   KC_Q,   KC_K,    KC_Z,    KC_UP,   KC_DEL },
    {KC_LCTL, KC_LGUI, _MEDIA, KC_LALT, LOWER, RAISE,   RAISE,  SP_SPC, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT}
  },

  /* gaming
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ esc │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │ bsp │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ tab │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │ ent │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ bsp │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │ up  │ del │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ctrl │ os  │ alt │space│lower│   raise   │space│media│left │down │right│
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_GAMING] = {
    {KC_ESC,  KC_Q,    KC_W,    KC_E,   KC_R,  KC_T,  KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_TAB,  KC_A,    KC_S,    KC_D,   KC_F,  KC_G,  KC_H,  KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT },
    {KC_BSPC, KC_Z,    KC_X,    KC_C,   KC_V,  KC_B,  KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_UP,   KC_DEL },
    {KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, LOWER, RAISE, RAISE, SP_SPC, _MEDIA,  KC_LEFT, KC_DOWN, KC_RGHT}
  },

  /* lower
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │  ^  │  @  │  #  │  $  │  %  │  &  │  *  │  _  │  -  │  +  │  =  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │  `  │  '  │  {  │  [  │  (  │  !  │  ?  │  )  │  ]  │  }  │  "  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │  |  │  /  │  <  │  >  │  \  │  |  │     │pgup │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │           │     │     │home │pgdwn│ end │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_LOWER] = {
    {KC_CIRC, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS, KC_PLUS, KC_EQUAL, _______},
    {KC_GRV,  KC_QUOT, KC_LCBR, KC_LBRC, KC_LPRN, KC_EXLM, KC_QUES, KC_RPRN, KC_RBRC, KC_RCBR, KC_DQT,   _______},
    {_______, _______, _______, KC_PIPE, KC_SLSH, SP_LESS, SP_MORE, KC_BSLS, KC_PIPE, _______, KC_PGUP,  _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN,  KC_END }
  },

  /* raise
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │     │ up  │     │     │     │     │  7  │  8  │  9  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │left │down │right│     │     │     │  4  │  5  │  6  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │     │  1  │  2  │  3  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │           │     │  0  │  +  │  -  │  /  │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_RAISE] = {
    {_______, _______, _______, KC_UP,   _______, _______, _______, _______, KC_7, KC_8,    KC_9,    _______},
    {_______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_4, KC_5,    KC_6,    _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2,    KC_3,    _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_0, KC_PLUS, KC_MINS, KC_SLSH}
  },

  /* adjust (lower + raise)
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │reset│     │     │     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │qwert│cstm │game │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │           │     │     │     │     │     │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_ADJUST] = {
    {RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, QWERTY,  CUSTOM,  GAMING,  _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
  },

  /* misc media and function keys
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │altF4│     │     │     │     │     │     │     │     │     │     │vol+ │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │     │     │     │play │vol- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │           │ptscr│     │prev │paus │next │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_MEDIA] = {
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
    {SP_NOPE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD},
    {_______, _______, _______, _______, _______, _______, _______, SP_PSCR, _______, KC_MPRV, KC_MPLY, KC_MNXT}
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to the qwerty layout\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case CUSTOM:
      if (record->event.pressed) {
        print("mode just switched to the custom layout\n");
        set_single_persistent_default_layer(_CUSTOM);
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        print("mode just switched to the gaming layout\n");
        set_single_persistent_default_layer(_GAMING);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
