#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "matrix.h"
#include "keymap.h"
#include "eeconfig.h"
#include "bootloader.h"
#include "bootmagic.h"


void bootmagic(void)
{
    /* do scans in case of bounce */
    uint8_t scan = 100;
    while (scan--) { matrix_scan(); _delay_ms(1); }

    if (!BOOTMAGIC_IS_ENABLE()) { return; }

    if (bootmagic_scan_keycode(BOOTMAGIC_BOOTLOADER_KEY)) {
        bootloader_jump();
    }

    if (bootmagic_scan_keycode(BOOTMAGIC_DEBUG_ENABLE_KEY)) {
        eeconfig_write_debug(eeconfig_read_debug() ^ EECONFIG_DEBUG_ENABLE);
    }

    if (bootmagic_scan_keycode(BOOTMAGIC_EEPROM_CLEAR_KEY)) {
        eeconfig_init();
    }
}

bool bootmagic_scan_keycode(uint8_t keycode)
{
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row_t matrix_row = matrix_get_row(r);
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            if (matrix_row & ((matrix_row_t)1<<c)) {
                if (keycode == keymap_key_to_keycode(0, (key_t){ .row = r, .col = c })) {
                    return true;
                }
            }
        }
    }
    return false;
}
