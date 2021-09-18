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

#include "bb-backlight.h"
/* Replaced functions with noeeprom varieties; I don't need retention across
 * booting.
 */

// Backlight LEDs
void keyboard_post_init_backlight(void) {
    backlight_enable();
    backlight_level(2);
#   ifdef BACKLIGHT_BREATHING
    breathing_enable();
#   endif // BACKLIGHT_BREATHING
}
