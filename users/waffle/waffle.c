/* Copyright 2021 @waffle#0007
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

#include "waffle.h"
#include "quantum.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LWRSPC:
            return TAPPING_TERM - 30;
        case RSEBSP:
            return TAPPING_TERM - 30;
        default:
            return TAPPING_TERM;
    }
}

#ifdef UNICODEMAP_ENABLE
const uint32_t PROGMEM unicode_map[] = {
    [SIDE] = 0x30C4,
    [UPAR] = 0x16CF,
    [HAS] = 0x262D,
    [STAR] = 0x2605,
    [VIB] = 0x0950,
};
#endif

#ifdef ENCODER_ENABLE
__attribute__ ((weak)) bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _RAISE:
#if (defined(RGB_LIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE))
                clockwise ? rgblight_increase_sat() : rgblight_decrease_sat();
#else
                clockwise ? tap_code(KC_MS_R) : tap_code(KC_MS_L);
#endif
                break;
            case _LOWER:
                clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
                break;
            default:
                clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
#ifdef KEYBOARD_crkbd  
            case _ADJUST:
              clockwise ? ball_increase_hue() : tap_code(KC_NO);
              break;
  #endif
            case _RAISE:
#if (defined(RGB_LIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE))
                clockwise ? rgblight_increase_hue() : rgblight_decrease_hue();
#else
                clockwise ? tap_code(KC_MS_U) : tap_code(KC_MS_D);
#endif
                break;
            case _LOWER:
                clockwise ? tap_code16(C(KC_TAB)) : tap_code16(S(C(KC_TAB)));
                break;
            default:
                clockwise ? tap_code_delay(KC_VOLU, 20) : tap_code_delay(KC_VOLD, 20);
                break;
        }
    }
    return true;
}
#endif

#ifdef RGBLIGHT_ENABLE 
__attribute__ ((weak)) void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_CYAN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif

#ifdef PIMORONI_TRACKBALL
uint8_t white = 0;
uint8_t red = 255;
uint8_t green = 0;
uint8_t blue = 0;

void ball_increase_hue(void){
    if (red != 255 && green != 255 && blue != 255) { red = 255; }
    if (red == 255 && green < 255 && blue == 0) { green += 15; }
    else if (green == 255 && blue == 0 && red > 0) { red -= 15; }
    else if (red == 0 && blue < 255 && green == 255 ) { blue += 15; }
    else if (blue == 255 && green > 0 && red == 0) { green -= 15; }
    else if (green == 0 && blue == 255 && red < 255) { red += 15; }
    else if (green == 0 && blue > 0 && red == 255) { blue -= 15; }
    trackball_set_rgbw (red,green,blue,white);
}

void decrease_color(void){
    if (green > 0) { green -= 15; }
    if (red > 0) { red -= 15; }
    if (blue > 0) { blue -= 15; }
    trackball_set_rgbw (red,green,blue,white);
}

void cycle_white(void){
    if (white < 255) { white += 15;}
    else { white = 0; }
    trackball_set_rgbw (red,green,blue,white);
}
#endif

#ifdef OLED_ENABLE
__attribute__((weak)) void suspend_power_down_user(void) {
    oled_off();
}
#endif
