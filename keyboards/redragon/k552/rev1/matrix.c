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
#include <SN32F240.h>
#include "ch.h"
#include "hal.h"
#include "CT16.h"
#include "CT32.h"

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

    // Enable Timer Clocks
    SN_SYS1->AHBCLKEN_b.CT16B0CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.CT16B2CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.CT32B0CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.CT32B1CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.CT32B2CLKEN = 1;

    // Set Timer Clock Prescalers
    SN_SYS1->APBCP0_b.CT16B0PRE = 0x00;
    SN_SYS1->APBCP0_b.CT16B1PRE = 0x00;
    SN_SYS1->APBCP1_b.CT16B2PRE = 0x00;
    SN_SYS1->APBCP0_b.CT32B0PRE = 0x00;
    SN_SYS1->APBCP0_b.CT32B1PRE = 0x00;
    SN_SYS1->APBCP0_b.CT32B2PRE = 0x00;

    // PFPA Timer Mapping
    // CT16B0   PWM0    P0.0        Col 0
    //          PWM1    P0.1        Col 1
    // CT16B1   PWM1    P1.3        Col 13
    //          PWM2    P0.15       Col 9
    // CT16B2   PWM0    P0.2        Col 2
    //          PWM1    P1.4        Col 14
    //          PWM2    P1.0        Col 10
    // CT32B0   PWM0    P0.4        Col 4
    //          PWM1    P1.11       Col 16
    //          PWM3    P1.2        Col 12
    // CT32B1   PWM1    P1.10       Col 15
    //          PWM2    P0.5        Col 5
    //          PWM3    P0.7        Col 7
    // CT32B2   PWM0    P1.1        Col 11
    //          PWM1    P0.14       Col 8
    //          PWM2    P0.3        Col 3
    //          PWM3    P0.6        Col 6
	SN_PFPA->CT16B0 = 0x00000;
    SN_PFPA->CT16B1 = 0x02330;
    SN_PFPA->CT16B2 = 0x02010;
    SN_PFPA->CT32B0 = 0x00410;
	SN_PFPA->CT32B1 = 0x21300;
    SN_PFPA->CT32B2 = 0x00030;

    // Set match interrupts and TC reset for CT16B0, which is used to generate interrupt
    SN_CT16B0->MCTRL = (mskCT16_MR3IE_EN|mskCT16_MR3STOP_EN);

    // COL match register
    SN_CT16B0->MR3 = 0xFF;

	// Set prescale value
    SN_CT16B0->PRE = 0x30;
    SN_CT16B1->PRE = 0x30;
    SN_CT16B2->PRE = 0x30;
    SN_CT32B0->PRE = 0x30;
    SN_CT32B1->PRE = 0x30;
    SN_CT32B2->PRE = 0x30;

	// Enable PWM on all timers
	SN_CT16B0->PWMCTRL =
		(mskCT16_PWM0EN_EN \
		|mskCT16_PWM1EN_EN);
	SN_CT16B1->PWMCTRL =
		(mskCT16_PWM1EN_EN \
		|mskCT16_PWM2EN_EN);
	SN_CT16B2->PWMCTRL =
		(mskCT16_PWM0EN_EN \
		|mskCT16_PWM1EN_EN \
		|mskCT16_PWM2EN_EN);
	SN_CT32B0->PWMCTRL =
		(mskCT32_PWM0EN_EN \
		|mskCT32_PWM1EN_EN \
		|mskCT32_PWM3EN_EN);
	SN_CT32B1->PWMCTRL =
		(mskCT32_PWM1EN_EN \
		|mskCT32_PWM2EN_EN \
		|mskCT32_PWM3EN_EN);
	SN_CT32B2->PWMCTRL =
		(mskCT32_PWM0EN_EN \
		|mskCT32_PWM1EN_EN \
		|mskCT32_PWM2EN_EN \
		|mskCT32_PWM3EN_EN);

	// Enable IO
	SN_CT16B0->PWMCTRL |=
		(mskCT16_PWM0IOEN_EN \
		|mskCT16_PWM1IOEN_EN);
	SN_CT16B1->PWMCTRL |=
		(mskCT16_PWM1IOEN_EN \
		|mskCT16_PWM2IOEN_EN);
	SN_CT16B2->PWMCTRL |=
		(mskCT16_PWM0IOEN_EN \
		|mskCT16_PWM1IOEN_EN \
		|mskCT16_PWM2IOEN_EN);
	SN_CT32B0->PWMCTRL |=
		(mskCT32_PWM0IOEN_EN \
		|mskCT32_PWM1IOEN_EN \
		|mskCT32_PWM3IOEN_EN);
	SN_CT32B1->PWMCTRL |=
		(mskCT32_PWM1IOEN_EN \
		|mskCT32_PWM2IOEN_EN \
		|mskCT32_PWM3IOEN_EN);
	SN_CT32B2->PWMCTRL |=
		(mskCT32_PWM0IOEN_EN \
		|mskCT32_PWM1IOEN_EN \
		|mskCT32_PWM2IOEN_EN \
		|mskCT32_PWM3IOEN_EN);

    // Clear match registers
	SN_CT16B0->MR0 = 0x0;
	SN_CT16B0->MR1 = 0x0;
	SN_CT16B0->MR2 = 0x0;
	SN_CT16B1->MR0 = 0x0;
	SN_CT16B1->MR1 = 0x0;
	SN_CT16B1->MR2 = 0x0;
	SN_CT16B1->MR3 = 0x0;
	SN_CT16B2->MR0 = 0x0;
	SN_CT16B2->MR1 = 0x0;
	SN_CT16B2->MR2 = 0x0;
	SN_CT16B2->MR3 = 0x0;
	SN_CT32B0->MR0 = 0x0;
	SN_CT32B0->MR1 = 0x0;
	SN_CT32B0->MR2 = 0x0;
	SN_CT32B0->MR3 = 0x0;
	SN_CT32B1->MR0 = 0x0;
	SN_CT32B1->MR1 = 0x0;
	SN_CT32B1->MR2 = 0x0;
	SN_CT32B1->MR3 = 0x0;
	SN_CT32B2->MR0 = 0x0;
	SN_CT32B2->MR1 = 0x0;
	SN_CT32B2->MR2 = 0x0;
	SN_CT32B2->MR3 = 0x0;

    //Set timers to the up-counting mode.
    SN_CT16B0->TMRCTRL = (mskCT16_CRST);
    SN_CT16B1->TMRCTRL = (mskCT16_CRST);
    SN_CT16B2->TMRCTRL = (mskCT16_CRST);
    SN_CT32B0->TMRCTRL = (mskCT32_CRST);
    SN_CT32B1->TMRCTRL = (mskCT32_CRST);
    SN_CT32B2->TMRCTRL = (mskCT32_CRST);

    // Wait until timer reset done.
    while( (SN_CT16B0->TMRCTRL & mskCT16_CRST)
        || (SN_CT16B1->TMRCTRL & mskCT16_CRST)
        || (SN_CT16B2->TMRCTRL & mskCT16_CRST)
        || (SN_CT32B0->TMRCTRL & mskCT32_CRST)
        || (SN_CT32B1->TMRCTRL & mskCT32_CRST)
        || (SN_CT32B2->TMRCTRL & mskCT32_CRST));

    // Let TC start counting.  Start CT16B0 last because it generates our interrupt
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;
    SN_CT16B2->TMRCTRL |= mskCT16_CEN_EN;
    SN_CT32B0->TMRCTRL |= mskCT32_CEN_EN;
    SN_CT32B1->TMRCTRL |= mskCT32_CEN_EN;
    SN_CT32B2->TMRCTRL |= mskCT32_CEN_EN;
    SN_CT16B0->TMRCTRL |= mskCT16_CEN_EN;

    NVIC_ClearPendingIRQ(CT16B0_IRQn);
    nvicEnableVector(CT16B0_IRQn, 0);
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
 * @brief   MR1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(SN32_CT16B0_HANDLER) {

	chSysDisable();

    OSAL_IRQ_PROLOGUE();

     // Disable PWM outputs on column pins
    SN_CT16B0->PWMCTRL = 0;
    SN_CT16B1->PWMCTRL = 0;
    SN_CT16B2->PWMCTRL = 0;
    SN_CT32B0->PWMCTRL = 0;
    SN_CT32B1->PWMCTRL = 0;
    SN_CT32B2->PWMCTRL = 0;

    SN_CT16B0->IC = mskCT16_MR3IC; // Clear match interrupt status

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
        for (uint8_t delay_idx = 0; delay_idx < 20; delay_idx++)
        {
            writePinHigh(col_pins[col_index]);
        }
    }

    // Turn the next row on
    current_row = (current_row + 1) % LED_MATRIX_ROWS_HW;

    uint8_t row_idx = hw_row_to_matrix_row[current_row];
    uint16_t row_ofst = row_ofsts[row_idx];

    //Set timers to the up-counting mode.
    SN_CT16B0->TMRCTRL = (mskCT16_CRST);
    SN_CT16B1->TMRCTRL = (mskCT16_CRST);
    SN_CT16B2->TMRCTRL = (mskCT16_CRST);
    SN_CT32B0->TMRCTRL = (mskCT32_CRST);
    SN_CT32B1->TMRCTRL = (mskCT32_CRST);
    SN_CT32B2->TMRCTRL = (mskCT32_CRST);

    // Wait until timer reset done.
    while( (SN_CT16B0->TMRCTRL & mskCT16_CRST)
        || (SN_CT16B1->TMRCTRL & mskCT16_CRST)
        || (SN_CT16B2->TMRCTRL & mskCT16_CRST)
        || (SN_CT32B0->TMRCTRL & mskCT32_CRST)
        || (SN_CT32B1->TMRCTRL & mskCT32_CRST)
        || (SN_CT32B2->TMRCTRL & mskCT32_CRST));

    if (current_row % 3 == 0)
    {
		SN_CT16B0->MR0 = led_state[row_ofst + 0 ].r;
		SN_CT16B0->MR1 = led_state[row_ofst + 1 ].r;
		SN_CT16B2->MR0 = led_state[row_ofst + 2 ].r;
		SN_CT32B2->MR2 = led_state[row_ofst + 3 ].r;
		SN_CT32B0->MR0 = led_state[row_ofst + 4 ].r;
		SN_CT32B1->MR2 = led_state[row_ofst + 5 ].r;
		SN_CT32B2->MR3 = led_state[row_ofst + 6 ].r;
		SN_CT32B1->MR3 = led_state[row_ofst + 7 ].r;
		SN_CT32B2->MR1 = led_state[row_ofst + 8 ].r;
		SN_CT16B1->MR2 = led_state[row_ofst + 9 ].r;
		SN_CT16B2->MR2 = led_state[row_ofst + 10].r;
		SN_CT32B2->MR0 = led_state[row_ofst + 11].r;
		SN_CT32B0->MR3 = led_state[row_ofst + 12].r;
		SN_CT16B1->MR1 = led_state[row_ofst + 13].r;
		SN_CT16B2->MR1 = led_state[row_ofst + 14].r;
		SN_CT32B1->MR1 = led_state[row_ofst + 15].r;
		SN_CT32B0->MR1 = led_state[row_ofst + 16].r;
	}

	if (current_row % 3 == 1)
    {
		SN_CT16B0->MR0 = led_state[row_ofst + 0 ].g;
		SN_CT16B0->MR1 = led_state[row_ofst + 1 ].g;
		SN_CT16B2->MR0 = led_state[row_ofst + 2 ].g;
		SN_CT32B2->MR2 = led_state[row_ofst + 3 ].g;
		SN_CT32B0->MR0 = led_state[row_ofst + 4 ].g;
		SN_CT32B1->MR2 = led_state[row_ofst + 5 ].g;
		SN_CT32B2->MR3 = led_state[row_ofst + 6 ].g;
		SN_CT32B1->MR3 = led_state[row_ofst + 7 ].g;
		SN_CT32B2->MR1 = led_state[row_ofst + 8 ].g;
		SN_CT16B1->MR2 = led_state[row_ofst + 9 ].g;
		SN_CT16B2->MR2 = led_state[row_ofst + 10].g;
		SN_CT32B2->MR0 = led_state[row_ofst + 11].g;
		SN_CT32B0->MR3 = led_state[row_ofst + 12].g;
		SN_CT16B1->MR1 = led_state[row_ofst + 13].g;
		SN_CT16B2->MR1 = led_state[row_ofst + 14].g;
		SN_CT32B1->MR1 = led_state[row_ofst + 15].g;
		SN_CT32B0->MR1 = led_state[row_ofst + 16].g;
	}

	if (current_row % 3 == 2)
    {
		SN_CT16B0->MR0 = led_state[row_ofst + 0 ].b;
		SN_CT16B0->MR1 = led_state[row_ofst + 1 ].b;
		SN_CT16B2->MR0 = led_state[row_ofst + 2 ].b;
		SN_CT32B2->MR2 = led_state[row_ofst + 3 ].b;
		SN_CT32B0->MR0 = led_state[row_ofst + 4 ].b;
		SN_CT32B1->MR2 = led_state[row_ofst + 5 ].b;
		SN_CT32B2->MR3 = led_state[row_ofst + 6 ].b;
		SN_CT32B1->MR3 = led_state[row_ofst + 7 ].b;
		SN_CT32B2->MR1 = led_state[row_ofst + 8 ].b;
		SN_CT16B1->MR2 = led_state[row_ofst + 9 ].b;
		SN_CT16B2->MR2 = led_state[row_ofst + 10].b;
		SN_CT32B2->MR0 = led_state[row_ofst + 11].b;
		SN_CT32B0->MR3 = led_state[row_ofst + 12].b;
		SN_CT16B1->MR1 = led_state[row_ofst + 13].b;
		SN_CT16B2->MR1 = led_state[row_ofst + 14].b;
		SN_CT32B1->MR1 = led_state[row_ofst + 15].b;
		SN_CT32B0->MR1 = led_state[row_ofst + 16].b;
	}

    // Enable PWM on all timers
    if(SN_CT16B0->MR0 > 0)
    {
        SN_CT16B0->PWMCTRL |=
            (mskCT16_PWM0EN_EN \
            |mskCT16_PWM0IOEN_EN);
    }
    if(SN_CT16B0->MR1 > 0)
    {
        SN_CT16B0->PWMCTRL |=
            (mskCT16_PWM1EN_EN \
            |mskCT16_PWM1IOEN_EN);
    }
    if(SN_CT16B2->MR0 > 0)
    {
        SN_CT16B2->PWMCTRL |=
            (mskCT16_PWM0EN_EN \
            |mskCT16_PWM0IOEN_EN);
    }
    if(SN_CT32B2->MR2 > 0)
    {
        SN_CT32B2->PWMCTRL |=
            (mskCT32_PWM2EN_EN \
            |mskCT32_PWM2IOEN_EN);
    }
    if(SN_CT32B0->MR0 > 0)
    {
        SN_CT32B0->PWMCTRL |=
            (mskCT32_PWM0EN_EN \
            |mskCT32_PWM0IOEN_EN);
    }
    if(SN_CT32B1->MR2 > 0)
    {
        SN_CT32B1->PWMCTRL |=
            (mskCT32_PWM2EN_EN \
            |mskCT32_PWM2IOEN_EN);
    }
    if(SN_CT32B2->MR3 > 0)
    {
        SN_CT32B2->PWMCTRL |=
            (mskCT32_PWM3EN_EN \
            |mskCT32_PWM3IOEN_EN);
    }
    if(SN_CT32B1->MR3 > 0)
    {
        SN_CT32B1->PWMCTRL |=
            (mskCT32_PWM3EN_EN \
            |mskCT32_PWM3IOEN_EN);
    }
    if(SN_CT32B2->MR1 > 0)
    {
        SN_CT32B2->PWMCTRL |=
            (mskCT32_PWM1EN_EN \
            |mskCT32_PWM1IOEN_EN);
    }
    if(SN_CT16B1->MR2 > 0)
    {
        SN_CT16B1->PWMCTRL |=
            (mskCT16_PWM2EN_EN \
            |mskCT16_PWM2IOEN_EN);
    }
    if(SN_CT16B2->MR2 > 0)
    {
        SN_CT16B2->PWMCTRL |=
            (mskCT16_PWM2EN_EN \
            |mskCT16_PWM2IOEN_EN);
    }
    if(SN_CT32B2->MR0 > 0)
    {
        SN_CT32B2->PWMCTRL |=
            (mskCT32_PWM0EN_EN \
            |mskCT32_PWM0IOEN_EN);
    }
    if(SN_CT32B0->MR3 > 0)
    {
        SN_CT32B0->PWMCTRL |=
            (mskCT32_PWM3EN_EN \
            |mskCT32_PWM3IOEN_EN);
    }
    if(SN_CT16B1->MR1 > 0)
    {
        SN_CT16B1->PWMCTRL |=
            (mskCT16_PWM1EN_EN \
            |mskCT16_PWM1IOEN_EN);
    }
    if(SN_CT16B2->MR1 > 0)
    {
        SN_CT16B2->PWMCTRL |=
            (mskCT16_PWM1EN_EN \
            |mskCT16_PWM1IOEN_EN);
    }
    if(SN_CT32B1->MR1 > 0)
    {
        SN_CT32B1->PWMCTRL |=
            (mskCT32_PWM1EN_EN \
            |mskCT32_PWM1IOEN_EN);
    }
    if(SN_CT32B0->MR1 > 0)
    {
        SN_CT32B0->PWMCTRL |=
            (mskCT32_PWM1EN_EN \
            |mskCT32_PWM1IOEN_EN);
    }

    // Set match interrupts and TC rest for CT16B0, which is used to generate interrupt
    SN_CT16B0->MCTRL = (mskCT16_MR3IE_EN|mskCT16_MR3STOP_EN);

    // COL match register
    SN_CT16B0->MR3 = 0xFF;

	// Set prescale value
    SN_CT16B0->PRE = 0x30;
    SN_CT16B1->PRE = 0x30;
    SN_CT16B2->PRE = 0x30;
    SN_CT32B0->PRE = 0x30;
    SN_CT32B1->PRE = 0x30;
    SN_CT32B2->PRE = 0x30;

    writePinHigh(led_row_pins[current_row]);

    // Let TC start counting.  Start CT16B0 last because it generates our interrupt
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;
    SN_CT16B2->TMRCTRL |= mskCT16_CEN_EN;
    SN_CT32B0->TMRCTRL |= mskCT32_CEN_EN;
    SN_CT32B1->TMRCTRL |= mskCT32_CEN_EN;
    SN_CT32B2->TMRCTRL |= mskCT32_CEN_EN;
    SN_CT16B0->TMRCTRL |= mskCT16_CEN_EN;

    chSysEnable();

    OSAL_IRQ_EPILOGUE();
}

void HardFault_Handler(void) {
    NVIC_SystemReset();
}
