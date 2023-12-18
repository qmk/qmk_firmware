/* Copyright 2021 3araht
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

#define DF_COLE  DF(_COLEMAK)

#define _________________QWERTY_L1_________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________COLEMAK_L1________________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________NUMBER_L__________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
// #define _________________NUMBER_R__________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________FUNC__L___________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
// #define _________________FUNC__R___________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

// Defines names for use in layer keycodes and the keymap
enum layer_names {
#ifndef PEDAL_NORMALLY_CLOSED
    _OPEN,
#endif
    _CLOSE,
#ifdef PEDAL_NORMALLY_CLOSED
    _OPEN,
#endif
     _QWERTY,
     _COLEMAK,
     _MISC,
     _FN
};

enum custom_keycodes {
    VERSION = SAFE_RANGE
};

// Alias layout macros that expand groups of keys.
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_OPEN] = LAYOUT(
                  MI_Gs1, MI_As1, MI_Cs2, MI_F2, MI_Gs3,
       MI_E1, MI_A1, MI_G2, MI_Ds2, MI_F3, MI_As2, MI_F1,
         MI_D2, MI_A2, MI_C3, MI_E3, MI_C2, MI_G1, TG_SWAP,
       MI_E2, MI_Gs2, MI_B2, MI_D3, MI_Fs3, MI_Cs3, MI_Fs1,
     MI_D1, MI_B1, MI_G3, MI_A3, MI_Ds3, MI_Fs2, MI_Ds1, MI_C1,

     MO_SWAP,    MI_B5, MI_Gs5, MI_G5, MI_F5,     FN_MUTE,
         MI_Cs3, MI_A5, MI_Fs5, MI_E5, MI_Ds5,
        MI_C3, MI_D3, MI_G3, MI_As4, MI_C5, MI_D5,
     TG_SWAP, MI_B2, MI_E3, MI_Cs4, MI_Fs3, MI_A3, MI_C4, MI_E4,
       MI_A2, MI_F3, MI_As3, MI_Gs3, MI_B3, MI_D4, MI_Gs4, MI_B4,
     MI_Gs2, MI_As2, MI_Ds3, MI_F4, MI_Ds4, MI_Fs4, MI_A4, MI_Cs5, MI_G4
    ),

    [_CLOSE] = LAYOUT(
                  MI_Gs1, MI_As1, MI_Ds2, MI_Ds3, MI_G3,
       MI_D1, MI_D2, MI_As2, MI_C3, MI_Cs2, MI_C2, MI_Fs1,
         MI_G1, MI_G2, MI_B2, MI_D3, MI_F3, MI_Fs2, TG_SWAP,
       MI_A1, MI_E2, MI_A2, MI_Cs3, MI_E3, MI_Gs2, MI_B1,
     MI_E1, MI_E2, MI_Fs3, MI_Gs3, MI_B3, MI_F2, MI_Cs1, MI_F1,

     MO_SWAP,    MI_A5, MI_Gs5, MI_Fs5, MI_F5,     FN_MUTE,
         MI_C3, MI_G5, MI_As4, MI_C5, MI_Ds5,
        MI_D3, MI_Cs3, MI_Gs3, MI_As3, MI_C4, MI_D5,
     TG_SWAP, MI_B2, MI_Fs3, MI_Fs4, MI_G3, MI_B3, MI_D4, MI_G4,
       MI_A2, MI_F3, MI_E3, MI_A3, MI_Cs4, MI_E4, MI_A4, MI_Cs5,
     MI_Gs2, MI_As2, MI_Ds3, MI_F4, MI_E4, MI_Gs4, MI_B4, MI_E5, MI_Ds4
    ),

    [_QWERTY] = LAYOUT_wrapper(
                   _________________NUMBER_L__________________,
       QK_GESC, KC_TAB, _________________QWERTY_L1_________________,
          KC_CAPS, _________________QWERTY_L2_________________, KC_H,
       KC_LSFT, _________________QWERTY_L3_________________, KC_N,
     KC_LCTL, KC_GRV, KC_LGUI, KC_LALT, MIS_EIS, KC_SPC, KC_SPC, KC_PSCR,

     MO(_MISC),        KC_LBRC, KC_RBRC, KC_BSLS, KC_0,         _______,
                  KC_6, KC_7, KC_8, KC_9, KC_BSPC,
                _________________QWERTY_R1_________________, KC_DEL,
     KC_PGUP, KC_G, _________________QWERTY_R2_________________, KC_ENT,
            KC_PGDN, KC_B, _________________QWERTY_R3_________________, KC_RSFT,
         KC_HOME, KC_END, KC_SPC, MIS_KAN, KC_RALT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
    ),

    [_COLEMAK] = LAYOUT_wrapper(
                   _________________NUMBER_L__________________,
       QK_GESC, KC_TAB, _________________COLEMAK_L1________________,
          KC_LCTL, _________________COLEMAK_L2________________, KC_ENT,
       KC_LSFT, _________________COLEMAK_L3________________, KC_M,
     KC_CAPS, KC_GRV, KC_LGUI, KC_LALT, MIS_EIS, KC_SPC, KC_SPC, KC_PSCR,

     MO(_MISC),        KC_LBRC, KC_RBRC, KC_BSLS, KC_0,         _______,
                  KC_6, KC_7, KC_8, KC_9, KC_BSPC,
                _________________COLEMAK_R1________________, KC_DEL,
     KC_PGUP, KC_D, _________________COLEMAK_R2________________, KC_ENT,
            KC_PGDN, KC_B, _________________COLEMAK_R3________________, KC_RSFT,
         KC_HOME, KC_END, KC_SPC, MIS_KAN, KC_RALT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
    ),

    [_MISC] = LAYOUT_wrapper(
                    _________________FUNC__L___________________,
       _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______,

     _______,        _______, _______, _______, KC_F10,         _______,
                  KC_F6, KC_F7, KC_F8, KC_F9, _______,
                _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, KC_QUOT, _______,
            _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT(
                   DF_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, DF_QWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          DF_COLE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     XXXXXXX, XXXXXXX, AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

     _______,        MI_OCTD, MI_OCTU, MI_VELD, MI_VELU,         _______,
                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, VERSION,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI, RGB_SPD, RGB_SPI, RGB_VAD, RGB_VAI,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD, RGB_MOD, EE_CLR, RGB_TOG
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_OPEN]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_CLOSE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_QWERTY]   = { ENCODER_CCW_CW(_______, _______) },
    [_COLEMAK]  = { ENCODER_CCW_CW(_______, _______) },
    [_MISC]     = { ENCODER_CCW_CW(_______, _______) },
    [_FN]       = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
};
#endif

void my_init(void){
    //  Set octave to 0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;

    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    midi_init();
    my_init();
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    rgb_matrix_set_speed(RGB_MATRIX_DEFAULT_SPD);
    rgb_matrix_sethsv(HSV_BLUE);

    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
    // rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
#endif
}

void keyboard_post_init_user(void) {
    my_init();

    //  party mode (for LED soldering test. Enable rainbow color effect, and disable led_indicator to check all LEDs)
    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            break;
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.
        uint8_t layer = get_highest_layer(layer_state);
        switch (layer) {
            case _CLOSE:
                // rgb_matrix_set_color(pgm_read_byte(&convert_led_location2number[11]),  RGB_RED);         //  RGB_TOG  <- too heavy.

                // Close state indicator
                rgb_matrix_set_color( 0, RGB_DARKWHITE);     //  oc
                break;

            case _FN:
                // left hand side
                rgb_matrix_set_color( 46, RGB_DARKORANGE);     //  DF_OPEN
                rgb_matrix_set_color( 48, RGB_DARKWHITE);      //  DF_QWER
                rgb_matrix_set_color( 60, RGB_DARKWHITE);      //  DF_COLE

                rgb_matrix_set_color( 73, RGB_DARKYELLOW);     //  AG_SWAP
                rgb_matrix_set_color( 72, RGB_DARKYELLOW);     //  AG_NORM


                // right hand side
                rgb_matrix_set_color( 1, RGB_DARKYELLOW);      //  MI_OCTD
                rgb_matrix_set_color(13, RGB_DARKGREEN);       //  MI_OCTU
                rgb_matrix_set_color(14, RGB_DARKYELLOW);      //  MI_VELD
                rgb_matrix_set_color(25, RGB_DARKGREEN);       //  MI_VELU

                rgb_matrix_set_color( 6, RGB_DARKBLUE);        //  RGB_SAD
                rgb_matrix_set_color( 9, RGB_DARKBLUE);        //  RGB_SAI
                rgb_matrix_set_color(18, RGB_DARKBLUE);        //  RGB_HUD
                rgb_matrix_set_color(21, RGB_DARKBLUE);        //  RGB_HUI
                rgb_matrix_set_color(29, RGB_DARKBLUE);        //  RGB_SPD
                rgb_matrix_set_color(32, RGB_DARKBLUE);        //  RGB_SPI
                rgb_matrix_set_color(36, RGB_DARKBLUE);        //  RGB_VAD
                rgb_matrix_set_color(39, RGB_DARKBLUE);        //  RGB_VAI

                rgb_matrix_set_color(31, RGB_DARKBLUE);        //  RGB_RMOD
                rgb_matrix_set_color(37, RGB_DARKBLUE);        //  RGB_MOD
                rgb_matrix_set_color(38, RGB_DARKPINK);        //  EE_CLR
                rgb_matrix_set_color(40, RGB_DARKRED);         //  RGB_TOG

                rgb_matrix_set_color(41, RGB_DARKORANGE);      //  _FN
                break;
        }
    }
    return false;
}
#endif
