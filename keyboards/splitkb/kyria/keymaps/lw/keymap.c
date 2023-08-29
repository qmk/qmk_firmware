/* Copyright 2022 Lucas Waelti (@LucasWaelti)
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

#include <keymap_us_international.h>
// US_ACUT KC_QUOT // ´ (dead)
// US_DGRV KC_GRV  // ` (dead)
// US_DCIR S(US_6)    // ^ (dead)
// US_DIAE S(US_ACUT) // ¨ (dead)

enum layers {
    _QWERTZ = 0,    // base text layer
    _SYM,           // symbol layer 
    _NAV,           // navigation layer + accents 
};

enum unicode_names {
    APOST,
    QUOTE,
    CIRCUM,
    GRAVE,
    ACUTE,
    UMLAUT,
    CEDIL_MAJ,
    CEDIL,
    SECTION,
    DEGREE,
};

const uint32_t unicode_map[] PROGMEM = {
    [APOST]         = 0x0027, // '
    [QUOTE]         = 0x0022, // "
    [ACUTE]         = 0x00B4, // ´
    [GRAVE]         = 0x0060, // `
    [CIRCUM]        = 0x005E, // ^ 
    [UMLAUT]        = 0x00A8, // ¨
    [CEDIL_MAJ]     = 0x00C7, // Ç
    [CEDIL]         = 0x00E7, // ç
    [SECTION]       = 0x00A7, // §
    [DEGREE]        = 0x00B0, // °
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
/*
 * 0. Base Layer: QWERTZ
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Esc   |   Q  |   W  |   E  |   R  |   T  |                              |   Z  |   U  |   I  |   O  |   P  |  Del   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Tab   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ' "  | BkSpace|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Y  |   X  |   C  |   V  |   B  | \ |  |  ` ~ |  |  (   |   )  |   N  |   M  | ,  < | . >  | ;  : | CpLock |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |LCtrl | LGUI | LAlt | Space| MO(1)|  | MO(2)| Enter| - _  |  !   | / ?  |
 *                        |      |      |      |      |      |  |      |/shift|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTZ] = LAYOUT(
  KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,  KC_DEL,
  KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L, UP(APOST,QUOTE), KC_BSPC, //  UP(APOST,QUOTE) or KC_QUOT
 KC_LSFT,    KC_Y,    KC_X,    KC_C,    KC_V,    KC_B, KC_BSLS, KC_GRV,  KC_LPRN,    KC_RPRN, KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SCLN, KC_CAPS,
                            KC_LCTL, KC_LGUI, KC_LALT,  KC_SPC,   MO(1),   MO(2),    SC_SENT, KC_MINS, KC_EXLM, KC_SLSH
    ),

// /*
//  * 1. Sym Layer: Numbers and symbols (DEPRECATED)
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |   F1   | F2   | F3   | F4   | F5   | F6   |                              |  F7  | F8   | F9   | F10  | F11  |  F12   |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |    .   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |  LAlt  |   ?  |  !   |  @   |  #   |  <   |  [   |  {   |  |  }   |  ]   |   >  |  ^   |  /   |  *   |  -   |   +    |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |  $   |  %   |  &   |      | MO(1)|  | MO(2)| RAlt |   ~  |   _  |  |   |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_SYM] = LAYOUT(
//    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                       KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
//   KC_DOT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PEQL,
//  KC_LALT, KC_QUES, KC_EXLM,   KC_AT, KC_HASH,   KC_LT, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC,   KC_GT, KC_CIRC, KC_PSLS, KC_ASTR, KC_PMNS, KC_PLUS,
//                              KC_DLR, KC_PERC, KC_AMPR, _______,   MO(1),   MO(2), KC_RALT, KC_TILD, KC_UNDS, KC_PIPE
//     ),

/*
 * 1. Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   F1   |  F2  |  F3  |  F4  | LAlt | PASTE|                              |   ,  |  7   |  8   |  9   |  *   |  /     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   F5   |  F6  |  F7  |  F8  |  @   | COPY |                              |   .  |  6   |  7   |  8   |  =   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   F9   |  F10 |  F11 |  F12 |  &   |  CUT | UNDO | FIND |  |   [  |  ]   |   0  |  1   |  2   |  3   |  +   |   -    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  $   |  #   |  %   |      | MO(1)|  | MO(2)|      |  \ | |  {   |   }  |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_LALT,LCTL(KC_V),                                         KC_COMM,     KC_7,    KC_8,    KC_9,  KC_ASTR, KC_PSLS,
  KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_AT,  LCTL(KC_C),                                          KC_DOT,     KC_4,    KC_5,    KC_6,  KC_PEQL, _______,
  KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_AMPR,LCTL(KC_X),LCTL(KC_Z), LCTL(KC_F), KC_LBRC, KC_RBRC,   KC_0,     KC_1,    KC_2,    KC_3,  KC_PLUS, KC_PMNS,
                            KC_DLR, KC_HASH,   KC_PERC, _______,   MO(1),        MO(2), _______, KC_BSLS, KC_LCBR, KC_RCBR
    ),

/*
 * 2. Nav Layer: Media, navigation, accents
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | Brt+ | Next | Fwd  | Play | Vol+ |                              | Home | PgUp |  Up  | PgDn |      | Del    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Brt- | Prev | Bckw | Stop | Vol- |                              |  End | Left | Down | Right|ScrLck| BkSpace|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |  ´   |  `   |  ^   |  ¨   | Mute |      |UC_Nxt|  |RShift| Menu | PrtSc| ç/Ç  | § °  |      | SAVE | Insert |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |LCtrl | LGUI | LAlt |      | MO(1)|  | MO(2)| UNDO |  CUT | COPY | PASTE|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
 _______, KC_BRIU, KC_MNXT, KC_MFFD, KC_MPLY, KC_VOLU,                                     KC_HOME, KC_PGUP,   KC_UP, KC_PGDN, _______,  KC_DEL,
 _______, KC_BRID, KC_MPRV, KC_MRWD, KC_MSTP, KC_VOLD,                                      KC_END, KC_LEFT, KC_DOWN, KC_RGHT, KC_SCRL, KC_BSPC,
 KC_LSFT, US_ACUT, US_DGRV, US_DCIR, US_DIAE, KC_MUTE, _______, UC_NEXT, KC_RSFT,  KC_APP, KC_PSCR, UP(CEDIL,CEDIL_MAJ), UP(SECTION,DEGREE), _______, LCTL(KC_S),  KC_INS,
                            KC_LCTL, KC_LGUI, KC_LALT, _______,   MO(1),   MO(2), LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V)
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

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

/* DELETE THIS LINE TO UNCOMMENT (1/2)
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTZ:
                oled_write_P(PSTR("QWERTZ\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
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
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

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
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
// DELETE THIS LINE TO UNCOMMENT (2/2) */
