/* Copyright 2021 David Rambo
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

//aliases for clarity in layering
#define ABSPC  LALT(KC_BSPC) // delete whole word in Mac
#define CBSPC  LCTL(KC_BSPC) // delete whole word in PC
#define ALEFT  LALT(KC_LEFT)
#define ARGHT  LALT(KC_RGHT)
#define CRGHT  LCTL(KC_RGHT)
#define CLEFT  LCTL(KC_LEFT)
#define SftEnt SFT_T(KC_ENT)
#define BSGUI  LGUI_T(KC_BSPC)
#define BSCTL  LCTL_T(KC_BSPC)

// internet browser tab shortcuts and window/application swapping for Mac and Win
#define GSL     LGUI(S(KC_LEFT)) // back one tab in Safari
#define GSR     LGUI(S(KC_RGHT)) // forward one tab in Safari
#define CTLPGDN LCTL(KC_PGDN)   // back one tab on PC
#define CTLPGUP LCTL(KC_PGUP)   // forward one tab on PC
#define GTAB    LGUI(KC_TAB)    // Mac: switch applications
#define GGRV    LGUI(KC_GRV)    // Mac: switch between windows within an application
#define ATAB    LALT(KC_TAB)
#define CTAB    LCTL(KC_TAB)

// toggles for navigation layers for Mac, PC, and Roguelike Numpad
#define NAV     LT(5, KC_ESC)
#define NAVPC   LT(6, KC_ESC)
#define NAVQUD  MO(7)

enum custom_layer {
    _COLEMAK,
    _PC,
    _GAME,     // Gaming layer
    _QUD,3     // Roguelike layer
    _SYMBOL,   // Function keys, numbers, symbols, Backlighting
    _NAV,      // Navigation Layer on Mac
    _NAVPC,    // Navigation Layer on Win
    _NAVQUD,   // Numpad for Roguelike 8-directional movement
}

// tapdance declarations
enum {
  SFT_LCK
};

// alias for tapdance
#define SftLck TD(SFT_LCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `~     | 1      | 2      | 3      | 4      | 5      | -_     |   PC   | =+     | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | ESC/`~ | Q      | W      | F      | P      | G      | [      |   \|   | ]      | J      | L      | U      | Y      | ;      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | NAVTAB | A      | S      | D      | F      | G      | PgUp   |PlayPaus| ENTER  | H      | N      | E      | I      | O      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |SFT/CAPS| Z      | X      | C      | V      | B      | PgDn   |  UP    | ENTER  | K      | M      | ,      | .      | /      | SftEnt |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | DEL    | LGUI   | LCTRL  | LALT   | LGUI   | BKSPC  | LEFT   | DOWN   | RIGHT  | SPACE  | SYMBOL | RGUI   | RALT   | RCTRL  | BL     |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_COLEMAK] = LAYOUT_ortho_5x15( /* COLEMAK */
   KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MINS, TO(1)  , KC_EQL,  KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
   KC_TAB , KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,   KC_LBRC, KC_BSLS, KC_RBRC, KC_J,   KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
   NAV    , KC_A,    KC_R,    KC_S,    KC_T,    KC_D,   KC_PGUP, KC_MPLY, GGRV   , KC_H,   KC_N,   KC_E,    KC_I,    KC_O,    KC_QUOT,
   SftLck , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_PGDN, KC_UP  , GTAB   , KC_K,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, SftEnt,
   KC_DEL , KC_LGUI, KC_LCTL, KC_LALT, KC_LCTL, BSGUI,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC, MO(4) , KC_RGUI, KC_RALT, KC_RCTL, BL_STEP
 ),
    
// Linux/Windows Layer: essentially swaps Control and GUI

 [_PC] = LAYOUT_ortho_5x15( /* WINDOWS */
   _______, _______, _______, _______, _______, _______, _______, TO(2)  , _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   NAVPC  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, ATAB   , _______, _______, _______, _______, _______, _______,
   _______, KC_PSCR, KC_LGUI, _______, KC_LGUI, BSCTL  , _______, _______, _______, _______, _______, KC_RCTL, _______, KC_RGUI, _______
 ),

 [_GAME] = LAYOUT_ortho_5x15( /* Gaming Layer */
   _______, _______, _______, _______, _______, _______, _______, TO(0)  , _______, _______, _______, _______, _______, _______, TO(3)  ,
   KC_ESC , KC_T   , KC_Q   , KC_W   , KC_E   , KC_R   , KC_F7  , KC_F8  , KC_F9  , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , _______,
   KC_TAB , KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_F4  , KC_F5  , KC_F6  , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, _______,
   KC_LALT, KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_F1  , KC_F2  , KC_F3  , KC_N   , KC_M   , _______, _______, _______, KC_ENT ,
   _______, _______, _______, KC_G   , KC_B   , KC_SPC , KC_I   , KC_M   , ATAB   , _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______
 ),
  
   [_QUD] = LAYOUT_ortho_5x15( /* Roguelike Layer */
   _______, _______, _______, _______, _______, _______, _______,KC_PSLS, KC_PAST, _______, _______, _______, _______, _______, TO(0),
   KC_GESC, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,   KC_LBRC, KC_BSLS, KC_RBRC, KC_J,   KC_L,   KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
   NAV    , KC_A,    KC_R,    KC_S,    KC_T,    KC_D,   KC_PGUP, KC_MPLY, GGRV   , KC_H,   KC_N,   KC_E,    KC_I,    KC_O,    KC_QUOT,
   SftLck , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_PGDN, KC_UP  , ATAB   , KC_K,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, SftEnt ,
   KC_DEL , KC_LGUI, KC_LGUI, KC_LALT, KC_LCTL, TO(7),  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC, MO(4) , KC_RGUI, KC_RALT, KC_RCTL, _______
 ),
    
/* SYMBOL
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F12    | F1     | F2     | F3     | F4     | F5     |        |        |        | F6     | F7     | F8     | F9     | F10    | F11    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | [{     | 1      | 2      | 3      | 4      | 5      |        |        |        | 6      | 7      | 8      | 9      | 0      | }]     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | !      | @      | #      | $      | %      |        |        |        | ^      | &      | *      | (      | )      | =      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | HOME   | END    | BL_OFF | BL_ON  |        |        |        |        |        | -_     |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_SYMBOL] = LAYOUT_ortho_5x15( /* SYMBOL */
   KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______, _______, _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
   KC_LBRC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, _______, _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_RBRC,
   _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL ,
   _______, KC_HOME, KC_END , BL_OFF , BL_ON  , KC_VOLD, _______, _______, _______, KC_VOLU, KC_MINS, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),

 
 [_NAV] = LAYOUT_ortho_5x15( /* NAVIGATION for Mac */
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, CTAB   , ALEFT  , KC_UP  , ARGHT  , KC_DEL , _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, CTLPGUP, KC_LEFT, KC_DOWN, KC_RGHT, CTLPGDN, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, GTAB   , ABSPC  , KC_HOME, KC_END , GGRV   , _______,
   QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),

 [_NAVPC] = LAYOUT_ortho_5x15( /* NAVIGATION FOR PC: replaces Alt with Control, GUI with Alt, and browser tab shortcuts*/
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, CTAB   , CLEFT  , KC_UP  , CRGHT  , KC_DEL , _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, CTLPGUP, KC_LEFT, KC_DOWN, KC_RGHT, CTLPGDN, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, ATAB   , CBSPC  , KC_HOME, KC_END , _______, _______,
   QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),
    
 [_NAVQUD] = LAYOUT_ortho_5x15( /* NAVIGATION for Mac */
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_2, KC_KP_6, KC_PPLS, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_5, KC_KP_3, _______, _______,
   _______, _______, _______, _______, _______,   TO(3), _______, _______, _______, _______, KC_KP_0, KC_PDOT, _______, _______, _______
 )
};

// Shift vs capslock function. From bbaserdem's Planck keymap.
void caps_tap (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LSFT);
    } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        register_code (KC_CAPS);
    }
}
void caps_tap_end (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_LSFT);
    } else {
        unregister_code (KC_CAPS);
    }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Shift, twice for Caps Lock
  [SFT_LCK] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end )
};

/* Template for future layers
 [_LAYER_NAME] = { 
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
 }
};
*/
