#include QMK_KEYBOARD_H
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  KANJI,
  RGBRST,
  SEND_SUM,
  SEND_AVERAGE,
  SEND_COUNTIF,
  SEND_MAX,
  SEND_MIN
};

// Fillers to make layering more clear
#define _____ KC_TRNS
#define XXXXX KC_NO

#define KC_CT11 LCTL_T(KC_F11)
#define KC_SF12 SFT_T(KC_F12)
#define KC_LOEN LT(_LOWER, KC_ENT)
#define KC_RASP LT(_RAISE, KC_SPC)

#define KC_SSUM  SEND_SUM
#define KC_SAVE  SEND_AVERAGE
#define KC_SCOU  SEND_COUNTIF
#define KC_SMAX  SEND_MAX
#define KC_SMIN  SEND_MIN

#define KC_RADO LT(_RAISE, KC_PDOT)
#define KC_LOP0 LT(_LOWER, KC_P0)
#define KC_ADNL LT(_ADJUST, KC_NLCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, JP_LBRC,       KC_LOP0,  KC_P1,  KC_P4,  KC_P7,KC_ADNL, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
     KC_LCTRL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, JP_MINS, JP_RBRC,                 KC_P2,  KC_P5,  KC_P8,KC_PSLS,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, JP_COMM,  JP_DOT, JP_SLSH, JP_BSLS,       KC_RADO,  KC_P3,  KC_P6,  KC_P9,KC_PAST, JP_EQL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
               KC_LEFT,KC_RIGHT, KC_LGUI, KC_MHEN, KC_LOEN, KC_BSPC,  KC_DEL, KC_RASP, KC_HENK, KC_LALT, KC_DOWN,   KC_UP,                        KC_PENT,        KC_PPLS,KC_PMNS, KC_DEL
          //`------------------------------------------------------------------------------------------------------------'               |-----------------------------------------------|
  ),

  [_LOWER] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
       KC_ESC, JP_EXLM, JP_QUES, JP_LBRC, JP_RBRC, JP_TILD,                      KC_6,    KC_7,    KC_8,    KC_9, JP_ASTR, JP_SLSH,         LOWER,  XXXXX,KC_LEFT,  XXXXX,  XXXXX, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      JP_QUOT, JP_HASH,  JP_DQT, JP_LPRN, JP_RPRN,   JP_AT,                     XXXXX,    KC_4,    KC_5,    KC_6, JP_MINS,  JP_EQL,               KC_DOWN,KC_DOWN,  KC_UP,KC_PSLS,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      JP_CIRC, JP_PERC, JP_AMPR, JP_SCLN, JP_COLN, JP_PIPE,                      KC_0,    KC_1,    KC_2,    KC_3, JP_PLUS,  KC_ENT,         RAISE,  XXXXX,KC_RIGHT, XXXXX,KC_PAST, JP_EQL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
                 _____,   _____,   _____, KC_ZKHK,   LOWER,   _____,   _____,   RAISE,    KC_0,  JP_DOT,   _____,   _____,                        KC_PENT,        KC_PPLS,KC_PMNS, KC_DEL
          //`------------------------------------------------------------------------------------------------------------'               |-----------------------------------------------|
  ),

  [_RAISE] = LAYOUT_with_setta21(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,   XXXXX,   KC_UP,   XXXXX, KC_PGUP,  KC_DEL,         LOWER, KC_F11,  KC_F4,  KC_F7,KC_SMIN, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      KC_CT11,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     XXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, KC_LSFT,  KC_ENT,                KC_F12,  KC_F5,  KC_F8,KC_SMAX,  KC_F2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
      KC_SF12,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                     XXXXX,   XXXXX,   XXXXX,   XXXXX, KC_PGDN,   XXXXX,         RAISE,  KC_F3,  KC_F6,  KC_F9,KC_SCOU, JP_EQL,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
                 _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,                        JP_RPRN,        KC_SSUM,KC_SAVE, KC_DEL
          //`------------------------------------------------------------------------------------------------------------'               |-----------------------------------------------|
  ),

  [_ADJUST] = LAYOUT_with_setta21( /* Base */
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |-----------------------------------------------|
        _____,   _____,   _____,   _____,   _____,   _____,                     _____,    KC_7,    KC_8,    KC_9,    KC_0,   _____,         LOWER,RGB_VAD,RGB_HUD,RGB_SAD, ADJUST,RGB_TOG,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
        _____,   _____,   _____,   _____,   _____,   _____,                   RGB_TOG, RGB_MOD,   XXXXX,LCA(KC_DEL),LALT(KC_PSCR),KC_PSCR,        RGB_VAI,RGB_HUI,RGB_SAI,  XXXXX,  _____,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |-------+-------+-------+-------+-------+-------|
        _____,   _____,   _____,   _____,   _____,   _____,                   RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI,         RAISE,  XXXXX,  XXXXX,  XXXXX,  XXXXX,  _____,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |---------------+---------------+-------+-------|
                 _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,                        RGB_MOD,          _____,  _____,  _____
          //`------------------------------------------------------------------------------------------------------------'               |-----------------------------------------------|
  )
};

static inline void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {

  pressed ? layer_on(layer1) : layer_off(layer1);
  IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2) ? layer_on(layer3) : layer_off(layer3);
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case LOWER:
      update_change_layer(record->event.pressed, _LOWER, _RAISE, _ADJUST);
      break;
    case RAISE:
      update_change_layer(record->event.pressed, _RAISE, _LOWER, _ADJUST);
        break;
    case KANJI:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui == false) {
          register_code(KC_LANG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      break;
    case SEND_SUM:
      if (record->event.pressed) {
        SEND_STRING("_SUM*");
      }
      break;
    case SEND_AVERAGE:
      if (record->event.pressed) {
        SEND_STRING("_AVERAGE*");
      }
      break;
    case SEND_COUNTIF:
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
      case RGBRST:
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
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}
