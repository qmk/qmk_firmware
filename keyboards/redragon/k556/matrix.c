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
matrix_row_t last_matrix[MATRIX_ROWS] = {0};  // raw values
matrix_row_t matrix[MATRIX_ROWS]; //debounced values

static bool matrix_changed = false;
static uint8_t current_row = 0;

extern volatile LED_TYPE led_state[DRIVER_LED_TOTAL];

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}

static void init_pins(void) {

    //  Unselect ROWs
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInput(row_pins[x]);
        writePinHigh(row_pins[x]);
    }

    // Unselect COLs
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinOutput(col_pins[x]);
        writePinHigh(col_pins[x]);
    }

   for (uint8_t x = 0; x < LED_MATRIX_ROWS_HW; x++) {
        setPinOutput(led_row_pins[x]);
        writePinHigh(led_row_pins[x]);
   }
}

void matrix_init(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    for (uint8_t i = 0; i < LED_MATRIX_ROWS; i++) {
        row_ofsts[i] = i * LED_MATRIX_COLS;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();

    // Enable Timer Clock
    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;

    // PFPA - Map all PWM outputs to their PWM A pins
    SN_PFPA->CT16B1 = 0x00000000;

    // Enable PWM function, IOs and select the PWM modes
    // Enable PWM0-PWM3, PWM8-PWM20 function (except PWM10)
    SN_CT16B1->PWMENB   =   (mskCT16_PWM0EN_EN  \
                            |mskCT16_PWM1EN_EN  \
                            |mskCT16_PWM2EN_EN  \
                            |mskCT16_PWM3EN_EN  \
                            |mskCT16_PWM4EN_EN  \
                            |mskCT16_PWM5EN_EN  \
                            |mskCT16_PWM6EN_EN  \
                            |mskCT16_PWM7EN_EN  \
                            |mskCT16_PWM8EN_EN  \
                            |mskCT16_PWM9EN_EN  \
                            |mskCT16_PWM10EN_EN \
                            |mskCT16_PWM11EN_EN \
                            |mskCT16_PWM12EN_EN \
                            |mskCT16_PWM13EN_EN \
                            |mskCT16_PWM14EN_EN \
                            |mskCT16_PWM16EN_EN \
                            |mskCT16_PWM17EN_EN \
                            |mskCT16_PWM18EN_EN \
                            |mskCT16_PWM19EN_EN \
                            |mskCT16_PWM20EN_EN \
                            |mskCT16_PWM21EN_EN);

    // Enable PWM0-PWM3, PWM8-PWM20 IO (except PWM10)
    SN_CT16B1->PWMIOENB =   (mskCT16_PWM0EN_EN  \
                            |mskCT16_PWM1EN_EN  \
                            |mskCT16_PWM2EN_EN  \
                            |mskCT16_PWM3EN_EN  \
                            |mskCT16_PWM4EN_EN  \
                            |mskCT16_PWM5EN_EN  \
                            |mskCT16_PWM6EN_EN  \
                            |mskCT16_PWM7EN_EN  \
                            |mskCT16_PWM8EN_EN  \
                            |mskCT16_PWM9EN_EN  \
                            |mskCT16_PWM10EN_EN \
                            |mskCT16_PWM11EN_EN \
                            |mskCT16_PWM12EN_EN \
                            |mskCT16_PWM13EN_EN \
                            |mskCT16_PWM14EN_EN \
                            |mskCT16_PWM16EN_EN \
                            |mskCT16_PWM17EN_EN \
                            |mskCT16_PWM18EN_EN \
                            |mskCT16_PWM19EN_EN \
                            |mskCT16_PWM20EN_EN \
                            |mskCT16_PWM21EN_EN);

    // Set match interrupts and TC rest
    SN_CT16B1->MCTRL3 = (mskCT16_MR22IE_EN | mskCT16_MR22STOP_EN);

    // COL match register
    SN_CT16B1->MR22 = 0xFF;

    // Set prescale value
    SN_CT16B1->PRE = 0x10;

    //Set CT16B1 as the up-counting mode.
	SN_CT16B1->TMRCTRL = (mskCT16_CRST);

    // Wait until timer reset done.
    while (SN_CT16B1->TMRCTRL & mskCT16_CRST);

    // Let TC start counting.
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;

    NVIC_ClearPendingIRQ(CT16B1_IRQn);
    nvicEnableVector(CT16B1_IRQn, 0);
}

uint8_t matrix_scan(void) {
    matrix_changed = false;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
            // Determine if the matrix changed state
            if ((last_matrix[row_index] != raw_matrix[row_index])) {
                matrix_changed         = true;
                last_matrix[row_index] = raw_matrix[row_index];
            }
        }
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, matrix_changed);

    matrix_scan_quantum();

    return matrix_changed;
}

uint8_t hw_row_to_matrix_row[18] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5 };
/**
 * @brief   CT16B1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(SN32_CT16B1_HANDLER) {

    chSysDisable();

    OSAL_IRQ_PROLOGUE();

        // Disable PWM outputs on column pins
        SN_CT16B1->PWMIOENB = 0;

        SN_CT16B1->IC = mskCT16_MR22IC; // Clear match interrupt status

        // Turn the selected row off
        writePinLow(led_row_pins[current_row]);

        // Read the key matrix
        for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
            // Enable the column
            writePinLow(col_pins[col_index]);

            for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
                // Check row pin state
                if (readPin(row_pins[row_index]) == 0) {
                    // Pin LO, set col bit
                    raw_matrix[row_index] |= (MATRIX_ROW_SHIFTER << col_index);
                } else {
                    // Pin HI, clear col bit
                    raw_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << col_index);
                }
            }

            // Disable the column
            writePinHigh(col_pins[col_index]);
        }

        // Turn the next row on
        current_row = (current_row + 1) % LED_MATRIX_ROWS_HW;

        uint8_t row_idx = hw_row_to_matrix_row[current_row];
        uint16_t row_ofst = row_ofsts[row_idx];

        //Set CT16B1 as the up-counting mode.
        SN_CT16B1->TMRCTRL = (mskCT16_CRST);

        // Wait until timer reset done.
        while (SN_CT16B1->TMRCTRL & mskCT16_CRST);

        if(current_row % 3 == 0)
        {
            SN_CT16B1->MR0  = led_state[row_ofst + 0 ].r;
            SN_CT16B1->MR1  = led_state[row_ofst + 1 ].r;
            SN_CT16B1->MR2  = led_state[row_ofst + 2 ].r;
            SN_CT16B1->MR3  = led_state[row_ofst + 3 ].r;
            SN_CT16B1->MR4  = led_state[row_ofst + 4 ].r;
            SN_CT16B1->MR5  = led_state[row_ofst + 5 ].r;
            SN_CT16B1->MR6  = led_state[row_ofst + 6 ].r;
            SN_CT16B1->MR7  = led_state[row_ofst + 7 ].r;
            SN_CT16B1->MR8  = led_state[row_ofst + 8 ].r;
            SN_CT16B1->MR9  = led_state[row_ofst + 9 ].r;
            SN_CT16B1->MR10 = led_state[row_ofst + 10].r;
            SN_CT16B1->MR11 = led_state[row_ofst + 11].r;
            SN_CT16B1->MR12 = led_state[row_ofst + 12].r;
            SN_CT16B1->MR13 = led_state[row_ofst + 13].r;
            SN_CT16B1->MR14 = led_state[row_ofst + 14].r;
            SN_CT16B1->MR16 = led_state[row_ofst + 15].r;
            SN_CT16B1->MR17 = led_state[row_ofst + 16].r;
            SN_CT16B1->MR18 = led_state[row_ofst + 17].r;
            SN_CT16B1->MR19 = led_state[row_ofst + 18].r;
            SN_CT16B1->MR20 = led_state[row_ofst + 19].r;
            SN_CT16B1->MR21 = led_state[row_ofst + 20].r;
        }

        if(current_row % 3 == 1)
        {
            SN_CT16B1->MR0  = led_state[row_ofst + 0 ].b;
            SN_CT16B1->MR1  = led_state[row_ofst + 1 ].b;
            SN_CT16B1->MR2  = led_state[row_ofst + 2 ].b;
            SN_CT16B1->MR3  = led_state[row_ofst + 3 ].b;
            SN_CT16B1->MR4  = led_state[row_ofst + 4 ].b;
            SN_CT16B1->MR5  = led_state[row_ofst + 5 ].b;
            SN_CT16B1->MR6  = led_state[row_ofst + 6 ].b;
            SN_CT16B1->MR7  = led_state[row_ofst + 7 ].b;
            SN_CT16B1->MR8  = led_state[row_ofst + 8 ].b;
            SN_CT16B1->MR9  = led_state[row_ofst + 9 ].b;
            SN_CT16B1->MR10 = led_state[row_ofst + 10].b;
            SN_CT16B1->MR11 = led_state[row_ofst + 11].b;
            SN_CT16B1->MR12 = led_state[row_ofst + 12].b;
            SN_CT16B1->MR13 = led_state[row_ofst + 13].b;
            SN_CT16B1->MR14 = led_state[row_ofst + 14].b;
            SN_CT16B1->MR16 = led_state[row_ofst + 15].b;
            SN_CT16B1->MR17 = led_state[row_ofst + 16].b;
            SN_CT16B1->MR18 = led_state[row_ofst + 17].b;
            SN_CT16B1->MR19 = led_state[row_ofst + 18].b;
            SN_CT16B1->MR20 = led_state[row_ofst + 19].b;
            SN_CT16B1->MR21 = led_state[row_ofst + 20].b;
        }

        if(current_row % 3 == 2)
        {
            SN_CT16B1->MR0  = led_state[row_ofst + 0 ].g;
            SN_CT16B1->MR1  = led_state[row_ofst + 1 ].g;
            SN_CT16B1->MR2  = led_state[row_ofst + 2 ].g;
            SN_CT16B1->MR3  = led_state[row_ofst + 3 ].g;
            SN_CT16B1->MR4  = led_state[row_ofst + 4 ].g;
            SN_CT16B1->MR5  = led_state[row_ofst + 5 ].g;
            SN_CT16B1->MR6  = led_state[row_ofst + 6 ].g;
            SN_CT16B1->MR7  = led_state[row_ofst + 7 ].g;
            SN_CT16B1->MR8  = led_state[row_ofst + 8 ].g;
            SN_CT16B1->MR9  = led_state[row_ofst + 9 ].g;
            SN_CT16B1->MR10 = led_state[row_ofst + 10].g;
            SN_CT16B1->MR11 = led_state[row_ofst + 11].g;
            SN_CT16B1->MR12 = led_state[row_ofst + 12].g;
            SN_CT16B1->MR13 = led_state[row_ofst + 13].g;
            SN_CT16B1->MR14 = led_state[row_ofst + 14].g;
            SN_CT16B1->MR16 = led_state[row_ofst + 15].g;
            SN_CT16B1->MR17 = led_state[row_ofst + 16].g;
            SN_CT16B1->MR18 = led_state[row_ofst + 17].g;
            SN_CT16B1->MR19 = led_state[row_ofst + 18].g;
            SN_CT16B1->MR20 = led_state[row_ofst + 19].g;
            SN_CT16B1->MR21 = led_state[row_ofst + 20].g;
        }

        // Enable PWM outputs on column pins
        SN_CT16B1->PWMIOENB = 0;

        if(SN_CT16B1->MR0 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM0EN_EN;
        }
        if(SN_CT16B1->MR1 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM1EN_EN;
        }
        if(SN_CT16B1->MR2 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM2EN_EN;
        }
        if(SN_CT16B1->MR3 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM3EN_EN;
        }
        if(SN_CT16B1->MR4 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM4EN_EN;
        }
        if(SN_CT16B1->MR5 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM5EN_EN;
        }
        if(SN_CT16B1->MR6 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM6EN_EN;
        }
        if(SN_CT16B1->MR6 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM6EN_EN;
        }
        if(SN_CT16B1->MR7 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM7EN_EN;
        }
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
        if(SN_CT16B1->MR10 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM10EN_EN;
        }
        if(SN_CT16B1->MR13 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM13EN_EN;
        }
        if(SN_CT16B1->MR14 > 0)
        {
            SN_CT16B1->PWMIOENB |= mskCT16_PWM14EN_EN;
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

    // Set match interrupts and TC rest
    SN_CT16B1->MCTRL3 = (mskCT16_MR22IE_EN | mskCT16_MR22STOP_EN);

    // COL match register
    SN_CT16B1->MR22 = 0xFF;

    // Set prescale value
    SN_CT16B1->PRE = 0x10;

    writePinHigh(led_row_pins[current_row]);

    // Let TC start counting.
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;

    chSysEnable();

    OSAL_IRQ_EPILOGUE();
}
