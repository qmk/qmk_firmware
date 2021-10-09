/* Copyright 2021 @ Grayson Carr
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

// clang-format off

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

// clang-format on

bool get_caps_lock_light_tab(void);
bool get_caps_lock_light_alphas(void);
bool get_fn_layer_transparent_keys_off(void);
bool get_fn_layer_color_enable(void);