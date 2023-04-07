/* Copyright 2023 @ Mike Killewald (https://github.com/mkillewald)
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

#include QMK_KEYBOARD_H
#include "keymap_user_config.h"

typedef struct {
    bool caps_lock_light_tab;
    bool caps_lock_light_alphas;
    bool fn_layer_transparent_keys_off;
    bool fn_layer_color_enable;
    uint8_t mode_win_base;
    uint8_t spd_win_base;
    HSV hsv_win_base;
    HSV hsv_mac_fn1;
    HSV hsv_win_fn1;
    HSV hsv_fn2;
} user_config_t;

user_config_t user_config;

void eeconfig_init_user(void) {
    user_config.caps_lock_light_tab = false;
    user_config.caps_lock_light_alphas = true;
    user_config.fn_layer_transparent_keys_off = false;
    user_config.fn_layer_color_enable = true;
    user_config.mode_win_base = RGB_MATRIX_DEFAULT_MODE;
    user_config.spd_win_base = RGB_MATRIX_DEFAULT_SPD;
    user_config.hsv_win_base.h = DEFAULT_HUE_WIN_BASE;
    user_config.hsv_win_base.s = RGB_MATRIX_DEFAULT_SAT;
    user_config.hsv_win_base.v = RGB_MATRIX_DEFAULT_VAL;
    user_config_write_eeprom();
}

void user_config_read_eeprom(void) {
    eeconfig_read_user_datablock(&user_config);
}

void user_config_write_eeprom(void) {
    eeconfig_update_user_datablock(&user_config);
}

// getters

bool user_config_get_caps_lock_light_tab(void) {
    return user_config.caps_lock_light_tab;
}

bool user_config_get_caps_lock_light_alphas(void) {
    return user_config.caps_lock_light_alphas;
}

bool user_config_get_fn_layer_transparent_keys_off(void) {
    return user_config.fn_layer_transparent_keys_off;
}

bool user_config_get_fn_layer_color_enable(void) {
    return user_config.fn_layer_color_enable;
}

uint8_t user_config_get_mode_win_base(void) {
    return user_config.mode_win_base;
}

uint8_t user_config_get_spd_win_base(void) {
    return user_config.spd_win_base;
}

HSV user_config_get_hsv_win_base(void) {
    return user_config.hsv_win_base;
}

HSV user_config_get_hsv_mac_fn1(void) {
    return user_config.hsv_mac_fn1;
}

HSV user_config_get_hsv_win_fn1(void) {
    return user_config.hsv_win_fn1;
}

HSV user_config_get_hsv_fn2(void) {
    return user_config.hsv_fn2;
}

// setters

void user_config_toggle_caps_lock_light_tab(void) {
    user_config.caps_lock_light_tab ^= 1; // bitwise xor to toggle status bit
    user_config_write_eeprom();
}

void user_config_toggle_caps_lock_light_alphas(void) {
    user_config.caps_lock_light_alphas ^= 1;
    user_config_write_eeprom();
}

void user_config_toggle_fn_layer_transparent_keys_off(void) {
    user_config.fn_layer_transparent_keys_off ^= 1;
    user_config_write_eeprom();
}

void user_config_toggle_fn_layer_color_enable(void) {
    user_config.fn_layer_color_enable ^= 1;
    user_config_write_eeprom();
}

void user_config_set_mode_win_base(uint8_t mode) {
    user_config.mode_win_base = mode;
    user_config_write_eeprom();
}

void user_config_set_spd_win_base(uint8_t spd) {
    user_config.spd_win_base = spd;
    user_config_write_eeprom();
}

void user_config_set_hsv_win_base(HSV hsv) {
    user_config.hsv_win_base = hsv;
    user_config_write_eeprom();
}

void user_config_set_hsv_mac_fn1(HSV hsv) {
    user_config.hsv_mac_fn1 = hsv;
    user_config_write_eeprom();
}

void user_config_set_hsv_win_fn1(HSV hsv) {
    user_config.hsv_win_fn1 = hsv;
    user_config_write_eeprom();
}

void user_config_set_hsv_fn2(HSV hsv) {
    user_config.hsv_fn2 = hsv;
    user_config_write_eeprom();
}









