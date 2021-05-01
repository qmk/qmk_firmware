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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _TRANS,
    _RESERVE,
    _FN
};

//  Don't change the DEFAULT_SCALE_COL value below. It must be 0.
#define DEFAULT_SCALE_COL 0
static uint8_t scale_indicator_col = DEFAULT_SCALE_COL;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    SHIFTDN = SAFE_RANGE,
    SHIFTUP,
    TGLINDI,  //  ToGgLeINDIcator

    L_BASE,
    L_TRANS
};

// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to MI_OCT_0
extern midi_config_t midi_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT( \
            FN_MUTE,                                                                                                                                                                             \
            MI_BENDU,                                                                                                                                                                            \
        SHIFTDN, SHIFTUP,    MI_C_1, MI_D_1, MI_E_1,  MI_Fs_1, MI_Ab_1, MI_Bb_1, MI_C_2, MI_D_2, MI_E_2, MI_Fs_2, MI_Ab_2, MI_Bb_2, MI_C_3,  MI_D_3,  MI_E_3, MI_Fs_3, MI_Ab_3, MI_Bb_3, MI_C_4, \
            MI_BENDD,           MI_Db_1, MI_Eb_1, MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1, MI_Db_2, MI_Eb_2, MI_F_2,  MI_G_2, MI_A_2,  MI_B_2, MI_Db_3, MI_Eb_3, MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3     \

    ),

    /* Trans   This layer must locate 1 layer above _BASE layer. */
    [_TRANS] = LAYOUT( \
            _______,                                                                                                                                                                                     \
            _______,                                                                                                                                                                                     \
        MI_TRNSD, MI_TRNSU,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
            _______,               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______      \
    ),

    /* Shift   This layer must locate 1 layer above _BASE layer. */
    [_RESERVE] = LAYOUT( \
            _______,                                                                                                                                                                                     \
            XXXXXXX,                                                                                                                                                                                     \
        XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   \
            XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX      \
    ),

    [_FN] =  LAYOUT( \
            _______,                                                                                                                                                                                        \
            MI_VELU,                                                                                                                                                                                        \
        MI_OCTD, MI_OCTU,   L_BASE, DF(_RESERVE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  \
            MI_VELD,               L_TRANS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_SPD, RGB_VAD, RGB_RMOD, TGLINDI        \
    )
};

void keyboard_post_init_user(void) {
    //  Set otave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    default_layer_set(1UL << _BASE);
};

void reset_scale_indicator(void) {
    //  reset transpose value and scale_indicator_col to default.
    midi_config.transpose = 0;
    scale_indicator_col = DEFAULT_SCALE_COL;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case L_BASE:
            reset_scale_indicator();
            default_layer_set(1UL << _BASE);
            break;

        case L_TRANS:
            reset_scale_indicator();
            default_layer_set(1UL << _TRANS);
            break;

        //  SHIFTDN and SHIFTUP can be pressed only when layer is _BASE.
        case SHIFTDN:
            if (record->event.pressed) {
                scale_indicator_col = shift_led_indicator_left(scale_indicator_col);
            }
            break;

        case SHIFTUP:
            if (record->event.pressed) {
                scale_indicator_col = shift_led_indicator_right(scale_indicator_col);
            }
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE
void encoder_update_user(int8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
#endif  // ENCODER_ENABLE
