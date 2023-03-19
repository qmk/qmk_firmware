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
#include "keymap_german.h"
#include "os_detection.h"
enum layers {
    _COLEMAK_DHk = 0,
    _NAV,
    _SYM,
    _NUMBERS,
    _COLEMAK_DHk_GERMANIZED,
};


// Aliases for readability
#define COLEMAK                 DF(_COLEMAK_DHk)


#define SYM         MO(_SYM)
#define NAV         MO(_NAV)
#define NUMBERS     MO(_NUMBERS)
#define COLEMAK_GERMANIZED      MO(_COLEMAK_DHk_GERMANIZED)

#define CTL_ESC     MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT    MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS    MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT     MT(MOD_LALT, KC_ENT)



enum custom_keycodes {
    USR_COPY,
    USR_PASTE,
};

tap_dance_action_t tap_dance_actions[] = {
    //[TD_SYM_ESC] = ACTION_TAP_DANCE_TAP_HOLD(KC_ENT, MO(_SYM)),
};
// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |Ctrl/Esc|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Bksp  |   A  |   R  |   S  |   T  |   G  |                              |   K  |   N  |   E  |   I  |   O  |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  | [ {  |CapsLk|  |F-keys|  ] } |   M  |   H  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DHk] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   DE_Y , DE_SCLN, DE_SLSH  ,
     KC_BSPC , KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G ,                                        KC_K,   KC_N ,  KC_E ,   KC_I ,  KC_O ,  DE_QUOT  ,
     KC_LSFT , DE_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V ,USR_COPY, CTL_ESC,     NAV,  USR_PASTE      ,    KC_M,   KC_H ,DE_COMM, DE_DOT ,DE_MINS, KC_RSFT   ,
                                CTL_ESC, KC_LGUI,ALT_ENT, CTL_ESC , NUMBERS,     NAV,  LT(SYM, KC_ENT),KC_SPC,COLEMAK_GERMANIZED, KC_APP

    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_PGDN, _______, KC_VOLD, KC_VOLU, KC_DEL,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_HOME, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_END,
      _______, _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  ?   |  #   |  $   |  %   |                              |      |  @   |  *   |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  [   |  ]   |  (   |  )   |      |                              |   &  |  {   |  }   |  <   |  >   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |  -   |  =   |  "   |      |      |  |      |      |   |  |      |      |  ~   |  +   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______, DE_EXLM, DE_QUES, KC_HASH, DE_DLR , DE_PERC,                                     _______,   DE_AT, DE_ASTR, _______, _______, _______,
      _______, DE_LBRC, DE_RBRC, DE_LPRN, DE_RPRN, _______,                                     DE_AMPR, DE_LCBR, DE_RCBR, DE_LABK, DE_RABK, _______,
      _______, _______, _______, DE_MINS,  DE_EQL, DE_DQUO,  _______, _______, _______, _______, DE_PIPE, _______, _______, DE_TILD, DE_PLUS, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Numbers and fkeys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  | F3   | F4   |  F5  |                              |  F6  |  F7  |   F8 |   F9 |  F10 |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  1   |  2   |  3   |  4   |   5  |                              |   6  |   7  |   8  |    9 |    0 |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUMBERS] = LAYOUT(
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , KC_F5  ,                                     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
      _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),


/*
 * Germanized Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   Ü  |   Y  | ;  : |Ctrl/Esc|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Bksp  |   Ä  |   R  |   ß  |   T  |   G  |                              |   K  |   N  |   €  |   I  |   Ö  |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  | [ {  |CapsLk|  |F-keys|  ] } |   M  |   H  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DHk_GERMANIZED] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, _______, DE_UDIA, _______, _______, _______,
       _______, DE_ADIA, _______, DE_SS  , _______, _______,                                     _______, _______, DE_EURO, _______, DE_ODIA, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("Lars <3 Linn\n\n"), false);
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _COLEMAK_DHk:
                oled_write_P(PSTR("COLEMAK\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _NUMBERS:
                oled_write_P(PSTR("Numbers\n"), false);
                break;
            case _COLEMAK_DHk_GERMANIZED:
                oled_write_P(PSTR("DEUTSCH\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Symbols\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }
    } else {
oled_write_P(PSTR("\nRunning on Host:\n"), false);

switch (detected_host_os()) {
    case OS_UNSURE:
        oled_write_P(PSTR("Not sure\n"), false);
        break;
    case OS_WINDOWS:
        oled_write_P(PSTR("Windows... ew\n"), false);
        break;
    case OS_MACOS:
        oled_write_P(PSTR("MacOS\n"), false);
        break;
    case OS_IOS:
        oled_write_P(PSTR("IOS\n"), false);
        break;
    case OS_LINUX:
        oled_write_P(PSTR("Linux\n"), false);
        break;
}
    }
    return false;
}
#endif


void process_platform_combo(uint16_t keycode, keyrecord_t *record) {
  os_variant_t host_os = detected_host_os();
  uint16_t keycode_to_press = KC_NO;
  if (host_os == OS_MACOS || host_os == OS_IOS) {
    switch (keycode) {
      case USR_COPY:
        keycode_to_press = G(KC_C);
        break;
      case USR_PASTE:
        keycode_to_press = G(KC_V);
        break;
    }
  } else {
    switch (keycode) {
      case USR_COPY:
        keycode_to_press = C(KC_C);
        break;
      case USR_PASTE:
        keycode_to_press = C(KC_V);
        break;
    }
  }
  if (record->event.pressed) {
    register_code16(keycode_to_press);
  } else {
    unregister_code16(keycode_to_press);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf("KL: kc: 0x%04X, pressed: %b, time: %u\n", keycode, record->event.pressed, record->event.time);
#endif
#ifdef REPEAT_KEY
  process_repeat_key(keycode, record);
#endif

    switch (keycode) {
    case USR_COPY:
        process_platform_combo(keycode, record);
        return false;
    case USR_PASTE:
        process_platform_combo(keycode, record);
        return false;
  }
  return true;
}