#include QMK_KEYBOARD_H
#include "keymap_japanese.h"


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
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  NUMPAD,
  KANJI,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};

enum tapdances{
  TD_CODO = 0,
  // TD_MNUB,
};

// Layer Mode aliases
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJST ADJUST
#define KC_DLNP NUMPAD //DF(_NUMPAD)
#define KC_DLBS BASE //DF(_BASE)

#define KC_ZSFT  LSFT_T(KC_Z)
#define KC_MNSF  LSFT_T(KC_MINS)
#define KC_ESCT  LCTL_T(KC_ESC)
#define KC_TBAL  LALT_T(KC_TAB)
#define KC_11SF  LSFT_T(KC_F11)
#define KC_ALAP  LALT_T(KC_APP)
#define KC_JEQL  LSFT(KC_MINS)
#define KC_WLCK  LALT(KC_L)
#define KC_SFEQ  LSFT(KC_MINS)
#define KC_SFPL  LSFT(KC_SCLN)
#define KC_SFAS  LSFT(KC_QUOT)

#define KC_CODO  TD(TD_CODO)
// #define KC_MNUB  TD(TD_MNUB)

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CODO] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_DOT),
  // [TD_MNUB] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, LSFT(KC_RO)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //,----------------------------------.             ,----------------------------------.
      KC_Q,  KC_W, KC_E,  KC_R,  KC_T,                KC_Y,  KC_U,  KC_I, KC_O,  KC_P,
  //|------+------+------+------+------|             |------+------+------+------+------|
      KC_A,  KC_S, KC_D,  KC_F,  KC_G,                KC_H,  KC_J,  KC_K, KC_L, KC_ENT,
  //|------+------+------+------+------|             |------+------+------+------+------|
    KC_ZSFT, KC_X, KC_C,  KC_V,  KC_B,                KC_N,  KC_M,  KC_CODO, KC_UP,  KC_MNSF,
  //|------+------+------+------+------|------+------+------+------+------+------+------|
    KC_ESCT, KC_TBAL, KC_LGUI, KC_LOWER, KC_BSPC, KC_BSPC, KC_SPC, KC_SPC, KC_RAISE, KC_LEFT, KC_DOWN, KC_RGHT
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  ),

  [_NUMPAD] = LAYOUT(
  //,----------------------------------.             ,----------------------------------.
    KC_P7,  KC_P8,  KC_P9, KC_PAST, KC_NLCK,          KC_P7, KC_P8, KC_P9, KC_PAST, KC_NLCK,
  //|------+------+------+------+------|             |------+------+------+------+------|
    KC_P4,  KC_P5,  KC_P6, KC_PMNS, KC_PSLS,          KC_P4, KC_P5, KC_P6, KC_PMNS, KC_PSLS,
  //|------+------+------+------+------|             |------+------+------+------+------|
    KC_P1,  KC_P2,  KC_P3, KC_PPLS, KC_QUOT,          KC_P1, KC_P2, KC_P3, KC_PPLS, KC_QUOT,
  //|------+------+------+------+------|------+------+------+------+------+------+------|
   KC_DLBS, KC_P0, KC_PDOT, KC_SFEQ, KC_SPC, KC_DEL, KC_SPC, KC_DLBS, KC_P0, KC_PDOT, KC_SFEQ, KC_BSPC
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  ),

  [_LOWER] = LAYOUT(
  //,----------------------------------.             ,----------------------------------.
    KC_F1,  KC_F2,  KC_F3,  KC_F4, KC_F5,            KC_MINS, KC_EQL, KC_JYEN, KC_LBRC, KC_RBRC,
  //|------+------+------+------+------|             |------+------+------+------+------|
    KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,           XXXXXXX, XXXXXXX, KC_SCLN, KC_QUOT, KC_BSLS,
  //|------+------+------+------+------|             |------+------+------+------+------|
    KC_11SF, KC_F12, KC_DLNP, KANJI, KC_ENT,         XXXXXXX, KC_COMM, KC_DOT, KC_SLSH, KC_RO,
  //|------+------+------+------+------|------+------+------+------+------+------+------|
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  ),

  [_RAISE] = LAYOUT(
  //,----------------------------------.             ,----------------------------------.
     KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                 KC_6,  KC_7, KC_8, KC_9, KC_0,
  //|------+------+------+------+------|             |------+------+------+------+------|
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_QUOT, KC_4, KC_5, KC_6, KC_MINS,
  //|------+------+------+------+------|             |------+------+------+------+------|
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        KC_SLSH, KC_1, KC_2, KC_3, KC_PPLS,
  //|------+------+------+------+------|------+------+------+------+------+------+------|
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WLCK, KC_TRNS, KC_0, KC_DOT, KC_JEQL
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  ),

  [_ADJUST] = LAYOUT(
  //,----------------------------------.             ,----------------------------------.
   RESET,  RGBRST, AG_NORM, AG_SWAP, KC_CAPS,        XXXXXXX, KC_WH_L, KC_WH_U, KC_HOME, KC_PGUP,
  //|------+------+------+------+------|             |------+------+------+------+------|
   RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_SLCK,      XXXXXXX, KC_WH_R, KC_WH_D,  KC_END, KC_PGDN,
  //|------+------+------+------+------|             |------+------+------+------+------|
   RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NLCK,      XXXXXXX, KC_BTN1, KC_BTN2, KC_MS_U, XXXXXXX,
  //|------+------+------+------+------|------+------+------+------+------+------+------|
   KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  )
};

#define L_BASE _BASE
#define L_NUMPAD (1<<_NUMPAD)

static inline void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {

  pressed ? layer_on(layer1) : layer_off(layer1);
  IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2) ? layer_on(layer3) : layer_off(layer3);
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        default_layer_set(L_BASE);
      }
      break;
    case NUMPAD:
      if (record->event.pressed) {
        default_layer_set(L_NUMPAD);
      }
      break;
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
          tap_code16(A(KC_GRV));
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
