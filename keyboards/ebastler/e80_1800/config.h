/*
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

#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 2

#ifdef OLED_ENABLE

/* I2C for OLED - only enable defines if driver is enabled */
#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN        B10
#define I2C1_SDA_PIN        B11
#define I2C1_SCL_PAL_MODE   1
#define I2C1_SDA_PAL_MODE   1
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH   3U
#define I2C1_TIMINGR_SCLL   9U

#endif