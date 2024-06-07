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

/* key matrix size, only 1x4 are used in current state.
   IO expander setup would allow up to 1x16 + 1 from the MCU */
#define MATRIX_ROWS 1
#define MATRIX_COLS 17

/* Fix for Apple Silicon Macs struggling to detect board after suspend/sleep */
#define USB_SUSPEND_WAKEUP_DELAY 200