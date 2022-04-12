/*
Copyright 2021 v3ritas <v3ritas@tempoturtle.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

extern MidiDevice midi_device;

enum layers {
    _NATURAL,
    _SHARP,
    _FLAT,
};

/*
MIDI CC codes for generic ON/OFF swiches
80,81,82,83
values off = 0-63
*/

#define OFF 0

/*values on = 64-127*/

#define ON 127

/*implementation inspo taken from here: https://github.com/luantty2/pheromone_keyboard/blob/master/keyboards/pheromone/keymaps/default/keymap.c */

enum custom_keycodes { MIDI_CC80 = SAFE_RANGE, MIDI_CC81, MIDI_CC82, MIDI_CC83 };

static bool toggled_MIDI_CC80 = 0, toggled_MIDI_CC81 = 0, toggled_MIDI_CC82 = 0, toggled_MIDI_CC83 = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MIDI_CC80:
            if (!IS_LAYER_ON(_NATURAL)) {
                toggled_MIDI_CC80 = false;
                if (record->event.pressed) {
                    midi_send_cc(&midi_device, midi_config.channel, 80, ON);
                } else {
                    midi_send_cc(&midi_device, midi_config.channel, 80, OFF);
                }
                return true;
            } else {
                if (record->event.pressed) {
                    if (!toggled_MIDI_CC80) {
                        midi_send_cc(&midi_device, midi_config.channel, 80, ON);
                    } else {
                        midi_send_cc(&midi_device, midi_config.channel, 80, OFF);
                    }
                    toggled_MIDI_CC80 = !toggled_MIDI_CC80;
                }
                return false;
            }
        case MIDI_CC81:
            if (!IS_LAYER_ON(_NATURAL)) {
                toggled_MIDI_CC81 = false;
                if (record->event.pressed) {
                    midi_send_cc(&midi_device, midi_config.channel, 81, ON);
                } else {
                    midi_send_cc(&midi_device, midi_config.channel, 81, OFF);
                }
                return true;
            } else {
                if (record->event.pressed) {
                    if (!toggled_MIDI_CC81) {
                        midi_send_cc(&midi_device, midi_config.channel, 81, ON);
                    } else {
                        midi_send_cc(&midi_device, midi_config.channel, 81, OFF);
                    }
                    toggled_MIDI_CC81 = !toggled_MIDI_CC81;
                }
                return false;
            }
        case MIDI_CC82:
            if (!IS_LAYER_ON(_NATURAL)) {
                toggled_MIDI_CC82 = false;
                if (record->event.pressed) {
                    midi_send_cc(&midi_device, midi_config.channel, 82, ON);
                } else {
                    midi_send_cc(&midi_device, midi_config.channel, 82, OFF);
                }
                return true;
            } else {
                if (record->event.pressed) {
                    if (!toggled_MIDI_CC82) {
                        midi_send_cc(&midi_device, midi_config.channel, 82, ON);
                    } else {
                        midi_send_cc(&midi_device, midi_config.channel, 82, OFF);
                    }
                    toggled_MIDI_CC82 = !toggled_MIDI_CC82;
                }
                return false;
            }
        case MIDI_CC83:
            if (!IS_LAYER_ON(_NATURAL)) {
                toggled_MIDI_CC83 = false;
                if (record->event.pressed) {
                    midi_send_cc(&midi_device, midi_config.channel, 83, ON);
                } else {
                    midi_send_cc(&midi_device, midi_config.channel, 83, OFF);
                }
                return true;
            } else {
                if (record->event.pressed) {
                    if (!toggled_MIDI_CC83) {
                        midi_send_cc(&midi_device, midi_config.channel, 83, ON);
                    } else {
                        midi_send_cc(&midi_device, midi_config.channel, 83, OFF);
                    }
                    toggled_MIDI_CC83 = !toggled_MIDI_CC83;
                }
                return false;
            }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NATURAL] = LAYOUT(
        MI_C, MI_BENDD,   MI_BENDU,  MI_G,
        MI_D, MIDI_CC80,  MIDI_CC81, MI_A,
        MI_E, MIDI_CC82,  MIDI_CC83, MI_B,
        MI_F, MI_OCTD,    MI_OCTU,   MI_C,
              MO(_SHARP), MO(_FLAT)),
    [_SHARP] = LAYOUT(
        MI_Cs, KC_TRNS,  KC_TRNS,  MI_Gs,
        MI_Ds, KC_TRNS,  KC_TRNS,  MI_As,
        MI_F , KC_TRNS,  KC_TRNS,  MI_C ,
        MI_Fs, MI_TRNSD, MI_TRNSU, MI_Cs,
               KC_TRNS,  KC_TRNS),
    [_FLAT] = LAYOUT(
        MI_B , KC_TRNS,  KC_TRNS,  MI_Gb,
        MI_Db, KC_TRNS,  KC_TRNS,  MI_Ab,
        MI_Eb, KC_TRNS,  KC_TRNS,  MI_Bb,
        MI_E , MI_TRNSD, MI_TRNSU, MI_B,
               KC_TRNS,  KC_TRNS),
};
