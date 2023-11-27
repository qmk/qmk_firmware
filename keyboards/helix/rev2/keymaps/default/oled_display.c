/* Copyright 2020 yushakobo
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

#include <stdio.h>
#include <string.h>
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

//OLED update loop
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_180;
    }
}

static void render_rgbled_status(bool full) {
#    ifdef RGBLIGHT_ENABLE
    char buf[30];
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        if (full) {
            snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                     rgblight_get_mode(),
                     rgblight_get_hue()/RGBLIGHT_HUE_STEP,
                     rgblight_get_sat()/RGBLIGHT_SAT_STEP,
                     rgblight_get_val()/RGBLIGHT_VAL_STEP);
        } else {
            snprintf(buf, sizeof(buf), "[%2d] ", rgblight_get_mode());
        }
        oled_write(buf, false);
    }
#    endif
}

static void render_layer_status(void) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
    char buf[10];
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
    case L_BASE:
        oled_write_P(PSTR("Default"), false);
        break;
    case L_RAISE:
        oled_write_P(PSTR("Raise"), false);
        break;
    case L_LOWER:
        oled_write_P(PSTR("Lower"), false);
        break;
    case L_ADJUST:
    case L_ADJUST_TRI:
        oled_write_P(PSTR("Adjust"), false);
        break;
    default:
        oled_write_P(PSTR("Undef-"), false);
        snprintf(buf,sizeof(buf), "%u", layer_state);
        oled_write(buf, false);
    }
    oled_write_P(PSTR("\n"), false);
}

void render_status(void) {
  // Render to mode icon
    static const char os_logo[][2][3] PROGMEM = {{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
    if (is_mac_mode()) {
        oled_write_P(os_logo[0][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[0][1], false);
    } else {
        oled_write_P(os_logo[1][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[1][1], false);
    }

    oled_write_P(PSTR(" "), false);
    render_layer_status();

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUMLOCK") : PSTR("       "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCLK") : PSTR("    "), false);
    oled_advance_page(true);
    render_rgbled_status(true);
    oled_write_P(PSTR("\n"), false);
}

bool oled_task_user(void) {

#        if DEBUG_TO_SCREEN
    if (debug_enable) {
        return;
    }
#        endif

    if (is_keyboard_master()) {
        render_status();
    } else {
        render_helix_logo();
        render_rgbled_status(false);
        render_layer_status();
    }
    return false;
}
#endif // end of OLED_ENABLE
