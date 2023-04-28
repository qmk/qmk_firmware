/*
Copyright 2022 <hello@keebfront.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "analog.h"
#include "string.h"

enum layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3
};

enum custom_keycodes {
    A_CW = QK_KB_0,
    A_CCW
};

// Set up EEPROM. Mostly boilerplate from QMK docs
typedef union {
    uint32_t raw;
    struct {
        uint8_t slider_func_state : 8; // Hold only the slider function state. Will be a low value integer, so 8 bits will be used to store.
    };
} user_config_t;
user_config_t user_config; 

uint8_t slider_func = 0;

// On keyboard initialization, pull the EEPROM values
void keyboard_post_init_user(void) {
    // Call the keymap level matrix init.
    user_config.raw = eeconfig_read_user();
    slider_func = user_config.slider_func_state;
};

// When the EEPROM gets forcefully reset, set the initialization value
void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.slider_func_state = 0;
    eeconfig_update_user(user_config.raw);
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_LAYER1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAYER2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAYER3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAYER0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT(
        QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, 
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_BSPC, KC_PGDN, 
        KC_LSFT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_MUTE, 
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_LAYER1] = LAYOUT(
        QK_GESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_HOME, 
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUSE, QK_BOOT, KC_PGUP,
        KC_TRNS, RGB_SPI, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AUDIO_VOL_UP, KC_AUDIO_MUTE, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, KC_MEDIA_NEXT_TRACK
    ),

    [_LAYER2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_LAYER3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

};

/* Configure custom MIDI Keycodes that will be placed on USER_00 and USER_01 */
extern MidiDevice midi_device;
#define MIDI_CC_OFF 0
#define MIDI_CC_ON 127

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_CW:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 89, 1);
            }
            return true;
        case A_CCW:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 89, 127);
            }
            return true;
        default:
            return true;
    }
}

// ====== Process VIA Custom UI ======
// enum for the Value ID of the slider control
enum via_slider_control {
    id_slider_func = 1
};

// Define the function to set the slider value
void slider_func_set_value ( uint8_t *data ) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_slider_func:
        {
            slider_func = *value_data;
            user_config.slider_func_state = *value_data;
            eeconfig_update_user(user_config.raw); // Going to set it here instead of separately in the VIA save function. No point since this value is not being toggled very often
            break;
        }
    }
}

// Define the function to read the slider value [so that VIA UI knows what to display]
void slider_func_get_value( uint8_t *data ) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_slider_func:
        {
            *value_data = slider_func;
            break;
        }
    }
}

// Boilerplate from VIA Custom UI Documentation. Listen on the custom command channel, 
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                slider_func_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                slider_func_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                //buttglow_config_save(); // Not doing this
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

/* MIDI Slider controls */
uint8_t last_val = 0;
uint8_t rgb_hue = 0;
uint8_t rgb_sat = 0;

void slider(void) {

    uint8_t current_val = analogReadPin(SLIDER_PINA) >>3; // Bit shift 2^10 [1024] to 2^7 [128]

    if ( last_val - current_val < -1 || last_val - current_val > 1 ) { 

        // Underglow RGB Brightness
        if ( slider_func == 0 ) {
            uint8_t rounded_val = 0;
            uint8_t round_coefficient = 3; // Set round-to-zero value target
            rgb_hue = rgblight_get_hue(); // Pull current hue and saturation values since we're just adjusting brightness
            rgb_sat = rgblight_get_sat();

            // Since the lower end range of the slider can be a little bit noisy, it's going to make the zero-value a little hard to hit when it bounces around between 0-1-2. Better off to round any super low values to zero so the lights will affirmatively turn off at lower values.
            if ( current_val < round_coefficient ) {
                rounded_val = 0;
            } else {
                rounded_val = current_val;
            }

            rgblight_sethsv(rgb_hue, rgb_sat, rounded_val * 2); // At 8 bits, it's going to be 0-128, so double to get full range.
        }

        // MIDI CC 90
        else if ( slider_func == 1 ) {
            midi_send_cc(&midi_device, 0, 90, current_val );
        }

        // Layer shift between layers 1 - 4 
        else if ( slider_func == 2 ) {
            layer_move(current_val >>5); // Bit shift 2^7 to 2^2
        }

        else {
            return;
        }

        last_val = current_val;
    }
}
 
void matrix_scan_user(void) {
    slider();
}