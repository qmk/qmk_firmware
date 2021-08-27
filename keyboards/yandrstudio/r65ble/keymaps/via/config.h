/* Copyright 2021 JasonRen(biu)
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
/* OLED */
#ifdef OLED_DRIVER_ENABLE
// #    define OLED_DISPLAY_128X64
#    define I2C_DRIVER I2CD1
#    define I2C1_TIMINGR_PRESC 0U
#    define I2C1_TIMINGR_SCLDEL 7U
#    define I2C1_TIMINGR_SDADEL 0U
#    define I2C1_TIMINGR_SCLH 38U
#    define I2C1_TIMINGR_SCLL 129U
#    define OLED_BRIGHTNESS 50
#    define OLED_TIMEOUT 300000
// #    define OLED_TIMEOUT 0
#    define OLED_FONT_HEIGHT 8
#    define OLED_FONT_WIDTH 6
#    define OLED_FONT_H "../../jason_fount.c"
#    define OLED_FONT_END 127
#    define OLED_FONT_START 0
#endif


#ifdef TAP_DANCE_ENABLE
#define TAPPING_TERM 200

#endif
