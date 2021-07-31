/* Copyright 2020 Stephen J. Bush
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

#ifdef RGBLIGHT_ENABLE
#    include QMK_KEYBOARD_H
#    include "rgblayers.h"

static rgblight_config_t home_rgb;

__attribute__((weak)) void set_layer_hsv(layer_state_t state, HSV* offset) {}

/* Placeholder function
 * If defined in a keymap.c, this will be ignored.
 */
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t* record) { return; }

void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Regular user keycode case statement
    switch (keycode) {
#    ifdef RGBLIGHT_ENABLE
        case RGB_HUD:
        case RGB_HUI:
        case RGB_SAD:
        case RGB_SAI:
        case RGB_VAD:
        case RGB_VAI:
            set_rgb_home();
            break;
#    endif
        default:
            break;
    }
}

void set_rgb_home(void) {
    home_rgb.raw = eeconfig_read_rgblight();
    // these get the current -- not eeprom
    // home_rgb.hue = rgblight_get_hue();
    // home_rgb.sat = rgblight_get_sat();
    // home_rgb.val = rgblight_get_val();
}

void set_rgb_by_layer(layer_state_t state) {
    if (!rgblight_is_enabled()) {
        return;  // lighting not enabled
    }

    HSV layer_color = {home_rgb.hue, home_rgb.sat, home_rgb.val};
    set_layer_hsv(state, &layer_color);
    rgblight_sethsv_noeeprom(  //
        layer_color.h,         // all 3 MUST be btwn 0 and 255
        layer_color.s,         //
        layer_color.v          //
    );
}
#endif
