/* Copyright 2021 adpenrose
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

#include "kintsugi.h"

/* Encoder */
#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { 
        return false; 
    }
/* The switch case allows for different encoder mappings on different layers, "default" map gets applied for all unspecified layers */
    switch(get_highest_layer(layer_state)){
        case 1:
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
            break;
        default:
            if (clockwise){
                tap_code(KC_VOLU);
            } else{
                tap_code(KC_VOLD);
            }
            break;
        }
    return true;
}
#endif

/* Rotation of the OLED: */
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) { 
        return false; 
    }
    /* Kintsugi logo render: */
    static const char PROGMEM logo_1[] = {
        0x83, 0x84, 0x85, 0x86, 0x87, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0x00
    };
    static const char PROGMEM logo_2[] = {
        0x88, 0x89, 0x8A, 0x8B, 0x8C, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0x00
    };
    static const char PROGMEM logo_3[] = {
        0x8D, 0x8E, 0x8F, 0x90, 0x91, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0x00
    };
    oled_set_cursor(1,3);
    oled_write_P(logo_1, false);
    oled_set_cursor(1,7);
    oled_write_P(logo_2, false);
    oled_set_cursor(1,11);
    oled_write_P(logo_3, false);
    return true;
}
#endif
