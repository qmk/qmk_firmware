/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include "quantum.h"

/** \brief Reset eeprom
 *
 * ...just incase someone wants to only change the eeprom behaviour
 */
__attribute__((weak)) void bootmagic_lite_reset_eeprom(void) { eeconfig_disable(); }

/** \brief The lite version of TMK's bootmagic based on Wilba.
 *
 *  100% less potential for accidentally making the keyboard do stupid things.
 */
__attribute__((weak)) void bootmagic_lite(void) {
    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
#if defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
#else
    wait_ms(30);
#endif
    matrix_scan();

    // If the configured key (commonly Esc) is held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    // This isn't very generalized, but we need something that doesn't
    // rely on user's keymaps in firmware or EEPROM.
    uint8_t row = BOOTMAGIC_LITE_ROW;
    uint8_t col = BOOTMAGIC_LITE_COLUMN;

#if defined(SPLIT_KEYBOARD) && defined(BOOTMAGIC_LITE_ROW_RIGHT) && defined(BOOTMAGIC_LITE_COLUMN_RIGHT)
    if (!is_keyboard_left()) {
        row = BOOTMAGIC_LITE_ROW_RIGHT;
        col = BOOTMAGIC_LITE_COLUMN_RIGHT;
    }
#endif

    if (matrix_get_row(row) & (1 << col)) {
        bootmagic_lite_reset_eeprom();

        // Jump to bootloader.
        bootloader_jump();
    }
}

void bootmagic(void) { bootmagic_lite(); }
