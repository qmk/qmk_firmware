/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#ifdef OLED_ENABLE
// reduce burn-in
//#    define OLED_TIMEOUT 60000
//#    define OLED_FADE_OUT
//#    define OLED_FADE_OUT_INTERVAL 3
//#    define OLED_BRIGHTNESS 100
#    define OLED_FONT_H "sheeplcdfont.c"
// reduce burn-in
#    define OLED_TIMEOUT 180000
//#    define OLED_FADE_OUT
//#    define OLED_FADE_OUT_INTERVAL 3
#    define OLED_BRIGHTNESS 60
// cosmetic
#    define SPLIT_WPM_ENABLE
#    define WPM_UNFILTERED
#    define WPM_SAMPLE_SECONDS 3
#    define WPM_SAMPLE_PERIODS 15
// choose between THUNDER or BIRDS
#    define MATRIX
//#    define THUNDER
//#    define BIRDS
#endif
