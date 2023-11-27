// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "drashna.h"
#include "bootmagic_lite.h"

void bootmagic_lite(void) {
    bool perform_reset = false;
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
    uint8_t row = BOOTMAGIC_LITE_ROW, col = BOOTMAGIC_LITE_COLUMN;
#if defined(BOOTMAGIC_LITE_EEPROM_ROW) && defined(BOOTMAGIC_LITE_EEPROM_COLUMN)
    uint8_t row_e = BOOTMAGIC_LITE_EEPROM_ROW, col_e = BOOTMAGIC_LITE_EEPROM_COLUMN;
#endif

#if defined(SPLIT_KEYBOARD) && defined(BOOTMAGIC_LITE_ROW_RIGHT) && defined(BOOTMAGIC_LITE_COLUMN_RIGHT)
    if (!is_keyboard_left()) {
        row = BOOTMAGIC_LITE_ROW_RIGHT;
        col = BOOTMAGIC_LITE_COLUMN_RIGHT;
#    if defined(BOOTMAGIC_LITE_EEPROM_ROW) && defined(BOOTMAGIC_LITE_EEPROM_COLUMN) && defined(BOOTMAGIC_LITE_EEPROM_ROW_RIGHT) && defined(BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT)
        row_e = BOOTMAGIC_LITE_EEPROM_ROW_RIGHT;
        col_e = BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT;
#    endif
    }
#endif

#if defined(BOOTMAGIC_LITE_EEPROM_ROW) && defined(BOOTMAGIC_LITE_EEPROM_COLUMN)
    if (matrix_get_row(row_e) & (1 << col_e)) {
        eeconfig_disable();
        perform_reset = true;
    }
#endif
    if (matrix_get_row(row) & (1 << col)) {
        perform_reset = true;
    }
#if defined(STM32F411xE) && !defined(CONVERTER_ENABLED)
    if (!readPin(A0)) {
        perform_reset = true;
    }
#endif

    if (perform_reset) {
        bootloader_jump();
    }
}
