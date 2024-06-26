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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _QWERTY,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    L_BASE = SAFE_RANGE,
    VERSION
};

// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)
#define QWERTY  DF(_QWERTY)

// Used to set octave to QK_MIDI_OCTAVE_0
extern midi_config_t midi_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
            MI_SUST,          MI_C2, MI_D2, MI_E2,  MI_Fs2, MI_Ab2, MI_Bb2, MI_C3, MI_D3, MI_E3, MI_Fs3, MI_Ab3, MI_Bb3, MI_C4,  MI_D4,  MI_E4, MI_Fs4, MI_Ab4, MI_Bb4, MI_C5,
                                MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2, MI_Db3, MI_Eb3, MI_F3,  MI_G3, MI_A3,  MI_B3, MI_Db4, MI_Eb4, MI_F4,  MI_G4,  MI_A4,  MI_B4,
            FN_MUTE,         MI_C2, MI_D2, MI_E2,  MI_Fs2, MI_Ab2, MI_Bb2, MI_C3, MI_D3, MI_E3, MI_Fs3, MI_Ab3, MI_Bb3, MI_C4,  MI_D4,  MI_E4, MI_Fs4, MI_Ab4, MI_Bb4, MI_C5,
            MI_BNDU,           MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2, MI_Db3, MI_Eb3, MI_F3,  MI_G3, MI_A3,  MI_B3, MI_Db4, MI_Eb4, MI_F4,  MI_G4,  MI_A4,  MI_B4,
        MI_TRSD, MI_TRSU,  MI_C2, MI_D2, MI_E2,  MI_Fs2, MI_Ab2, MI_Bb2, MI_C3, MI_D3, MI_E3, MI_Fs3, MI_Ab3, MI_Bb3, MI_C4,  MI_D4,  MI_E4, MI_Fs4, MI_Ab4, MI_Bb4, MI_C5,
            MI_BNDD,           MI_Db2, MI_Eb2, MI_F2,  MI_G2,  MI_A2,  MI_B2, MI_Db3, MI_Eb3, MI_F3,  MI_G3, MI_A3,  MI_B3, MI_Db4, MI_Eb4, MI_F4,  MI_G4,  MI_A4,  MI_B4
    ),

    [_QWERTY] = LAYOUT(
            _______,          QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,
                                KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,   KC_7,   KC_8,   KC_9,      KC_0,    KC_MINS, KC_EQL,   KC_BSLS, KC_BSPC, KC_PSCR, KC_SCRL, KC_PAUS, KC_INS,
            _______,          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_PSLS, KC_BSPC, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
            KC_UP,              KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,   KC_H,   KC_J,   KC_K,      KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,  KC_ENT,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_LEFT,   KC_RGHT,   KC_CAPS, KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_RSFT, KC_RSFT, KC_P4,   KC_P5,   KC_P6,   KC_PENT,
            KC_DOWN,            KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, KC_LNG2, KC_SPC, KC_SPC, KC_SPC, KC_LNG1,  KC_APP,  KC_RALT, KC_RGUI,  KC_RCTL, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PENT
    ),

    [_FN] =  LAYOUT(
            XXXXXXX,          QWERTY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            MI_VELU,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        MI_OCTD, MI_OCTU,     L_BASE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            MI_VELD,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR, XXXXXXX, XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_QWERTY]   = { ENCODER_CCW_CW(_______, _______) },
    [_FN]       = { ENCODER_CCW_CW(_______, _______) }
};
#endif


// commom codes called from eeconfig_init_user() and keyboard_post_init_user().
void my_init(void){
    //  Set octave to QK_MIDI_OCTAVE_0
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
        case L_BASE:
            reset_scale_indicator();
            default_layer_set(1UL << _BASE);
            break;
        }
    return true;
}
