 /* Copyright 2021 Jesper Nellemann Jakobsen
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

enum layers {
    _BASE,
    _ARROWS,
    _HDUE, /* Home, pgDown, pgUp, End */
    _MOUSE,
    _FN
};

/* Custom keys */

/* Word movement/deletetion */
#define WORD_BK A(KC_LEFT)
#define WORD_FW A(KC_RIGHT)
#define D_WORD_BK A(KC_BSPACE)
#define D_WORD_FW A(KC_DELETE)
/* Fine volume control */
#define FVOLU S(A(KC_VOLU))
#define F_VOLD S(A(KC_VOLD))
/* Multi-purpose keys */
#define HYPR_CAPS ALL_T(KC_CAPS)
#define CTL_ESC LCTL_T(KC_ESC)
/* Layer keys */
#define ARROWS LT(_ARROWS, KC_D)
#define HDUE MO(_HDUE)
#define MOUSP LT(_MOUSE, KC_SPC)
#define FN MO(_FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  Default layer:
     * Space Cadet shifts (parentheses on tap)
     * Caps Lock is Control on hold, Esc on tap
     * Hyper/Caps Lock on Control keys
     * Hold D to activate layer 1 (Arrows)
     * Hold Space to activate layer 3 (Mouse keys)
     * Hold FN to activate layer 4 (FN layer)
     */
    [_BASE] = LAYOUT_60_ansi(
        KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CTL_ESC,   KC_A,    KC_S,    ARROWS,  KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSPO,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC,
        HYPR_CAPS, KC_LALT, KC_LGUI,                            MOUSP,                              KC_RGUI, KC_RALT, FN,      HYPR_CAPS
    ),

    /*  Layer 1:
     * Vim arrows (HJKL)
     * Vim-like move across words with W(ord), and B(eginning)
     * Media controls (fine volume controls using Option+Shift)
     * Backspace/Del on N/M
     * Hold F to activate layer 2 (HDUE: Home, Down, Up, End)
     */
    [_ARROWS] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, WORD_FW, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, F_VOLD,  FVOLU,   _______,
        _______, _______, _______, _______, HDUE,    _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______,          _______, _______, _______, _______, WORD_BK, KC_BSPC, KC_DEL,  _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),

    /*  Layer 2:
     * Home, Page Down, Page Up, End
     * Delete word forward/back on W/B
     */
    [_HDUE] = LAYOUT_60_ansi(
        _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, D_WORD_FW, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,   _______, _______, _______, KC_HOME,   KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,
        _______,          _______,   _______, _______, _______, D_WORD_BK, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                              _______,                              _______, _______, _______, _______
    ),

    /*  Layer 3:
     * Mouse keys
     * Cursor movement: HJKL
     * MB 1, 2, and 3 on F, D, and S, respectively
     * Mouse wheel: up (V), down (R) (reversed because of Natural Scrolling)
     * Change mouse acceleration on U, I, O (0, 1, 2)
     */
    [_MOUSE] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_WH_D, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______,
        _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,          _______,
        _______,          _______, _______, _______, KC_WH_U, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),

    /*  Layer 4:
     * F1-12
     * Del on backspace
     * Lots of RGB controls
     * RESET firmware on backslash
     * Screen brightness: Z (decrease), X (increase)
     */
    [_FN] = LAYOUT_60_ansi(
        _______, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_M_P,  RGB_M_B,  RGB_M_R, _______, _______, _______, RESET,
        _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_M_SW, RGB_M_SN, RGB_M_K, _______, _______,          _______,
        _______,          KC_BRID,  KC_BRIU, _______, _______, _______, _______,  RGB_M_X,  RGB_M_G, RGB_M_T, _______,          _______,
        _______, _______, _______,                             _______,                              _______, _______, _______, _______
    )

    // TEMPLATE
    // LAYOUT_60_ansi(
    //    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //    _______, _______, _______,                            _______,                            _______, _______, _______, _______,
    // ),
};
