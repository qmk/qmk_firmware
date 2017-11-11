#include "splinter.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _______ KC_TRNS

#define _BL 0 // The base layer.
#define _UL 1 // The up layer.
#define _VL 3 // This is for up layer but should be used by MO with the shift key pressed.
#define _DL 2 // The down layer.

#define _baseLayer KEYMAP(KC_QUOTE,     KC_COMMA,     KC_DOT,           KC_P,       KC_Y,           KC_F, KC_G, KC_C, KC_R, KC_L, \
                          CTL_T(KC_A),  SFT_T(KC_O),  ALT_T(KC_E),      KC_U,       KC_I,           KC_D, KC_H, KC_T, KC_N, KC_S, \
                          KC_SCOLON,    KC_Q,  KC_J,  KC_K,             KC_X,                       KC_B, KC_M, KC_W, KC_V, KC_Z, \
                          TO(_UL),      MO(_VL),      KC_TAB,           KC_BSPACE,  KC_ESCAPE,      _______,_______,_______,_______,_______, \
                          TO(_DL),      KC_LCTRL,     LSFT_T(KC_CAPS),  KC_LGUI,    LGUI_T(KC_SPC),_______,_______,_______,_______,_______)

#define _upLayer KEYMAP(KC_4,          KC_5,          KC_6,          _______,  _______,  _______,_______,_______,_______,_______, \
                        LCTL_T(KC_1),  LSFT_T(KC_2),  LALT_T(KC_3),  _______,  _______,  _______,_______,_______,_______,_______, \
                        KC_7,          KC_8,  KC_9,   KC_0,          KC_GRV,             _______,_______,_______,_______,_______, \
                        TO(_BL),       _______,       _______,       _______,  _______,  _______,_______,_______,_______,_______, \
                        TO(_DL),       KC_MPLY,       KC_MPRV,       KC_MNXT,  _______,  _______,_______,_______,_______,_______)

#define _downLayer KEYMAP(KC_F4,          KC_F5,          KC_F6,          KC_F12,   _______,  _______,_______,_______,_______,_______, \
                          LCTL_T(KC_F1),  LSFT_T(KC_F2),  LALT_T(KC_F3),  KC_F11,   _______,  _______,_______,_______,_______,_______, \
                          KC_F7,          KC_F8,          KC_F9,          KC_F10,   _______,  _______,_______,_______,_______,_______, \
                          TO(_UL),        _______,        _______,        _______,  _______,  _______,_______,_______,_______,_______, \
                          TO(_BL),        KC_MUTE,        KC_VOLD,        KC_VOLU,  _______,  _______,_______,_______,_______,_______)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = _baseLayer,
  [_UL] = _upLayer,
  [_DL] = _downLayer,
  [_VL] = _upLayer
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
