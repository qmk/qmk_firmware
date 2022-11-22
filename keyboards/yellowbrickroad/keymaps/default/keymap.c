/* Copyright 2022 3araht
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

// Long press: go to _FN , tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to MI_OCT_0
extern midi_config_t midi_config;

// Defines names for use in  keycodes and the keymap
enum _names {
    _BASE,
    _RESERVE01,
    _FN                  //  FN layer
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    VERSION = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        FN_MUTE,
        MI_C_1,  MI_Db_1,  MI_D_1,   MI_Eb_1, MI_E_1, MI_F_1, MI_Fs_1, MI_G_1, MI_Ab_1, MI_A_1, MI_Bb_1, MI_B_1,
        MI_C_2,  MI_Db_2,  MI_D_2,   MI_Eb_2, MI_E_2, MI_F_2, MI_Fs_2, MI_G_2, MI_Ab_2, MI_A_2, MI_Bb_2, MI_B_2,
        MI_C_3,  MI_Db_3,  MI_D_3,   MI_Eb_3, MI_E_3, MI_F_3, MI_Fs_3, MI_G_3, MI_Ab_3, MI_A_3, MI_Bb_3, MI_B_3,
        MI_C_4,  MI_Db_4,  MI_D_4,   MI_Eb_4, MI_E_4, MI_F_4, MI_Fs_4, MI_G_4, MI_Ab_4, MI_A_4, MI_Bb_4, MI_B_4,
        MI_C_5,  MI_Db_5,  MI_D_5,   MI_Eb_5, MI_E_5,
        MI_F_5,
        MI_SUS
    ),

    [_RESERVE01] = LAYOUT(
        _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______,
        _______
    ),

    [_FN] = LAYOUT(
        _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, VERSION, EE_CLR,
        XXXXXXX,
        XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]        = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MI_TRNSD, MI_TRNSU) },
    [_RESERVE01]   = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______,  _______)  },
    [_FN]          = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(MI_OCTD,  MI_OCTU)  }
};
#endif


void my_init(void){
    //  Set octave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    midi_init();
    my_init();

    //  Reset the midi keyboard layout
    set_single_persistent_default_layer(_BASE);
}

void keyboard_post_init_user(void) {
    my_init();
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
