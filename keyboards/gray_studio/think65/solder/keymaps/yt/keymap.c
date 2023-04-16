/* Copyright 2021 Qiaowei Tang
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



 /*
 * LED ranges for Think6.5v2 2U
 * These values were derived from manual testing. Derived from keymaps/rys.
 * ┌───────┬───────┬─────────────┬───────────────────────────────────────────┐
 * │ 00 01 │ 02 03 │ 04 05 06 07 │ 08 09 10 11 12 13 14 15 16 17 18 19 20 21 │
 * │ badge │ badge │    (?)      │              underglow (?)                │
 * │  bar  │ icon  │             │                                           │
 * └───────┴───────┴─────────────┴───────────────────────────────────────────┘
 */


// Setup some layers to control mac/win layouts
#include QMK_KEYBOARD_H

enum bs_layers {
    _WIN,
    _MAC,
    _FN,
    _BLANC
};

// Setup some keycodes to control cycling and range toggling
enum bs_keycodes {
  WIN = SAFE_RANGE,
  MAC
};

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_WHITE}     // Light 4 LEDs, starting with LED 12
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
};

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
};

layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == _MAC) {
        rgblight_mode_noeeprom(6);
    } else {
        rgblight_mode_noeeprom(9);
    }
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Win Layer
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
    * │Esc│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ Bckspc│pup│
    * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
    * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│|   \│pdw│
    * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
    * │lTCap │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│   Enter│   │
    * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤   │
    * │Shift   │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│ Shift│ Up│   │
    * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┴───┴┬─┬───┼───┼───┤
    * │Ctrl│ win│ alt│          Space         │   Func  │ │Lef│Dow│Rig│
    * └────┴────┴────┴────────────────────────┴─────────┴─┴───┴───┴───┘
    */
    [_WIN] = LAYOUT_65_ansi_blocker(
        QK_GESC,            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_PGUP,
        KC_TAB,             KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGDN,
        LT(_FN, KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,             _______,
        KC_LSFT,            KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,        KC_UP,   _______,
        KC_LCTL,            KC_LGUI, KC_LALT,                      KC_SPC,                          KC_1,   MO(_FN),          KC_LEFT, KC_DOWN,  KC_RGHT
    ),
    /* Mac Layer
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
    * │Esc│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ Bckspc│pup│
    * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
    * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│|   \│pdw│
    * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
    * │lTCap │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│   Enter│   │
    * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤   │
    * │Shift   │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│ Shift│ Up│   │
    * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┴───┴┬─┬───┼───┼───┤
    * │Ctrl│ Opt│ Cmd│          Space         │   Func  │ │Lef│Dow│Rig│
    * └────┴────┴────┴────────────────────────┴─────────┴─┴───┴───┴───┘
    */
    [_MAC] = LAYOUT_65_ansi_blocker(
        QK_GESC,            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_PGUP,
        KC_TAB,             KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGDN,
        LT(_FN, KC_CAPS),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           _______,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   _______,
        KC_LCTL,            KC_LOPT, KC_LCMD,                      KC_SPC,                          KC_1,   MO(_FN),           KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* Fn Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────────┬───┐
     * │lck│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│ delete │mac│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┼───┤
     * │ TOG │MB1│MSU│MB2│MDU│   │   │   │UP │   │Hom│pgu│End│      │win│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──────┼───┤
     * │MO(2) │MSL│MSD│MSR│MWD│   │   │Lft│Dwn│rgt│END│pgd│  reset  │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬────┤   │
     * │ RGB_mod│F13│F14│F15│F16│F17│F18│F19│F20│F21│F22│F23   │Bri+│   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼────┼───┤
     * │Vold│Mute│Volu│                        │    │    │ │   │Bri-│   │
     * └────┴────┴────┴────────────────────────┴────┴────┴─┴───┴────┴───┘
     */
    [_FN] = LAYOUT_65_ansi_blocker(
        KC_LOCK, KC_F1,      KC_F2,      KC_F3,       KC_F4,          KC_F5,    KC_F6,    KC_F7,    KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_DEL,    MAC,
        RGB_TOG, KC_MS_BTN1, KC_MS_UP,   KC_MS_BTN2,  KC_MS_WH_UP,    _______,  _______,  _______,  KC_UP,   _______,  KC_HOME, KC_PGUP, _______, _______,   WIN,
        _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN,  _______,  _______,  KC_LEFT,  KC_DOWN, KC_RIGHT, KC_END,  KC_PGDN,          QK_BOOT,     _______,
        RGB_MOD, KC_F13,     KC_F14,     KC_F15,      KC_F16,         KC_F17,   KC_F18,   KC_F19,   KC_F20,  KC_F21,   KC_F22,  KC_F23,           KC_BRIU,   _______, 
        KC_VOLD, KC_MUTE,    KC_VOLU,                 _______,                            _______,  _______,                             _______, KC_BRID,   _______
    ),

};

    
