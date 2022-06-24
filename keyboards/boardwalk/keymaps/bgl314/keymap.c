/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "features/caps_word.h"
#include "color.h"

extern keymap_config_t keymap_config;
layer_state_t prior = -1;

// Layer shorthand
enum layer_names {
    _COLEMAK,
    _QWERTY,
    _SYMBOLS,
     _NUMBERS,
      _NAV,
      _ADJUST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | '      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | CAP LK | A      | S      | D      | F      | G      | HOME   | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * | LSHIFT | Z      | X      | C      | V      | B      | END    | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * | LCTRL  | LGUI   | FN     | LALT   | RAISE  |      SPACE      |      SPACE      | LEFT   | DOWN   | UP     | RIGHT  | RCTRL  |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT_ortho_2x2u(
       KC_GRV,       KC_1,    KC_2,     KC_3,    KC_4,    KC_5,   TG(_QWERTY),  KC_GRV,      KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLASH ,
        KC_TAB,         KC_Q,    KC_W,     KC_F,    KC_P,    KC_G,   KC_PSCR,      KC_MINUS,    KC_J,   KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        KC_ESC,         KC_A,    KC_R,     KC_S,    KC_T,    KC_D,   KC_INSERT,    KC_EQL,      KC_H,   KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
       LSFT_T(KC_ENT),  KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,   KC_DEL,       KC_BSPC,     KC_K,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
      KC_LALT,KC_NO,  KC_CAPS, KC_SCLN,TT(_NUMBERS),   MT(MOD_LCTL,KC_SPC), LT(_NAV,KC_SPC),MO(_SYMBOLS),KC_DEL, KC_PIPE, KC_NO,  MT(MOD_RALT,KC_RGUI)

    ),
    /* Function Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | DEL    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        | MENU   |        |        |        |        |        |        |        |        |        | PRT SC |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        | RESET  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        | MUTE   | VOL DN | VOL UP | \      |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        |                 |                 |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_ortho_2x2u(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  _______, _______,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  _______, _______,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  _______, _______,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  _______, _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENTER,
        KC_LCTL, _______, KC_LALT, KC_LGUI, KC_SPC, KC_SPC,                 _______, _______, _______,    KC_RALT, _______, KC_RCTL
    ),

    /* Raise Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | DEL    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        | MENU   |        |        |        |        |        |        |        |        |        | PRT SC |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        | RESET  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        | MUTE   | VOL DN | VOL UP | \      |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        |                 |                 |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_SYMBOLS] = LAYOUT_ortho_2x2u(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
        _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO, KC_NO,KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  _______,
       KC_BSPC,  KC_TILD,  KC_GRV, KC_LCBR, KC_LPRN,  KC_LBRC,  KC_NO, KC_NO, KC_RBRC, KC_RPRN,  KC_RCBR, KC_PIPE,KC_BSLS   , KC_NO,
       KC_NO, KC_NO,    KC_NO, KC_UNDS, KC_MINS,    KC_LT, _______, _______, KC_GT, KC_EQL , KC_PLUS,KC_NO, KC_QUES,   _______,
        _______, _______, _______, _______, _______,     _______,          KC_NO,     _______, _______, _______, _______, _______
    ),
    [_NUMBERS] = LAYOUT_ortho_2x2u(
        _______, KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,   KC_F11,   KC_F12,     KC_F6,   KC_F7, KC_F8,  KC_F9,   KC_F10,  KC_NO,
        _______, KC_NO,  KC_7,   KC_8,   KC_9,    KC_NO,   KC_NO,    KC_NO,      KC_NO,   KC_7,  KC_8,   KC_9,    KC_NO,   _______,
        KC_BSPC, KC_PLUS,KC_4,   KC_5,   KC_6,    KC_PAST, KC_NO,    _______,    KC_PLUS, KC_4,  KC_5,   KC_6,    KC_PAST, KC_NO,
        KC_0,    KC_MINS,  KC_1,   KC_2,   KC_3,    KC_PSLS, KC_NO,    _______,    KC_MINS, KC_1,  KC_2,   KC_3,    KC_PSLS, KC_0,
        KC_NO,    KC_NO,   KC_NO, KC_DOT,  _______, KC_NO,   KC_0,     _______,    KC_DOT, KC_NO, KC_NO, KC_NO
    )
,
    [_NAV] = LAYOUT_ortho_2x2u(
        KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,       KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO,
       _______   , KC_PGUP, KC_HOME, KC_UP, KC_END,    KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,  _______,
       KC_BSPC,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,  KC_NO,   KC_NO,  KC_NO,  KC_RSHIFT,KC_RCTL,  KC_INS,  KC_NO,  KC_NO,
      _______,    RCTL(KC_Z),RCTL(KC_X),RCTL(KC_C),RCTL(KC_V),  KC_NO,   _______,            KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,  _______,
        KC_NO, KC_NO, KC_NO, _______,    KC_ENT, _______,            _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
     [_ADJUST] = LAYOUT_ortho_2x2u(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RESET, DEBUG,    KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO,  KC_NO, KC_NO,    KC_NO,   RGB_TOG, RGB_MODE_PLAIN ,  KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO,  RGB_HUI, RGB_SAI, RGB_VAI,  RGB_MOD, KC_BRIGHTNESS_UP,  KC_NO, KC_NO,   KC_MUTE, KC_VOLU, KC_MSTP, KC_MPLY, KC_NO, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_NO,   RGB_HUD, RGB_SAD,RGB_VAD , RGB_RMOD,KC_BRIGHTNESS_DOWN,KC_NO,    KC_NO,   KC_NO,   KC_VOLD, KC_NO,   KC_NO,  KC_NO, 	KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
        KC_NO, KC_NO,  KC_NO,                              KC_NO,   KC_NO,  KC_NO,                      KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_caps_word(keycode, record)) { return false; }
  // Your macros ...

  return true;
}



// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_PURPLE},       // Light 4 LEDs, starting with LED 6
    {1, 1, HSV_PURPLE}       // Light 4 LEDs, starting with LED 12
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_RED},       // Light 4 LEDs, starting with LED 6
    {1, 1, HSV_RED}       // Light 4 LEDs, starting with LED 12
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_number_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_GREEN},       // Light 4 LEDs, starting with LED 6
    {1, 1, HSV_GREEN}       // Light 4 LEDs, starting with LED 12
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_CYAN},       // Light 4 LEDs, starting with LED 6
    {1, 1, HSV_CYAN}       // Light 4 LEDs, starting with LED 12
);

// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {5, 1, HSV_MAGENTA},       // Light 4 LEDs, starting with LED 6
    {1, 1, HSV_MAGENTA}       // Light 4 LEDs, starting with LED 12
);

// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {5, 1, HSV_BLUE},       // Light 4 LEDs, starting with LED 6
    {1, 1, HSV_BLUE}       // Light 4 LEDs, starting with LED 12
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_qwerty_layer,    // Overrides caps lock layer
    my_symbol_layer,
    my_number_layer,    // Overrides other layers
    my_nav_layer,     // Overrides other layers
     my_adjust_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

// layer_state_t default_layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(1, layer_state_cmp(state, _DVORAK));
//     return state;
// }

layer_state_t layer_state_set_user(layer_state_t state) {

     state = update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);
    rgblight_set_layer_state(1, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SYMBOLS));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUMBERS));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(5, layer_state_cmp(state, _ADJUST));
    return state;
}


// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);
// }

