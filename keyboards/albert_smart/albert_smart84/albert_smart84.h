/* Copyright 2024 albet-zheng
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

#include "quantum.h"

enum custom_keycodes {
#ifdef VIA_ENABLE
    KC_USB = QK_KB_0,
#else
    KC_USB = SAFE_RANGE,
#endif
    KC_MAC,
    KC_WIN,
    KC_RESET,
    GU_TOG
};
