/* Copyright 2021 Jonathan Rascher
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

#include <stdbool.h>
#include <stdint.h>

#include "led.h"

/* Renders the logo embedded at the "standard" location in the OLED font at the
 * cursor. By default, this is a "QMK Firmware" logo, but many keyboards put
 * their own logo here instead. Occupies 21x3 character cells.
 */
void render_oled_logo(void);

/* Note: Functions below assume a vertical OLED that is 32px (5 chars) wide. */

/* Renders layer status at the cursor. Occupies 5x1 character cells. */
void render_oled_layers(void);

/* Renders LED indicators (Num/Caps/Scroll Lock) at the cursor. Occupies 5x3
 * character cells.
 */
void render_oled_indicators(led_t leds);

/* Renders calculated WPM count at the cursor. Occupies 5x2 character cells. */
void render_oled_wpm(uint8_t wpm);

#if defined(BCAT_OLED_PET)
/* Renders an animated critter at the cursor that can respond to keystrokes,
 * typing speed, etc. Should be about 5 character cells wide, but exact height
 * varies depending on the specific OLED pet implementation linked in.
 *
 * The rendered image will be one line taller than the OLED pet's animation
 * frame height to accommodate pets that "jump" when the spacebar is pressed.
 */
void render_oled_pet(uint8_t col, uint8_t line, uint8_t mods, led_t leds, uint8_t wpm);
#endif
