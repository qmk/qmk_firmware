/*
Copyright 2021 @Yowkees
Copyright 2021 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#if defined(OLED_ENABLE) && !defined(OLEDKIT_DISABLE)

// oledkit_render_info_user renders keyboard's internal state information to
// primary board. A keymap can override this by defining a function with same
// signature.
//
// It render a logo as default.
void oledkit_render_info_user(void);

// oledkit_render_logo_user renders a logo of keyboard to secondary board.
// A keymap can override this by defining a function with same signature.
void oledkit_render_logo_user(void);

#endif // OLED_ENABLE
