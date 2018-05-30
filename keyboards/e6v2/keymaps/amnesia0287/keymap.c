#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL  0
#define _HLa 1
#define _HLb 2
#define _HL  3
#define _XL  4

enum hype_keycodes {
  FN_HLa = SAFE_RANGE,
  FN_HLb
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT_hhkb(
        KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,     KC_QUOT,       KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,   KC_DOT,     KC_SLSH,    KC_RSFT,  FN_HLb,
                KC_LGUI, KC_LALT,               KC_SPACE,                               KC_RALT, FN_HLa
        ),
    [_HLa] = LAYOUT_hhkb(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK,  KC_PAUS, KC_UP,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP,    KC_LEFT,   KC_RGHT,      KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END,   KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,               KC_MPLY,                               KC_TRNS,  KC_TRNS
        ),
    [_HLb] = LAYOUT_hhkb(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK,  KC_PAUS, KC_UP,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP,    KC_LEFT,   KC_RGHT,      KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END,   KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,               KC_MPLY,                               KC_TRNS,  KC_TRNS
        ),
    [_HL] = LAYOUT_hhkb(
        RGB_TOG, RGB_M_P, RGB_RMOD, RGB_MOD, KC_TRNS,  KC_TRNS, KC_TRNS, BL_BRTG, BL_OFF, BL_STEP, BL_ON, BL_DEC, BL_INC, LALT(KC_F4),
        RESET, RGB_HUI, RGB_SAI,  RGB_VAI, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_HUD, RGB_SAD,  RGB_VAD, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, RGB_VAD,  RGB_VAI,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,                        KC_TRNS,                               KC_TRNS, KC_TRNS
        ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FN_HLa:
      if (record->event.pressed)
      {
        layer_on(_HLa);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      else
      {
        layer_off(_HLa);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      return false;
      break;
    case FN_HLb:
      if (record->event.pressed)
      {
        layer_on(_HLb);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      else
      {
        layer_off(_HLb);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      return false;
      break;
  }
  return true;
}
