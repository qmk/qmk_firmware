/* Copyright 2019 /u/KeepItUnder
 * Copyright 2020 Reza Jelveh
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
 */

/*
 * Macroblock's MBI5042GP is a 16-channel constant current LED driver.
 *
 * The chip has a data input interface, a set of synchronisation clocks
 * and 16 PWM output pins capapble of 16-bit PWM.
 *
 * Data interface: SDI, SDO, DCLK
 * General clock: GCLK
 * Data Latch: LE
 *
 * Commands available (differentiated by numbers of rising edge DCLKS)
 * Command is actioned on subsequent falling edge of LE:
 *
 *
 * Data Latch
 * ==========
 *
 * Take LE high. Keep high for maximum of 1 DCLK rising edges.
 *
 * Allow LE to fall - falling edge causes serial data to be
 * transferred to the buffers only.
 *
 *
 * Global Latch
 * ============
 *
 * Take LE high. Keep high for 2 or 3 DCLK rising edges.
 *
 * Allow LE to fall - falling edge causes buffer data to be
 * transferred to the comparators.
 *
 *
 * Read Configuration
 * ==================
 *
 * Take LE high. Keep high for 4 or 5 DCLK rising edges.
 *
 * Allow LE to fall - falling edge moves config data to the
 * shift registers.
 *
 *
 * Write Configuration
 * ===================
 *
 * Take LE high. Keep high for 10 or 11 DCLK rising edges.
 *
 * Allow LE to fall - falling edge transfers serial data
 * to the configuration register ONLY IF "Enable Writing
 * Configuration" is sent prior (see below)
 *
 *
 * Reset PWM Counter
 * =================
 *
 * Take LE high. Keep high for 12 or 13 DCLK rising edges.
 *
 * Allow LE to fall - falling edge resets the PWM counter
 * If bit "B" of the configuration register is "1"
 *
 *
 * Enable Writing Configuration
 * ============================
 *
 * Take LE high. Keep high for 14 or 15 DCLK rising edges.
 *
 * Allow LE to fall - falling edge enables configuration
 * writing. This should be sent immediately prior to any
 * attempt to write to configuration register.
 *
 *
 * Configuration Register
 * ======================
 *
 * 16 bits wide
 *
 * MSB            Definition       Value          Function
 * --------------------------------------------------------------------------------
 *     |       |                |  0 (Default)  | 15 x data latch + 1 global latch
 *  F  |  R/W  |  Data Loading  |               |
 *     |       |                |  1            | 16 x data latch + 1 global latch
 * ----|-------|----------------|---------------|----------------------------------
 *  E  |       |                |               |
 *  D  |  R/W  |  Reserved      |  Don't Care   | N/A
 *  C  |       |                |               |
 * ----|-------|----------------|---------------|----------------------------------
 *     |       | PWM counter    |  0 (Default)  | Disable
 *  B  |  R/W  | reset          |               |
 *     |       |                |  1            | Enable (12/13 DCLKs + LE assert)
 * ----|-------|----------------|---------------|----------------------------------
 *     |       | PWM data       |  0 (Default)  | Auto synchronization
 *  A  |  R/W  | synch mode     |               |
 *     |       |                |  1            | Manual synchronization
 * ----|-------|----------------|---------------|----------------------------------
 *  9  |       |                |               |
 *  8  |       |                |               |
 *  7  |  R/W  | Current gain   |  000000       | 6'b101011 (Default)
 *  6  |       | adjustment     |  ~            |
 *  5  |       |                |  111111       |
 *  4  |       |                |               |
 * ----|-------|----------------|---------------|----------------------------------
 *  3  |       |                |               |
 *  2  |  R/W  |  Reserved      |  Don't Care   | N/A
 *  1  |       |                |               |
 *  0  |       |                |               |
 * --------------------------------------------------------------------------------
 * LSB
 *
 */

//#include "mbi5042gp.h"
#include <string.h>
#include "progmem.h"
#include "rgb_matrix.h"
#include "led_tables.h"
#include "mbi5042gp.h"

/**
 * @brief   RGB Matrix LED layout
 * @details We need a layout for ISO and ANSI
 */
#define USB_LED_CAPSLOCK_INDEX 28  /* Location of CAPS LOCK led in matrix */
const mbi_led g_mbi_leds[DRIVER_LED_TOTAL] = {
    { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 }, { 0, 8 }, { 0, 9 }, { 0, 10 }, { 0, 11 }, { 0, 12 }, { 0, 13 },
    { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 }, { 1, 8 }, { 1, 9 }, { 1, 10 }, { 1, 11 }, { 1, 12 },
    { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 }, { 2, 8 }, { 2, 9 }, { 2, 10 }, { 2, 11 }, { 2, 12 }, { 2, 13 },
    { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 }, { 3, 6 }, { 3, 7 }, { 3, 8 }, { 3, 9 }, { 3, 10 }, { 3, 11 }, { 3, 12 },
    { 4, 0 }, { 4, 1 }, { 4, 2 },                     { 4, 5 },                                         { 4, 10 }, { 4, 11 }, { 4, 12 }, { 4, 13 }
};

//rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
led_config_t g_led_config = { {
/**
 * RGB Layout
 * 
 *  0_0,  0_1,  0_2,  0_3,  0_4,  0_5,  0_6,  0_7,  0_8,  0_9, 0_10, 0_11, 0_12, 0_13
 *  1_0,  1_1,  1_2,  1_3,  1_4,  1_5,  1_6,  1_7,  1_8,  1_9, 1_10, 1_11, 1_12, ----
 *  2_0,  2_1,  2_2,  2_3,  2_4,  2_5,  2_6,  2_7,  2_8,  2_9, 2_10, 2_11, 2_12, 2_13
 *  3_0,  3_1,  3_2,  3_3,  3_4,  3_5,  3_6,  3_7,  3_8,  3_9, 3_10, 3_11, 3_12, ----
 *  4_0,  4_1,  4_2,  ---,  ---,  4_5,  ---,  ---,  ---,  ---, 4_10, 4_11, 4_12, 4_13
 * 
 */
	// Key Matrix to LED Index
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 },
	{ 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, NO_LED },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 },
	{ 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, NO_LED, 53 },
	{ 54, 55, 56, NO_LED, NO_LED, 57, NO_LED, NO_LED, NO_LED, NO_LED, 58, 59, 60, 61 }
}, {
	// Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
	{ 0, 0 }, { 16, 0 }, { 32, 0 }, { 48, 0 }, { 64, 0 }, {80, 0 }, { 96, 0 }, { 112, 0 }, { 128, 0 }, { 144, 0 }, {160, 0 }, {176, 0 }, { 192, 0 }, { 224, 0 },
	// Tab, Q, W, E, R, T, Y, U, I, O, P, [, ]
	{ 0, 16 }, { 16, 16 }, { 32, 16 }, { 48, 16 }, { 64, 16 }, {80, 16 }, { 96, 16 }, { 112, 16 }, { 128, 16 }, { 144, 16 }, {160, 16 }, {176, 16 }, { 192, 16 },
	// Caps Lock, A, S, D, F, G, H, J, K, L, ;, ', #, Enter
	{ 0, 32 }, { 16, 32 }, { 32, 32 }, { 48, 32 }, { 64, 32 }, {80, 32 }, { 96, 32 }, { 112, 32 }, { 128, 32 }, { 144, 32 }, {160, 32 }, {176, 32 }, { 192, 32 }, { 224, 32 },
	// Shift, \, Z, X, C, V, B, N, M, ,, ., /, Shift
	{ 0, 48 }, { 16, 48 }, { 32, 48 }, { 48, 48 }, { 64, 48 }, {80, 48 }, { 96, 48 }, { 112, 48 }, { 128, 48 }, { 144, 48 }, {160, 48 }, {176, 48 }, { 224, 48 },
	// Ctrl, Win, Alt, Space, AltGr, Win, Fn, Ctrl
	{ 0, 64 }, { 16, 64 }, { 32, 64 }, {80, 64 }, {160, 64 }, {176, 64 }, { 192, 64 }, { 224, 64 }
}, {
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
	5, 5, 5, 4, 5, 5, 5, 5
	
} }; 

#ifndef MBI5042GP_GCLK_SRC
#    define MBI5042GP_GCLK_SRC PWM0
#endif
#ifndef MBI5042GP_DCLK
#    define MBI5042GP_DCLK PD4
#endif
#ifndef MBI5042GP_LE
#    define MBI5042GP_LE PD3
#endif

/** The PWM buffers the full rows of 16 PWM registers in each MBI5042 driver
 *  The buffers are arranged in serial format
 *  (MSB_R, MSB_G, MSB_B...LSB_R, LSB_G, LSB_B)
 *  as needed by the SDO pins on the MCU (R is B14; G is B13; B is B12)
 *
 *  g_pwm_buffer has the DCLK-able output for an "R" row, a "G" row, and a "B" row of PWM
 */
uint16_t g_pwm_buffer[MBI5042GP_ROW_COUNT][16 * 16];

bool    g_pwm_buffer_update_required = false;
uint8_t g_pwm_buffer_row             = 0;

void MBI5042GP_init(void) {
    /* Initialise all PWM arrays to zero.
     * Perform one group transfer to turn LEDs off
     *
     * If there's a DMA requirement, set up DMA subsystems
     */
    for (int i = 0; i < MBI5042GP_ROW_COUNT; i++) {
        for (int j = 0; j < 256; j++) {
            g_pwm_buffer[i][j] = 0;
        }
    }

#if MBI5042GP_GCLK_SRC == PWM0
    /* Setup PWM0 control registers for 2MHz GCLK
     * and also 50 percentage PWM duty (makes a nice clock)
     *
     * Set PWM1 to be used as a 2kHz timer (interrupt but no output pin)
     * which is used for row refresh/enable.
     */

    /* Enable PWM module clock */
    // CLK_EnableModuleClock(PWM01_MODULE);
    // clks_lld_enable_module_clock(PWM01_MODULE);
    clks_lld_enable_module_clock(PWM01_ModuleNum);

    /* Select PWM module clock source */
    // CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HCLK | CLK_CLKSEL2_PWM01_EXT_HCLK, 0);
    // clks_lld_set_module_clock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HCLK | CLK_CLKSEL2_PWM01_EXT_HCLK, 0);
    clks_lld_set_module_clock(PWM01_ModuleNum, CLK_CLKSEL1_PWM01_S_HCLK, 0);

    /* Combined method to configure PWM0 */
    // PWM_ConfigOutputChannel(PWMA, PWM_CH0, MBI5042GP_GCLK_SPD, 50);
    pwm_lld_config_output_channel(PWMA, PWM_CH0, MBI5042GP_GCLK_SPD, 50);

    /* Enable PWM Output path for PWMA channel 0 */
    // PWM_EnableOutput(PWMA, 0x1);
    (PWMA)->POE |= PWM_CH1;

    /* Set GPIO PA.12/PWM0 to be PWM0 */
    SYS->GPA_MFP |= SYS_GPA_MFP_PA12_PWM0;

    /* PWM1 Config */
    /* Combined method to configure PWM1 */
    // PWM_ConfigOutputChannel(PWMA, PWM_CH1, MBI5042GP_REFRESH_SPD, 50);
    pwm_lld_config_output_channel(PWMA, PWM_CH1, MBI5042GP_REFRESH_SPD, 50);

    /* Set interrupt handler */
    nvicEnableVector(PWMA_IRQn, 3);

    /* Need an interrupt for PWM1 */
    // (PWMA)->PIER = (PWMA)->PIER & ~(PWM_PIER_INT01TYPE_Msk | PWM_PIER_PWMIE1_Msk);
    pwm_lld_enable_period_int(PWMA, PWM_CH1, PWM_PERIOD_INT_UNDERFLOW);

    /* Start PWM0 and PWM1 */
    // PWM_Start(PWMA, (0x1u << PWM_CH0 | 0x1u << PWM_CH1));
    pwm_lld_start(PWMA, (0x1u << PWM_CH0 | 0x1u << PWM_CH1));

#elif
#endif

    MBI5042GP_disable_rows();

    MBI5042GP_set_current_gain(0b000011u);
}

/**
 * @brief Set LED driver current gain
 * @detail The MBI5042 has a 6-bit current gain value (000000b ~ 111111b)
 * used to adjust the global brightness of the LEDs attached to the PWM outputs
 *
 * Default value is 101011b
 *
 * Use MBI5042_CURRENT_GAIN to pass from keyboard config
 */
void MBI5042GP_set_current_gain(uint8_t gain) {
    /** MB data transfer requires:
     *      Tell chip config register change is coming (Enable Write Configutarion)
     *      Pass config register data (Write Configuration Register)
     */
    uint16_t regConfig = 0b00111111u & gain;

    regConfig <<= 4;
    regConfig |= MBI5042GP_CFGREG_DEFAULT;

    MBI5042GP_write_config_register(regConfig);
}

/**
 * @brief   Write configuration register ONLY DURING INIT
 * @detail  Set the contents of the configuration register (see top for bitfields)
 *          Each register write needs 2 * 16 bit transfers (1 x setup and 1 x data)
 *
 * For the Ducky One 2 mini there are 3 drivers, so output all three configs at once
 */
void MBI5042GP_write_config_register(uint16_t regValue) {
    uint32_t b_mask;
    uint16_t tmp_r, tmp_g, tmp_b;

    /* Set Mask for GPIOB */
    b_mask    = PB->DMASK;
    PB->DMASK = ~(0x1u << 14 | 0x1u << 13 | 0x1u << 12);

    /* LE Low & DCLK Low */
    MBI5042GP_LE   = PAL_LOW;
    MBI5042GP_DCLK = PAL_LOW;

    /* Do one DCLK cycle */
    MBI5042GP_DCLK = PAL_HIGH;
    MBI5042GP_DCLK = PAL_LOW;

    /* Set LE High */
    MBI5042GP_LE = PAL_HIGH;

    /* Loop 15 - Enable Write Configuration */
    for (int i = 0; i < 15; i++) {
        /* Cycle DCLK */
        MBI5042GP_DCLK = PAL_HIGH;
        MBI5042GP_DCLK = PAL_LOW;
    }

    /* Reset LE Low */
    MBI5042GP_LE = PAL_LOW;

    /* Loop 16 - Transfer actual command data to all 3 LED drivers */
    for (int i = 0; i < 16; i++) {
        tmp_r = tmp_g = tmp_b = regValue;
        /* Set data bit */
        uint16_t bits = ((0x1u & (tmp_r >> 15)) << 14) | ((0x1u & (tmp_g >> 15)) << 13) | ((0x1u & (tmp_b >> 15)) << 12);
        PB->DOUT      = bits;

        /* Cycle DCLK */
        MBI5042GP_DCLK = PAL_HIGH;
        MBI5042GP_DCLK = PAL_LOW;

        if (i == 5) {
            MBI5042GP_LE = PAL_HIGH;
        }

        /* Next bit to sample */
        regValue <<= 1;
    }

    /* Put GPIOB DMASK back */
    PB->DMASK = b_mask;

    /* Reset LE Low */
    MBI5042GP_LE = PAL_LOW;
}

void MBI5042GP_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    /*
     * @brief Pick a colour! Any colour!
     */
    // led_config_t led;
    mbi_led led_pos;

    if (index >= 0 && index < DRIVER_LED_TOTAL) {
        // Convert index into row/column
        led_pos = g_mbi_leds[index];

        // MBI5042GP_planar_recode(led.matrix_co.row, 15 - (led.matrix_co.col), red, green, blue);
        if (index == 27 && IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
            MBI5042GP_planar_recode(led_pos.row, led_pos.col, 0xff, 0xff, 0xff);
        } else {
            MBI5042GP_planar_recode(led_pos.row, led_pos.col, red, green, blue);
        }

        g_pwm_buffer_update_required = true;
    }
}

void MBI5042GP_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    /*
     * brief Set every led to the provided colour
     */

    for (int i = 0; i < MBI5042GP_ROW_COUNT; i++) {
        for (int j = 0; j < 16; j++) {
            if (i == 2) {
                if (j == 0) {
                    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
                        MBI5042GP_planar_recode(i, j, 0xff, 0xff, 0xff);
                    }
                }
            } else {
                MBI5042GP_planar_recode(i, j, red, green, blue);
            }
        }
    }

    g_pwm_buffer_update_required = true;
}

void MBI5042GP_update_pwm_buffers(void) {
    /**
     * Pass current PWM row to MBI5042GP shift registers
     *
     * LE low
     * Outer Loop 16 (one per register transfer - high to low):
     *      Inner Loop 16 (one per PWM bit):
     *          R_SDIN, G_SDIN & B_SDIN write
     *          DCLK High
     *          DCLK Low
     *          For final loop, set LE High
     *
     * Send Global Latch (16 DCLKs with LE high for last 3)
     *
     * Disable current row
     *
     * Reset PWM count:
     * Loop 3:
     *      DCLK High
     *      DCLK Low
     * LE High
     * Loop 13:
     *      DCLK High
     *      DCLK Low
     * LE Low
     *
     * Select new row (row meant for above data)
     */

    uint32_t b_mask;

    /* Set Mask for GPIOB */
    b_mask    = PB->DMASK;
    PB->DMASK = ~(0x1u << 14 | 0x1u << 13 | 0x1u << 12);

    // LE Low & DCLK Low
    MBI5042GP_LE   = PAL_LOW;
    MBI5042GP_DCLK = PAL_LOW;

    for (int i = 0; i < 16; i++) {
        /* Inner Loop 16 */
        for (int j = 0; j < 16; j++) {
            /* R_SDIN/G_SDIN/B_SDIN write */
            PB->DOUT = g_pwm_buffer[g_pwm_buffer_row][16 * (15 - i) + j];

            // If j is 15 set LE High
            if (j == 15) {
                MBI5042GP_LE = PAL_HIGH;
            }

            /* Cycle DCLK */
            MBI5042GP_DCLK = PAL_HIGH;
            MBI5042GP_DCLK = PAL_LOW;
        }  // Inner Loop 16

        // LE Low
        MBI5042GP_LE = PAL_LOW;
    }

    /* Send Global Latch */
    for (int i = 0; i < 16; i++) {
        /* Cycle DCLK */
        MBI5042GP_DCLK = PAL_HIGH;
        MBI5042GP_DCLK = PAL_LOW;

        //  if i is 13 set LE high
        if (i == 13) {
            MBI5042GP_LE = PAL_HIGH;
        }
    }

    // Reset LE Low
    MBI5042GP_LE = PAL_LOW;

    // Reset Masks
    PB->DMASK = b_mask;

    // Disable current row
    MBI5042GP_disable_rows();

    // Reset PWM count
    // 3 DCLK cycles
    for (int i = 0; i < 3; i++) {
        MBI5042GP_DCLK = PAL_HIGH;
        MBI5042GP_DCLK = PAL_LOW;
    }

    // Set LE High
    MBI5042GP_LE = PAL_HIGH;

    // Loop 13 to generate PWM count reset
    for (int i = 0; i < 13; i++) {
        MBI5042GP_DCLK = PAL_HIGH;
        MBI5042GP_DCLK = PAL_LOW;
    }

    // Set LE Low
    MBI5042GP_LE = PAL_LOW;

    // Set new row
    MBI5042GP_enable_row(g_pwm_buffer_row);

    // increment row count + check
    g_pwm_buffer_row++;
    if (g_pwm_buffer_row >= MBI5042GP_ROW_COUNT) {
        g_pwm_buffer_row = 0;
    }
}

/**
 * @brief Write is a zero-output routine to handle the FLUSH from the RGB LED driver calls
 * @details Since the RGB data is recoded every time a colour is changed (by the relevant
 * single or "all" set_color routines), there is no point at which a mass flush of RGB
 * information is needed. The MBI5042GP needs to be fed 16 sets of R, G, or B information
 * for each row on a totally different schedule from the animations that affect the colours.
 */
void MBI5042GP_write_pwm_buffers(void) {}

/**
 * @brief Bitwise reorder of RGB information.
 * @details Recode the 8-bit standard RGB to 16-bit separated values and
 * turn the 16-bit "chunky" values into 16 sequential bitwise "planes"
 */
void MBI5042GP_planar_recode(int row, int column, uint8_t red, uint8_t green, uint8_t blue) {
    uint16_t cur_r = pgm_read_word(&CIE1931_16_CURVE[red]);
    uint16_t cur_g = pgm_read_word(&CIE1931_16_CURVE[green]);
    uint16_t cur_b = pgm_read_word(&CIE1931_16_CURVE[blue]);

    // int row, column;

    for (int i = 0; i < 16; i++) {
        uint16_t tmp_r = cur_r;
        uint16_t tmp_g = cur_g;
        uint16_t tmp_b = cur_b;

        // g_pwm_buffer[row][0][i * column] = ;
        g_pwm_buffer[row][i + (column * 16)] = ((0x1u & (tmp_r >> 15)) << 14) | ((0x1u & (tmp_g >> 15)) << 13) | ((0x1u & (tmp_b >> 15)) << 12);
        cur_r <<= 1;
        cur_g <<= 1;
        cur_b <<= 1;
    }
}

/**
 * @brief Disable all LED Rows
 */
void MBI5042GP_disable_rows(void) {
    // Quick and dirty hardcoded row clear
    // 5 rows total
    // TODO: Create enum that can be configured for individual MCUs

    // Row 0
    PC4 = PAL_LOW;

    // Row 1
    PC5 = PAL_LOW;

    // Row 2
    PB3 = PAL_LOW;

    // Row 3
    PB2 = PAL_LOW;

    // Row 4
    PD9 = PAL_LOW;
}

/**
 * @brief Disable specific LED row
 */
void MBI5042GP_disable_row(int row) {
    switch (row) {
        case 0:  // Row 0
            PC4 = PAL_LOW;
            break;
        case 1:  // Row 1
            PC5 = PAL_LOW;
            break;
        case 2:  // Row 2
            PB3 = PAL_LOW;
            break;
        case 3:  // Row 3
            PB2 = PAL_LOW;
            break;
        case 4:  // Row 4
            PD9 = PAL_LOW;
            break;
    }
}

/**
 * @brief Enable specific LED row
 */
void MBI5042GP_enable_row(int row) {
    switch (row) {
        case 0:  // Row 0
            PC4 = PAL_HIGH;
            break;
        case 1:  // Row 1
            PC5 = PAL_HIGH;
            break;
        case 2:  // Row 2
            PB3 = PAL_HIGH;
            break;
        case 3:  // Row 3
            PB2 = PAL_HIGH;
            break;
        case 4:  // Row 4
            PD9 = PAL_HIGH;
            break;
    }
}

OSAL_IRQ_HANDLER(NUC123_PWMA_HANDLER) {
    OSAL_IRQ_PROLOGUE();

    /* Check for PWM1 underflow IRQ */
    // if (PWM_GetPeriodIntFlag(PWMA, PWM_CH1) == 1) {
    //     PWM_ClearPeriodIntFlag(PWMA, PWM_CH1);
    //     MBI5042GP_update_pwm_buffers();
    // }
    if (pwm_lld_get_period_int(PWMA, PWM_CH1) == 1) {
        pwm_lld_clear_period_int(PWMA, PWM_CH1);
        MBI5042GP_update_pwm_buffers();
    }

    OSAL_IRQ_EPILOGUE();
}

static void init(void) { MBI5042GP_init(); }

static void flush(void) { MBI5042GP_write_pwm_buffers(); }

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = MBI5042GP_set_color,
    .set_color_all = MBI5042GP_set_color_all,
};
