/* Copyright 2019 kratsyn
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

#include	"hal.h"
#include	"backlight.h"
#include	"printf.h"

#define	BLT_LINE	B0
#define	BLT_PWMD	PWMD3

void backlight_init_ports(void) {
	palSetLineMode(BLT_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLine(BLT_LINE);
	printf("[BL] Backlight Init.\n");
};

void backlight_set(uint8_t level) {
	if (level == 0) {
		// turn it off
		palClearLine(BLT_LINE);
	} else {
		palSetLine(BLT_LINE);
	}
};
