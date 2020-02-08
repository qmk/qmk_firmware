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

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_KANJI KANJI

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
  [_BASE] = LAYOUT_kc( \
  //,----------------------------------.             ,----------------------------------.
          Q,     W,     E,     R,     T,                   Y,     U,     I,     O,     P,\
  //|------+------+------+------+------|             |------+------+------+------+------|
          A,     S,     D,     F,     G,                   H,     J,     K,     L,   ENT,\
  //|------+------+------+------+------|             |------+------+------+------+------|
       ZSFT,     X,     C,     V,     B,                   N,     M,  CODO,    UP,  MNSF,\
  //|------+------+------+------+------|------+------+------+------+------+------+------|
       ESCT,  TBAL,  LGUI, LOWER,  BSPC,  BSPC,   SPC,   SPC, RAISE,  LEFT,  DOWN,  RGHT \
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  ),

  [_NUMPAD] = LAYOUT_kc( \
  //,----------------------------------.             ,----------------------------------.
         P7,    P8,    P9,  PAST,  NLCK,                  P7,    P8,    P9,  PAST,  NLCK,\
  //|------+------+------+------+------|             |------+------+------+------+------|
         P4,    P5,    P6,  PMNS,  PSLS,                  P4,    P5,    P6,  PMNS,  PSLS,\
  //|------+------+------+------+------|             |------+------+------+------+------|
         P1,    P2,    P3,  PPLS,  QUOT,                  P1,    P2,    P3,  PPLS,  QUOT,\
  //|------+------+------+------+------|------+------+------+------+------+------+------|
       DLBS,    P0,  PDOT,  SFEQ,   SPC,   DEL,   SPC,  DLBS,    P0,  PDOT,  SFEQ,  BSPC \
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  ),

  [_LOWER] = LAYOUT_kc( \
  //,----------------------------------.             ,----------------------------------.
         F1,    F2,    F3,    F4,    F5,                MINS,   EQL,  JYEN,  LBRC,  RBRC,\
  //|------+------+------+------+------|             |------+------+------+------+------|
         F6,    F7,    F8,    F9,   F10,               XXXXX, XXXXX,  SCLN,  QUOT,  BSLS,\
  //|------+------+------+------+------|             |------+------+------+------+------|
       11SF,   F12,  DLNP, KANJI,   ENT,               XXXXX,  COMM,   DOT,  SLSH,    RO,\
  //|------+------+------+------+------|------+------+------+------+------+------+------|
      _____, _____, _____, _____,   DEL, _____, _____, _____, _____, _____, _____, _____ \
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  ),

  [_RAISE] = LAYOUT_kc( \
  //,----------------------------------.             ,----------------------------------.
          1,     2,     3,     4,     5,                   6,     7,     8,     9,     0,\
  //|------+------+------+------+------|             |------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                QUOT,     4,     5,     6,  MINS,\
  //|------+------+------+------+------|             |------+------+------+------+------|
       LSFT, XXXXX, XXXXX, XXXXX, XXXXX,                SLSH,     1,     2,     3,  PPLS,\
  //|------+------+------+------+------|------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____,  WLCK, _____,     0,   DOT,  JEQL \
  //|------+------+------+------+-------------+------+------+------+------+------+------|
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,----------------------------------.             ,----------------------------------.
        RST,  LRST,  KNRM,  KSWP,  CAPS,               XXXXX,  WH_L,  WH_U,  HOME,  PGUP,\
  //|------+------+------+------+------|             |------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI,  SLCK,               XXXXX,  WH_R,  WH_D,   END,  PGDN,\
  //|------+------+------+------+------|             |------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD,  NLCK,               XXXXX,  BTN1,  BTN2,  MS_U, XXXXX,\
  //|------+------+------+------+------|------+------+------+------+------+------+------|
       LSFT, _____, _____, _____, _____, _____, _____, _____, _____,  MS_L,  MS_D,  MS_R \
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
