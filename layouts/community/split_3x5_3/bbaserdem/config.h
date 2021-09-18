
/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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

// Split definition; use the following to flash;
//  pro-micro:      avrdude-split-left/right
//  elite-c:        dfu-split-left/right
#define EE_HANDS

#ifdef KEYBOARD_crkbd_rev1
    // Corne overrides
#   ifdef RGBLED_NUM
#   undef RGBLED_NUM
#   endif
#   ifdef DRIVER_LED_TOTAL
#   undef DRIVER_LED_TOTAL
#   endif
#   define RGBLED_NUM 48
#   define DRIVER_LED_TOTAL RGBLED_NUM
#endif // KEYBOARD_crkbd_rev1
