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
    userspace_config.rgb_mat_hue =      rgb_matrix_config.hue;
    userspace_config.rgb_mat_sat =      rgb_matrix_config.sat;
    userspace_config.rgb_mat_val =      rgb_matrix_config.val;
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

__attribute__ ((weak)) void rgb_matrix_game(void) { }
__attribute__ ((weak)) void rgb_matrix_number(void) { }
__attribute__ ((weak)) void rgb_matrix_settings(void) { }
__attribute__ ((weak)) void rgb_matrix_mouse(void) { }
__attribute__ ((weak)) void rgb_matrix_music(void) { }

// Set RGB state depending on layer
void rgb_matrix_indicators_rgb(void) {
    uint8_t this_layer = biton32(layer_state);

    // Save if leaving base loaded state
    if( (this_layer != _BA) && (userspace_config.rgb_mat_state) ) {
        rgb_matrix_saveBase();
    }

    switch ( this_layer ) {
        case _BA:   // Load base layer iff it's not loaded yet
            if( !userspace_config.rgb_mat_state ) {
                rgb_matrix_loadBase();
            }
            break;
        case _GA:   // Do game layer
            rgb_matrix_game();
            break;
        case _NU:   // Do number layer
            rgb_matrix_number();
            break;
        case _SE:   // Do setting layer
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

// Make it so that RGB keys first load the base layer
bool process_record_rgb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
        case RGB_MOD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_HUI:
        case RGB_HUD:
            if ( !userspace_config.rgb_mat_state ) {
                rgb_matrix_loadBase();
            }
            return true;
            break;
    }
    return true;
}

// RGB lighting initialize base layer
void matrix_init_rgb() {
    // Load HSV colors
    rgb_matrix_sethsv( userspace_config.rgb_mat_hue,
            userspace_config.rgb_mat_sat,
            userspace_config.rgb_mat_val );
    rgb_matrix_sethsv(300,255,255);
    rgb_matrix_mode(1);
    rgb_matrix_enable();
    rgb_matrix_saveBase();
    rgb_matrix_loadBase();
}
