/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "rgb_key_stuff.h"

extern rgb_config_t rgb_matrix_config;

// Save configuration of base layer rgb matrix state
void rgb_matrix_saveBase(void) {
    // Get HSV, speed, mode and activation state
    userspace_config.rgb_mat_hue =      rgb_matrix_config.hsv.h;
    userspace_config.rgb_mat_sat =      rgb_matrix_config.hsv.s;
    userspace_config.rgb_mat_val =      rgb_matrix_config.hsv.v;
    userspace_config.rgb_mat_speed =    rgb_matrix_config.speed;
    userspace_config.rgb_mat_mode =     rgb_matrix_get_mode();
    userspace_config.rgb_mat_toggle =   rgb_matrix_config.enable;
    // Turn off effects so custom ones can be replaced
    rgb_matrix_disable();
    // If saving, that means base layer is being left
    userspace_config.rgb_mat_state =   false;
}

// Load the base state back
void rgb_matrix_loadBase(void) {
    // If loading, this means coming to base layer
    userspace_config.rgb_mat_state = true;
    // Load speed
    rgb_matrix_config.speed = userspace_config.rgb_mat_speed;
    // Load HSV colors
    rgb_matrix_sethsv( userspace_config.rgb_mat_hue,
            userspace_config.rgb_mat_sat,
            userspace_config.rgb_mat_val );
    // Load mode
    rgb_matrix_mode( userspace_config.rgb_mat_mode );
    // Enable or disable
    if( userspace_config.rgb_mat_toggle ) {
        rgb_matrix_enable();
    } else {
        rgb_matrix_disable();
    }
}

// These are keyboard, and matrix, specific so they need to be defined there
__attribute__ ((weak)) void rgb_matrix_game(void) { }
__attribute__ ((weak)) void rgb_matrix_number(void) { }
__attribute__ ((weak)) void rgb_matrix_settings(void) { }
__attribute__ ((weak)) void rgb_matrix_mouse(void) { }
__attribute__ ((weak)) void rgb_matrix_music(void) { }

// RGB matrix initialize base layer
void matrix_init_rgb_matrix() {
    // Load HSV colors
    rgb_matrix_sethsv_noeeprom(75,192,100);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_UP_DOWN);
    rgb_matrix_enable();
    rgb_matrix_saveBase();
    rgb_matrix_loadBase();
}

// This code loads or saves base state on layer changes
uint32_t layer_state_set_rgb_matrix(uint32_t state) {
    // If base is loaded, save it
    if ( userspace_config.rgb_mat_state ) {
        rgb_matrix_saveBase();
    }
    // If coming to base, load
    if ( biton32(state) == _BA ) {
        rgb_matrix_loadBase();
    }
    return state;
}

// Set RGB state depending on layer, loaded by some higher function
__attribute__ ((weak)) void rgb_matrix_indicators_keymap(void) { }
void rgb_matrix_indicators_user(void) {
    // If base is not loaded
    if( !userspace_config.rgb_mat_state ) {
        switch ( biton32(layer_state) ) {
            case _GA:   // Do game layer
                rgb_matrix_game();
                break;
            case _NU:   // Do number layer
                rgb_matrix_number();
                break;
            case _SE:   // Do setting layer, if not loaded
                rgb_matrix_settings();
                break;
            case _MO:   // Do mouse layer
                rgb_matrix_mouse();
                break;
            case _MU:   // Do music layer
                rgb_matrix_music();
                break;
        }
    }
    rgb_matrix_indicators_keymap();
}

// Make it so that RGB keys first load the base layer
bool process_record_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
        case RGB_MOD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_HUI:
        case RGB_HUD:
            // If base is not loaded already, load base layer
            if ( !userspace_config.rgb_mat_state ) {
                rgb_matrix_loadBase();
            }
            return true;
            break;
    }
    return true;
}
