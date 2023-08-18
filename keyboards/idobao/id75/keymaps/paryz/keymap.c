/* ht 2018 Milton Griffin
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

// Keyboard Layers
enum layers {
    _QWERTY,
    _FN,
    _LOWER,
    _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAPS   | A      | S      | D      | F      | G      | HOME   | DEL    | PG UP  | H      | J      | K      | L      | ;      | ' RAISE|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | UP     |? RSHIFT|
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |  CTRL  | ADJUST | ALT    | GUI    | SPACE  | SPACE  | LEFT   | DOWN   | RIGHT  | BSPACE | BSPACE |   ALT  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QWERTY] = LAYOUT_ortho_5x15( /* QWERTY */
    QK_GESC,            KC_1,   KC_2,    KC_3,    KC_4,   KC_5,  KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,             KC_Q,   KC_W,    KC_E,    KC_R,   KC_T,  KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
    LT(_LOWER,KC_CAPS), KC_A,   KC_S,    KC_D,    KC_F,   KC_G,  KC_HOME, KC_DEL,  KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT(_RAISE, KC_QUOT),
    KC_LSFT,            KC_Z,   KC_X,    KC_C,    KC_V,   KC_B,  KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   RSFT_T(KC_SLSH),
    KC_LCTL,            MO(_FN),KC_LGUI, KC_LALT, KC_SPC, KC_SPC,KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_BSPC, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
 ),

 [_FN] = LAYOUT_ortho_5x15(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NUM,  KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_PSCR, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_MINS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
    KC_MPRV, KC_MPLY, KC_MNXT, RGB_HUI, KC_NO,   KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_NO,   QK_BOOT, KC_NO,   KC_NO,   KC_TRNS,
    KC_VOLD, KC_MUTE, KC_VOLU, RGB_SAI, RGB_SPD, RGB_RMOD,KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   RGB_TOG, RGB_VAI, RGB_SPI, RGB_MOD, KC_P0,   KC_NO,   KC_PDOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),

 [_LOWER] = LAYOUT_ortho_5x15(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TRNS, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_NO,   KC_NUHS, KC_NUBS, KC_NO,   KC_NO,   KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0,   KC_NO,   KC_PDOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_RAISE] = LAYOUT_ortho_5x15(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TRNS, KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TRNS, KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_NO,   KC_NUHS, KC_NUBS, KC_NO,   KC_NO,   KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0,   KC_NO,   KC_PDOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)
};

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    g_led_config = (led_config_t){{
            // Key Matrix to LED Index
            { 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70 },
            { 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55 },
            { 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40 },
            { 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25 },
            { 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10 }
        }, {
            // LED Index to Physical Position
            {8, 12},{60, 12},{112, 12},{164, 12},{216, 12},
            {216, 60},{164, 60},{112, 60},{60, 60},{8, 60},
            {224, 64}, {208, 64}, {192, 64}, {176, 64}, {160, 64}, {144, 64}, {128, 64}, {112, 64}, {96, 64}, {80, 64}, {64, 64}, {48, 64}, {32, 64}, {16, 64}, {0, 64},
            {224, 48}, {208, 48}, {192, 48}, {176, 48}, {160, 48}, {144, 48}, {128, 48}, {112, 48}, {96, 48}, {80, 48}, {64, 48}, {48, 48}, {32, 48}, {16, 48}, {0, 48},
            {224, 32}, {208, 32}, {192, 32}, {176, 32}, {160, 32}, {144, 32}, {128, 32}, {112, 32}, {96, 32}, {80, 32}, {64, 32}, {48, 32}, {32, 32}, {16, 32}, {0, 32},
            {224, 16}, {208, 16}, {192, 16}, {176, 16}, {160, 16}, {144, 16}, {128, 16}, {112, 16}, {96, 16}, {80, 16}, {64, 16}, {48, 16}, {32, 16}, {16, 16}, {0, 16},
            {224,  0}, {208,  0}, {192,  0}, {176,  0}, {160,  0}, {144,  0}, {128,  0}, {112,  0}, {96,  0}, {80,  0}, {64,  0}, {48,  0}, {32,  0}, {16,  0}, {0,  0}
        }, {
            // LED Index to Flag
            2,2,2,2,2,2,2,2,2,2,
            1,1,1,1,4,4,9,9,9,4,4,1,1,1,1,
            1,4,4,4,4,4,9,9,9,4,4,4,4,4,1,
            1,4,4,4,4,4,9,9,9,4,4,4,4,4,1,
            1,4,4,4,4,4,9,9,9,4,4,4,4,4,1,
            1,4,4,4,4,4,9,9,9,4,4,4,4,4,1
        }
    };
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (int i = 10; i <= 84; i++) {
            if (g_led_config.flags[i] & LED_FLAG_MODIFIER) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }

    if ( get_highest_layer(layer_state) > _QWERTY) {
        HSV hsv = {0, 255, 255};

        switch (get_highest_layer(layer_state)) {
            case _FN:
                hsv.h = 32;
                break;
            case _LOWER:
                hsv.h = 116;
                break;
            case _RAISE:
                hsv.h = 200;
                break;
            default:
                break;
        };

        if (hsv.v > rgb_matrix_get_val()) {
            hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
        }
        RGB rgb = hsv_to_rgb(hsv);

        for (int i = 10; i <= 84; i++) {
            if ( g_led_config.flags[i] & LED_FLAG_INDICATOR) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        };
    }
    return false;
};
#endif
