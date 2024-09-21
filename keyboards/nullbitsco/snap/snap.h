/* Copyright 2021 Jay Greco
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
#include "common/remote_kb.h"
#include "common/bitc_led.h"

#ifdef VIA_ENABLE
enum custom_keycodes {
    DISC_MUTE = QK_USER_0,
    SUPER_ALT_TAB
};
#else
enum custom_keycodes {
    DISC_MUTE = SAFE_RANGE,
    SUPER_ALT_TAB
};
#endif
