/* Copyright 2022 Cole Smith <cole@boardsource.xyz>
 * Copyright 2022 David Rambo <davidrambo@mailfence.com>
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

enum custom_layers {
    _COLEMAK,
    _GAME,
    _SYMBOL,
    _NAVIGATION,
    _FKEYS,
};

//keycode shorthands
#define SYM  MO(2)
#define NAV  LT(3, KC_ESC)
#define FKEY MO(4)

//aliases for clarity in layering
#define SftEnt  SFT_T(KC_ENT)   // Shift when held, Enter when tapped
#define BSCTL   LCTL_T(KC_BSPC) // Ctrl when held, Backspace when tapped

//aliases for clarity in layering
#define C_TAB   LCTL(KC_TAB)
#define A_TAB   LALT(KC_TAB)
#define G_TAB   LGUI(KC_TAB)    // Mac: switch applications

#define CBSPC   LCTL(KC_BSPC)  // delete whole word
#define G_LEFT  LGUI(KC_LEFT)
#define G_RGHT  LGUI(KC_RGHT)
#define CRGHT   LCTL(KC_RGHT)
#define CLEFT   LCTL(KC_LEFT)

// Left-hand home row mods
#define HOME_A LALT_T(KC_A)
#define HOME_R LGUI_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_N RCTL_T(KC_N)
#define HOME_E RSFT_T(KC_E)
#define HOME_I LGUI_T(KC_I)
#define HOME_O LALT_T(KC_O)

//internet browser tab shortcuts and window swapping
#define CTLPGDN LCTL(KC_PGDN)
#define CTLPGUP LCTL(KC_PGUP)

#define G_GRV   LGUI(KC_GRV)
#define SftEnt  SFT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `~  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   :  | BSP  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |EscNAV|   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   NO  |    |   NO  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |EntSft|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Del  | LGUI | LALT | /LCTL/BS/       \Space \  | SYM  | FKEY | RALT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEMAK] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  NAV,      HOME_A, HOME_R,  HOME_S,  HOME_T,  KC_D,                     KC_H,    HOME_N,  HOME_E,  HOME_I,  HOME_O,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_MUTE,   KC_NO, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SftEnt,
                     MEH_T(KC_DEL), KC_LALT, KC_LGUI, BSCTL,          KC_SPC,   SYM,   FKEY, KC_RALT
),

/* Gaming Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ESC |  T   |  Q   |  W   |  E   |  R   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  TAB | LSFT |  S   |  A   |  D   |  F   |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | LALT | LCTL |  Z   |  X   |  C   |  V   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_GAME] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, TO(0),
  KC_ESC , KC_T   , KC_Q   , KC_W   , KC_E   , KC_R   ,                      _______, _______, _______, _______, _______, _______,
  KC_TAB , KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   ,                      _______, _______, _______, _______, _______, _______,
  KC_LALT, KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   ,  _______,  _______,  _______, _______, _______, _______, _______, _______,
                               KC_M,    KC_I,    KC_B,  KC_SPC ,    _______,  _______, _______, _______
),

/* Symbol Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   [  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   ]  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  \|  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | HOME |  END |   [  |   ]  |      |-------|    |-------|  `~  |   _  | PGUP |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | ____ | ____ | ____ | / ____  /       \ ____ \  |RAISE | PGDN | ____ |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SYMBOL] = LAYOUT(
  KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                    KC_F6  , KC_F7  , KC_F8  , KC_F9 ,  KC_F10 , KC_F11 ,
  KC_LBRC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                    KC_6   , KC_7   , KC_8   , KC_9  ,  KC_0   , KC_RBRC,
  KC_BSLS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL ,
  _______, KC_HOME, KC_END , KC_LBRC, KC_RBRC, _______, _______,  _______, KC_GRV , KC_MINS, KC_PGUP, _______, _______, _______,
                            _______, _______, _______, _______,    _______, _______, KC_PGDN, _______
),
/* Navigation
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |  UP  |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | LEFT | DOWN |RIGHT |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_NAVIGATION] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  _______, _______, KC_BTN2, KC_MS_U, KC_BTN1, _______,                      C_TAB  , CLEFT  ,  KC_UP , CRGHT  , KC_DEL , _______,
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                      CTLPGUP, KC_LEFT, KC_DOWN, KC_RGHT, CTLPGDN, _______,
  _______, _______, _______, KC_WH_U, KC_WH_D, _______,  _______,  _______,  A_TAB  , CBSPC  , _______, _______, G_GRV  , _______,
                            _______, _______, _______,  _______,    _______,  _______, _______, _______
),
/* Function Keys
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | BOOT |      |      |      |      |      |                    | LALT<-->LGUI|      |      |      | BOOT |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |BRGHT-| SAT- | HUE- |BRGHT+|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |RGBMOD| SAT+ | HUE+ |RGBTOG|-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |VOL UP|VOL DN| PLAY |    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_FKEYS] = LAYOUT(
  QK_BOOT, _______, _______, _______, _______, _______,                      LAG_SWP, LAG_NRM, _______, _______, _______, QK_BOOT,
  _______, _______, RGB_VAD, RGB_SAD, RGB_HUD, RGB_VAI,                      _______, _______, _______, _______, _______, TO(1)  ,
  _______, _______, RGB_MOD, RGB_SAI, RGB_HUI, RGB_TOG,                      _______, _______, _______, _______, _______, TO(0)  ,
  _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPLY,  _______,  _______,  _______, _______, _______, _______, _______, _______,
                            _______, _______, _______,  _______,    _______,  _______, _______, _______
)
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }
    return false;
}
#endif
