#ifndef XD75_DRZ_LAYOUT_MIRRORED

/*
Drzoid's mirrored 5x15 ortho layout
This layout:
  -> http://www.keyboard-layout-editor.com/#/gists/a59dd1a00a45c5dcd38d9e765675dd41
*/
#include QMK_KEYBOARD_H
#include "config.h"
#include "keymap.h"
#include "keymap_french.h"

#define _QWERTY 0
#define _AZERTY 0
#define _L2 1
#define _L3 2
#define _FN 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FN,
  L2,
  L3,
  //DRZ_CONTROL_ALT,
  //DRZ_CONTROL_SHIFT,
  DRZ_LOCK,
  DRZ_SWAP_HANDS,
  DRZ_LEFT_SHIFT_CAPSLOCK,
  DRZ_RIGHT_SHIFT_CAPSLOCK,
  DRZ_ACCENTS_TAPDANCE,
  DRZ_EMOJIS_TAPDANCE,
  DRZ_CMS,
  DRZ_CME,
  DRZ_SQUARE,
  DRZ_CUBE
};

#define DRZ_ST LSFT(KC_TAB)
#define DRZ_SH DRZ_SWAP_HANDS
#define DRZ_LS KC_LSHIFT
#define DRZ_RS KC_RSHIFT
#define DRZ_AC DRZ_ACCENTS_TAPDANCE
#define DRZ_EM DRZ_EMOJIS_TAPDANCE
#define DRZ_CA LCTL(KC_LALT)
#define DRZ_CS LCTL(KC_LSHIFT)
#define DRZ_EU LCTL(RALT(KC_E))

//#define DRZ_CMS SEND_STRING("/*")
//#define DRZ_CME SEND_STRING("*/")


//#define DRZ_AZERTY_OS       /* Qwerty keycaps & layout with Azerty OS */
#define DRZ_QWERTY_OS     /* Qwerty keycaps & layout with Qwerty OS */

#ifdef DRZ_QWERTY_OS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] =
    KEYMAP(
      DRZ_LOCK,   KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,    KC_6,    KC_7,      KC_8,    KC_9,    KC_0,     KC_ESC,   DRZ_LOCK,
      MO(_FN),    KC_LGUI,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     _______,    KC_Y,    KC_U,      KC_I,    KC_O,    KC_P,     KC_LGUI,  MO(_FN),
      MO(_L3),    KC_LALT,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     _______,    KC_H,    KC_J,      KC_K,    KC_L,    KC_SCLN,  KC_LALT,  MO(_L3),
      MO(_L2),    DRZ_LS,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     _______,    KC_N,    KC_M,      _______, KC_UP,   KC_COLN,  DRZ_RS,   MO(_L2),
      DRZ_SH,     KC_LCTL,    DRZ_AC,   DRZ_EM,   KC_MENU,  KC_SPC,   KC_SPC,   KC_ENT,     KC_SPC,  KC_SPC,    KC_LEFT, KC_DOWN, KC_RGHT,  KC_RCTL,  DRZ_SH
    ),

  [_FN] =
    KEYMAP(
      _______,    _______,    KC_F1,    KC_F2,    KC_F3,  KC_F4,    KC_F5,      _______,    KC_F6,    KC_F7,    KC_F8,    KC_F9,  KC_F10,   _______,  _______,
      _______,    _______,    KC_F11,   KC_F12,   KC_F13, KC_F14,   KC_F15,     _______,    KC_F16,   KC_F17,   KC_F18,   KC_F19, KC_F20,   _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______ ,   KC_PSCR,  KC_CALC,  KC_PAUS, XXXXXXX, XXXXXXX,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______,    _______,  _______,  _______, _______, _______,    _______,    _______,  _______,  _______,  _______, _______, _______,  _______
    ),

  [_L2] =
    KEYMAP(
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, KC_QUOT, KC_DQT,     _______,   XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_UNDS, KC_EQL,  _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_LBRC,    _______,   KC_RBRC,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_LPRN,    _______,   KC_RPRN,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_EXLM, _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_LCBR,    _______,   KC_RCBR,  XXXXXXX,  KC_PIPE,  KC_PGUP, KC_QUES, _______,  _______,
      _______,    DRZ_CA,     _______,  _______,  _______, KC_BSPC, DRZ_ST,     _______,   KC_TAB,   KC_DELT,  KC_HOME,  KC_PGDN, KC_END,  DRZ_CA,   _______
    ),

  [_L3] =
    KEYMAP(
      _______,    _______,    KC_TILD,  DRZ_SQUARE, DRZ_CUBE, XXXXXXX, KC_GRV,    _______,   KC_ASTR,  XXXXXXX,  XXXXXXX,  KC_MINS, KC_PLUS, _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  DRZ_EU ,  XXXXXXX, KC_BSLS,   _______,   KC_SLASH, XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______,    XXXXXXX,  KC_DLR,   XXXXXXX,  XXXXXXX, KC_LABK,   _______,   KC_RABK,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, DRZ_CMS,   _______,   DRZ_CME,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    DRZ_CS,     _______,  _______,  _______,  _______, _______,   _______,   _______,  _______,  _______,  _______, _______, DRZ_CS,   _______
    )

};
#endif

#ifdef DRZ_AZERTY_OS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_AZERTY] =
    KEYMAP(
      DRZ_LOCK,   KC_ESC,     FR_1,     FR_2,     FR_3,     FR_4,     FR_5,     _______,    FR_6,    FR_7,      FR_8,    FR_9,    FR_0,     KC_ESC,   DRZ_LOCK,
      MO(_FN),    KC_LGUI,    FR_Q,     FR_W,     FR_E,     FR_R,     FR_T,     _______,    FR_Y,    FR_U,      FR_I,    FR_O,    FR_P,     KC_LGUI,  MO(_FN),
      MO(_L3),    KC_LALT,    FR_A,     FR_S,     FR_D,     FR_F,     FR_G,     _______,    FR_H,    FR_J,      FR_K,    FR_L,    FR_SCLN,  KC_LALT,  MO(_L3),
      MO(_L2),    DRZ_LS,     FR_Z,     FR_X,     FR_C,     FR_V,     FR_B,     _______,    FR_N,    FR_M,      _______, KC_UP,   FR_COLN,  DRZ_RS,   MO(_L2),
      DRZ_SH,     KC_LCTL,    DRZ_AC,   DRZ_EM,   KC_MENU,  KC_SPC,   KC_SPC,   KC_ENT,     KC_SPC,  KC_SPC,    KC_LEFT, KC_DOWN, KC_RGHT,  KC_RCTL,  DRZ_SH
    ),

  [_FN] =
    KEYMAP(
      _______,    _______,    FR_F1,    FR_F2,    FR_F3,  FR_F4,    FR_F5,      _______,    FR_F6,    FR_F7,    FR_F8,    FR_F9,  FR_F10,   _______,  _______,
      _______,    _______,    FR_F11,   FR_F12,   FR_F13, FR_F14,   FR_F15,     _______,    FR_F16,   FR_F17,   FR_F18,   FR_F19, FR_F20,   _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______ ,   KC_PSCR,  KC_CALC,  KC_PAUS, XXXXXXX, XXXXXXX,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______,    _______,  _______,  _______, _______, _______,    _______,    _______,  _______,  _______,  _______, _______, _______,  _______
    ),

  [_L2] =
    KEYMAP(
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, FR_APOS, FR_QUOT,     _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  FR_UNDS, FR_EQUA,  _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, RALT(FR_LPAR),    _______,  RALT(FR_RPAR),  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, FR_LPAR,    _______,   FR_RPAR,  XXXXXXX,  XXXXXXX,  XXXXXXX, FR_EXCL, _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, RALT(FR_APOS),    _______,   RALT(FR_EQUA),  XXXXXXX, RALT(FR_MOIN),  FR_PGUP, LSFT(FR_COMM), _______,  _______,
      _______,    DRZ_CA,     _______,  _______,  _______, FR_BSPC, DRZ_ST,     _______,   FR_TAB,   FR_DEL,  FR_HOME,  FR_PGDN, FR_END,  DRZ_CA,   _______
    ),

  [_L3] =
    KEYMAP(
      _______,    _______,    RALT(FR_EACU),  DRZ_SQUARE, DRZ_CUBE, XXXXXXX, RALT(FR_EGRV),    _______, FR_AST,  XXXXXXX,  XXXXXXX,  FR_MINS, FR_PLUS, _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  DRZ_EU ,  XXXXXXX, LALT(FR_UNDS),   _______,   FR_SLSH, XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______,    XXXXXXX,  FR_DLR,   XXXXXXX,  XXXXXXX, FR_LESS,   _______,   LSFT(FR_LESS),  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, DRZ_CMS,   _______,   DRZ_CME,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, _______,  _______,
      _______,    DRZ_CS,     _______,  _______,  _______,  _______, _______,   _______,   _______,  _______,  _______,  _______, _______, DRZ_CS,   _______
    )

};
#endif

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
  set_unicode_input_mode(UC_WINC);
}

void matrix_scan_user(void) {

}

uint32_t layer_state_set_user(uint32_t state) {

    uint16_t h = rgblight_get_hue();
    uint8_t s = rgblight_get_sat();
    uint8_t v = rgblight_get_val();

    switch (biton32(state)) {
      case _FN:
          rgblight_setrgb_azure();
          break;
      case _L2:
          rgblight_setrgb_pink();
          break;
      case _L3:
          rgblight_setrgb_purple();
          break;
      default:
          rgblight_sethsv(h, s, v);
          break;
    }

  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  //Fait rien sur les touches de layer
  switch(keycode) {

    case TO(_FN):
    case TO(_L2):
    case TO(_L3):
    break;

    case LSFT(FR_1):
      if(IS_RELEASED(record->event))
        SEND_STRING("/*")
      return false;
    break;


    case DRZ_CMS:
      if(IS_RELEASED(record->event)) SEND_STRING("/*");
    break;

    case DRZ_CME:
      if(IS_RELEASED(record->event)) SEND_STRING("*/");
    break;

    case DRZ_SQUARE:
      if(IS_PRESSED(record->event)) SEND_STRING("²");
    break;

    case DRZ_CUBE:
      if(IS_PRESSED(record->event)) SEND_STRING("³");
    break;
  }

  if(IS_PRESSED(record->event)) {
    rgblight_setrgb_white();
  }

  if(IS_RELEASED(record->event)){
    uint16_t h = rgblight_get_hue();
    uint8_t s = rgblight_get_sat();
    uint8_t v = rgblight_get_val();
    rgblight_sethsv(h, s, v);
  }

	return true;
}

void led_set_user(uint8_t usb_led) {

}

#endif
