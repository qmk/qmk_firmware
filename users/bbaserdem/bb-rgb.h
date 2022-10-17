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
#include "bbaserdem.h"

/* Hooks involving perkey RGB LEDs
 */

// For custom indicators
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);
// Hook into shutdown code
void shutdown_rgb(void);
void suspend_wakeup_init_rgb(void);
void suspend_power_down_rgb(void);
