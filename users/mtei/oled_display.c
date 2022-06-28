/* Copyright 2020 mtei
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

#include "pseudo_sprintf.h"

extern int current_default_layer;

//OLED update loop
#if defined(OLED_ENABLE)

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_180;
    }
}

#ifndef PSEUDO_SPRINTF_DEFINED
#include "pseudo_sprintf.c"
#endif

static void render_logo(void) {
    static const char helix_logo[] PROGMEM = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
        0};
    oled_write_P(helix_logo, false);
#    if defined(RGBLIGHT_ENABLE) || defined(DEBUG_MATRIX_SCAN_RATE)
    char buf[30];
    char *bufp;
#    endif
#    ifdef RGBLIGHT_ENABLE
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        bufp = sprint2d(buf, " LED ", rgblight_get_mode());
#        ifdef DEBUG_MATRIX_SCAN_RATE
        bufp = sprintd(bufp, "  scan:", get_matrix_scan_rate());
#        else
        bufp = sprintd(bufp, ": ", rgblight_get_hue()/RGBLIGHT_HUE_STEP);
        bufp = sprintd(bufp, ",", rgblight_get_sat()/RGBLIGHT_SAT_STEP);
        bufp = sprintd(bufp, ",", rgblight_get_val()/RGBLIGHT_VAL_STEP);
        bufp = sprints(bufp, " ");
#        endif
        oled_write(buf, false);
    } else {
#        ifdef DEBUG_MATRIX_SCAN_RATE
        bufp = sprintd(buf, "  scan:", get_matrix_scan_rate());
        oled_write(buf, false);
#        endif // DEBUG_MATRIX_SCAN_RATE
        oled_write_P( PSTR("\n"), false);
    }
#    else // ifndef RGBLIGHT_ENABLE
#        ifdef DEBUG_MATRIX_SCAN_RATE
    bufp = sprintd(buf, " scan:", get_matrix_scan_rate());
    bufp = sprints(bufp, " ");
    oled_write(buf, false);
#        endif
#    endif // RGBLIGHT_ENABLE
}

/* weak reference */ __attribute__((weak)) extern const char *layer_names[];
/* weak reference */ __attribute__((weak)) extern const size_t num_of_layer_names;

void render_status(void) {
    // Render to mode icon
    static const char os_logo[][2][3] PROGMEM ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
    if(keymap_config.swap_lalt_lgui==false){
        oled_write_P(os_logo[0][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[0][1], false);
    } else {
        oled_write_P(os_logo[1][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[1][1], false);
    }

    // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
    int name_num, max_name_num;
    uint32_t lstate;
    char buf[16];
    max_name_num = 0;
    if (layer_names != NULL) {
        max_name_num = num_of_layer_names;
        oled_write_P(layer_names[current_default_layer], false);
    } else {
        sprintd(buf, " layer:", current_default_layer);
        oled_write(buf, false);
    }
#    ifdef DEBUG_MATRIX_SCAN_RATE
    sprintd(buf, " scan:", get_matrix_scan_rate());
    oled_write(buf, false);
#    endif
    oled_write_P(PSTR("\n"), false);
    for (lstate = layer_state, name_num = 0; lstate; lstate >>=1, name_num++) {
        if ((lstate & 1) != 0) {
            if (name_num < max_name_num && layer_names[name_num]) {
                oled_write_P(layer_names[name_num], false);
            } else {
                sprintd(buf, ":", name_num);
                oled_write(buf, false);
            }
        }
    }
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUMLOCK  ") : PSTR("         "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS  ") : PSTR("      "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCLK  ") : PSTR("      "), false);
}

bool oled_task_user(void) {

#    if DEBUG_TO_SCREEN
    if (debug_enable) {
        return;
    }
#    endif

    if(is_keyboard_master()){
        render_status();
    }else{
        render_logo();
    }
    return false;
}

#endif
