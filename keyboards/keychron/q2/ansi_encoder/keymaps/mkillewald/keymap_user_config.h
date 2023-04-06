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

#pragma once

void user_config_read_eeprom(void);
void user_config_write_eeprom(void);

// getters

bool user_config_get_caps_lock_light_tab(void);
bool user_config_get_caps_lock_light_alphas(void);
bool user_config_get_fn_layer_transparent_keys_off(void);
bool user_config_get_fn_layer_color_enable(void);

uint8_t user_config_get_mode_win_base(void);
uint8_t user_config_get_spd_win_base(void);

HSV user_config_get_hsv_win_base(void);
HSV user_config_get_hsv_mac_fn1(void);
HSV user_config_get_hsv_win_fn1(void);
HSV user_config_get_hsv_fn2(void);

// setters 

void user_config_toggle_caps_lock_light_tab(void);
void user_config_toggle_caps_lock_light_alphas(void);
void user_config_toggle_fn_layer_transparent_keys_off(void);
void user_config_toggle_fn_layer_color_enable(void);

void user_config_set_mode_win_base(uint8_t mode);
void user_config_set_spd_win_base(uint8_t spd);

void user_config_set_hsv_win_base(HSV hsv);
void user_config_set_hsv_mac_fn1(HSV hsv);
void user_config_set_hsv_win_fn1(HSV hsv);
void user_config_set_hsv_fn2(HSV hsv);


