/*
Copyright 2019 Yiancar

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
#include <string.h>
#include "quantum.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"
#include "ch.h"
#include "hal.h"

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

volatile uint16_t porta_buffer = 0;
volatile uint16_t portb_buffer = 0;

static uint32_t switch_buffer = 0;

static void pal_cb(void* unused);

static void enable_input_events(void)
{
    palDisablePadEventI(GPIOA, 0);
    palDisablePadEventI(GPIOA, 1);
    palDisablePadEventI(GPIOA, 2);
    palDisablePadEventI(GPIOA, 9);
    palDisablePadEventI(GPIOA, 10);
    palDisablePadEventI(GPIOB, 12);
    palDisablePadEventI(GPIOB, 13);
    palDisablePadEventI(GPIOB, 14);
    palDisablePadEventI(GPIOB, 15);

    palEnablePadEventI(GPIOA, 0, PAL_EVENT_MODE_FALLING_EDGE);
    palEnablePadEventI(GPIOA, 1, PAL_EVENT_MODE_FALLING_EDGE);
    palEnablePadEventI(GPIOA, 2, PAL_EVENT_MODE_FALLING_EDGE);
    palEnablePadEventI(GPIOA, 9, PAL_EVENT_MODE_FALLING_EDGE);
    palEnablePadEventI(GPIOA, 10, PAL_EVENT_MODE_FALLING_EDGE);
    palEnablePadEventI(GPIOB, 12, PAL_EVENT_MODE_FALLING_EDGE);
    palEnablePadEventI(GPIOB, 13, PAL_EVENT_MODE_FALLING_EDGE);
    palEnablePadEventI(GPIOB, 14, PAL_EVENT_MODE_FALLING_EDGE);
    palEnablePadEventI(GPIOB, 15, PAL_EVENT_MODE_FALLING_EDGE);

    palSetPadCallbackI(GPIOA, 0, &pal_cb, 0);
    palSetPadCallbackI(GPIOA, 1, &pal_cb, 0);
    palSetPadCallbackI(GPIOA, 2, &pal_cb, 0);
    palSetPadCallbackI(GPIOA, 9, &pal_cb, 0);
    palSetPadCallbackI(GPIOA, 10, &pal_cb, 0);
    palSetPadCallbackI(GPIOB, 12, &pal_cb, 0);
    palSetPadCallbackI(GPIOB, 13, &pal_cb, 0);
    palSetPadCallbackI(GPIOB, 14, &pal_cb, 0);
    palSetPadCallbackI(GPIOB, 15, &pal_cb, 0);
}

// Trigger on negative edge of any of the sense lines.
static void pal_cb(void* unused) {

    (void)unused;
    chSysLockFromISR();
    porta_buffer = palReadPort(GPIOA);
    portb_buffer = palReadPort(GPIOB);
    //Disable further interrupts that might occur on same button press.
    enable_input_events();
    chSysUnlockFromISR();
}

void matrix_init(void) {
    //Set I/O as pull-up inputs to read states
    setPinInputHigh(A0);
    setPinInputHigh(A1);
    setPinInputHigh(A2);
    setPinInputHigh(A3);
    setPinInputHigh(A4);
    setPinInputHigh(A5);
    setPinInputHigh(A6);
    setPinInputHigh(A7);
    setPinInputHigh(A8);
    setPinInputHigh(A9);
    setPinInputHigh(A10);
    setPinInputHigh(B3);
    setPinInputHigh(B4);
    setPinInputHigh(B5);
    setPinInputHigh(B6);
    setPinInputHigh(B7);
    setPinInputHigh(B8);
    setPinInputHigh(B9);
    setPinInputHigh(B11);
    setPinInputHigh(B12);
    setPinInputHigh(B13);
    setPinInputHigh(B14);
    setPinInputHigh(B15);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    matrix_init_quantum();

    osalSysLock();
    enable_input_events();
    osalSysUnlock();
}

uint8_t matrix_scan(void) {
    switch_buffer = ((uint32_t)(porta_buffer & 0x7FF)) | ((uint32_t)(portb_buffer & 0x3F8) << 8);

    switch (switch_buffer) {
        case 0x1134E: matrix[0] = 0x01; break;
        case 0x3774D: matrix[0] = 0x02; break;
        case 0x10BCC: matrix[0] = 0x04; break;
        case 0x16B4B: matrix[0] = 0x08; break;
        case 0x167CA: matrix[0] = 0x10; break;
        case 0x35FC9: matrix[0] = 0x20; break;
        case 0x15B48: matrix[0] = 0x40; break;
        case 0x28347: matrix[0] = 0x80; break;
        case 0x173C6: matrix[0] = 0x100; break;
        case 0x143CF: matrix[0] = 0x200; break;
        case 0x3FDC5: matrix[0] = 0x400; break;
        case 0x3FD21: matrix[0] = 0x800; break;
        case 0x3FD77: matrix[0] = 0x1000; break;
        case 0x3FD72: matrix[0] = 0x2000; break;
        //Special pin
        case 0x3E7FA: matrix[0] = 0x8000; break;
        case 0x183EE: matrix[0] = 0x10000; break;
        case 0x197F3: matrix[0] = 0x20000; break;
        case 0x1AB7E: matrix[0] = 0x40000; break;

        case 0x107C3: matrix[1] = 0x01; break;
        case 0x3FD2E: matrix[1] = 0x02; break;
        case 0x3FD28: matrix[1] = 0x04; break;
        case 0x3FD3A: matrix[1] = 0x08; break;
        case 0x3FD2D: matrix[1] = 0x10; break;
        case 0x3FD2B: matrix[1] = 0x20; break;
        case 0x3FDA5: matrix[1] = 0x40; break;
        case 0x3FDAA: matrix[1] = 0x80; break;
        case 0x3FD36: matrix[1] = 0x100; break;
        case 0x3FD30: matrix[1] = 0x200; break;
        case 0x3FDAF: matrix[1] = 0x400; break;
        case 0x3FD22: matrix[1] = 0x800; break;
        case 0x157D4: matrix[1] = 0x1000; break;
        //Does not exist in matrix
        //Special pin
        case 0x1C778: matrix[1] = 0x8000; break;
        case 0x387ED: matrix[1] = 0x10000; break;
        case 0x19B74: matrix[1] = 0x20000; break;
        case 0x3FD7D: matrix[1] = 0x40000; break;

        //Special pin
        case 0x3FDBE: matrix[2] = 0x02; break;
        case 0x3FDAC: matrix[2] = 0x04; break;
        case 0x3FDBB: matrix[2] = 0x08; break;
        case 0x3FD39: matrix[2] = 0x10; break;
        case 0x3FDB8: matrix[2] = 0x20; break;
        case 0x3FDB7: matrix[2] = 0x40; break;
        case 0x3FD35: matrix[2] = 0x80; break;
        case 0x3FDB4: matrix[2] = 0x100; break;
        case 0x3FD33: matrix[2] = 0x200; break;
        case 0x3FDA3: matrix[2] = 0x400; break;
        case 0x3FD24: matrix[2] = 0x800; break;
        case 0x0FFDB: matrix[2] = 0x1000; break;
        case 0x3FDF5: matrix[2] = 0x2000; break;
        case 0x3FDFF: matrix[2] = 0x4000; break;
        case 0x3C3E4: matrix[2] = 0x8000; break;
        case 0x38B6C: matrix[2] = 0x10000; break;
        case 0x39FF6: matrix[2] = 0x20000; break;
        case 0x3FDFC: matrix[2] = 0x40000; break;

        //Special pin
        case 0x3FDA6: matrix[3] = 0x02; break;
        case 0x3FD27: matrix[3] = 0x04; break;
        case 0x3FD3C: matrix[3] = 0x08; break;
        case 0x3FDA9: matrix[3] = 0x10; break;
        case 0x3FDBD: matrix[3] = 0x20; break;
        case 0x3FDB1: matrix[3] = 0x40; break;
        case 0x3FDB2: matrix[3] = 0x80; break;
        case 0x30353: matrix[3] = 0x100; break;
        case 0x37BD1: matrix[3] = 0x200; break;
        case 0x363D2: matrix[3] = 0x400; break;
        case 0x3FD5F: matrix[3] = 0x800; break;
        //Does not exist in matrix
        //Does not exist in matrix
        //Special pin
        case 0x1BF00: matrix[3] = 0x8000; break;
        case 0x18FEB: matrix[3] = 0x10000; break;
        case 0x3FF69: matrix[3] = 0x20000; break;
        case 0x3A37B: matrix[3] = 0x40000; break;
        default:
                 if ((portb_buffer & 0x1000) == 0) { matrix[1] = 0x4000; break; }
                 if ((portb_buffer & 0x2000) == 0) { matrix[3] = 0x4000; break; }
                 if ((portb_buffer & 0x4000) == 0) { matrix[0] = 0x4000; break; }
                 if ((portb_buffer & 0x8000) == 0) { matrix[2] = 0x01; break; }
                 matrix[0] = 0x00;
                 matrix[1] = 0x00;
                 matrix[2] = 0x00;
                 matrix[3] = 0x00;
    }
    //Special case for Shift
    if (readPin(B11) == 0) { matrix[3] |= 0x01; }

    porta_buffer = 65535;
    portb_buffer = 65535;

    matrix_scan_quantum();
    return 1;
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{

}

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

