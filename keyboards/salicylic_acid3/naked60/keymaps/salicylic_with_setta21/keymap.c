#include QMK_KEYBOARD_H
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _FLOCK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
  SEND_SUM,
  SEND_AVE,
  SEND_CIF,
  SEND_MAX,
  SEND_MIN
};

enum tapdances{
  TD_ESFL = 0,
  TD_ESQW,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESFL] = ACTION_TAP_DANCE_DUAL_ROLE(KC_ESC, _FLOCK),
  [TD_ESQW] = ACTION_TAP_DANCE_DUAL_ROLE(KC_ESC, _QWERTY),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
  TD(TD_ESFL),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,LT(_LOWER, KC_P0),KC_P1,  KC_P4,  KC_P7,KC_NLCK, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, JP_LBRC,                 KC_P2,  KC_P5,  KC_P8,KC_PSLS,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
     KC_LCTRL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, JP_MINS, JP_RBRC,LT(_RAISE, KC_PDOT),KC_P3,KC_P6, KC_P9,KC_PAST, JP_EQL,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, JP_COMM,  JP_DOT, JP_SLSH, JP_BSLS,               KC_PENT,        KC_PPLS,KC_PMNS, KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |-----------------------------------------------|
      KC_LEFT,KC_RIGHT, KC_LGUI, KC_MHEN, LT(_LOWER,KC_ENT),KC_BSPC,  KC_DEL,LT(_RAISE,KC_SPC), KC_HENK, KC_LALT, KC_DOWN,   KC_UP
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_FLOCK] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
  TD(TD_ESQW),   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,       _______,_______,_______,_______,_______,_______,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______,_______,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,       _______,_______,_______,_______,_______,_______,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,               _______,        _______,_______,_______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |-----------------------------------------------|
               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
       KC_ESC,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,    MO(_LOWER),XXXXXXX,KC_LEFT,XXXXXXX,XXXXXXX, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      JP_COLN, JP_EXLM, JP_QUES, JP_LBRC, JP_RBRC, JP_TILD,                      KC_6,    KC_7,    KC_8,    KC_9, JP_ASTR, JP_SLSH,               KC_DOWN,KC_DOWN,  KC_UP,KC_PSLS,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      JP_QUOT, JP_HASH, JP_DQUO, JP_LPRN, JP_RPRN,   JP_AT,                   XXXXXXX,    KC_4,    KC_5,    KC_6, JP_MINS,  JP_EQL,    MO(_RAISE),XXXXXXX,KC_RIGHT,XXXXXXX,KC_PAST, JP_EQL,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
      JP_CIRC, JP_PERC, JP_AMPR, JP_SCLN, JP_COLN, JP_PIPE,                      KC_0,    KC_1,    KC_2,    KC_3, JP_PLUS,  KC_ENT,               KC_PENT,        KC_PPLS,KC_PMNS, KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |-----------------------------------------------|
               _______, _______, _______, KC_ZKHK,MO(_LOWER),_______,_______,MO(_RAISE), JP_DOT,_______, _______, _______
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |------------------------------------------------|
       KC_ESC,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,       _______, KC_F11,  KC_F4,  KC_F7,SEND_MIN, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+--------+-------|
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP,  KC_DEL,                KC_F12,  KC_F5,  KC_F8,SEND_MAX,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+--------+-------|
LCTL_T(KC_F11),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                   XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, KC_LSFT,  KC_ENT,       _______,  KC_F3,  KC_F6,  KC_F9,SEND_CIF, JP_EQL,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |---------------+---------------+--------+-------|
SFT_T(KC_F12),   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX,               JP_RPRN,       SEND_SUM,SEND_AVE, KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |------------------------------------------------|
               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT_with_setta21( /* Base */
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
       KC_ESC,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,       _______,RGB_VAD,RGB_HUD,RGB_SAD,XXXXXXX,_______,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX,LALT(KC_PSCR),          RGB_VAI,RGB_HUI,RGB_SAI,XXXXXXX,_______,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
     KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, KC_PSCR,       _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,LCA(KC_DEL),            RGB_MOD,        RGB_TOG,_______,_______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |-----------------------------------------------|
               _______, _______, _______, _______, _______,   RESET,   RESET, _______, _______, _______, _______, _______
          //`------------------------------------------------------------------------------------------------------------'
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  switch (keycode) {
    case SEND_SUM:
      if (record->event.pressed) {
        SEND_STRING("_SUM*");
      }
      break;
    case SEND_AVE:
      if (record->event.pressed) {
        SEND_STRING("_AVERAGE*");
      }
      break;
    case SEND_CIF:
      if (record->event.pressed) {
        SEND_STRING("_COUNTIF*");
      }
      break;
    case SEND_MAX:
      if (record->event.pressed) {
        SEND_STRING("_MAX*");
      }
      break;
    case SEND_MIN:
      if (record->event.pressed) {
        SEND_STRING("_MIN*");
      }
      break;
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}

void matrix_init_user(void) {

}
