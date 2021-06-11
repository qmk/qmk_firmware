/*
 * Copyright 2011 Jun Wako <wakojun@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Ported to QMK by Stephen Peery <https://github.com/smp4488/>
 */

#include <stdint.h>
#include <stdbool.h>
#include "ch.h"
#include "hal.h"

#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "led_matrix.h"
#include <SN32F240B.h>
#include <string.h>
#include "CT16.h"
#include "ch.h"
#include "hal.h"
#include "rgb.h"
#include "rgb_matrix.h"
#include "rgb_matrix_types.h"
#include "led.h"
#include "color.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

// static const pin_t led_row_pins[MATRIX_ROWS][3] = LED_MATRIX_ROW_PINS;
// static const pin_t led_row_pins[LED_MATRIX_ROWS] = LED_MATRIX_ROW_PINS;

// LED COL pins are the same as the keyboard matrix

volatile matrix_row_t raw_matrix[MATRIX_ROWS]  = {0};  // raw values
matrix_row_t          last_matrix[MATRIX_ROWS] = {0};  // raw values
matrix_row_t          matrix[MATRIX_ROWS]      = {0};  // debounced values
volatile bool         matrix_changed           = false;

void matrix_scan_kb(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}

// static void select_col(uint8_t col) {
//     setPinOutput(col_pins[col]);
//     writePinLow(col_pins[col]);
// }

static void unselect_col(uint8_t col) { setPinInputHigh(col_pins[col]); }

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
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

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
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

    debounce(last_matrix, matrix, MATRIX_ROWS, matrix_changed);

    matrix_scan_quantum();

    return (uint8_t)matrix_changed;
}

void __assert_func (const char * file, int line, const char * func, const char * expr)
{
    while (1)
    {
        /* Do nothing. */
    }
}

volatile SN_CT16B1_Type * ct_b1 = (SN_CT16B1_Type *) SN_CT16B1_BASE;

static struct
{
    uint8_t g;
    uint8_t b;
    uint8_t r;
} __attribute__((packed)) led_state[DRIVER_LED_TOTAL];

// led_t status_leds = {0};

// bool led_update_user(led_t led_state);
// bool led_update_user(led_t led_state) { status_leds=led_state; return true; }

static uint8_t col_index = 0;
static uint8_t led_index = 1;

// set counter reset on MRn (setting MRn to the full period) and set the other MRs to the PWM duty cycle you want for that pin
// on period interrupt update all the PWM MRs to the values for the next LED
// the only issue is that when you do that, the timer has reset and may count during the ISR, so you'll have to detect low or 0 values and set the pin accordingly

void init (void) {
    // Enable Timer Clock
    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;

    //// PFPA - Set PWM to port B pins
    // SN_PFPA->CT16B1 = 0xFFFF00;        // 8-9, 11-23 = top half 16 bits
    // 1111 1111 1111 1011 0000 0000

    ////Set MR23 value for 1ms PWM period ==> count value = 1000*12 = 12000
    //// SN_CT16B1->MR22 = 12000;
    //// base 0x40002000
    //// MR0 at Offset:0x20
    //// MR8 at Offset:0x40
    //// MR24 at Offset:0x80
    //// set all match registers the same for now

    // 16 bits - max = 65535
    SN_CT16B1->MR0 = 0;
    SN_CT16B1->MR1 = 0;
    SN_CT16B1->MR2 = 0xFFFF;

    SN_CT16B1->MR3 = 0x40;
    SN_CT16B1->MR4 = 0x40;
    SN_CT16B1->MR5 = 0xFFFF;

    SN_CT16B1->MR6 = 0xFFFF;
    SN_CT16B1->MR7 = 0xFFFF;
    SN_CT16B1->MR8 = 0xFFFF;

    SN_CT16B1->MR9  = 0x40;
    SN_CT16B1->MR10 = 0xFFFF;
    SN_CT16B1->MR11 = 0x40;

    SN_CT16B1->MR12 = 0;
    SN_CT16B1->MR13 = 0xFFFF;
    SN_CT16B1->MR14 = 0;

    /* clang-format off */

    // Enable PWM function, IOs and select the PWM modes
    // SN_CT16B1->PWMENB   = 0xFFFB00;     //Enable PWM8-PWM9, PWM11-PWM23 function
    // |mskCT16_PWM10EN_EN
    SN_CT16B1->PWMENB = (mskCT16_PWM0EN_EN |  \
                         mskCT16_PWM1EN_EN |  \
                         mskCT16_PWM2EN_EN |  \
                         mskCT16_PWM3EN_EN |  \
                         mskCT16_PWM4EN_EN |  \
                         mskCT16_PWM5EN_EN |  \
                         mskCT16_PWM6EN_EN |  \
                         mskCT16_PWM7EN_EN |  \
                         mskCT16_PWM8EN_EN |  \
                         mskCT16_PWM9EN_EN |  \
                         mskCT16_PWM10EN_EN | \
                         mskCT16_PWM11EN_EN | \
                         mskCT16_PWM12EN_EN | \
                         mskCT16_PWM13EN_EN | \
                         mskCT16_PWM14EN_EN);

    // SN_CT16B1->PWMIOENB = 0xFFFB00;     //Enable PWM8-PWM9 PWM12-PWM23 IO
    // |mskCT16_PWM0IOEN_EN
    SN_CT16B1->PWMIOENB = (mskCT16_PWM0IOEN_EN |  \
                           mskCT16_PWM1IOEN_EN |  \
                           mskCT16_PWM2IOEN_EN |  \
                           mskCT16_PWM3IOEN_EN |  \
                           mskCT16_PWM4IOEN_EN |  \
                           mskCT16_PWM5IOEN_EN |  \
                           mskCT16_PWM6IOEN_EN |  \
                           mskCT16_PWM7IOEN_EN |  \
                           mskCT16_PWM8IOEN_EN |  \
                           mskCT16_PWM9IOEN_EN |  \
                           mskCT16_PWM10IOEN_EN | \
                           mskCT16_PWM11IOEN_EN | \
                           mskCT16_PWM12IOEN_EN | \
                           mskCT16_PWM13IOEN_EN | \
                           mskCT16_PWM14IOEN_EN);

    // SN_CT16B1->PWMCTRL  = 0x55650000;   //PWM08-PWM9 , PWM11-PWM15 select as PWM mode 2
    // |mskCT16_PWM10MODE_2
    SN_CT16B1->PWMCTRL = (mskCT16_PWM0MODE_2 |  \
                          mskCT16_PWM1MODE_2 |  \
                          mskCT16_PWM2MODE_2 |  \
                          mskCT16_PWM3MODE_2 |  \
                          mskCT16_PWM4MODE_2 |  \
                          mskCT16_PWM5MODE_2 |  \
                          mskCT16_PWM6MODE_2 |  \
                          mskCT16_PWM7MODE_2 |  \
                          mskCT16_PWM8MODE_2 |  \
                          mskCT16_PWM9MODE_2 |  \
                          mskCT16_PWM10MODE_2 | \
                          mskCT16_PWM11MODE_2 | \
                          mskCT16_PWM12MODE_2 | \
                          mskCT16_PWM13MODE_2 | \
                          mskCT16_PWM14MODE_2);

    /* clang-format on */

    SN_CT16B1->MR15   = 0xFF;
    SN_CT16B1->MCTRL2 = (mskCT16_MR15IE_EN);

    // Set prescale value - This seems to give us .1ms per col select
    SN_CT16B1->PRE = 0x4;

    // Let TC start counting.
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++)
    {
        setPinOutput(col_pins[current_col]);
        writePinHigh(col_pins[current_col]);
    }

    // Set col, read rows
    // for (uint8_t current_col = 0; current_col < MATRIX_ROWS; current_col++)
    // {
    //     setPinOutput(row_pins[current_col]);
    //     writePinHigh(row_pins[col_index]);
    // }

    writePinLow(col_pins[0]);

    SN_CT16B1->MCTRL2_b.MR15RST = 1;

    // Wait until timer reset done.
    while (SN_CT16B1->TMRCTRL & mskCT16_CRST)
    {
        ;
    }

    NVIC_ClearPendingIRQ(CT16B1_IRQn);
    nvicEnableVector(CT16B1_IRQn, 4);
}

static void flush (void) {
}

static void set_color (int index, uint8_t r, uint8_t g, uint8_t b) {
    led_state[index].r = r;
    led_state[index].g = g;
    led_state[index].b = b;
}

static void set_color_all (uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        set_color(i, r, g, b);
    }
}

const rgb_matrix_driver_t rgb_matrix_driver =
{
    .init          = init,
    .flush         = flush,
    .set_color     = set_color,
    .set_color_all = set_color_all,
};

volatile uint32_t * rgb_match_registers[5][3] =
{
    {&SN_CT16B1->MR0,  &SN_CT16B1->MR1,   &SN_CT16B1->MR2    },
    {&SN_CT16B1->MR3,  &SN_CT16B1->MR4,   &SN_CT16B1->MR5    },
    {&SN_CT16B1->MR6,  &SN_CT16B1->MR7,   &SN_CT16B1->MR8    },
    {&SN_CT16B1->MR9,  &SN_CT16B1->MR10,  &SN_CT16B1->MR11   },
    {&SN_CT16B1->MR12, &SN_CT16B1->MR13,  &SN_CT16B1->MR14   },
};

/**
 * @brief   TIM2 interrupt handler.
 *
 * @isr
 */
extern volatile bool matrix_changed;

// OSAL_IRQ_HANDLER(Vector84)
void RgbIsr () {
    OSAL_IRQ_PROLOGUE();

    // if (status_leds.caps_lock)
    // {
    //     led_state[g_led_config.matrix_co[0][0]].g = 0xFF;
    //     led_state[g_led_config.matrix_co[0][0]].b = 0xFF;
    //     led_state[g_led_config.matrix_co[0][0]].r = 0xFF;
    // }

    writePinHigh(col_pins[col_index]);

    col_index = (col_index + 1) % MATRIX_COLS;
    led_index = (led_index + 1) % MATRIX_COLS;

    writePinLow(col_pins[col_index]);

    for (uint8_t row_index = 0; row_index < 5; row_index++)
    {

        if ((NO_LED != g_led_config.matrix_co[row_index][led_index]))
        {
            *rgb_match_registers[row_index][0] = led_state[g_led_config.matrix_co[row_index][led_index]].g;
            *rgb_match_registers[row_index][1] = led_state[g_led_config.matrix_co[row_index][led_index]].b;
            *rgb_match_registers[row_index][2] = led_state[g_led_config.matrix_co[row_index][led_index]].r;
        }

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0)
        {
            // Pin LO, set col bit
            raw_matrix[row_index] |= (MATRIX_ROW_SHIFTER << col_index);
        }
        else
        {
            // Pin HI, clear col bit
            raw_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << col_index);
        }
    }

    SN_CT16B1->IC = SN_CT16B1->RIS;    // Clear all for now

    OSAL_IRQ_EPILOGUE();
}
