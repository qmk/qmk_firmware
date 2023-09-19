/* Copyright 2023 9R
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

#include "oled.h"
#include "oled_driver.h"
#include "progmem.h"
#include "util.h"

uint8_t shiftbits =32 ;

//////////// OLED output helpers //////////////
void draw_mode(controller_state_t controller_state) {
    //draw oled row showing thumbstick mode
    oled_write_P(PSTR("Mode: "), false);
    if (controller_state.wasdShiftMode) {
        oled_write_ln_P(PSTR("WASD + Shift"), false);
    } else if (controller_state.wasdMode) {
        oled_write_ln_P(PSTR("WASD"), false);
    } else {
        oled_write_ln_P(PSTR("JoyStick"), false);
    }
}

void draw_wasd_key(wasd_state_t wasd_state) {
    //draw oled row showing active keypresses emulated from thumbstick
    const char* keys = "wasd";
    bool keystates [] = { wasd_state.w, wasd_state.a, wasd_state.s, wasd_state.d };
    // iterate over keystates
    for (uint8_t i = 0 ; i < ARRAY_SIZE(keystates); ++i) {
        if (keystates[i]) {
            char k = keys[i] ;
            //bitshift char to upper case
            if (wasd_state.shift) {
                k &= ~shiftbits;
            }
            oled_write_char(k, false);
        } else {
            oled_write_P(PSTR(" "), false);
        }
    }
}

void draw_thumb_debug(thumbstick_polar_position_t thumbstick_polar_position) {
    //draw oled row showing thumbstick direction and distance from center
    oled_write_P(PSTR("Dir:"), false);
    oled_write(get_u16_str(thumbstick_polar_position.angle, ' '), false);
    oled_write_P(PSTR(" Dist:"), false);
    oled_write_ln(get_u16_str(thumbstick_polar_position.distance, ' '), false);
    //print registered key codes
    oled_write_P(PSTR("Keycodes: "), false);
    draw_wasd_key( wasd_state );
}

//////////// draw OLED output //////////////
void draw_oled(controller_state_t controller_state) {
    oled_write_P(PSTR("Layer: "), false);

    switch (controller_state.highestActiveLayer) {
        case _SHOOTER:
            oled_write_ln_P(PSTR("Shooter"), false);
            break;

        case _MISC:
            oled_write_ln_P(PSTR("Misc"), false);
            break;

        case _SETTINGS:
            oled_write_ln_P(PSTR("Settings"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Default"), false);
    }

    draw_mode(controller_state);
    if (controller_state.highestActiveLayer == _SETTINGS ) {
        draw_thumb_debug(thumbstick_polar_position);
    }
    else {
        oled_write_ln_P(PSTR(" "), false);
    }
    oled_write_ln_P(PSTR(" "), false);
}
