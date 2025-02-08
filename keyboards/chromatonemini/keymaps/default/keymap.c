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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RESERVE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    L_BASE = SAFE_RANGE,
    L_RESERVE,
    VERSION
};

// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to 0
extern midi_config_t midi_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
            FN_MUTE,          MI_SUST,
            MI_BNDU,
        MI_TRSD,  MI_TRSU,   MI_C2, MI_D2, MI_E2,  MI_Fs2, MI_Ab2, MI_Bb2, MI_C3, MI_D3, MI_E3, MI_Fs3, MI_Ab3, MI_Bb3, MI_C4,  MI_D4,  MI_E4, MI_Fs4, MI_Ab4, MI_Bb4, MI_C5,
            MI_BNDD,            MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2, MI_Db3, MI_Eb3, MI_F3,  MI_G3, MI_A3,  MI_B3, MI_Db4, MI_Eb4, MI_F4,  MI_G4,  MI_A4,  MI_B4
    ),

    /* RESERVE */
    [_RESERVE] = LAYOUT(
            _______,          _______,
            _______,
        _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FN] =  LAYOUT(
            _______,          XXXXXXX,
            MI_VELU,
        MI_OCTD, MI_OCTU,     L_BASE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, VERSION, XXXXXXX, XXXXXXX,
            MI_VELD,               L_RESERVE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR, XXXXXXX, XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_RESERVE] = { ENCODER_CCW_CW(_______, _______)  },
    [_FN]      = { ENCODER_CCW_CW(_______, _______)  },
};
#endif

// commom codes called from eeconfig_init_user() and keyboard_post_init_user().
void my_init(void){
    //  Set octave to 0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
    default_layer_set(1UL << _BASE);
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    midi_init();
    my_init(); // commom codes called from eeconfig_init_user() and keyboard_post_init_user().
}

void keyboard_post_init_user(void) {
    my_init(); // commom codes called from eeconfig_init_user() and keyboard_post_init_user().
};

void reset_scale_indicator(void) {
    //  reset transpose value and scale_indicator_col to default.
    midi_config.transpose = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            break;

        case L_BASE:
            reset_scale_indicator();
            default_layer_set(1UL << _BASE);
            break;

        case L_RESERVE:
            reset_scale_indicator();
            default_layer_set(1UL << _RESERVE);
            break;
    }
    return true;
}
