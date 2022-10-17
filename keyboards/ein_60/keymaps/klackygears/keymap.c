/* Copyright 2020 klackygears
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
#include "klackygears.h"
#include "stdio.h"

//For an explanation of what's going on here with the keymap wrappers, check out drashna's user folder.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WINBASE] = LAYOUT_wrapper(
      KC_ESC,  _______________DVORAK_L1___________________,   KC_MUTE,  _______________DVORAK_R1___________________, KC_BSPC,
      AU_TOG,  _______________DVORAK_L2___________________,             _______________DVORAK_R2___________________, RGB_TOG,
      CK_TOGG, _______________WINDVK_L3___________________,             _______________WINDVK_R3___________________, RGB_MOD,
      KC_1,    KC_2,    KC_3,    ________WIN_THUMB_L______,   KC_SPC,   ________WIN_THUMB_R______,    KC_1,    KC_2, KC_GAMER
    ),
    [_MACBASE] = LAYOUT_wrapper(
      KC_ESC,  _______________DVORAK_L1___________________,   _______,   _______________DVORAK_R1___________________, KC_BSPC,
      RGB_TOG, _______________DVORAK_L2___________________,              _______________DVORAK_R2___________________, RGB_TOG,
      RGB_MOD, _______________MACDVK_L3___________________,              _______________MACDVK_R3___________________, RGB_MOD,
      _______, _______, _______, ________MAC_THUMB_L______,   _______,   ________MAC_THUMB_R______, _______, _______, _______
    ),
    [_QWERTY] = LAYOUT_wrapper(
      KC_ESC,  _________________COLEMAK_L1________________,    KC_ESC,   _________________QWERTY_R1_________________, KC_BSPC,
      KC_CAPS, _________________COLEMAK_L2________________,              _________________QWERTY_R2_________________, KC_ENT,
      KC_LSFT, _________________COLEMAK_L3________________,              _________________QWERTY_R3_________________, KC_RSFT,
      KC_LCTL, KC_LGUI, KC_LALT, _______, MO(_MNMB), MO(_SYMB), KC_SPC, MO(_SYMB), MO(_MNMB), KC_RGUI,_______, MO(_MDIA), MO(_FUNC)
    ),

    //Borderlands
    [_GAMER] = LAYOUT_wrapper(
      KC_ESC,  KC_R,    KC_G,    KC_W,    KC_E,    KC_1,     _______,    _________________RGB_1_____________________, KC_WINBASE,
      KC_TAB,  KC_V,    KC_A,    KC_S,    KC_D,    KC_2,                 _________________RGB_2_____________________, _______,
      KC_C,    KC_I,    KC_F,    KC_Q,    KC_4,    KC_3,                 _________________MEDIA_____________________, _______,
      KC_Z,    KC_X,    KC_K,    KC_LCTL, KC_LSFT, KC_SPC,   KC_SPC,     KC_F12,  KC_P,  KC_LEFT,  KC_UP,   KC_DOWN,  KC_RIGHT
    ),

    [_SYMB] = LAYOUT_wrapper(
      _______, _________________PUNC_L1_ALT_______________,    _______,  _________________PUNC_R1___________________, _______,
      _______, _________________PUNC_L3___________________,              _________________PUNC_R2___________________, _______,
      RGB_MOD, _________________PUNC_L3_ALT_______________,              _________________PUNC_R3___________________, _______,
      _______, _______, KC_NUM, KC_SCRL, KC_DEL,  _______,    _______,  _______, KC_CAPS, _______, _______, _______, _______
    ),

    [_FUNC] = LAYOUT_wrapper(
      _______, _____________FUNC_L1_______________________,    _______,  _______, _____________FUNC_1_______________, _______,
      _______, ________MAC_MISSION_CTRL__________, LGUI(KC_L),           _______, _____________FUNC_2_______________, _______,
      RGB_MOD, _____________FUNC_L3_______________________,              _______, _____________FUNC_3_______________, _______,
      _______, _______, _______, _______, _______, _______,    _______,  _______, KC_CAPS, _______, _______, _______, _______
    ),

    [_MNMB] = LAYOUT_wrapper(
      _______, _________________MACNAV_L1_________________,    _______,  _________________NUMB_R1___________________, _______,
      _______, _________________MACNAV_L2_________________,              _________________NUMB_R2___________________, _______,
      RGB_MOD, _________________MACNAV_L3_________________,              _________________NUMB_R3_MAC_______________, _______,
      _______, _______, _______, _______, _______, _______,    _______,  _______, RSFT_T(KC_ENT), KC_RSFT, _______, _______, _______
    ),


    [_NUMB] = LAYOUT_wrapper(
      _______, _________________WINNAV_L1_________________,    _______,  _________________NUMB_R1___________________, _______,
      _______, _________________WINNAV_L2_________________,              _________________NUMB_R2___________________, _______,
      RGB_MOD, _________________WINNAV_L3_________________,              _________________NUMB_R3_WIN_______________, _______,
      _______, _______, _______, TO(_WINBASE), _______, _______,    _______,  _______, RSFT_T(KC_ENT), KC_RSFT, _______, _______, _______
    ),

    [_MDIA] = LAYOUT_wrapper(
      _______, _________________LYOUT_____________________,    _______,  _________________RGB_1_____________________, RGB_TOG,
      _______, MU_TOG, _______, _______, _______,    CK_UP,              _________________RGB_2_____________________, _______,
      RGB_MOD, MU_MOD,  MU_TOG,  CK_TOGG,  CK_RST, CK_DOWN,              _________________MEDIA_____________________, _______,
      _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, _______, _______
    )

};


#ifdef OLED_ENABLE

    char wpm_str[10];

static void render_ein60_logo(void) {
        static const char PROGMEM ein60_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255, 11,251,139,139,139,139,139,139,139,139,139,139,139, 11, 15,  0,240,240, 16,240,  0,240,240, 16,240,224,192,128,  0,  0,  0,  0,240, 16,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255, 11,251,139,139,139,139,139,139,139,139,139,139,139,143,128,  0,  0,  0,  0,254,255, 11,251, 11, 11, 11, 11,139,203,235,123,187,219,235,251,255,  7,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,  4,253,197,197,197,197,197,197,197,197,197,197,199,192,192,  0,255,255,  0,255,  0,255,255,  0,254, 13, 27, 55,111,222,188,120,255,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,  0,255,197,197,197,197,197,197,197,197,197,197,253,253,255,131,254,  0,  0,255,255,  0,255,184,220,238,247,219,205,198,195,193,192,255,255,255,128,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  0,  3,  3,  2,  3,  0,  3,  3,  2,  3,  0,  0,  0,  0,  0,  1,  3,  2,  2,  3,  0,  8, 28, 20, 20, 20, 20, 20, 28,  8,  0,  1,  3,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  0,  0,  0,  1,  3,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        };
        oled_write_raw_P(ein60_logo, sizeof(ein60_logo));
    }



static void render_status(void) {
//bool oled_task_user(void) {

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _WINBASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("Symbol\n"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case _MNMB:
            oled_write_P(PSTR("Numbpad Mac\n"), false);
            break;
        case _NUMB:
            oled_write_P(PSTR("Numbpad\n"), false);
            break;
        case _MDIA:
            oled_write_P(PSTR("Media\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);


    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_set_cursor(1,2);
    oled_write(wpm_str, false);

}

bool oled_task_user(void) {

    render_status();
    oled_write_ln_P(PSTR(""), false);
    render_ein60_logo();

    return false;
}

#endif


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}
