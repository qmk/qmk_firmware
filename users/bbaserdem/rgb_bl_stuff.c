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
#include "rgb_bl_stuff.h"

void rgblight_saveBase(void) {
    userspace_config.rgb_base_hue =     rgblight_config.hue;
    userspace_config.rgb_base_sat =     rgblight_config.sat;
    userspace_config.rgb_base_val =     rgblight_config.val;
    userspace_config.rgb_base_mode =    rgblight_config.mode;
    userspace_config.rgb_base_toggle =  rgblight_config.enable;
    // If saving, that means base layer is being left
    userspace_config.rgb_base_state =   false;
}

// Load the base state back
void rgblight_loadBase(void) {
    // Don't do anything if not enabled
    if ( !userspace_config.rgb_base_state ) {
        if ( userspace_config.rgb_base_toggle ) {
            rgblight_enable();
            rgblight_mode( userspace_config.rgb_base_mode );
            rgblight_sethsv( userspace_config.rgb_base_hue,
                    userspace_config.rgb_base_sat,
                    userspace_config.rgb_base_val );
            rgblight_enable();
        } else {
            rgblight_disable();
        }
    }
    // Mark that base is loaded, and to be saved before leaving
    userspace_config.rgb_base_state = true;
}

// Set to plain HSV color
void rgblight_colorStatic( int hu, int sa, int va ) {
    // First, it must be enabled or color change is not written
    rgblight_enable();
    rgblight_mode(1);
    rgblight_sethsv(hu,sa,va);
    rgblight_enable();
}

// Set RGBLIGHT state depending on layer
uint32_t led_set_rgb( uint32_t state ) {
    // Get most recent state
    uint8_t this_layer = biton32(state);
    // Save state, if saving is requested
    if ( userspace_config.rgb_base_state ) {
        rgblight_saveBase();
    }
    // Change RGB light
    switch ( this_layer ) {
        case _BA:   // Load base layer
            rgblight_loadBase();
            break;
        case _GA:   // Do purple for game
            rgblight_colorStatic(285,255,255);
            break;
        case _NU:   // Do azure for number
            rgblight_colorStatic(186,200,255);
            break;
        case _SE:   // Do red for settings
            rgblight_colorStatic( 16,255,255);
            break;
        case _MO:   // Do green for mouse
            rgblight_colorStatic(120,255,255);
            break;
        case _MU:   // Do yellow for music
            rgblight_colorStatic( 60,255,255);
            break;
        default:    // Something went wrong: RED
            rgblight_colorStatic(  0,255,255);
            break;
    }
    // For lets split it up
#ifdef SPLIT_KEYBOARD
    RGB_DIRTY = true;
#endif

    return(state);
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
#ifdef RGBLIGHT_ENABLE
            if ( !userspace_config.rgb_base_state ) {
                rgblight_loadBase();
            }
#endif // RGBLIGHT_ENABLE
            return true;
            break;
    }
    return true;
}

// RGB lighting initialize base layer
void matrix_init_rgb() {
    rgblight_enable();
    rgblight_mode(2);
    rgblight_sethsv(100,0,255);
    rgblight_disable();
    rgblight_saveBase();
    rgblight_loadBase();
}
