/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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

#pragma once

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
rgblight_config_t        RGB_current_config;
#endif

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
rgb_config_t        RGB_current_config;
#endif

void save_rgb_config(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_config.enable = rgblight_config.enable;
    RGB_current_config.mode   = rgblight_get_mode();
    RGB_current_config.speed  = rgblight_get_speed();
    RGB_current_config.hue    = rgblight_get_hue();
    RGB_current_config.sat    = rgblight_get_sat();
    RGB_current_config.val    = rgblight_get_val();
#elif RGB_MATRIX_ENABLE
    RGB_current_config.enable = rgb_matrix_config.enable;
    RGB_current_config.mode   = rgb_matrix_get_mode();
    RGB_current_config.speed  = rgb_matrix_config.speed;
    RGB_current_config.hsv    = rgb_matrix_config.hsv;
#endif
}

void restore_rgb_config(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_set_speed_noeeprom(RGB_current_config.speed);
    if (rgblight_config.mode != RGB_current_config.mode) {
        rgblight_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hue != rgblight_config.hue) || (RGB_current_config.sat != rgblight_config.sat) || (RGB_current_config.val != rgblight_config.val)) {
        rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
    }
    if (rgblight_config.enable) {
        rgblight_enable_noeeprom();
    } else {
        rgblight_disable_noeeprom();
    }
#elif RGB_MATRIX_ENABLE
    rgb_matrix_config.speed   = RGB_current_config.speed;
    if (rgb_matrix_config.mode != RGB_current_config.mode) {
        rgb_matrix_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hsv.h != rgb_matrix_config.hsv.h) || (RGB_current_config.hsv.s != rgb_matrix_config.hsv.s) || (RGB_current_config.hsv.v != rgb_matrix_config.hsv.v)) {
        rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
    }
    if (rgb_matrix_config.enable) {
        rgb_matrix_enable_noeeprom();
    } else {
        rgb_matrix_disable_noeeprom();
    }
#endif
}

void rgb_by_layer(int layer) {
#ifdef RGBLIGHT_ENABLE
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#elif RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif

    switch (layer) {
        case _ADJUST:
            rgblight_sethsv_noeeprom(9, 255, 255);
            break;
        case _RAISE:
            rgblight_sethsv_noeeprom(HSV_CYAN);
            break;
        case _LOWER:
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            break;
        default:
            rgblight_sethsv_noeeprom(HSV_RED);
    }
}
