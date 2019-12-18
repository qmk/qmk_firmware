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

/*---------------------------*\
|*-----KEYBOARD PRE INIT-----*|
\*---------------------------*/

/*
 * This code runs before anything is started.
 * Good for early hardware setup
 */

__attribute__ ((weak)) void keyboard_pre_init_keymap(void) {}
__attribute__ ((weak)) void keyboard_pre_init_user(void) {
    // Keymap specific stuff
    keyboard_pre_init_keymap()
}

/*---------------------*\
|*-----MATRIX INIT-----*|
\*---------------------*/

/*
 * This code runs once midway thru the firmware process.
 * So far, sets the base layer and fixes unicode mode
 */

__attribute__ ((weak)) void matrix_init_keymap(void) {}

void matrix_init_user (void) {
    // Fix beginning base layer
    set_single_persistent_default_layer(_BA);

    // Unicode mode
#ifdef UNICODE_ENABLE
    set_unicode_input_mode(UC_LNX);
#endif

    // Keymap specific things
    matrix_init_keymap();
}

/*----------------------------*\
|*-----KEYBOARD POST INIT-----*|
\*----------------------------*/

/*
 * This code runs after anything is started.
 * Good for late hardware setup
 */

__attribute__ ((weak)) void keyboard_post_init_keymap(void) {}
__attribute__ ((weak)) void keyboard_post_init_user(void) {
    // Backlight LED
#ifdef BACKLIGHT_ENABLE
    matrix_init_backlight();
#endif

    // RGB backlight
#ifdef RGBLIGHT_ENABLE
    matrix_init_rgb_light();
#endif

    // RGB Matrix
#ifdef RGB_MATRIX_ENABLE
    matrix_init_rgb_matrix();
#endif

    // Keymap specific stuff
    keyboard_post_init_keymap()
}

/*---------------------*\
|*-----MATRIX SCAN-----*|
\*---------------------*/

/*
 * This code runs every frame
 * I used to check for layer switching here, but layer state is better used.
 * Try to not put anything here
 */

__attribute__ ((weak)) void matrix_scan_keymap(void) { }

void matrix_scan_user (void) {
    // Keymap specific scan function
    matrix_scan_keymap();
}

/*---------------------*\
|*-----LAYER STATE-----*|
\*---------------------*/

/*
 * This code runs after every layer change
 * State represents the new layer state.
 */

__attribute__ ((weak)) uint32_t layer_state_set_keymap (uint32_t state) {
    return state;
}
uint32_t layer_state_set_user(uint32_t state) {

    // Keymap layer state setting
    state = layer_state_set_keymap(state);

    // RGB Backlight
#ifdef RGBLIGHT_ENABLE
    layer_state_set_rgb_light(state);
#endif // RGBLIGHT_ENABLE

    // RGB Matrix
#ifdef RGB_MATRIX_ENABLE
    layer_state_set_rgb_matrix(state);
#endif // RGBLIGHT_ENABLE

    // Audio sounds
#ifdef AUDIO_ENABLE
    layer_state_set_audio(state);
#endif // AUDIO_ENABLE

    return state;
}

/*-----------------------------*\
|*-----DEFAULT LAYER STATE-----*|
\*-----------------------------*/

/*
 * This code runs after every time default base layer is changed
 */

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

/*
 * I assume this runs to update LEDs, I don't really know
 */

__attribute__ ((weak)) void led_set_keymap(uint8_t usb_led) {}
void led_set_user(uint8_t usb_led) {
    led_set_keymap(usb_led);
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
