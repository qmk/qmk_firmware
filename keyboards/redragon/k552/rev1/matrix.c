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
static uint8_t current_col = 0;
//static uint8_t current_row = 0;
static uint8_t current_led_row =0;

extern volatile LED_TYPE led_state[DRIVER_LED_TOTAL];

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}

static void select_col(uint8_t col) {
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void unselect_col(uint8_t col) { setPinInputHigh(col_pins[col]); }

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

//static void init_pins(void) {
//
//    //  Unselect ROWs
//    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
//        setPinOutput(row_pins[x]);
//        writePinHigh(row_pins[x]);
//    }
//
//    // Unselect COLs
//    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
//        setPinInput(col_pins[x]);
//        writePinHigh(col_pins[x]);
//    }
//
////    for (uint8_t x = 0; x < LED_MATRIX_ROWS_HW; x++) {
////        setPinOutput(led_row_pins[x]);
////        writePinHigh(led_row_pins[x]);
////    }
//}


static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
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

    while (0)
    {

        for (uint8_t x = 0; x < MATRIX_COLS; x++) {
            // Turn COL On
            setPinOutput(col_pins[x]);
            writePinLow(col_pins[x]);
//            chThdSleepMilliseconds(100);

            for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y++) {

                // On
                // setPinInput(led_row_pins[y]);
                setPinOutput(led_row_pins[y]);
                writePinHigh(led_row_pins[y]);

                chThdSleepMilliseconds(10);

                // Off
                // setPinOutput(led_row_pins[y]);
                writePinLow(led_row_pins[y]);

//                chThdSleepMilliseconds(100);
            }
            // Turn COL Off
            setPinInput(col_pins[x]);
            writePinHigh(col_pins[x]);
//            chThdSleepMilliseconds(100);
        }
    }

    matrix_init_quantum();

    // Enable Timer Clock
//    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;
    SN_SYS1->AHBCLKEN_b.CT32B0CLKEN = 1;

    // PFPA - Map most PWM outputs to their PWM A pins
    SN_PFPA->CT32B0 = 0x410;
//    SN_PFPA->CT16B1 = 0x00006660;

//    // Enable PWM function, IOs and select the PWM modes
//    // Enable PWM0-PWM3, PWM8-23
//    SN_CT32B0->EM = (mskCT32_EMC2_TOGGLE);
//    SN_CT16B1->PWMCTRL   =   (mskCT16_PWM0EN_EN  \
//                            |mskCT16_PWM1EN_EN  \
//                            |mskCT16_PWM2EN_EN ); \
//                            |mskCT16_PWM8EN_EN  \
//                            |mskCT16_PWM9EN_EN  \
//                            |mskCT16_PWM10EN_EN \
//                            |mskCT16_PWM11EN_EN \
//                            |mskCT16_PWM12EN_EN \
//                            |mskCT16_PWM13EN_EN \
//                            |mskCT16_PWM14EN_EN \
//                            |mskCT16_PWM15EN_EN \
//                            |mskCT16_PWM16EN_EN \
//                            |mskCT16_PWM17EN_EN \
//                            |mskCT16_PWM18EN_EN \
//                            |mskCT16_PWM19EN_EN \
//                            |mskCT16_PWM20EN_EN \
//                            |mskCT16_PWM21EN_EN \
//                            |mskCT16_PWM22EN_EN \
//                            |mskCT16_PWM23EN_EN);
//
//    // Enable PWM0-PWM3, PWM8-PWM23 IO
	SN_CT32B0->PWMCTRL	=
	   (mskCT32_PWM0EN_EN|mskCT32_PWM0MODE_1|mskCT32_PWM0IOEN_EN
	   |mskCT32_PWM1EN_EN|mskCT32_PWM1MODE_1|mskCT32_PWM1IOEN_EN
	   |mskCT32_PWM2EN_EN|mskCT32_PWM2MODE_1|mskCT32_PWM2IOEN_EN);
//    SN_CT16B1->PWMCTRL   |= (mskCT16_PWM0IOEN_EN  \
//                            |mskCT16_PWM1IOEN_EN  \
//                            |mskCT16_PWM2IOEN_EN  ); \
//                            |mskCT16_PWM8IOEN_EN  \
//                            |mskCT16_PWM9IOEN_EN  \
//                            |mskCT16_PWM1IO0EN_EN \
//                            |mskCT16_PWM1IO1EN_EN \
//                            |mskCT16_PWM1IO2EN_EN \
//                            |mskCT16_PWM1IO3EN_EN \
//                            |mskCT16_PWM1IO4EN_EN \
//                            |mskCT16_PWM1IO5EN_EN \
//                            |mskCT16_PWM1IO6EN_EN \
//                            |mskCT16_PWM1IO7EN_EN \
//                            |mskCT16_PWM1IO8EN_EN \
//                            |mskCT16_PWM1IO9EN_EN \
//                            |mskCT16_PWM2IO0EN_EN \
//                            |mskCT16_PWM2IO1EN_EN \
//                            |mskCT16_PWM2IO2EN_EN \
//                            |mskCT16_PWM2IO3EN_EN);

    // Set match interrupts and TC rest
    SN_CT32B0->MCTRL = (mskCT32_MR3IE_EN|mskCT32_MR3RST_EN);

    // COL match register
	SN_CT32B0->MR3 = 0xFF;
	SN_CT32B0->MR0 = 0x0;
	SN_CT32B0->MR1 = 0x0;
	SN_CT32B0->MR2 = 0x0;
	
    // Set prescale value
    SN_CT32B0->PRE = 0x30;

    //Set CT16B1 as the up-counting mode.
    SN_CT32B0->TMRCTRL = (mskCT32_CRST|mskCT32_CM_EDGE_UP);

    // Wait until timer reset done.
    while (SN_CT32B0->TMRCTRL & mskCT32_CRST);

    // Let TC start counting.
    SN_CT32B0->TMRCTRL |= mskCT32_CEN_EN;

    NVIC_ClearPendingIRQ(CT32B0_IRQn);
    nvicEnableVector(CT32B0_IRQn, 0);
}

uint8_t matrix_scan(void) {
    matrix_changed = false;
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Determine if the matrix changed state
        if ((last_matrix[row_index] != raw_matrix[row_index])) {
            matrix_changed         = true;
            last_matrix[row_index] = raw_matrix[row_index];
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
OSAL_IRQ_HANDLER(SN32_CT32B0_HANDLER) {

	chSysDisable();
	
    OSAL_IRQ_PROLOGUE();

    // Disable PWM outputs on column pins
//    SN_CT16B1->PWMCTRL &= ~(mskCT16_PWM0IOEN_DIS| mskCT16_PWM1IOEN_DIS| mskCT16_PWM2IOEN_DIS);

    SN_CT32B0->PWMCTRL = 0;

    SN_CT32B0->IC = mskCT32_MR3IC; // Clear match interrupt status
    SN_CT32B0->TMRCTRL = CT32_CRST;

//    // Turn the selected LED row off
//    writePinLow(led_row_pins[current_led_row]);

    // Enable current matrix row
    select_col(current_col);


    // Read the key matrix
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (readPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            raw_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            raw_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
        }
    }

    // Disable current matrix row
    unselect_col(current_col);

    // Turn the next row on
//    current_led_row = (current_led_row + 1) % LED_MATRIX_ROWS_HW;

//    current_col = (current_col + 1) % MATRIX_COLS;

    uint8_t row_idx = hw_row_to_matrix_row[current_led_row];
    uint16_t row_ofst = row_ofsts[row_idx];


//    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
//        // Turn COL On
//        setPinOutput(col_pins[col_index]);
//        writePinLow(col_pins[col_index]);
        //        chThdSleepMilliseconds(10);
//
//        for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y += 3) {
//            // On
//            // setPinInput(led_row_pins[y]);
//            setPinOutput(led_row_pins[y]);
//            setPinOutput(led_row_pins[y+1]);
//            setPinOutput(led_row_pins[y+2]);
//            writePin(led_row_pins[y], (led_state[current_col * 17 + y / 3].r) > 127);
//            writePin(led_row_pins[y+1], 0);
//            writePin(led_row_pins[y+2], 0);
////            chThdSleepMilliseconds(5);
//
//            //        }
//            //
//            //        ;
//            //
//            //        chThdSleepMilliseconds(100);
//            //
//            //        for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y+=3)
//            //        {
//            // Off
//            // setPinOutput(led_row_pins[y]);
//            //            writePinLow(led_row_pins[y]);
//            //            chThdSleepMilliseconds(1000);
//        }

        // Turn COL Off
//        setPinInput(col_pins[col_index]);
//        writePinHigh(col_pins[col_index]);
        //        chThdSleepMilliseconds(10);
//    }
    select_col(current_col);

    //    for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y += 3) {
    writePin(led_row_pins[0], led_state[current_col + 0 * 17].r > 127);
//    SN_CT32B0->MR2 = led_state[current_col + 0 * 17].r | 1;
    writePin(led_row_pins[1], led_state[current_col + 0 * 17].b > 127);
    writePin(led_row_pins[2], led_state[current_col + 0 * 17].g > 127);

    writePin(led_row_pins[3], led_state[current_col + 1 * 17].r > 127);
    writePin(led_row_pins[4], led_state[current_col + 1 * 17].b > 127);
    //        SN_CT32B0->MR0 = led_state[current_col + 1 * 17].g | 1;
    writePin(led_row_pins[5], led_state[current_col + 1 * 17].g > 127);
    //        SN_CT32B0->MR2 = led_state[current_col + 1 * 17].b | 1;

    writePin(led_row_pins[6], led_state[current_col + 2 * 17].r > 127);
    writePin(led_row_pins[7], led_state[current_col + 2 * 17].b > 127);
    writePin(led_row_pins[8], led_state[current_col + 2 * 17].g > 127);

    writePin(led_row_pins[9], led_state[current_col + 3 * 17].r > 127);
    writePin(led_row_pins[10], led_state[current_col + 3 * 17].b > 127);
    writePin(led_row_pins[11], led_state[current_col + 3 * 17].g > 127);

    writePin(led_row_pins[12], led_state[current_col + 4 * 17].r > 127);
    writePin(led_row_pins[13], led_state[current_col + 4 * 17].b > 127);
    writePin(led_row_pins[14], led_state[current_col + 4 * 17].g > 127);

    writePin(led_row_pins[15], led_state[current_col + 5 * 17].r > 127);
    writePin(led_row_pins[16], led_state[current_col + 5 * 17].b > 127);
//    SN_CT32B0->MR2 = led_state[current_col + 5 * 17].g | 1;
    writePin(led_row_pins[17], led_state[current_col + 5 * 17].g > 127);
    //    }

    unselect_col(current_col);

    current_col = (current_col + 1) % MATRIX_COLS;


    //    for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y++) {
//        if (current_led_row % 3 == 0) {
////            SN_CT16B1->MR8  = led_state[row_ofst + 0].b | 1;
////            SN_CT16B1->MR9  = led_state[row_ofst + 1].b | 1;
////            SN_CT16B1->MR10 = led_state[row_ofst + 2].b | 1;
////            SN_CT16B1->MR11 = led_state[row_ofst + 3].b | 1;
////            SN_CT16B1->MR12 = led_state[row_ofst + 4].b | 1;
////            SN_CT16B1->MR13 = led_state[row_ofst + 5].b | 1;
////            SN_CT16B1->MR14 = led_state[row_ofst + 6].b | 1;
////            SN_CT16B1->MR15 = led_state[row_ofst + 7].b | 1;
////            SN_CT16B1->MR16 = led_state[row_ofst + 8].b | 1;
////            SN_CT16B1->MR17 = led_state[row_ofst + 9].b | 1;
////            SN_CT16B1->MR18 = led_state[row_ofst + 10].b | 1;
////            SN_CT16B1->MR19 = led_state[row_ofst + 11].b | 1;
////            SN_CT16B1->MR20 = led_state[row_ofst + 12].b | 1;
////            SN_CT16B1->MR21 = led_state[row_ofst + 13].b | 1;
////            SN_CT16B1->MR22 = led_state[row_ofst + 14].b | 1;
////            SN_CT16B1->MR23 = led_state[row_ofst + 15].b | 1;
//            SN_CT32B0->MR0  = led_state[row_ofst + 16].b | 1;
//            SN_CT32B0->MR1  = led_state[row_ofst + 17].b | 1;
//            SN_CT32B0->MR2  = led_state[row_ofst + 18].b | 1;
//        }
//
//        if (current_led_row % 3 == 1) {
////            SN_CT16B1->MR8  = led_state[row_ofst + 0].g | 1;
////            SN_CT16B1->MR9  = led_state[row_ofst + 1].g | 1;
////            SN_CT16B1->MR10 = led_state[row_ofst + 2].g | 1;
////            SN_CT16B1->MR11 = led_state[row_ofst + 3].g | 1;
////            SN_CT16B1->MR12 = led_state[row_ofst + 4].g | 1;
////            SN_CT16B1->MR13 = led_state[row_ofst + 5].g | 1;
////            SN_CT16B1->MR14 = led_state[row_ofst + 6].g | 1;
////            SN_CT16B1->MR15 = led_state[row_ofst + 7].g | 1;
////            SN_CT16B1->MR16 = led_state[row_ofst + 8].g | 1;
////            SN_CT16B1->MR17 = led_state[row_ofst + 9].g | 1;
////            SN_CT16B1->MR18 = led_state[row_ofst + 10].g | 1;
////            SN_CT16B1->MR19 = led_state[row_ofst + 11].g | 1;
////            SN_CT16B1->MR20 = led_state[row_ofst + 12].g | 1;
////            SN_CT16B1->MR21 = led_state[row_ofst + 13].g | 1;
////            SN_CT16B1->MR22 = led_state[row_ofst + 14].g | 1;
////            SN_CT16B1->MR23 = led_state[row_ofst + 15].g | 1;
//            SN_CT32B0->MR0  = led_state[row_ofst + 16].g | 1;
//            SN_CT32B0->MR1  = led_state[row_ofst + 17].g | 1;
//            SN_CT32B0->MR2  = led_state[row_ofst + 18].g | 1;
//        }
//        if (current_led_row % 3 == 2) {
////            SN_CT16B1->MR8  = led_state[row_ofst + 0].r | 1;
////            SN_CT16B1->MR9  = led_state[row_ofst + 1].r | 1;
////            SN_CT16B1->MR10 = led_state[row_ofst + 2].r | 1;
////            SN_CT16B1->MR11 = led_state[row_ofst + 3].r | 1;
////            SN_CT16B1->MR12 = led_state[row_ofst + 4].r | 1;
////            SN_CT16B1->MR13 = led_state[row_ofst + 5].r | 1;
////            SN_CT16B1->MR14 = led_state[row_ofst + 6].r | 1;
////            SN_CT16B1->MR15 = led_state[row_ofst + 7].r | 1;
////            SN_CT16B1->MR16 = led_state[row_ofst + 8].r | 1;
////            SN_CT16B1->MR17 = led_state[row_ofst + 9].r | 1;
////            SN_CT16B1->MR18 = led_state[row_ofst + 10].r | 1;
////            SN_CT16B1->MR19 = led_state[row_ofst + 11].r | 1;
////            SN_CT16B1->MR20 = led_state[row_ofst + 12].r | 1;
////            SN_CT16B1->MR21 = led_state[row_ofst + 13].r | 1;
////            SN_CT16B1->MR22 = led_state[row_ofst + 14].r | 1;
////            SN_CT16B1->MR23 = led_state[row_ofst + 15].r | 1;
//            SN_CT32B0->MR0  = led_state[row_ofst + 16].r | 1;
//            SN_CT32B0->MR1  = led_state[row_ofst + 17].r | 1;
//            SN_CT32B0->MR2  = led_state[row_ofst + 18].r | 1;
//        }
//    }
//
//        // Enable PWM outputs on column pins
//    SN_CT32B0->PWMCTRL |= mskCT32_PWM0IOEN_EN | mskCT32_PWM1IOEN_EN | mskCT32_PWM2IOEN_EN;
    SN_CT32B0->PWMCTRL	=
	   (mskCT32_PWM0EN_EN|mskCT32_PWM0MODE_1|mskCT32_PWM0IOEN_EN
	   |mskCT32_PWM1EN_EN|mskCT32_PWM1MODE_1|mskCT32_PWM1IOEN_EN
	   |mskCT32_PWM2EN_EN|mskCT32_PWM2MODE_1|mskCT32_PWM2IOEN_EN);

//        SN_CT16B1->PWMIOENB   = (mskCT16_PWM0EN_EN  \
//                            |mskCT16_PWM1EN_EN  \
//                            |mskCT16_PWM2EN_EN  ); \
//                            |mskCT16_PWM8EN_EN  \
//                            |mskCT16_PWM9EN_EN  \
//                            |mskCT16_PWM10EN_EN \
//                            |mskCT16_PWM11EN_EN \
//                            |mskCT16_PWM12EN_EN \
//                            |mskCT16_PWM13EN_EN \
//                            |mskCT16_PWM14EN_EN \
//                            |mskCT16_PWM15EN_EN \
//                            |mskCT16_PWM16EN_EN \
//                            |mskCT16_PWM17EN_EN \
//                            |mskCT16_PWM18EN_EN \
//                            |mskCT16_PWM19EN_EN \
//                            |mskCT16_PWM20EN_EN \
//                            |mskCT16_PWM21EN_EN \
//                            |mskCT16_PWM22EN_EN \
//                            |mskCT16_PWM23EN_EN);

    // Set match interrupts and TC rest
    SN_CT32B0->MCTRL = (mskCT32_MR3IE_EN|mskCT32_MR3RST_EN);

    // COL match register
	SN_CT32B0->MR3 = 0xFF;
	SN_CT32B0->MR0 = 0x0;
	SN_CT32B0->MR1 = 0x0;
	SN_CT32B0->MR2 = 0x0;
	
    // Set prescale value
    SN_CT32B0->PRE = 0x30;

//    writePinHigh(led_row_pins[current_led_row]);

	chSysEnable();
	
    OSAL_IRQ_EPILOGUE();
}

void HardFault_Handler(void) {
    NVIC_SystemReset();
}