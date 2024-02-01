/* Copyright 2021 Filip Paryż (@FilipParyz)
 *
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
#define LOWER_CAPS  LT(_LOWER,KC_CAPS)
#define FUNC        MO(_FN)
#define RAISE_QUOT  LT(_RAISE, KC_QUOT)
#define SHIFT_SLASH RSFT_T(KC_SLSH)

enum layers {
    _QWERTY,
    _FN,
    _LOWER,
    _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,--------------------------------------------------------------------------------------------.
 * |   ` ESC    |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   Del   |
 * |------------+------+------+------+------+------+------+------+------+------+------+---------|
 * |     Tab    |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Enter  |
 * |------------+------+------+------+------+-------------+------+------+------+------+---------|
 * | Caps/LOWER |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | "/RAISE |
 * |------------+------+------+------+------+------|------+------+------+------+------+---------|
 * |    Shift   |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | ?/Shift |
 * |------------+------+------+------+------+------+------+------+------+------+------+---------|
 * |     Ctrl   |  FN  | Alt  | GUI  |    Space    |  Backspace  | Alt  | Left |Down  |  Right  |
 * `--------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT(
    QK_GESC,    KC_1, KC_2,    KC_3,    KC_4,   KC_5, KC_6,    KC_7, KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,     KC_Q, KC_W,    KC_E,    KC_R,   KC_T, KC_Y,    KC_U, KC_I,    KC_O,    KC_P,    KC_ENT,
    LOWER_CAPS, KC_A, KC_S,    KC_D,    KC_F,   KC_G, KC_H,    KC_J, KC_K,    KC_L,    KC_SCLN, RAISE_QUOT,
    KC_LSFT,    KC_Z, KC_X,    KC_C,    KC_V,   KC_B, KC_N,    KC_M, KC_COMM, KC_DOT,  KC_UP,   SHIFT_SLASH,
    KC_LCTL,    FUNC, KC_LGUI, KC_LALT, KC_SPC,       KC_BSPC,       KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
 ),

[_LOWER] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    QK_BOOT, KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_NO, KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TRNS, KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,   KC_NUHS, KC_NUBS, KC_NO,   KC_NO,   KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_RAISE] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TRNS, KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_NO, QK_BOOT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TRNS, KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,   KC_NUHS, KC_NUBS, KC_NO,   KC_NO,   KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_FN] =  LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_PSCR, KC_NO,   KC_NO,   RGB_HUD,  RGB_HUI, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
    KC_MPRV, KC_MPLY, KC_MNXT, RGB_SAD,  RGB_SAI, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
    KC_VOLD, KC_MUTE, KC_VOLU, RGB_VAD,  RGB_VAI, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, RGB_TOG, RGB_RMOD, RGB_MOD,        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)
};

// Light all LEDs red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, 0},
    {7, 24, HSV_RED},
    {24, RGBLED_NUM, 0}
);
// Light all LEDs in green when keyboard layer 1 is active
const rgblight_segment_t PROGMEM layer_lower[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 16, HSV_GREEN}
);
// Light all LEDs in blue when keyboard layer 2 is active
const rgblight_segment_t PROGMEM layer_raise[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 16, HSV_MAGENTA}
);
// Light all LEDs in yellow when keyboard layer 3 is active
const rgblight_segment_t PROGMEM layer_fn[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 16, HSV_ORANGE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    layer_fn,
    layer_lower,
    layer_raise
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
