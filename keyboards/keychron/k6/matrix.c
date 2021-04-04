/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

Ported to QMK by Stephen Peery <https://github.com/smp4488/>
*/

#include <stdint.h>
#include <stdbool.h>
#include <SN32F240B.h>
#include "ch.h"
#include "hal.h"
#include "CT16.h"

#include "color.h"
#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const pin_t led_row_pins[LED_MATRIX_ROWS_HW] = LED_MATRIX_ROW_PINS;
static uint16_t row_ofsts[LED_MATRIX_ROWS];

matrix_row_t raw_matrix[MATRIX_ROWS]; //raw values
matrix_row_t matrix[MATRIX_ROWS];     //debounced values

#define INTERRUPT_SCAN
#ifdef INTERRUPT_SCAN
#define PRESCALE 0x10
#else
#define PRESCALE 0x02
#endif

#define MRCOUNT 0xFF

static uint8_t current_led_row = 0;

extern volatile LED_TYPE led_state[DRIVER_LED_TOTAL];

void sn32_wait_x10us(uint32_t n) {
    n *= 21;
    while (n--);
}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}

static void init_pins(void) {

    //  Unselect ROWs
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinOutput(row_pins[x]);
        writePinHigh(row_pins[x]);
    }

    // COLs: select keyswitches, turnoff LEDs
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInput(col_pins[x]);
        writePinHigh(col_pins[x]);
    }

    //turn LEDs off
    for (uint8_t x = 0; x < LED_MATRIX_ROWS_HW; x++) {
        setPinOutput(led_row_pins[x]);
        writePinLow(led_row_pins[x]);
   }
}

#ifndef INTERRUPT_SCAN
static void disable_rgb_matrix(void) {
    syssts_t sts = chSysGetStatusAndLockX();
    // Disable LED row output
    writePinLow(led_row_pins[current_led_row]);
    // Disable PWM outputs on column pins
    // Enable GPIO control on column pins
    SN_CT16B1->PWMIOENB = 0;
    CT16B1_NvicDisable();
    chSysRestoreStatusX(sts);
}
#endif

static void enable_rgb_matrix(void) {
#ifndef INTERRUPT_SCAN
    syssts_t sts = chSysGetStatusAndLockX();
#endif
    // Enable PWM outputs on column pins
    SN_CT16B1->PWMIOENB   = (mskCT16_PWM8IOEN_EN  \
                            |mskCT16_PWM9IOEN_EN  \
                            |mskCT16_PWM10IOEN_EN \
                            |mskCT16_PWM11IOEN_EN \
                            |mskCT16_PWM12IOEN_EN \
                            |mskCT16_PWM13IOEN_EN \
                            |mskCT16_PWM14IOEN_EN \
                            |mskCT16_PWM15IOEN_EN \
                            |mskCT16_PWM16IOEN_EN \
                            |mskCT16_PWM17IOEN_EN \
                            |mskCT16_PWM18IOEN_EN \
                            |mskCT16_PWM19IOEN_EN \
                            |mskCT16_PWM20IOEN_EN \
                            |mskCT16_PWM21IOEN_EN \
                            |mskCT16_PWM22IOEN_EN \
                            |mskCT16_PWM23IOEN_EN);
    CT16B1_NvicEnable();
#ifndef INTERRUPT_SCAN
    chSysRestoreStatusX(sts);
#endif
}

static void init_rgb_matrix(void) {
    // Calculate the row offsets
    for (uint8_t i = 0; i < LED_MATRIX_ROWS; i++) {
        row_ofsts[i] = i * LED_MATRIX_COLS;
    }
    // Enable Timer Clock
    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;
    SN_PFPA->CT16B1 = 0x00000000;

    // Enable PWM function, IOs and select the PWM modes
    // Enable PWM8-23
    SN_CT16B1->PWMENB   =   (mskCT16_PWM8EN_EN  \
                            |mskCT16_PWM9EN_EN  \
                            |mskCT16_PWM10EN_EN \
                            |mskCT16_PWM11EN_EN \
                            |mskCT16_PWM12EN_EN \
                            |mskCT16_PWM13EN_EN \
                            |mskCT16_PWM14EN_EN \
                            |mskCT16_PWM15EN_EN \
                            |mskCT16_PWM16EN_EN \
                            |mskCT16_PWM17EN_EN \
                            |mskCT16_PWM18EN_EN \
                            |mskCT16_PWM19EN_EN \
                            |mskCT16_PWM20EN_EN \
                            |mskCT16_PWM21EN_EN \
                            |mskCT16_PWM22EN_EN \
                            |mskCT16_PWM23EN_EN);

    SN_CT16B1->MCTRL3 = (mskCT16_MR24IE_EN);
    SN_CT16B1->MCTRL3_b.MR24RST = 1;

    SN_CT16B1->MR24 = MRCOUNT;

    // Set prescale value
    //256 * 5 / 12Mhz PCLK = 0.1067 ms
    //256 * 17 / 12Mhz PCLK = 0.363 ms
    //256 * 33 / 12Mhz PCLK = 0.704 ms
    //256 * 65 / 12Mhz PCLK = 1.3867 ms
    //256 * 256 / 12Mhz PCLK = 5.4613 ms
    SN_CT16B1->PRE = PRESCALE;

    enable_rgb_matrix();

    //reset counter, wait till it is reset and start counting
    SN_CT16B1->TMRCTRL = (mskCT16_CRST);
    while (SN_CT16B1->TMRCTRL & mskCT16_CRST);
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;
}

#ifndef INTERRUPT_SCAN
static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];
    // Clear data in matrix row
    current_matrix[current_row] = 0;
    // Enable current matrix row
    writePinLow(row_pins[current_row]);
    // Wait to stabilize
    wait_us(10);

    // Read the key matrix
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
    	disable_rgb_matrix();
        // Enable the column
        writePinHigh(col_pins[col_index]);
        // Check col pin state
        if (readPin(col_pins[col_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[current_row] |= (MATRIX_ROW_SHIFTER << col_index);
        } else {
            // Pin HI, clear col bit
            current_matrix[current_row] &= ~(MATRIX_ROW_SHIFTER << col_index);
        }

        // Disable the column
        writePinLow(col_pins[col_index]);
        enable_rgb_matrix();
    }

    // Disable current matrix row
    writePinHigh(row_pins[current_row]);
    return (last_row_value != current_matrix[current_row]);
}
#endif

void matrix_init(void) {
    // Enable GPIO Clock
    SN_SYS1->AHBCLKEN_b.P0CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.P1CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.P2CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.P3CLKEN = 1;
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
    // initialize the rgb matrix
    init_rgb_matrix();
}

uint8_t matrix_scan(void) {
#ifdef INTERRUPT_SCAN
    //Same col pin control keyswitches and LEDs.
    //LED updates and matrix scan is done in the CT16 timer interrupt
    //This function can be interrupted by timer event which also updates raw_matrix
    //minimize chances for this occuring to a minimum to one assignment.
    //alternatively can disable interrupts.
    matrix_row_t buffer = 0;
#endif
    bool changed = false;

#ifdef INTERRUPT_SCAN
    //can try to disable/enable interupts to avoid contention between
    //matrix read here and update in interrupt
    //chSysDisable();
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        // this is the only point of contention between matrix scan and CT16 interrupt
        buffer = raw_matrix[i];
        // Determine if the matrix changed state
        if ((matrix[i] != buffer)) {
            changed   = true;
            matrix[i] = buffer;
        }
    }
    //chSysEnable();
#else
    // Set row, read cols
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        changed |= read_cols_on_row(raw_matrix, row);

    }
#endif
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
    matrix_scan_quantum();
    return (uint8_t)changed;
}

uint8_t hw_row_to_matrix_row[15] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4 };
/**
 * @brief   CT16B1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(SN32_CT16B1_HANDLER) {

    OSAL_IRQ_PROLOGUE();

    // Turn the selected LED row off
    writePinLow(led_row_pins[current_led_row]);
#ifdef INTERRUPT_SCAN
    SN_CT16B1->PWMIOENB = 0;
    uint8_t key_row = current_led_row / 3;
    if (current_led_row % 3 == 0){
        // Interrupt is generated 3 times for every row (R,G,B). Scan matrix only 1/3 of all interrupts
        // with current prescale it amounts roughly to 1.3867*3*5 = 4.1601ms*5 = 20.8005ms per row
        // with current prescale it amounts roughly to 0.704*3*5 = 2.112ms*5 = 10.56ms per row
        // with current prescale it amounts roughly to 0.363*3*5 = 1.088ms*5 = 5.44ms per row
        //already set in init
        //setPinOutput(row_pins[key_row]);
        writePinLow(row_pins[key_row]);
        for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
            // Enable the column
            writePinHigh(col_pins[col_index]);
            // would be good to have a few micros delay here before reading pin
            // Check row pin state
            if (readPin(col_pins[col_index]) == 0) {
                // Pin LO, set col bit
                raw_matrix[key_row] |= (MATRIX_ROW_SHIFTER << col_index);
            } else {
                // Pin HI, clear col bit
                raw_matrix[key_row] &= ~(MATRIX_ROW_SHIFTER << col_index);
            }
            // Disable the column for keyswitch, and this will enable COL for LED
            writePinLow(col_pins[col_index]);
        }
        //no need to change it here
        //setPinInput(row_pins[key_row]);
        writePinHigh(row_pins[key_row]);
    }
#endif
    // Turn the next row on
    current_led_row = (current_led_row + 1) % LED_MATRIX_ROWS_HW;

    uint8_t  row_idx  = hw_row_to_matrix_row[current_led_row];
    uint16_t row_ofst = row_ofsts[row_idx];

    if(current_led_row % 3 == 0)
    {
        SN_CT16B1->MR8  = led_state[row_ofst + 0 ].r;
        SN_CT16B1->MR9  = led_state[row_ofst + 1 ].r;
        SN_CT16B1->MR10 = led_state[row_ofst + 2 ].r;
        SN_CT16B1->MR11 = led_state[row_ofst + 3 ].r;
        SN_CT16B1->MR12 = led_state[row_ofst + 4 ].r;
        SN_CT16B1->MR13 = led_state[row_ofst + 5 ].r;
        SN_CT16B1->MR14 = led_state[row_ofst + 6 ].r;
        SN_CT16B1->MR15 = led_state[row_ofst + 7 ].r;
        SN_CT16B1->MR16 = led_state[row_ofst + 8 ].r;
        SN_CT16B1->MR17 = led_state[row_ofst + 9 ].r;
        SN_CT16B1->MR18 = led_state[row_ofst + 10].r;
        SN_CT16B1->MR19 = led_state[row_ofst + 11].r;
        SN_CT16B1->MR20 = led_state[row_ofst + 12].r;
        SN_CT16B1->MR21 = led_state[row_ofst + 13].r;
        SN_CT16B1->MR22 = led_state[row_ofst + 14].r;
        SN_CT16B1->MR23 = led_state[row_ofst + 15].r;
    }

    if(current_led_row % 3 == 1)
    {
        SN_CT16B1->MR8  = led_state[row_ofst + 0 ].b;
        SN_CT16B1->MR9  = led_state[row_ofst + 1 ].b;
        SN_CT16B1->MR10 = led_state[row_ofst + 2 ].b;
        SN_CT16B1->MR11 = led_state[row_ofst + 3 ].b;
        SN_CT16B1->MR12 = led_state[row_ofst + 4 ].b;
        SN_CT16B1->MR13 = led_state[row_ofst + 5 ].b;
        SN_CT16B1->MR14 = led_state[row_ofst + 6 ].b;
        SN_CT16B1->MR15 = led_state[row_ofst + 7 ].b;
        SN_CT16B1->MR16 = led_state[row_ofst + 8 ].b;
        SN_CT16B1->MR17 = led_state[row_ofst + 9 ].b;
        SN_CT16B1->MR18 = led_state[row_ofst + 10].b;
        SN_CT16B1->MR19 = led_state[row_ofst + 11].b;
        SN_CT16B1->MR20 = led_state[row_ofst + 12].b;
        SN_CT16B1->MR21 = led_state[row_ofst + 13].b;
        SN_CT16B1->MR22 = led_state[row_ofst + 14].b;
        SN_CT16B1->MR23 = led_state[row_ofst + 15].b;
    }

    if(current_led_row % 3 == 2)
    {
        SN_CT16B1->MR8  = led_state[row_ofst + 0 ].g;
        SN_CT16B1->MR9  = led_state[row_ofst + 1 ].g;
        SN_CT16B1->MR10 = led_state[row_ofst + 2 ].g;
        SN_CT16B1->MR11 = led_state[row_ofst + 3 ].g;
        SN_CT16B1->MR12 = led_state[row_ofst + 4 ].g;
        SN_CT16B1->MR13 = led_state[row_ofst + 5 ].g;
        SN_CT16B1->MR14 = led_state[row_ofst + 6 ].g;
        SN_CT16B1->MR15 = led_state[row_ofst + 7 ].g;
        SN_CT16B1->MR16 = led_state[row_ofst + 8 ].g;
        SN_CT16B1->MR17 = led_state[row_ofst + 9 ].g;
        SN_CT16B1->MR18 = led_state[row_ofst + 10].g;
        SN_CT16B1->MR19 = led_state[row_ofst + 11].g;
        SN_CT16B1->MR20 = led_state[row_ofst + 12].g;
        SN_CT16B1->MR21 = led_state[row_ofst + 13].g;
        SN_CT16B1->MR22 = led_state[row_ofst + 14].g;
        SN_CT16B1->MR23 = led_state[row_ofst + 15].g;
    }

#ifdef INTERRUPT_SCAN
    //Do not enable led at all if color is black.
    //that avoids mild glowing at 0 brightness
    if(SN_CT16B1->MR8 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM8EN_EN;
    }
    if(SN_CT16B1->MR9 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM9EN_EN;
    }
    if(SN_CT16B1->MR10 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM10EN_EN;
    }
    if(SN_CT16B1->MR11 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM11EN_EN;
    }
    if(SN_CT16B1->MR12 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM12EN_EN;
    }
    if(SN_CT16B1->MR13 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM13EN_EN;
    }
    if(SN_CT16B1->MR14 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM14EN_EN;
    }
    if(SN_CT16B1->MR15 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM15EN_EN;
    }
    if(SN_CT16B1->MR16 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM16EN_EN;
    }
    if(SN_CT16B1->MR17 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM17EN_EN;
    }
    if(SN_CT16B1->MR18 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM18EN_EN;
    }
    if(SN_CT16B1->MR19 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM19EN_EN;
    }
    if(SN_CT16B1->MR20 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM20EN_EN;
    }
    if(SN_CT16B1->MR21 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM21EN_EN;
    }
    if(SN_CT16B1->MR22 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM22EN_EN;
    }
    if(SN_CT16B1->MR23 > 0)
    {
        SN_CT16B1->PWMIOENB |= mskCT16_PWM23EN_EN;
    }
#endif
    writePinHigh(led_row_pins[current_led_row]);
    //reset counter, wait till it is reset, clear interrupt and start counting
    SN_CT16B1->TMRCTRL = (mskCT16_CRST);
    while (SN_CT16B1->TMRCTRL & mskCT16_CRST);
    SN_CT16B1->IC = SN_CT16B1->RIS;
    SN_CT16B1->TMRCTRL = CT16_CEN_EN;
    OSAL_IRQ_EPILOGUE();
}

void HardFault_Handler(void) {
    NVIC_SystemReset();
}
