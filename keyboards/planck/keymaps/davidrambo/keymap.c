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

#define A_BSPC  LALT(KC_BSPC)
#define A_LEFT  LALT(KC_LEFT)
#define A_RGHT  LALT(KC_RGHT)
#define C_TAB   LCTL(KC_TAB)
#define CTLPGUP LCTL(KC_PGUP) // back one tab in Brave
#define CTLPGDN LCTL(KC_PGDN) // forward one tab in Brave
#define G_TAB   LGUI(KC_TAB)
#define G_GRV   LGUI(KC_GRV)
#define SftEnt  SFT_T(KC_ENT)
#define NAV     LT(2, KC_TAB)
#define RECT    LCA_T(KC_DEL) // Ctrl+Alt is the basis for Rectangle WM shortcuts

enum custom_layers {
    _COLEMAK,
    _SYMBOL,
    _NAVIGATION,
}

//tapdance declarations
enum {
  SFT_LCK
};

#define SftLck TD(SFT_LCK) /* alias for tapdance */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | ESC` |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |SftLck|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |  /?  |SftEnt|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  | GUI  | Ctrl | Alt  | GUI  |    Space    |Symbol| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
*/

[_COLEMAK] = LAYOUT_planck_grid(
  KC_GESC, KC_Q   , KC_W   , KC_F   , KC_P   , KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  NAV    , KC_A   , KC_R   , KC_S   , KC_T   , KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  SftLck , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SftEnt ,
  RECT   , KC_LGUI, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  MO(1),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |   [  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   ]  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  \|  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  =+  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Home | End  |      |      | BRMD | BRMU |  -_  |Pg Up |      |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  `~  |      |      |      |Alt(Bk)|            |      |Pg Dn | Vol- | Vol+ |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOL] = LAYOUT_planck_grid(
  KC_LBRC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_RBRC,
  KC_BSLS, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL ,
  _______, KC_HOME, KC_END , _______, _______, KC_BRMD, KC_BRMU, KC_MINS, KC_PGUP, _______, _______, _______,
  _______, KC_GRV , _______, _______, _______ , _______, _______, _______, KC_PGDN, KC_VOLD, KC_VOLU, KC_MUTE
  ),

/* Navigation*/

[_NAVIGATION] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, C_TAB  , A_LEFT,  KC_UP,   A_RGHT , KC_DEL , _______,
    _______, _______, _______, _______, _______, _______, CTLPGUP, KC_LEFT, KC_DOWN, KC_RGHT, CTLPGDN, _______,
    _______, _______, _______, _______, _______, _______, G_TAB  , A_BSPC , KC_HOME, KC_END,  G_GRV  , _______,
    RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
