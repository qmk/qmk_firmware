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

#include "bbaserdem.h"

userspace_config_t userspace_config;

/*---------------------*\
|*-----MATRIX INIT-----*|
\*---------------------*/

/* This code runs once on startup
 * So far, sets the base layer and fixes unicode mode
 */

__attribute__ ((weak)) void matrix_init_keymap(void) {}
__attribute__ ((weak)) void matrix_init_rgb(void) {}

void matrix_init_user (void) {
    // Keymap specific things, do it first thing to allow for delays etc
    matrix_init_keymap();

    // Unicode mode
#ifdef UNICODE_ENABLE
    set_unicode_input_mode(UC_LNX);
#endif

    // Fix beginning base layer
    set_single_persistent_default_layer(_BA);

    // RGB backlight
#if (defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE))
    matrix_init_rgb();
#endif
}

/*---------------------*\
|*-----MATRIX SCAN-----*|
\*---------------------*/
__attribute__ ((weak)) void matrix_scan_keymap(void) { }

void matrix_scan_user (void) {
    // Keymap specific scan function
    matrix_scan_keymap();

    /*/
    // Hook on to layer change events
    uint8_t static prev_layer;
    uint8_t current_layer = biton32( layer_state );
    if ( prev_layer != current_layer ) {
        prev_layer = current_layer;
    }
    //*/
}

/*---------------------*\
|*-----LAYER STATE-----*|
\*---------------------*/

/* Ideally layer switching stuff would go here, but doesn't work consistently
 * across keyboards for me; thus I do explicit layer checking in matrix-scan */

__attribute__ ((weak)) uint32_t layer_state_set_keymap (uint32_t state) {
    return state;
}
uint32_t layer_state_set_user(uint32_t state) {

    // Keymap layer state setting
    state = layer_state_set_keymap(state);

    // RGB Backlight
#ifdef RGBLIGHT_ENABLE
    layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE

    // Audio sounds
#ifdef AUDIO_ENABLE
    layer_state_set_audio(state);
#endif // AUDIO_ENABLE

    // Mark as having been on gaming layer
    if( biton32(state) == _GA ) {
        userspace_config.game_flag = true;
    } else {
        userspace_config.game_flag = false;
    }

    return state;
}

/*-----------------------------*\
|*-----DEFAULT LAYER STATE-----*|
\*-----------------------------*/

__attribute__ ((weak)) uint32_t default_layer_state_set_keymap (uint32_t state) {
    return state;
}

// Runs state check and changes underglow color and animation
uint32_t default_layer_state_set_user(uint32_t state) {
    state = default_layer_state_set_keymap(state);
    return state;
}

/*------------------------*\
|*-----LED SET KEYMAP-----*|
\*------------------------*/

// Used for custom LED code
__attribute__ ((weak)) void led_set_keymap(uint8_t usb_led) {}
void led_set_user(uint8_t usb_led) {
    led_set_keymap(usb_led);
}

/*------------------------*\
|*-----LED SET KEYMAP-----*|
\*------------------------*/

// Used for custom LED code
__attribute__ ((weak)) void rgb_matrix_indicators_keymap(void) {}
void rgb_matrix_indicators_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_indicators_rgb();
#endif // RGB_MATRIX_ENABLE
    rgb_matrix_indicators_keymap();
}

/*-----------------------*\
|*-----EECONFIG INIT-----*|
\*-----------------------*/

__attribute__ ((weak)) void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
    userspace_config.raw = 0;
    eeconfig_update_user(userspace_config.raw);
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(UC_LNX);
    get_unicode_input_mode();
#else
    eeprom_update_byte(EECONFIG_UNICODEMODE, UC_LNX);
#endif
}

/*-----------------*\
|*-----SUSPEND-----*|
\*-----------------*/

/* Suspend stuff here, mostly for the rgb lighting. 
 * Which got scrapped because suspend code should be in keyboard variant. */

__attribute__ ((weak)) void suspend_power_down_keymap (void) { }
void suspend_power_down_user(void) {
    suspend_power_down_keymap();
}

__attribute__ ((weak)) void suspend_wakeup_init_keymap (void) { }
void suspend_wakeup_init_user(void) {
    suspend_wakeup_init_keymap();
}
/*------------------*\
|*-----SHUTDOWN-----*|
\*------------------*/

__attribute__ ((weak)) void shutdown_keymap (void) { }
void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb_red();
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    uint16_t timer_start = timer_read();
    rgb_matrix_set_color_all( 0xFF, 0x00, 0x00 );
    while(timer_elapsed(timer_start) < 250) { wait_ms(1); }
#endif //RGB_MATRIX_ENABLE
    shutdown_keymap();
}
