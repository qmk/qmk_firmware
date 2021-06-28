/* Copyright 2020 Fredrik Salomonsson <plattfot@gmail.com>
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
#include "version.h"

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // can always be here
    // Macros, where | is the cursor
    M_LRBRC,  // [|]
    M_LRCBR,  // {|}
    M_LRPRN,  // (|)
    M_LRABR,  // <|>
    M_DQUOT,  // '|'
    // New keys
    DBL_TAP,  // Repeat next key
};

// Double Tap feature based on post from drashna
// https://www.reddit.com/r/olkb/comments/citkbx/double_key_press_modifier_qmkwould_work_like/ev9cue8/
static bool double_tap_it = false;

enum layers {
    _DEFAULT,
    _LOWER,
    _RAISE,
    _NAV,
    _ADJUST,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Default
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   `    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Tab   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | Lead | RAISE|  | LOWER|DBLTAP|   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | MPlay| GUI  | LCtrl| Space| LALT |  | Enter|BSpace| NAV  |LCTL+ |Worksp|
 *                        |      |      |      |      |      |  |      |      |      |LALT  |toggle|
 *                        `----------------------------------'  `----------------------------------'
 */
    [_DEFAULT] = LAYOUT(
      KC_GRV,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
      KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,    KC_LEAD,  OSL(_RAISE),       OSL(_LOWER), DBL_TAP, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                             KC_MPLY, KC_LGUI, KC_LCTL, KC_SPACE, KC_LALT,               KC_ENT,  KC_BSPC, MO(_NAV), LCTL(KC_LALT), LGUI(KC_B)
    ),

/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   ~    |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  |   |  _   |  \   |  -   |  +   |                              |   =  |  {   |  }   |  [   |  ]   |   ''   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  []  |  {}  |  ()  |  <>  |      |      |      |  |      |      |      |      |  <   |  >   |  ?   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Mute |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      KC_TILDE,KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, KC_PIPE, KC_UNDS, KC_BSLS, KC_MINS, KC_PLUS,                                     KC_EQUAL,KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, M_DQUOT,
      _______, M_LRBRC, M_LRCBR, M_LRPRN, M_LRABR, _______, _______, _______, _______, _______, _______, _______, KC_LT,   KC_GT,   KC_QUES, _______,
                                 KC_MUTE, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Raise Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      | F11  |                              | F12  |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |ScLock|      |  |      | Ins  |      |      |      |      |      |CapsLock|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      | RAlt |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, _______, _______, _______, _______, KC_F11,                                      KC_F12,  _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, KC_SLCK, _______, _______, KC_INS,  _______, _______, _______, _______, _______, KC_CAPS,
                                 _______, _______, _______, _______, _______, _______, _______, _______, KC_RALT, _______

    ),
/*
 * Navigation Layer: Number keys, navigation, modification
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Esc  | Del  |      |      |                              |      | Left | Up   | Down | Right|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      | RCtrl|      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, KC_1, 	KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, KC_ESC,  KC_DEL,  _______, _______,                                     _______, KC_LEFT, KC_UP, KC_DOWN,   KC_RGHT, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, KC_RCTL, _______
    ),
/*
 * Adjust Layer: RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
// clang-format on

/* void keyboard_post_init_user(void) { */
/*   rgblight_setrgb(51, 135, 204); */
/* } */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case M_LRPRN:
                // Double tap gets messed up with macros, turning it off
                double_tap_it = false;
                SEND_STRING("()" SS_TAP(X_LEFT));
                return false;
            case M_LRCBR:
                double_tap_it = false;
                SEND_STRING("{}" SS_TAP(X_LEFT));
                return false;
            case M_LRBRC:
                double_tap_it = false;
                SEND_STRING("[]" SS_TAP(X_LEFT));
                return false;
            case M_LRABR:
                double_tap_it = false;
                SEND_STRING("<>" SS_TAP(X_LEFT));
                return false;
            case M_DQUOT:
                double_tap_it = false;
                SEND_STRING("''" SS_TAP(X_LEFT));
                return false;
            case DBL_TAP:
                double_tap_it = !double_tap_it;
                return false;
            case KC_LEAD:
                double_tap_it = false;
                return true;
        }

    } else if (double_tap_it &&
               keycode != DBL_TAP &&
               keycode != OSL(_RAISE) &&
               keycode != OSL(_LOWER) &&
               keycode != MO(_NAV)) {
        double_tap_it = false;
        tap_code16(keycode);
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

// clang-format off
static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, false);
}
// clang-format on

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n"), false);
    oled_write_P(PSTR("v" QMK_VERSION "\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_write_P(PSTR("plattfot\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("symbols\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("function keys\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("numbers/navi\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("undefined\n"), false);
    }

    // Host Keyboard LED Status and Double tap
    led_t led_state = host_keyboard_led_state();
    if (led_state.num_lock) {
        oled_write_P(PSTR("NUMLCK "), false);
    } else if (double_tap_it) {
        oled_write_P(PSTR("Double "), false);
    } else {
        oled_write_P(PSTR("       "), false);
    }

    if (led_state.caps_lock) {
        oled_write_P(PSTR("CAPLCK "), false);
    } else if (double_tap_it) {
        oled_write_P(PSTR("Tap    "), false);
    } else {
        oled_write_P(PSTR("       "), false);
    }

    oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _LOWER:
                // Skip/Prev song
                if (clockwise) {
                    tap_code(KC_MNXT);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code(KC_MPRV);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
            default:
                // Volume control
                if (clockwise) {
                    tap_code(KC_VOLU);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code(KC_VOLD);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _RAISE:
                // Credit to Thomas Baart for this
                // See https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code16(S(C(KC_TAB)));
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
            default:
                // Scrolling
                if (clockwise) {
                    tap_code(KC_PGDN);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code(KC_PGUP);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
        }
    }
    return true;
}
#endif

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        // Sway navigation
        SEQ_ONE_KEY(KC_Q) {  // Jump to workspace 1
            SEND_STRING(SS_LGUI("1"));
        }
        SEQ_ONE_KEY(KC_W) {  // Jump to workspace 2
            SEND_STRING(SS_LGUI("2"));
        }
        SEQ_ONE_KEY(KC_E) {  // Jump to workspace 3
            SEND_STRING(SS_LGUI("3"));
        }
        SEQ_ONE_KEY(KC_R) {  // Jump to workspace 4
            SEND_STRING(SS_LGUI("4"));
        }
        SEQ_ONE_KEY(KC_T) {  // Jump to workspace 5
            SEND_STRING(SS_LGUI("5"));
        }

        SEQ_ONE_KEY(KC_Y) {  // Jump to workspace 6
            SEND_STRING(SS_LGUI("6"));
        }
        SEQ_ONE_KEY(KC_U) {  // Jump to workspace 7
            SEND_STRING(SS_LGUI("7"));
        }
        SEQ_ONE_KEY(KC_I) {  // Jump to workspace 8
            SEND_STRING(SS_LGUI("8"));
        }
        SEQ_ONE_KEY(KC_O) {  // Jump to workspace 9
            SEND_STRING(SS_LGUI("9"));
        }
        SEQ_ONE_KEY(KC_P) {  // Jump to workspace 0
            SEND_STRING(SS_LGUI("0"));
        }
        SEQ_ONE_KEY(KC_G) {  // View scratch pad
            SEND_STRING(SS_LGUI("-"));
        }

        // Sway move window
        SEQ_TWO_KEYS(KC_M, KC_Q) {  // Move to workspace 1
            SEND_STRING(SS_LSFT(SS_LGUI("1")));
        }
        SEQ_TWO_KEYS(KC_M, KC_W) {  // Move to workspace 2
            SEND_STRING(SS_LSFT(SS_LGUI("2")));
        }
        SEQ_TWO_KEYS(KC_M, KC_E) {  // Move to workspace 3
            SEND_STRING(SS_LSFT(SS_LGUI("3")));
        }
        SEQ_TWO_KEYS(KC_M, KC_R) {  // Move to workspace 4
            SEND_STRING(SS_LSFT(SS_LGUI("4")));
        }
        SEQ_TWO_KEYS(KC_M, KC_T) {  // Move to workspace 5
            SEND_STRING(SS_LSFT(SS_LGUI("5")));
        }

        SEQ_TWO_KEYS(KC_M, KC_Y) {  // Move to workspace 6
            SEND_STRING(SS_LSFT(SS_LGUI("6")));
        }
        SEQ_TWO_KEYS(KC_M, KC_U) {  // Move to workspace 7
            SEND_STRING(SS_LSFT(SS_LGUI("7")));
        }
        SEQ_TWO_KEYS(KC_M, KC_I) {  // Move to workspace 8
            SEND_STRING(SS_LSFT(SS_LGUI("8")));
        }
        SEQ_TWO_KEYS(KC_M, KC_O) {  // Move to workspace 9
            SEND_STRING(SS_LSFT(SS_LGUI("9")));
        }
        SEQ_TWO_KEYS(KC_M, KC_P) {  // Move to workspace 0
            SEND_STRING(SS_LSFT(SS_LGUI("0")));
        }
        SEQ_TWO_KEYS(KC_M, KC_G) {  // Move to scratch pad
            SEND_STRING(SS_LSFT(SS_LGUI("-")));
        }
    }
}
