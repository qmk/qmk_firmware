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

// Kyria specific
#ifdef KEYBOARD_splitkb_kyria_rev1
    // Split definition; use the following to flash;
    //  pro-micro:      avrdude-split-left/right
    //  elite-c:        dfu-split-left/right
#   define ENCODER_DIRECTION_FLIP
#   define EE_HANDS

    // Make sure kyria has bigger oled display
#   ifdef OLED_ENABLE
#   define OLED_DISPLAY_128X64
#   endif
#endif
