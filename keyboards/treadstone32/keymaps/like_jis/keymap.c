#include QMK_KEYBOARD_H
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  LOWER,
  RAISE,
  KANJI,
};

// enum tapdances{
//   TD_CODO = 0,
//   TD_SLRO,
// };

// Layer Mode aliases
#define KC_MLAD  MO(_ADJUST)

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_KANJI KANJI

// Adjust layer keys
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP

// Base layer mod tap
#define KC_A_SF  LSFT_T(KC_A)
#define KC_Z_CT  LCTL_T(KC_Z)
#define KC_X_AL  LALT_T(KC_X)
#define KC_C_GU  LGUI_T(KC_C)
#define KC_SSCT  LCTL_T(KC_SLSH)
#define KC_ENSF  LSFT_T(KC_ENT)

// Lower layer mod tap
#define KC_F6SF  LSFT_T(KC_F6)
#define KC_BSSF  LSFT_T(KC_BSLS)
#define KC_11CT  LCTL_T(KC_F11)
#define KC_12AL  LALT_T(KC_F12)

// Layer tap
#define KC_BSLO  LT(_LOWER, KC_BSPC)
#define KC_SPRA  LT(_RAISE, KC_SPC)

// Tap dance
// #define KC_CODO  TD(TD_CODO)
// #define KC_SLRO  TD(TD_SLRO)

// qk_tap_dance_action_t tap_dance_actions[] = {
//   [TD_CODO] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_DOT),
//   [TD_SLRO] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_RO),
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( \
  //,---------------------------------------------------------------------------------------------------.
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P, \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_A_SF,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,  KC_ENSF, \
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_Z_CT,  KC_X_AL,  KC_C_GU,     KC_V,     KC_B,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SSCT, \
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                               KC_BSLO,  KC_SPRA \
  //                                        `---------|---------'
  ),

  [_LOWER] = LAYOUT( \
  //,---------------------------------------------------------------------------------------------------.
         KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,  KC_MINS,   KC_EQL,  KC_JYEN,  KC_LBRC,  KC_RBRC,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_F6SF,    KC_F7,    KC_F8,    KC_F9,   KC_F10, KC_XXXXX, KC_XXXXX,  KC_SCLN,  KC_QUOT,  KC_BSSF,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_11CT,  KC_12AL,   KC_ESC,   KC_TAB, KC_KANJI,   KC_DEL, KC_XXXXX, KC_XXXXX, KC_XXXXX,    KC_RO,\
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              KC______,  KC_MLAD \
  //                                        `---------|---------'
  ),

  [_RAISE] = LAYOUT( \
  //,---------------------------------------------------------------------------------------------------.
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LSFT, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,  KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  KC_LSFT,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LCTL,  KC_LALT,  KC_LGUI, KC_XXXXX, KC_XXXXX,  KC_MINS,    KC_RO,  KC_COMM,   KC_DOT,  KC_SSCT,\
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              KC______, KC______ \
  //                                        `---------|---------'
  ),

  [_ADJUST] = LAYOUT( \
  //,---------------------------------------------------------------------------------------------------.
        KC_RST,  KC_LRST,  KC_KNRM,  KC_KSWP, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LTOG,  KC_LHUI,  KC_LSAI,  KC_LVAI, KC_XXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R, KC_XXXXX,\
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LMOD,  KC_LHUD,  KC_LSAD,  KC_LVAD, KC_XXXXX,  KC_BTN1,  KC_BTN2, KC_XXXXX, KC_XXXXX, KC_XXXXX,\
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              KC______, KC______ \
  //                                        `---------|---------'
  )
};

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case KC_BSLO:
      return TAPPING_LAYER_TERM;
    case KC_SPRA:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
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
    #ifdef RGBLIGHT_ENABLE
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
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
