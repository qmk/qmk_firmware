/*
This is the keymap for the keyboard

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _QWERTY 1
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum combos //match combo_count in config.h
{
	EU_ENT,
};

const uint16_t PROGMEM eu_combo[]     = {KC_E, KC_U, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
	[EU_ENT]                = COMBO_ACTION(eu_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case EU_ENT:
      if (pressed) {
        tap_code16(KC_ENT);
      }
      break;
  }
}


enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  VELOCI
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define TO_DV TO(_DVORAK)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_DVORAK] = LAYOUT( \
  KC_ESC,  KC_QUOT, KC_COMM, KC_DOT, KC_P,    KC_Y,                                                                            KC_F,    KC_G,   KC_C,  KC_R,   KC_L,    KC_SLSH, \
  KC_TAB, GUI_T(KC_A), ALT_T(KC_O), KC_E, KC_U,  KC_I, KC_ENT,             KC_LALT,         KC_DEL,                 KC_LGUI,   KC_D,    KC_H,   KC_T,  KC_N,   KC_S,    KC_MINS, \
  KC_EQL,  KC_SCLN, KC_Q,    KC_J,   KC_K,    KC_X,    TT(LOWER), KC_LSFT, KC_LCTL,         KC_BSPC, ALT_T(KC_SPC), TT(RAISE), KC_B,    KC_M,   KC_W,  KC_V,   KC_Z,    KC_BSLS \
),

[_QWERTY] = LAYOUT( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                                    KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,          _______,          _______,           _______, KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, _______,          _______, _______,  _______, KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT \
),

[_LOWER] = LAYOUT( \
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR,                                                                _______, KC_P7, KC_P8, KC_P9, KC_PMNS, _______, \
  _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR, _______,          _______,          _______,          _______, _______, KC_P4, KC_P5, KC_P6, KC_PPLS, _______, \
  _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_GRV,	_______, _______, _______,          _______, _______, KC_KP_0, _______, KC_P1, KC_P2, KC_P3, KC_PENT, _______ \
),

[_RAISE] = LAYOUT( \
  _______, KC_PSCR, KC_HOME, KC_UP,   KC_END,  KC_PGUP,                                                                KC_VOLU, KC_F7, KC_F8,  KC_F9,  KC_F10,  XXXXXXX,\
  KC_CAPS, KC_INS,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  _______,          _______,         _______,          _______, KC_VOLD, KC_F4, KC_F5,  KC_F6,  KC_F11,  XXXXXXX,\
  _______, KC_NLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  _______, _______, _______,         _______, _______, _______, KC_MUTE, KC_F1, KC_F2,  KC_F3,  KC_F12,  XXXXXXX\
),

[_ADJUST] =  LAYOUT( \
    TO_DV, RESET,   _______, _______, _______, _______,                                                                _______, _______, _______, _______, _______, KC_SLEP,  \
  RGB_TOG, RGB_MOD, VLK_TOG,  AU_ON,   AU_OFF,  AG_NORM, _______,          _______,          _______,          _______, AG_SWAP,  QWERTY,  DVORAK, _______, _______, _______, \
  RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______,          _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
)


};

// void matrix_init_user(void) { 
// #ifdef BOOTLOADER_CATERINA
//     // This will disable the red LEDs on the ProMicros. UPDATE: I don't think the power LEDs can be turned off. This is for the others I think... and they were already not on... I think.
//     setPinInput(D5);
//     setPinInput(B0);
// #endif
// };

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!
};

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
//   case VELOCI:
// #ifdef VELOCIKEY_ENABLE
//     velocikey_toggle();
//     return false;
// #endif
//     break;
  }
  return true;
}

#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_RED}       // Light 10 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_CHARTREUSE}       // Light 10 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, HSV_BLUE}    // Light LEDs 0-4
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 2, HSV_ORANGE}    // Light LEDs 5-10
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 4, HSV_GREEN}       // Light 10 LEDs, starting with LED 0
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_qwerty_layer,   // Overrides other layers
    my_lower_layer,    // Overrides other layers
    my_raise_layer,    // Overrides other layers
    my_adjust_layer    // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    //rgblight_sethsv_noeeprom(HSV_CYAN);
    //rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _QWERTY));
    return state;
}

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

#ifdef RGBLIGHT_ENABLE
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));
#endif

  return state;
}
