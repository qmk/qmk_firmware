/* Copyright 2023 str studio
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

#include "oled.c"
// #include "encoder.c"
extern MidiDevice midi_device;
#define MIDI_CC_OFF 0
#define MIDI_CC_ON  127

enum custom_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _NUMBER,
    _FN,
    _MIDI
};

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,
    MIDI_CC80,
    CYCLE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * NUMBER
 * ,---------------------------.
 * |      |      |      | Mute |
 * |------+------+------+------|
 * |   7  |   8  |   9  |   -  |
 * |------+------+------+------|
 * |   4  |   5  |   6  |   +  |
 * |------+------+------+------|
 * |   1  |   2  |   3  |  En  |
 * |--------------------|  te  |
 * | LOWR |   0  |  .   |  r   |
 * `---------------------------'
 */

[_NUMBER] = LAYOUT(
                                        KC_MUTE,
   KC_KP_7,     KC_KP_8,    KC_KP_9,    KC_KP_MINUS,
   KC_KP_4,     KC_KP_5,    KC_KP_6,    KC_KP_PLUS,
   KC_KP_1,     KC_KP_2,    KC_KP_3,    KC_KP_ENTER,
   MO(_FN),     KC_KP_0,    KC_KP_DOT
),

/* FUNCTION
 * ,---------------------------.
 * |      |      |      | Mute |
 * |------+------+------+------|
 * | Nlck |  Up  | Bksp |   /  |
 * |------+------+------+------|
 * | Left | Down | Rght |   *  |
 * |------+------+------+------|
 * |      | Home | PgUp |  En  |
 * |--------------------|  te  |
 * |  Fn  | End  | PgDn |  r   |
 * `---------------------------'
 */
 
[_FN] = LAYOUT(
                                            TO(_MIDI),
   KC_NUM_LOCK, KC_UP,      KC_BACKSPACE,   KC_KP_SLASH,
   KC_LEFT,     KC_DOWN,    KC_RGHT,        KC_KP_ASTERISK,
   QK_BOOT,       KC_HOME,    KC_PAGE_UP,     KC_KP_ENTER,
   MO(_FN),     KC_END,     KC_PAGE_DOWN
),

[_MIDI] = LAYOUT(
                                            QK_MIDI_ON,
    QK_MIDI_NOTE_A_0,     QK_MIDI_NOTE_A_SHARP_0,    QK_MIDI_NOTE_B_0,    QK_MIDI_NOTE_C_1,
    QK_MIDI_NOTE_F_0,     QK_MIDI_NOTE_F_SHARP_0,    QK_MIDI_NOTE_G_0,    QK_MIDI_NOTE_G_SHARP_0,
    QK_MIDI_NOTE_D_0,     QK_MIDI_NOTE_D_SHARP_0,    QK_MIDI_NOTE_E_0,    MIDI_CC80,
    TO(_NUMBER),     QK_MIDI_NOTE_C_0,    QK_MIDI_NOTE_C_SHARP_0
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MIDI_CC80:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 80, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 80, MIDI_CC_OFF);
            }
            return true;
    }
    return true;
};

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _FN);
// }

// ================== Encoder ==================
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_NUMBER] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_FN]     =   { ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  },
    [_MIDI]   =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    //                  Encoder 1              
};  
#endif