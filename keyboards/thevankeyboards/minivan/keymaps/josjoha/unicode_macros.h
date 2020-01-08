/*
 * License (GPL):
  
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

 * Authors: This QMK keymap file is a combination of the default
 * keymap, led code original copied/edited from ../jetpacktuxedo, some
 * copy/paste from QMK documentation code examples (etc).
 * Remainder: (C) 2019 by J.B. <joshb@xs4all.nl>
 *
 */

/* This file contains function declarations for functions used in
 * unicode_macros.c
 */

#define PRESCRAMBLED_U "f"  // This is the letter 'u' for Unicode input, as effective on GNU/Debian/Linux 10 set to Dvorak
static uint16_t key_timer; // Used in _DDL to differentiate layer switching in half or full descramble mode.
                           // In 'full' mode it goes to _DDD and _DDA Unicode layers, in 'half' mode to _DRA and _ACC.

void deactivate_all_but (int layer);
void activate_this_layer (int layer);
void indicate_scramble (void);
void leds_show_off (void);
