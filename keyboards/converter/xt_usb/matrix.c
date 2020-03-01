/*
Copyright 2011 Jun Wako <wakojun@gmail.com>
Copyright 2016 Ethan Apodaca <papodaca@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "print.h"
#include "util.h"
#include "debug.h"
#include "xt.h"
#include "matrix.h"


static void matrix_make(uint8_t code);
static void matrix_break(uint8_t code);

static uint8_t matrix[MATRIX_ROWS];
#define ROW(code)      (code>>3)
#define COL(code)      (code&0x07)

__attribute__ ((weak))
void matrix_init_kb(void) {
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void)
{
    debug_enable = true;
    xt_host_init();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    matrix_init_quantum();
}

// convert E0-escaped codes into unused area
static uint8_t move_e0code(uint8_t code) {
    switch(code) {
        // Original IBM XT keyboard has these keys
        case 0x37: return 0x54; // Print Screen
        case 0x46: return 0x55; // Ctrl + Pause
        case 0x1C: return 0x6F; // Keypad Enter
        case 0x35: return 0x7F; // Keypad /

        // Any XT keyobard with these keys?
        // http://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/translate.pdf
        // https://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/scancode.doc
        case 0x5B: return 0x5A; // Left  GUI
        case 0x5C: return 0x5B; // Right GUI
        case 0x5D: return 0x5C; // Application
        case 0x5E: return 0x5D; // Power(not used)
        case 0x5F: return 0x5E; // Sleep(not used)
        case 0x63: return 0x5F; // Wake (not used)
        case 0x48: return 0x60; // Up
        case 0x4B: return 0x61; // Left
        case 0x50: return 0x62; // Down
        case 0x4D: return 0x63; // Right
        case 0x52: return 0x71; // Insert
        case 0x53: return 0x72; // Delete
        case 0x47: return 0x74; // Home
        case 0x4F: return 0x75; // End
        case 0x49: return 0x77; // Home
        case 0x51: return 0x78; // End
        case 0x1D: return 0x7A; // Right Ctrl
        case 0x38: return 0x7C; // Right Alt
    }
    return 0x00;
}

uint8_t matrix_scan(void)
{
    static enum {
        XT_STATE_INIT,
        XT_STATE_E0,
        // Pause: E1 1D 45, E1 9D C5
        XT_STATE_E1,
        XT_STATE_E1_1D,
        XT_STATE_E1_9D,
    } state = XT_STATE_INIT;

    uint8_t code = xt_host_recv();
    if (!code) return 0;
    xprintf("%02X ", code);
    switch (state) {
        case XT_STATE_INIT:
            switch (code) {
                case 0xE0:
                    state = XT_STATE_E0;
                    break;
                case 0xE1:
                    state = XT_STATE_E1;
                    break;
                default:
                    if (code < 0x80)
                        matrix_make(code);
                    else
                        matrix_break(code & 0x7F);
                    break;
            }
            break;
        case XT_STATE_E0:
            switch (code) {
                case 0x2A:
                case 0xAA:
                case 0x36:
                case 0xB6:
                    //ignore fake shift
                    state = XT_STATE_INIT;
                    break;
                default:
                    if (code < 0x80)
                        matrix_make(move_e0code(code));
                    else
                        matrix_break(move_e0code(code & 0x7F));
                    state = XT_STATE_INIT;
                    break;
            }
            break;
        case XT_STATE_E1:
            switch (code) {
                case 0x1D:
                    state = XT_STATE_E1_1D;
                    break;
                case 0x9D:
                    state = XT_STATE_E1_9D;
                    break;
                default:
                    state = XT_STATE_INIT;
                    break;
            }
            break;
        case XT_STATE_E1_1D:
            switch (code) {
                case 0x45:
                    matrix_make(0x55);
                    break;
                default:
                    state = XT_STATE_INIT;
                    break;
            }
            break;
        case XT_STATE_E1_9D:
            switch (code) {
                case 0x45:
                    matrix_break(0x55);
                    break;
                default:
                    state = XT_STATE_INIT;
                    break;
            }
            break;
        default:
            state = XT_STATE_INIT;
    }
    matrix_scan_quantum();
    return 1;
}

inline
uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

inline
static void matrix_make(uint8_t code)
{
    if (!matrix_is_on(ROW(code), COL(code))) {
        matrix[ROW(code)] |= 1<<COL(code);
    }
}

inline
static void matrix_break(uint8_t code)
{
    if (matrix_is_on(ROW(code), COL(code))) {
        matrix[ROW(code)] &= ~(1<<COL(code));
    }
}

void matrix_clear(void)
{
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix_get_row(row) & (1<<col));
}

#if (MATRIX_COLS <= 8)
#    define print_matrix_header()  print("\nr/c 01234567\n")
#    define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#endif

void matrix_print(void)
{
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

/*
XT Scancodes
============
- http://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/translate.pdf
- https://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/scancode.doc

01-53: Normal codes used in original XT keyboard
54-7F: Not used in original XT keyboard

	0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
    50  -   -   -   -   *   *   x   x   x   x   *   *   *   o   o   o
    60  *   *   *   *   x   x   x   x   x   x   x   x   x   x   x   *
    70  x   *   *   x   *   *   x   *   *   x   *   x   *   x   x   *

-: codes existed in original XT keyboard
*: E0-escaped codes converted into unused code area(internal use in TMK)
x: Non-espcaped codes(not used in real keyboards probably, for CodeSet2-CodeSet1 translation purpose)
o: reserved

Usage in TMK:

    00  (reserved) DO NOT USE
    54  PrintScr*
    55  Pause*
    56  Euro2
    57  F11
    58  F12
    59  Keypad =
    5A  LGUI*
    5B  RGUI*
    5C  APP*
    5D  (reserved)
    5E  (reserved)
    5F  (reserved)
    60  cursor*
    61  cursor*
    62  cursor*
    63  cursor*
    64  F13
    65  F14
    66  F15
    67  F16
    68  F17
    69  F18
    6A  F19
    6B  F20
    6C  F21
    6D  F22
    6E  F23
    6F  Keypad Enter*
    70  KANA
    71  nav*
    72  nav*
    73  RO
    74  nav*
    75  nav*
    76  F24
    77  nav*
    78  nav*
    79  HENKAN
    7A  RCTL*
    7B  MUHENKAN
    7C  RALT*
    7D  JPY
    7E  Keypad ,
    7F  Keypad / *

*/
