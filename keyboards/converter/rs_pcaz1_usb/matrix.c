/*
Copyright 2021 Kamel Makhloufi <melkalehun@gmail.com>

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

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

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
    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;

    serial_init();

    // Wait a bit for serial to be initialized
    _delay_ms(500);

    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    matrix_init_quantum();
    return;
}

uint8_t matrix_scan(void)
{
    bool matrix_has_changed = false;

    uint8_t code = 0;
    uint8_t new_code = 0;
    uint8_t new_mods = 0;
    uint8_t saved_mods = get_mods();
    del_mods(saved_mods);

    code = serial_recv();

    // Alpha characters
    if (code >= 0x61 && code <= 0x7A) {
        // convert ASCII min to matrix pos 0x00 to 0x19
        new_code = code - 0x61;
    } else if (code >= 0x41 && code <= 0x5A) {
        // convert ASCII maj to Shift + matrix pos 0x00 to 0x19
        new_code = code - 0x41;
        new_mods = MOD_BIT(KC_LSHIFT);
    } else if (code >= 0x01 && code <= 0x1A
                && code != 0x09 && code != 0x0A && code != 0x0D ) {  // CONFLICTS WITH TAB / LF / CR, so no ctrl+I, ctrl+J, ctrl+M
        // convert ASCII ctrl to Control + matrix pos 0x00 to 0x19
        new_code = code - 0x01;
        new_mods = MOD_BIT(CTRL_MOD);
    } else if (code >= 0x30 && code <= 0x39) {    // Number line
        // convert ASCII number line to matrix pos 0x1A to 0x23
        new_code = code - 0x16;
    } else if (code >= 0x21 && code <= 0x29) {
        // convert ASCII number line to Shift + matrix pos 0x1A to 0x23
        new_code = code - 0x06;
        new_mods = MOD_BIT(KC_LSHIFT);
    } else if (code >= 0xE0 && code <= 0xE9) {    // Function keys
        // convert F1 - F10 to matrix pos 0x24 - 0x2D
        new_code = code - 0xBC;
    } else if (code >= 0xC0 && code <= 0xC9) {
        // convert Shift + F1 - F10 to Shift + matrix pos 0x24 - 0x2D
        new_code = code - 0x9C;
        new_mods = MOD_BIT(KC_LSHIFT);
    } else if (code >= 0x80 && code <= 0x89) {
        // convert Ctrl + F1 - F10 to Ctrl + matrix pos 0x24 - 0x2D
        new_code = code - 0x5C;
        new_mods = MOD_BIT(CTRL_MOD);
    } else if (code >= 0xB0 && code <= 0xB9) {    // Numpad
        // convert np0 - np9 to matrix pos 0x40 - 0x49
        new_code = code - 0x70;
    } else if (code >= 0x30 && code <= 0x39) { // Shift + np0 - np9 = number line
    //     // convert Shift + np0 - np9 to Shift + matrix pos 0x40 - 0x49
    //     new_code = code + 0x10;
    //     new_mods = MOD_BIT(KC_LSHIFT);
    } else if (code >= 0xF0 && code <= 0xF9) {
        // convert Ctrl + np0 - np9 to Ctrl + matrix pos 0x40 - 0x49
        new_code = code - 0xB0;
        new_mods = MOD_BIT(CTRL_MOD);
    } else {
        switch(code) {
            case 0x1B:  // ESC
                new_code = 0x2E;
                break;
            case 0x09: // TAB
                new_code = 0x2F;
                break;
            case 0x0A: // LINEFEED
                new_code = 0x30;
                break;
            case 0x0D: // ENTER/CR
                new_code = 0x31;
                break;
            case 0xFF: // BREAK
                new_code = 0x32;
                break;
            case 0x20: // SPACE
                new_code = 0x33;
                break;

            case 0x7F: // DEL
                new_code = 0x34;
                break;
            case 0x5F: // Shift+DEL
                new_code = 0x34;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;
            case 0x1F: // Ctrl+DEL
                new_code = 0x34;
                new_mods = MOD_BIT(CTRL_MOD);
                break;

            case 0x2D: // Minus
                new_code = 0x35;
                break;
            case 0x3D: // Shift+Minus
                new_code = 0x35;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;

            case 0x5E: // ^
                new_code = 0x36;
                break;
            case 0x7E: // Shift+^
                new_code = 0x36;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;
            case 0x1E: // Ctrl+^
                new_code = 0x36;
                new_mods = MOD_BIT(CTRL_MOD);
                break;

            case 0x5C: // Slash
                new_code = 0x37;
                break;
            case 0x7C: // Shift+Slash
                new_code = 0x37;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;
            case 0x1C: // Ctrl+Slash
                new_code = 0x37;
                new_mods = MOD_BIT(CTRL_MOD);
                break;

            case 0x60: // @
                new_code = 0x38;
                break;
            case 0x40: // Shift+@
                new_code = 0x38;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;

            case 0x5B: // [
                new_code = 0x39;
                break;
            case 0x7B: // Shift+[
                new_code = 0x39;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;
            // case 0x1B: // Ctrl+[ > Same as escape...
            //     new_code = 0x39;
            //     new_mods = MOD_BIT(CTRL_MOD);
            //     break;

            case 0x5D: // ]
                new_code = 0x3A;
                break;
            case 0x7D: // Shift+]
                new_code = 0x3A;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;
            case 0x1D: // Ctrl+]
                new_code = 0x3A;
                new_mods = MOD_BIT(CTRL_MOD);
                break;

            case 0x3B: // ; > 0x32
                new_code = 0x3B;
                break;
            case 0x2B: // Shift+; > 0x32 + Shift
                new_code = 0x3B;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;

            case 0x3A: // : > 0x33
                new_code = 0x3C;
                break;
            case 0x2A: // Shift+: > 0x33 + Shift
                new_code = 0x3C;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;

            case 0x2C: // ,
                new_code = 0x3D;
                break;
            case 0x3C: // Shift+,
                new_code = 0x3D;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;

            case 0x2E: // .
                new_code = 0x3E;
                break;
            case 0x3E: // Shift+.
                new_code = 0x3E;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;

            case 0x2F: // /
                new_code = 0x3F;
                break;
            case 0x3F: // Shift+/
                new_code = 0x3F;
                new_mods = MOD_BIT(KC_LSHIFT);
                break;

            case 0xAE: // npdot
                new_code = 0x4E;
                break;
            // case 0x2E: // Shift+npdot >> Same as dot
            //     new_code = 0x40;
            //     new_mods = MOD_BIT(KC_LSHIFT);
            //     break;
            case 0xFB: // Ctrl+npdot
                new_code = 0x4E;
                new_mods = MOD_BIT(CTRL_MOD);
                break;

            case 0xAD: // np-
                new_code = 0x4F;
                break;
            // case 0x2D: // Shift+np- >> Same as number line minus
            //     new_code = 0x40;
            //     new_mods = MOD_BIT(KC_LSHIFT);
            //     break;
            case 0xFA: // Ctrl+np-
                new_code = 0x4F;
                new_mods = MOD_BIT(CTRL_MOD);
                break;

            case 0xEA: // ENC LEFT > 0x5A
                new_code = 0x5A;
                break;
            case 0xEB: // ENC RIGHT > 0x5B
                new_code = 0x5B;
                break;
            case 0xCA: // ENC DOWN > 0x5C
                new_code = 0x5C;
                break;
            case 0xCB: // ENC UP > 0x5D
                new_code = 0x5D;
                break;
            case 0x8A: // ENC CTRL DOWN > 0x5E
                new_code = 0x5E;
                break;
            case 0x8B: // ENC CTRL UP > 0x5F
                new_code = 0x5F;
                break;
            default:
                // No key pressed, reset matrix
                for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
                break;
        }

    }

    if (code != 0) {
        matrix_has_changed = true;
        register_key(new_code);
        add_mods(new_mods);
        xprintf(">>> ASCII  : 0x%02X\n", code);
        xprintf(">>> MATRIX : 0x%02X\n", new_code);
    }

    matrix_scan_quantum();

    return matrix_has_changed;
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
    matrix[row] |=  (1<<col);

    xprintf(">>> col : 0x%02X row : 0x%02X\n", col, row);
}
