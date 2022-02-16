/*
 * Copyright 2022 Uthol
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

//Animation loader file
#include "helix.c" //animation file
#include <stdio.h>

char wpm_str[10];

#    define ANIM_SIZE 1024  // number of bytes in array, minimize for adequate firmware size, max is 1024
#    define ANIM_FRAMES 50 // Number of frames
#    define ANIM_FRAME_DURATION 160 // How long each frame lasts in ms

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;

static void render_anim(void) {
    // assumes 1 frame prep stage
    void animation_phase(void) {
        current_idle_frame = (current_idle_frame + 1) % ANIM_FRAMES;
        oled_write_raw_P(animation[abs((ANIM_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);

    }
    if (get_current_wpm() != 000) {
        oled_on();  
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

// Used to draw on to the oled screen
bool oled_task_user(void) {
    render_anim(); 
    oled_write_P(PSTR("Layer:"), false);
    switch (get_highest_layer(layer_state   |  default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("Colemak\n"), false);
            break;
        case _SETTINGS:
            oled_write_P(PSTR("Settings\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    sprintf(wpm_str, "WPM:%03d", get_current_wpm());  // edit the string to change what shows up, edit %03d to change how many digits show up
    oled_write(wpm_str, false);                       // writes wpm
    return false;
}
