/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
    _MACBASE = 0,
    _WINBASE,
    _MACNAV,
    _WINNAV,
    _SYMBOLS,
    _NUM,
    _ADJUST
};

enum custom_keycodes {
    MacBase = SAFE_RANGE,
    WinBase
};

//Mac specific
#define M_PRVWD LALT(KC_LEFT)      // Previous word
#define M_NXTWD LALT(KC_RIGHT)     // Next word
#define M_UNDO  LGUI(KC_Z)         // UNDO
#define M_CUT   LGUI(KC_X)         // CUT
#define M_COPY  LGUI(KC_C)         // COPY
#define M_PASTE LGUI(KC_V)         // PASTE

//Win specific
#define W_PRVWD LCTL(KC_LEFT)      // Previous word
#define W_NXTWD LCTL(KC_RIGHT)     // Next word
#define W_UNDO  LCTL(KC_Z)         // UNDO
#define W_CUT   LCTL(KC_X)         // CUT
#define W_COPY  LCTL(KC_C)         // COPY
#define W_PASTE LCTL(KC_V)         // PASTE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   TAB  |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   NAV  |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |Enter |  ESC |  |ADJUST|Space |   N  |   M  | ,  < | . >  | /  ? |  Del   |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        | LCTL | GUI  | SYMB |      | NUM  |  | NUM  |      | SYMB | NAV  |LEADER|
 *                        |      |      |      | RAlt |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MACBASE] = LAYOUT(
      KC_TAB  , KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      MO(_MACNAV), KC_A,   KC_S,   KC_D,   KC_F, KC_G,                                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT , KC_Z,   KC_X,   KC_C,   KC_V,   KC_B, XXXXXXX   ,   KC_ESC,    MO(_ADJUST), XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_DEL),
                   KC_LCTL, KC_LGUI, MO(_SYMBOLS), RALT_T(KC_ENT), TT(_NUM),  TT(_NUM), KC_SPC, MO(_SYMBOLS), TT(_NUM), KC_LEAD
    ),
    [_WINBASE] = LAYOUT(
      KC_TAB  , KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      MO(_WINNAV), KC_A,   KC_S,   KC_D,   KC_F, KC_G,                                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT , KC_Z,   KC_X,   KC_C,   KC_V,   KC_B, XXXXXXX    ,   KC_ESC,    MO(_ADJUST), XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_DEL),
                    KC_LCTL, KC_LGUI, MO(_SYMBOLS), RALT_T(KC_ENT), TT(_NUM),  TT(_NUM), KC_SPC, MO(_SYMBOLS), MO(_WINNAV), KC_LEAD
    ),
/*
 * Navigation Layer: Cursor, Text Navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |WheelU|      |      |                              |      |PrevW |  Up  |NextW |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |       | LCTL |WheelD|LSFT |      |                              | Bksp | Left | Down |Right | Del  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | Undo | Cut  | Copy |Paste |      |      |      |  |      |      |      | Home |      | End  |      |        |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        |      |      |      |Trans |Trans |  |Trans |Trans |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MACNAV] = LAYOUT(
      _______, _______, _______, KC_WH_U, _______, _______,                                     _______, M_PRVWD, KC_UP, M_NXTWD, _______, _______,
      _______, _______, KC_LCTL, KC_WH_D, KC_LSFT, _______,                                     KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL, _______,
      _______, M_UNDO , M_CUT  , M_COPY , M_PASTE, _______, XXXXXXX, _______, _______, XXXXXXX, _______, KC_HOME, _______, KC_END, _______, _______,
                                 _______, _______, _______, _______, KC_TRNS, KC_TRNS, _______, _______, _______, _______
    ),
    [_WINNAV] = LAYOUT(
      _______, _______, _______, KC_WH_U, _______, _______,                                     _______, M_PRVWD, KC_UP, M_NXTWD, _______, _______,
      KC_TRNS, _______, KC_LCTL, KC_WH_D, KC_LSFT, _______,                                     KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL, _______,
      _______, W_UNDO , W_CUT  , W_COPY , W_PASTE, _______, XXXXXXX, _______, _______, XXXXXXX, _______, KC_HOME, _______, KC_END, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, KC_TRNS, _______
    ),
/*
 * Symbol Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ` ~   |   !  |  @   |  #   |  $   |  %   |                              |  ^   |  {   |  }   |      |  €   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   ~    |      |      | - _  | = +  |  &   |                              |  *   |  (   |  )   |      |  |   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |  _   |  +   |      |      |      |  |      |      |      | [ {  | ] }  |      | \ |  |        |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        |      |      |Trans |Trans |      |  |      |Trans |Trans |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT(
       KC_GRV, KC_EXLM,  KC_AT , KC_HASH, KC_DLR , KC_PERC,                                     KC_CIRC, KC_LCBR, KC_RCBR, _______, ALGR(KC_5), _______,
      KC_TILD, _______, _______, KC_MINS, KC_EQL , KC_AMPR,                                     KC_ASTR, KC_LPRN, KC_RPRN, _______, KC_PIPE, _______,
      _______, _______, _______, KC_UNDS, KC_PLUS, _______, XXXXXXX, _______, _______, XXXXXXX, _______, KC_LBRC, KC_RBRC, _______, KC_BSLS, _______,
                                 _______, _______, KC_TRNS, _______, _______, _______, _______, KC_TRNS, _______, _______
    ),
/*
 * Num Layer: Numblock and Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |  /   |  7 & |  8 * |  9 ( |  -   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | Trans  |  F5  |  F6  |  F7  |  F8  |      |                              |  *   |  4 $ |  5 % |  6 ^ |  +   | Space  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |  0 ) |  1 ! |  2 @ |  3 # |  ,   |   =    |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        |      | LCTL |      | LALT |      |  |      |      |      |Trans |  .   |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      _______,  KC_F9 , KC_F10 , KC_F11 , KC_F12 , _______,                                     KC_PSLS,  KC_7  ,  KC_8  ,  KC_9  , KC_PMNS, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     KC_PAST,  KC_4  ,  KC_5  ,  KC_6  , KC_PLUS, KC_SPC ,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, XXXXXXX, _______, _______, XXXXXXX,  KC_0  ,  KC_1  ,  KC_2  ,  KC_3  , KC_PCMM, KC_PEQL,
                                 _______, KC_LCTL, _______, KC_LALT, KC_TRNS, KC_TRNS, _______, _______, _______, KC_PDOT
    ),
/*
 * Adjust Layer: Media, Mouse movement
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |WheelU|MouseU|WheelD|      |                              | SAI  |      | Vol+ |      | Play |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |MouseL|MouseD|MouseR|      |                              | HUI  | Prev | Vol- |  Nxt |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |Mouse1|Mouse3|Mouse2|      |      |      |  |Trans |      | VAI  | Mute |      |      |      |        |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        | Win  | Mac  |      |      |      |  | RGB  |      | RGB  |      |      |
 *                        | Dflt | Dflt |      |      |      |  |Toggle|      | Mode |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______,                                     RGB_SAI, _______, KC_VOLU, _______, KC_MPLY, _______,
      _______, _______, KC_MS_L, KC_MS_D, KC_MS_L, _______,                                     RGB_HUI, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______,
      _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, XXXXXXX, _______, KC_TRNS, XXXXXXX, RGB_VAI, KC_MUTE, _______, _______, _______, _______,
                       WinBase, MacBase, _______, _______, _______, RGB_TOG, _______, RGB_MOD, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _NAVIGATION, _SYMBOLS, _NUM);
// }

void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(HSV_CYAN);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MacBase:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_MACBASE);
            }
            break;
        case WinBase:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WINBASE);
            }
            break;
    }
    return true;
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_S) {
      // No clue why I have to add 1 to default_layer to get into correct branch
            if (default_layer_state == 1) { // _MACBASE is default
                SEND_STRING(SS_LGUI(SS_LSFT("4"))); // Mac screenshot
            } else if (default_layer_state == 2) { // _WINBASE is default
                SEND_STRING(SS_LGUI("\nS")); // Win screenshot
            }
        }
        SEQ_ONE_KEY(KC_V) {
            if (default_layer_state == 1) {
                SEND_STRING(SS_LGUI(SS_LSFT("5"))); // Mac video
            }
        }
        SEQ_ONE_KEY(KC_P) {
            if (default_layer_state == 1) {
                SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_PWR())))); // Mac Sleep
            } else if (default_layer_state == 2) {
                SEND_STRING(SS_LGUI("x") "u" "h"); // Win hibernate
            }
        }
    }
}
