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
void render_oled_indicators(void);

/* Renders calculated WPM count at the cursor. Occupies 5x2 character cells. */
void render_oled_wpm(void);
