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
    _QWERTY = 0,
    _COLEMAK,
    _NAV,
    _SYMBOLS,
    _NUM,
    _ADJUST
};

enum custom_keycodes {
    Qwerty = SAFE_RANGE,
    Colemak
};

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
 *                        | LCTL | GUI  | RALT |      | NUM  |  | NUM  |      | SYMB | NAV  |LEADER|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
      MO(_NAV), KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN, KC_QUOT,
      KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , XXXXXXX, KC_ESC , MO(_ADJUST), XXXXXXX, KC_N,  KC_M ,KC_COMM, KC_DOT ,KC_SLSH, RSFT_T(KC_DEL),
                                 KC_LCTL, KC_LGUI, KC_RALT, KC_ENT ,TT(_NUM),TT(_NUM), KC_SPC, MO(_SYMBOLS), MO(_NAV), KC_LEAD
    ),

/*
 * Base Layer: Colemak
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   TAB  |   Q  |   W  |   F  |   P  |   G  |                              |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   NAV  |   A  |   R  |  S   |   T  |   D  |                              |   H  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |Enter |  ESC |  |ADJUST|Space |   K  |   M  | ,  < | . >  | /  ? |  Del   |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        | LCTL | GUI  | RALT |      | NUM  |  | NUM  |      | SYMB | NAV  |LEADER|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK] = LAYOUT(
      KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_G ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_BSPC,
      MO(_NAV), KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_D ,                                        KC_H,   KC_N ,  KC_E ,   KC_I ,  KC_O , KC_QUOT,
      KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , XXXXXXX, KC_ESC , MO(_ADJUST), XXXXXXX, KC_K,  KC_M ,KC_COMM, KC_DOT ,KC_SLSH, RSFT_T(KC_DEL),
                                 KC_LCTL, KC_LGUI, KC_RALT, KC_ENT ,TT(_NUM),TT(_NUM), KC_SPC, MO(_SYMBOLS), MO(_NAV), KC_LEAD
    ),

/*
 * Navigation Layer: Cursor, Text Navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |WheelU|      |      |                              |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |       | LCTL |WheelD|LSFT | Bksp |                              | Bksp | Left | Down |Right | Del  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | Undo | Cut  | Copy |Paste |      |      |      |  |      |      |      | Home |      | End  |      |        |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        |      |      |      |      |Space |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, KC_WH_U, _______, _______,                                     _______, _______,  KC_UP , _______, _______, _______,
      _______, _______, KC_LCTL, KC_WH_D, KC_LSFT, KC_BSPC,                                     KC_BSPC, KC_LEFT, KC_DOWN,KC_RIGHT, KC_DEL, _______,
      _______, KC_UNDO, KC_CUT , KC_COPY,KC_PASTE, _______, XXXXXXX, _______, _______, XXXXXXX, _______, KC_HOME, _______, KC_END, _______, _______,
                                 _______, _______, _______, _______, KC_SPC , _______, _______, _______, _______, _______
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
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT(
       KC_GRV, KC_EXLM,  KC_AT , KC_HASH, KC_DLR , KC_PERC,                                     KC_CIRC, KC_LCBR, KC_RCBR, _______,ALGR(KC_5),_______,
      KC_TILD, _______, _______, KC_MINS, KC_EQL , KC_AMPR,                                     KC_ASTR, KC_LPRN, KC_RPRN, _______, KC_PIPE, _______,
      _______, _______, _______, KC_UNDS, KC_PLUS, _______, XXXXXXX, _______, _______, XXXXXXX, _______, KC_LBRC, KC_RBRC, _______, KC_BSLS, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Num Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  1 ! |  2 @ |  3 # |  4 $ |  5 % |                              |  /   |  7 & |  8 * |  9 ( |  -   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |                              |  *   |  4 $ |  5 % |  6 ^ |  +   | Space  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |  0 ) |  1 ! |  2 @ |  3 # |  =   | Enter  |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |  ,   |  .   |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                     KC_PSLS,  KC_7  ,  KC_8  ,  KC_9  , KC_PMNS, _______,
      _______,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,                                     KC_PAST,  KC_4  ,  KC_5  ,  KC_6  , KC_PLUS, KC_SPC ,
      _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, XXXXXXX,  KC_0  ,  KC_1  ,  KC_2  ,  KC_3  , KC_PEQL, KC_ENT ,
                                 _______, _______, _______, _______, _______, _______, _______, _______, KC_PCMM,  KC_DOT
    ),

/*
 * Adjust Layer: Media
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              | SAI  |      | Vol+ |      | Play |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              | HUI  | Prev | Vol- |  Nxt |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      | VAI  | Mute |      |      |      |        |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                       |Qwerty|Colemak|      |      |      |  | RGB  |      | RGB  |      |      |
 *                        | Dflt | Dflt |      |      |      |  |Toggle|      | Mode |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______,  KC_F9 , KC_F10 , KC_F11 , KC_F12 , _______,                                     RGB_SAI, _______, KC_VOLU, _______, KC_MPLY, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     RGB_HUI, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, XXXXXXX, _______, _______, XXXXXXX, RGB_VAI, KC_MUTE, _______, _______, _______, _______,
                                 Qwerty , Colemak, _______, _______, _______, RGB_TOG, _______, RGB_MOD, _______, _______
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
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case Qwerty:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
        case Colemak:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
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

        SEQ_TWO_KEYS(KC_M, KC_S) { // Mac screenshot
              SEND_STRING(SS_LGUI(SS_LSFT("4")));
        }
        SEQ_TWO_KEYS(KC_W, KC_S) { // Win screenshot
              SEND_STRING(SS_LGUI("\nS"));
        }
        SEQ_TWO_KEYS(KC_M, KC_V) { // Mac video
            SEND_STRING(SS_LGUI(SS_LSFT("5")));
        }
        SEQ_TWO_KEYS(KC_M, KC_P) { // Mac Sleep
            SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_PWR()))));
        }
        SEQ_TWO_KEYS(KC_W, KC_P) { // Win hibernate
            SEND_STRING(SS_LGUI("x") "u" "h");
        }
    }
}
