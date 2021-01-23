/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "protocol/serial.h"

// matrix state buffer(1:on, 0:off)
static matrix_row_t matrix[MATRIX_ROWS];

static void register_key(uint8_t key);

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;

    serial_init();

    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    _delay_ms(500);

    matrix_init_quantum();
    return;
}

uint8_t matrix_scan(void)
{

    uint8_t code = 0;
    uint8_t new_code = 0;
    uint8_t new_mods = 0;
    uint8_t saved_mods = get_mods();
    del_mods(saved_mods);

    code = serial_recv();

    if (code >= 0x61 && code <= 0x7A) {
        // convert ASCII min to matrix pos 0x00 to 0x19
        new_code = code - 0x61;
        register_key(new_code);
    } else if (code >= 0x41 && code <= 0x5A) {
        // convert ASCII maj to Shift + matrix pos 0x00 to 0x19
        new_code = code - 0x41;
        new_mods = MOD_BIT(KC_LSHIFT);
        register_key(new_code);
        add_mods(new_mods);
    /* } else if (code >= 0x01 && code <= 0x1A) {  // CONFLICTS WITH TAB / LF / CR
        // convert ASCII ctrl to Control + matrix pos 0x00 to 0x19
        new_code = code - 0x01;
        new_mods = MOD_BIT(KC_LCTRL);
        register_key(new_code);
        add_mods(new_mods); */
    } else if (code >= 0x30 && code <= 0x39) {
        // convert ASCII number line to matrix pos 0x1A to 0x23
        new_code = code - 0x16;
        register_key(new_code);
    } else if (code >= 0x21 && code <= 0x29) {
        // convert ASCII number line to Shift + matrix pos 0x1A to 0x23
        new_code = code - 0x06;
        new_mods = MOD_BIT(KC_LSHIFT);
        register_key(new_code);
        add_mods(new_mods);
    } else if (code >= 0xE0 && code <= 0xE9) {
        // convert F1 - F10 to matrix pos 0x24
        new_code = code - 0xBC;
        register_key(new_code);
    } else if (code >= 0xC0 && code <= 0xC9) {
        // convert Shift + F1 - F10 to Shift + matrix pos 0x24
        new_code = code - 0x9C;
        new_mods = MOD_BIT(KC_LSHIFT);
        register_key(new_code);
        add_mods(new_mods);
    } else if (code >= 0x80 && code <= 0x89) {
        // convert Shift + F1 - F10 to Shift + matrix pos 0x24
        new_code = code - 0x5C;
        new_mods = MOD_BIT(KC_LCTRL);
        register_key(new_code);
        add_mods(new_mods);
    } else {
        switch(code) {
            case 0x1B:  // ESC > 0x25
                new_code = 0x25;
                register_key(new_code);
                break;
            case 0x09: // TAB > 0x26
                new_code = 0x26;
                register_key(new_code);
                break;
            case 0x0A: // LINEFEED > 0x27
                new_code = 0x27;
                register_key(new_code);
                break;
            case 0x0D: // ENTER/CR > 0x28
                new_code = 0x28;
                register_key(new_code);
                break;
            case 0xFF: // BREAK > 0x29
                new_code = 0x29;
                register_key(new_code);
                break;
            case 0x20: // SPACE > 0x2A
                new_code = 0x2A;
                register_key(new_code);
                break;
            case 0xEA: // ENC LEFT
                new_code = 0x5A;
                register_key(new_code);
                break;
            case 0xEB: // ENC RIGHT
                new_code = 0x5B;
                register_key(new_code);
                break;
            case 0xCA: // ENC DOWN
                new_code = 0x5C;
                register_key(new_code);
                break;
            case 0xCB: // ENC UP
                new_code = 0x5D;
                register_key(new_code);
                break;
            case 0x8A: // ENC CTRL DOWN
                new_code = 0x5E;
                register_key(new_code);
                break;
            case 0x8B: // ENC CTRL UP
                new_code = 0x5F;
                register_key(new_code);
                break;
            default:
                // Reset Matrix
                for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
                break;
        }

    }

    if (code != 0 && debug_enable == true) {
        xprintf("\n>>> ASCII  : 0x%02X\n", code);
        xprintf("\n>>> MATRIX : 0x%02X\n", new_code);
    }

    matrix_scan_quantum();

    return 1;
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
        print("\n");
    }
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

inline
static void register_key(uint8_t key)
{
    uint8_t col, row;
    col = key&0x07;
    row = (key>>3)&0x0F;
    if (debug_enable == true) {
        xprintf("\n>>> col : 0x%02X row : 0x%02X", col, row);
    }
    matrix[row] |=  (1<<col);
}
