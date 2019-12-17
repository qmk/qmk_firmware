/*
 * Replaced functions with noeeprom varieties; I don't need retention across
 * booting.
*/
#include "rgb_bl_stuff.h"

extern rgblight_config_t rgblight_config;

void rgblight_saveBase(void) {
    // Get HSV, speed, mode and activation state
    userspace_config.rgb_blt_hue = rgblight_get_hue();
    userspace_config.rgb_blt_sat = rgblight_get_sat();
    userspace_config.rgb_blt_val = rgblight_get_val();
    userspace_config.rgb_blt_speed = rgblight_config.speed;
    userspace_config.rgb_blt_mode= rgblight_get_mode();
    userspace_config.rgb_blt_toggle = rgblight_config.enable;
    // Turn on effects so custom ones can be replaced
    rgblight_enable_noeeprom();
    // If saving, that means base layer is being left
    userspace_config.rgb_blt_state = false;
}

// Load the base state back
void rgblight_loadBase(void) {
    // If loading, coming to base layer
    userspace_config.rgb_blt_state = true;
    // Load speed
    rgblight_config.speed = userspace_config.rgb_blt_speed;
    // Load HSV colors
    rgblight_sethsv_noeeprom( userspace_config.rgb_blt_hue,
            userspace_config.rgb_blt_sat,
            userspace_config.rgb_blt_val );
    // Load mode
    rgblight_mode_noeeprom( userspace_config.rgb_blt_mode );
    // Enable or disable
    if( userspace_config.rgb_blt_toggle ) {
        rgblight_enable_noeeprom();
    } else {
        rgblight_disable_noeeprom();
    }
}

// Set RGBLIGHT state depending on layer
uint32_t layer_state_set_rgb_light( uint32_t state ) {
    // Get most recent state
    uint8_t this_layer = biton32(state);
    // Save if leaving base state
    if ( (this_layer != _BA) && (userspace_config.rgb_blt_state) ) {
        rgblight_saveBase();
    }

    // Make mode static by default
    if ( this_layer != _BA ) {
        rgblight_mode_noeeprom(1);
    };

    // Change RGB light
    switch ( this_layer ) {
        case _BA:   // Load base layer iff it's not loaded yet
            if( !userspace_config.rgb_blt_state ) {
                rgblight_loadBase();
            }
            break;
        case _GA:
            rgblight_sethsv_noeeprom_purple();
            break;
        case _NU:
            rgblight_sethsv_noeeprom_azure();
            break;
        case _SE:
            rgblight_sethsv_noeeprom_coral();
            break;
        case _MO:
            rgblight_sethsv_noeeprom_springgreen();
            break;
        case _MU:   // Do yellow for music
            rgblight_sethsv_noeeprom_gold();
            break;
        default:    // Something went wrong: RED
            rgblight_sethsv_noeeprom_red();
            break;
    }

    return(state);
}

// Make it so that RGB keys first load the base layer
bool process_record_rgb_light(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
        case RGB_MOD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_HUI:
        case RGB_HUD:
            if ( !userspace_config.rgb_blt_state ) {
                rgblight_loadBase();
            }
            return true;
            break;
    }
    return true;
}

// RGB lighting initialize base layer
void matrix_init_rgb_light(void) {
    rgblight_enable();
    rgblight_mode(2);
    rgblight_sethsv(100,0,255);
    rgblight_disable();
    rgblight_saveBase();
    rgblight_loadBase();
}
