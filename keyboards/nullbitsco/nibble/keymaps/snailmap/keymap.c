/* Copyright 2021 dogspace <https://github.com/dogspace>
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

enum custom_keycodes {
    KC_CUST = SAFE_RANGE,
};

enum layer_names {
    _MA,
    _L1,
    _L2,
    _L3
};

// NOTE: Default keymap layers were designed for ANSI split-space layout  http://www.keyboard-layout-editor.com/#/gists/f28bd5ff4e62f69e89896df3a59671c6
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MA] = LAYOUT_ansi(
                   KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,       KC_0,          KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_MUTE,   KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,          KC_LBRC, KC_RBRC, KC_BSLS, LCTL(KC_F),
        KC_CAPS,   MO(_L2),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,       KC_SCLN,       KC_QUOT,          KC_ENT,  KC_CALC,
        TG(_L2),   KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,     KC_SLSH,       KC_RSFT,          KC_UP,   KC_WHOM,
        MO(_L3),   KC_LCTL,    KC_LGUI, KC_LALT,                   KC_SPC,                    MO(_L1), LCTL(KC_C), LCTL(KC_V),    KC_LEFT,          KC_DOWN, KC_RGHT
    ),
    [_L1] = LAYOUT_ansi(
                   KC_GRAVE,   _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,       _______, _______, _______, _______,
        RGB_TOG,   _______,    _______, _______, _______, _______, _______, _______, KC_PGUP, KC_UP,   _______,    _______,       _______, _______, _______, _______,
        _______,   LCTL(KC_Z), KC_LCTL, KC_LSFT, _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,   KC_END,        _______,          _______, _______,
        _______,   _______,    _______, _______, _______, _______, _______, _______, KC_PGDN, _______, _______,    LCTL(KC_SLSH), _______,          _______, _______,
        _______,   _______,    _______, _______,                   _______,                   _______, LCTL(KC_X), _______,       _______,          _______, _______
    ),
    [_L2] = LAYOUT_ansi(
                   KC_GRAVE,   _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,       _______, _______, _______, _______,
        RGB_TOG,   _______,    _______, _______, _______, _______, _______, KC_PAST, KC_7,    KC_8,    KC_9,       _______,       _______, _______, _______, _______,
        _______,   _______,    _______, _______, _______, _______, _______, KC_PPLS, KC_4,    KC_5,    KC_6,       _______,       _______,          _______, _______,
        _______,   _______,    _______, _______, _______, _______, _______, KC_PMNS, KC_1,    KC_2,    KC_3,       _______,       _______,          _______, _______,
        _______,   _______,    _______, _______,                   KC_0,                      KC_PSLS, _______,    _______,       _______,          _______, _______
    ),
    [_L3] = LAYOUT_ansi(
                   _______,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,        KC_F11,  KC_F12,  _______, _______,
        RGB_TOG,   _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,       _______, _______, _______, _______,
        _______,   _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,       _______,          _______, _______,
        KC_SYSREQ, _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,       _______,          _______, _______,
        _______,   _______,    _______, _______,                   _______,                   _______, _______,    _______,       _______,          _______, _______
    )
};

#ifdef OLED_ENABLE
/*===========================================    OLED CONFIGURATION    ===========================================*/
bool  oled_horizontal   = true;         // OLED rotation  (true = horizontal,  false = vertical)
bool  ansi_layout       = true;         // ANSI or ISO layout  (true = ANSI,  false = ISO)
bool  split_space       = true;         // Split spacebar  (true = split spacebar,  false = 6.25u or 7u spacebar)
bool  three_mods_left   = true;         // Left mods layout  (true = 3x 1.25u keys,  false = 2x 1.5u keys)
bool  three_mods_right  = false;        // Right mods layout  (true = 3x 1u keys,  false = 2x 1.5u keys)
bool  graph_direction   = true;         // Graph movement  (true = right to left,  false = left to right)
float graph_top_wpm     = 100.0;        // Minimum WPM required to reach the top of the graph
int   graph_refresh     = 1000;         // In milliseconds, determines the graph-line frequency
int   icon_med_wpm      = 50;           // WPM required to display the medium snail
int   icon_fast_wpm     = 72;           // WPM required to display the fast snail
// Layer names:  Should be exactly 5 characters in length if vertical display, or 6 characters if horizontal
#define MA_LAYER_NAME     "QWERTY"      // Layer _MA name
#define L1_LAYER_NAME     "ARROWS"      // Layer _L1 name
#define L2_LAYER_NAME     "NUMPAD"      // Layer _L2 name
#define L3_LAYER_NAME     "FUNCTN"      // Layer _L3 name
/*================================================================================================================*/
bool  first_loop  = true;
int   timer       = 0;
int   wpm_limit   = 20;
int   max_wpm     = -1;
int   wpm_icon    = -1;
int   graph_lines[64];

// Set OLED rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (oled_horizontal) {
        return OLED_ROTATION_180;
    } else {
        return OLED_ROTATION_90;
    }
}

// Toggles pixel on/off, converts horizontal coordinates to vertical equivalent if necessary
static void write_pixel(int x, int y, bool onoff) {
    if (oled_horizontal) {
        oled_write_pixel(x, y, onoff);
    } else {
        oled_write_pixel(y, 127 - x, onoff);
    }
}

// Draw static background image to OLED (keyboard with no bottom row)
static void render_background(void) {
    if (oled_horizontal) {
        static const char PROGMEM oled_keymap_horizontal[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x84, 0x80, 0x80, 0x80, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x04,
            0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00,
            0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00,
            0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00,
            0x80, 0x04, 0x04, 0x04, 0x04, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
            0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
            0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
            0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
            0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
            0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02,
            0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        oled_write_raw_P(oled_keymap_horizontal, sizeof(oled_keymap_horizontal));
    } else {
        static const char PROGMEM oled_keymap_vertical[] = {
            0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00,
            0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00,
            0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
            0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
            0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00,
            0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
            0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
            0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00,
            0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        oled_write_raw_P(oled_keymap_vertical, sizeof(oled_keymap_vertical));
    }
}

// Location of OLED keyboard's top left pixel, relative to the display
static const int keymap_template[2] = {41, 0};
// Location of key highlights top left pixels, relative to keymap_template  {X, Y, Key length in px}
static int keymap_coords[MATRIX_ROWS][MATRIX_COLS][3] = {
    { {12, 15, 1}, {5, 0, 1},  {10, 0, 1},  {15, 0, 1},  {20, 0, 1},  {25, 0, 1},  {30, 0, 1},   {35, 0, 1},  {40, 0, 1},  {45, 0, 1},  {50, 0, 1},  {55, 0, 1},  {60, 0, 1},  {65, 0, 1}, {70, 0, 8},  {82, 0, 1}  },
    { {0, 5, 1},   {5, 5, 5},  {14, 5, 1},  {19, 5, 1},  {24, 5, 1},  {29, 5, 1},  {34, 5, 1},   {39, 5, 1},  {44, 5, 1},  {49, 5, 1},  {54, 5, 1},  {59, 5, 1},  {64, 5, 1},  {69, 5, 1}, {74, 5, 4},  {82, 5, 1}  },
    { {0, 10, 1},  {5, 10, 6}, {15, 10, 1}, {20, 10, 1}, {25, 10, 1}, {30, 10, 1}, {35, 10, 1},  {40, 10, 1}, {45, 10, 1}, {50, 10, 1}, {55, 10, 1}, {60, 10, 1}, {65, 10, 1}, {0, 0, 0},  {70, 10, 8}, {82, 10, 1} },
    { {0, 15, 1},  {5, 15, 8}, {17, 15, 1}, {22, 15, 1}, {27, 15, 1}, {32, 15, 1}, {37, 15, 1},  {42, 15, 1}, {47, 15, 1}, {52, 15, 1}, {57, 15, 1}, {62, 15, 1}, {67, 15, 6}, {0, 0, 0},  {77, 15, 1}, {82, 15, 1} },
    { {0, 20, 1},  {5, 20, 2}, {11, 20, 2}, {17, 20, 2}, {0, 0, 0},   {0, 0, 0},   {23, 20, 12}, {0, 0, 0},   {0, 0, 0},   {39, 20, 3}, {56, 20, 4}, {64, 20, 4}, {72, 20, 1}, {0, 0, 0},  {77, 20, 1}, {82, 20, 1} }
};

// Draw the bottom row of the keyboard (based on OLED config variables), update coordinates
static void render_fn_row(void) {
    // Update locations of spacebar and modifier key highlights
    if ((split_space == false) && (three_mods_left == false)) {
        keymap_coords[4][1][2] = 3;
        keymap_coords[4][2][0] = 12;
        keymap_coords[4][2][2] = 3;
        keymap_coords[4][3][0] = 0;
        keymap_coords[4][3][1] = 0;
        keymap_coords[4][3][2] = 0;
        keymap_coords[4][6][0] = 19;
        keymap_coords[4][6][2] = 34;
    } else if ((split_space == false) && (three_mods_left == true)) {
        keymap_coords[4][6][2] = 30;
    }
    if ((split_space == false) && (three_mods_right == true)) {
        keymap_coords[4][9][0]  = 57;
        keymap_coords[4][9][2]  = 1;
        keymap_coords[4][10][0] = 62;
        keymap_coords[4][10][2] = 1;
        keymap_coords[4][11][0] = 67;
        keymap_coords[4][11][2] = 1;
    }
    // Draw modifiers
    for (int i = 0; i < 16; i++) {
        if (keymap_coords[4][i][2] != 0) {
            for (int p = 0; p < keymap_coords[4][i][2]; p++) {
                int x = keymap_template[0] + keymap_coords[4][i][0] + 2 + p;
                write_pixel(x, 22, true);
            }
        }
    }
    // Draw second line for split spacebar
    if (split_space == true) {
        for (int i = 0; i < 6; i++) {
            int x = keymap_template[0] + 46 + 2 + i;
            write_pixel(x, 22, true);
        }
    }
}

// Update OLED keyboard with ISO layout, update coordinates
static void render_iso(void) {
    for (int i = 0; i < 6; i++) {
        // Turn off ANSI enter
        write_pixel(keymap_template[0] + 73 + i, keymap_template[1] + 12, false);
        if (i < 4) {
            // Turn off part of ANSI left shift
            write_pixel(keymap_template[0] + 10 + i, keymap_template[1] + 17, false);
            // Draw vertical line for ISO enter
            write_pixel(keymap_template[0] + 79, keymap_template[1] + 8 + i, true);
        }
    }
    // Update locations of shift and grave key highlights
    keymap_coords[3][1][2]  = 3;
    keymap_coords[1][14][0] = 70;
    keymap_coords[1][14][1] = 10;
    keymap_coords[1][14][2] = 1;
}

// Toggles pixels surrounding key
static void render_keymap(uint8_t key_row, uint8_t key_col, bool onoff) {
    int length = keymap_coords[key_row][key_col][2] + 4;
    int left   = keymap_coords[key_row][key_col][0] + keymap_template[0];
    int top    = keymap_coords[key_row][key_col][1] + keymap_template[1];
    int right  = left + length - 1;
    int bottom = top + 4;

    // Special case 1 - Draw enter key on ISO layout, return
    if ((ansi_layout == false) && (key_row == 2) && (key_col == 14)) {
        for (int i = 0; i < 10; i++) {
            write_pixel(keymap_template[0] + 81, keymap_template[1] + 5 + i, onoff);
            if (i < 5) {
                write_pixel(keymap_template[0] + 74, keymap_template[1] + 5 + i, onoff);
            }
            if (i < 6) {
                write_pixel(keymap_template[0] + 75, keymap_template[1] + 9 + i, onoff);
            }
            if (i < 7) {
                write_pixel(keymap_template[0] + 75 + i, keymap_template[1] + 5, onoff);
                write_pixel(keymap_template[0] + 75 + i, keymap_template[1] + 14, onoff);
            }
        }
        return;
    }
    // Draw top and bottom walls (horizontal for <length>px)
    for (int x = 0; x < length; x++) {
        write_pixel(left + x, top, onoff);
        write_pixel(left + x, bottom, onoff);
    }
    // Draw left and right walls (vertical for 5px)
    for (int y = 0; y < 5; y++) {
        write_pixel(left,  top + y, onoff);
        write_pixel(right, top + y, onoff);
    }
    // Special case 2 - Draw right spacebar on split-space layout
    if ((split_space == true) && (key_row == 4) && (key_col == 6)) {
        int start = keymap_template[0] + 46;
        int stop  = keymap_template[0] + 55;
        for (int x = start; x < stop; x++) {
            write_pixel(x, top, onoff);
            write_pixel(x, bottom, onoff);
        }
        for (int y = 0; y < 5; y++) {
            write_pixel(start, top + y, onoff);
            write_pixel(stop,  top + y, onoff);
        }
    }
}

// Write active layer name
static void render_layer_state(void) {
  if (oled_horizontal) {
    oled_set_cursor(0, 0);
  } else {
    oled_set_cursor(0, 15);
  }
  switch (get_highest_layer(layer_state)) {
  case _MA:
      oled_write_P(PSTR(MA_LAYER_NAME), false);
      break;
  case _L1:
      oled_write_P(PSTR(L1_LAYER_NAME), false);
      break;
  case _L2:
      oled_write_P(PSTR(L2_LAYER_NAME), false);
      break;
  case _L3:
      oled_write_P(PSTR(L3_LAYER_NAME), false);
      break;
  default:
      oled_write("ERROR", false);
      break;
  }
}

// Update WPM counters
static void render_wpm_counters(int current_wpm) {
    int cursorposition_cur = 2;
    int cursorposition_max = 1;
    if (oled_horizontal == false) {
        cursorposition_cur = 13;
        cursorposition_max = 14;
    }

    char wpm_counter[4];
    wpm_counter[3] = '\0';
    wpm_counter[2] = '0' + current_wpm % 10;
    wpm_counter[1] = '0' + (current_wpm / 10) % 10;
    wpm_counter[0] = '0' + (current_wpm / 100) % 10;
    oled_set_cursor(0, cursorposition_cur);
    oled_write(wpm_counter, false);

    if (current_wpm > max_wpm) {
        max_wpm = current_wpm;
        wpm_limit = max_wpm + 20;
        oled_set_cursor(0, cursorposition_max);
        oled_write(wpm_counter, false);
    }
}

// Update WPM snail icon
static void render_wpm_icon(int current_wpm) {
    // wpm_icon is used to prevent unnecessary redraw
    if ((current_wpm < icon_med_wpm) && (wpm_icon != 0)) {
        wpm_icon = 0;
    } else if ((current_wpm >= icon_med_wpm) && (current_wpm < icon_fast_wpm) && (wpm_icon != 1)) {
        wpm_icon = 1;
    } else if ((current_wpm >= icon_fast_wpm) && (wpm_icon != 2)) {
        wpm_icon = 2;
    } else {
        return;
    }
    static const char PROGMEM snails[][2][24] = {
        {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0xA0, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x50, 0x88, 0x04, 0x00, 0x00},
         {0x40, 0x60, 0x50, 0x4E, 0x51, 0x64, 0x4A, 0x51, 0x54, 0x49, 0x41, 0x62, 0x54, 0x49, 0x46, 0x41, 0x40, 0x30, 0x09, 0x04, 0x02, 0x01, 0x00, 0x00}},
        {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x04, 0x98, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00},
         {0x60, 0x50, 0x54, 0x4A, 0x51, 0x64, 0x4A, 0x51, 0x55, 0x49, 0x41, 0x62, 0x54, 0x49, 0x46, 0x41, 0x21, 0x10, 0x0A, 0x08, 0x05, 0x02, 0x00, 0x00}},
        {{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x10, 0x10, 0x10, 0x20, 0x40, 0x40, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00},
         {0x60, 0x58, 0x54, 0x62, 0x49, 0x54, 0x52, 0x51, 0x55, 0x49, 0x62, 0x52, 0x4D, 0x45, 0x46, 0x22, 0x21, 0x11, 0x10, 0x0A, 0x08, 0x05, 0x02, 0x00}}
    };
    if (oled_horizontal) {
        oled_set_cursor(3, 1);
        oled_write_raw_P(snails[wpm_icon][0], sizeof(snails[wpm_icon][0]));
        oled_set_cursor(3, 2);
        oled_write_raw_P(snails[wpm_icon][1], sizeof(snails[wpm_icon][1]));
    } else {
        oled_set_cursor(0, 11);
        oled_write_raw_P(snails[wpm_icon][0], sizeof(snails[wpm_icon][0]));
        oled_set_cursor(0, 12);
        oled_write_raw_P(snails[wpm_icon][1], sizeof(snails[wpm_icon][1]));
    }
}

// Update WPM graph
static void render_wpm_graph(int current_wpm) {
    int line_height = ((current_wpm / graph_top_wpm) * 7);
    if (line_height > 7) {
        line_height = 7;
    }
    // Count graph line pixels, return if nothing to draw
    int pixel_count = line_height;
    for (int i = 0; i < 63; i++) {
        pixel_count += graph_lines[i];
    }
    if (pixel_count == 0) {
        return;
    }
    // Shift array elements left or right depending on graph_direction, append new graph line
    if (graph_direction) {
        for (int i = 0; i < 63; i++) {
            graph_lines[i] = graph_lines[i + 1];
        }
        graph_lines[63] = line_height;
    } else {
        for (int i = 63; i > 0; i--) {
            graph_lines[i] = graph_lines[i - 1];
        }
        graph_lines[0] = line_height;
    }
    // Draw all graph lines (left to right, bottom to top)
    int draw_count, arrpos;
    for (int x = 1; x <= 127; x += 2) {
        arrpos = x / 2;
        draw_count = graph_lines[arrpos];
        for (int y = 31; y >= 25; y--) {
            if (draw_count > 0) {
                write_pixel(x, y, true);
                draw_count--;
            } else {
                write_pixel(x, y, false);
            }
        }
    }
}

// Call OLED functions
bool oled_task_user(void) {
    // Draw OLED keyboard, prevent redraw
    if (first_loop) {
        render_background();
        render_fn_row();
        if (ansi_layout == false) {
            render_iso();
        }
        first_loop = false;
    }
    // Get current WPM, subtract 25% for accuracy and prevent large jumps caused by simultaneous keypresses
    int current_wpm = get_current_wpm();
    // Note: This will most likely be removed once QMK's WPM calculation is updated
    current_wpm -= current_wpm >> 2;
    if (current_wpm > wpm_limit) {
        current_wpm = max_wpm;
        set_current_wpm(max_wpm);
    }
    // Write active layer name to display
    render_layer_state();
    // Update WPM counters
    render_wpm_counters(current_wpm);
    // Update WPM snail icon
    render_wpm_icon(current_wpm);
    // Update WPM graph every graph_refresh milliseconds
    if (timer_elapsed(timer) > graph_refresh) {
        render_wpm_graph(current_wpm);
        timer = timer_read();
    }
    return false;
}
#endif

// Called by QMK during key processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Forwards keystrokes from an external input device over UART/TRRS
    process_record_remote_kb(keycode, record);

    #ifdef OLED_ENABLE
    // Toggle pixels surrounding key
    render_keymap(record->event.key.row, record->event.key.col, record->event.pressed);
    #endif

    return true;
}

// Rotary encoder - RGB and OLED settings
void change_RGB(bool clockwise) {
    // While on any layer except default:       // Rotary         = RGB Mode
    bool shift = get_mods() & MOD_MASK_SHIFT;   // Rotary + Shift = OLED Brightness
    bool ctrl = get_mods() & MOD_MASK_CTRL;     // Rotary + Ctrl  = RGB Brightness
    bool gui = get_mods() & MOD_MASK_GUI;       // Rotary + Gui   = RGB Saturation
    bool alt = get_mods() & MOD_MASK_ALT;       // Rotary + Alt   = RGB Hue

    if (clockwise) {
        if (shift) {
            int new_brightness = oled_get_brightness() + 10;
            if (new_brightness < 255) {
                oled_set_brightness(new_brightness);
            } else {
                oled_set_brightness(255);
            }
        } else if (ctrl) {
            rgblight_increase_val();
        } else if (gui) {
            rgblight_increase_sat();
        } else if (alt) {
            rgblight_increase_hue();
        } else {
            rgblight_step();
        }
    } else {
        if (shift) {
            int new_brightness = oled_get_brightness() - 10;
            if (new_brightness > 0) {
                oled_set_brightness(new_brightness);
            } else {
                oled_set_brightness(0);
            }
        } else if (ctrl) {
            rgblight_decrease_val();
        } else if (gui) {
            rgblight_decrease_sat();
        } else if (alt) {
            rgblight_decrease_hue();
        } else {
            rgblight_step_reverse();
        }
    }
}

// Rotary encoder behavior - Change volume on default layer, RGB/OLED on other layers
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (layer_state_is(0)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else {
        change_RGB(clockwise);
    }
    return true;
}

// Initialize remote keyboard, if connected
void matrix_init_user(void) {
    matrix_init_remote_kb();
}

// Scan and parse keystrokes from remote keyboard, if connected
void matrix_scan_user(void) {
    matrix_scan_remote_kb();
}
