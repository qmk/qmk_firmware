/* Copyright 2019 /u/KeepItUnder
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

#ifndef MBI5042GP_GCLK_SRC
    #define MBI5042GP_GCLK_SRC PWM0
#endif
#ifndef MBI5042GP_DCLK
    #define MBI5042GP_DCLK PD4
#endif
#ifndef MBI5042GP_LE
    #define MBI5042GP_LE PD3
#endif

/** The PWM buffers the full rows of 16 PWM registers in each MBI5042 driver
 *  The buffers are arranged in serial format
 *  (MSB_R, MSB_G, MSB_B...LSB_R, LSB_G, LSB_B)
 *  as needed by the SDO pins on the MCU (R is B14; G is B13; B is B12)
 *  
 *  g_pwm_buffer has the DCLK-able output for an "R" row, a "G" row, and a "B" row of PWM
 */
uint16_t g_pwm_buffer[MBI5042GP_ROW_COUNT][16*16];

bool g_pwm_buffer_update_required = false;
uint8_t g_pwm_buffer_row = 0;

void MBI5042GP_init( void ) {
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

    #if (MBI5042GP_GCLK_SRC == PWM0)
        /* Setup PWM control registers for 2MHz (makes a nice clock)        
         * and also 50 percentage PWM
         * 
         * Set PWM1 to be used as a 2kHz timer (interrupt but no output pin)
         */

        /* Enable PWM module clock */
        CLK_EnableModuleClock(PWM01_MODULE);

        /* Select PWM module clock source */
        CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HCLK | CLK_CLKSEL2_PWM01_EXT_HCLK, 0);

        /* Combined method to configure PWM0 */
        PWM_ConfigOutputChannel(PWMA, PWM_CH0, MBI5042GP_GCLK_SPD, 50);

        /* Enable PWM Output path for PWMA channel 0 */
        PWM_EnableOutput(PWMA, 0x1);

        /* Set GPIO PA.12/PWM0 to be PWM0 */
        SYS->GPA_MFP |= SYS_GPA_MFP_PA12_PWM0;

        /* PWM1 Config */
        /* Combined method to configure PWM1 */
        PWM_ConfigOutputChannel(PWMA, PWM_CH1, MBI5042GP_REFRESH_SPD, 50);

        /* Set interrupt handler */
        nvicEnableVector(PWMA_IRQn, 1);

        /* Need an interrupt for PWM1 */
        PWM_EnablePeriodInt(PWMA, PWM_CH1, PWM_PERIOD_INT_UNDERFLOW);

        /* Start PWM0 and PWM1 */
        PWM_Start(PWMA, (0x1u << PWM_CH0 | 0x1u << PWM_CH1));

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
void MBI5042GP_set_current_gain( uint8_t gain ) {
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
void MBI5042GP_write_config_register( uint16_t regValue ) {
    uint32_t b_mask;
    uint16_t tmp_r, tmp_g, tmp_b;

    /* Set Mask for GPIOB */
    b_mask = PB->DMASK;
    PB->DMASK = ~(0x1u << 14 | 0x1u << 13 | 0x1u << 12);

    /* LE Low & DCLK Low */
    MBI5042GP_LE = PAL_LOW;
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
        PB->DOUT = bits;

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

void MBI5042GP_set_color( int index, uint8_t red, uint8_t green, uint8_t blue ) {
    /*
     * @brief Pick a colour! Any colour!
     */
    //led_config_t led;
    mbi_led led_pos;

    if ( index >= 0 && index < DRIVER_LED_TOTAL ) {
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

void MBI5042GP_set_color_all( uint8_t red, uint8_t green, uint8_t blue ) {
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

void MBI5042GP_update_pwm_buffers( void ) {
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
    b_mask = PB->DMASK;
    PB->DMASK = ~(0x1u << 14 | 0x1u << 13 | 0x1u << 12);

    // LE Low & DCLK Low
    MBI5042GP_LE = PAL_LOW;
    MBI5042GP_DCLK = PAL_LOW;

    for (int i = 0; i < 16; i++) {
        /* Inner Loop 16 */
        for (int j = 0; j < 16; j++) {

            /* R_SDIN/G_SDIN/B_SDIN write */
            PB->DOUT = g_pwm_buffer[g_pwm_buffer_row][16*(15 - i) + j];

            // If j is 15 set LE High
            if (j == 15) {
                MBI5042GP_LE = PAL_HIGH;
            }

            /* Cycle DCLK */
            MBI5042GP_DCLK = PAL_HIGH;
            MBI5042GP_DCLK = PAL_LOW;
        } // Inner Loop 16

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
 * single of "all" set_color routines), there is no point at which a mass flush of RGB
 * information is needed. The MBI5042GP needs to be fed 16 sets of R, G, or B information
 * for each row on a totally different schedule from the animations that affect the colours.
 */
void MBI5042GP_write_pwm_buffers( void ) {

}

/**
 * @brief Bitwise reorder of RGB information.
 * @details Recode the 8-bit standard RGB to 16-bit separated values and
 * turn the 16-bit "chunky" values into 16 sequential bitwise "planes"
 */
void MBI5042GP_planar_recode( int row, int column, uint8_t red, uint8_t green, uint8_t blue) {
    uint16_t cur_r = pgm_read_word( &CIE1931_16_CURVE[red] );
    uint16_t cur_g = pgm_read_word( &CIE1931_16_CURVE[green] );
    uint16_t cur_b = pgm_read_word( &CIE1931_16_CURVE[blue] );

    //int row, column;

    for (int i = 0; i < 16; i ++) {
        uint16_t tmp_r = cur_r;
        uint16_t tmp_g = cur_g;
        uint16_t tmp_b = cur_b;

        //g_pwm_buffer[row][0][i * column] = ;
        g_pwm_buffer[row][i + (column * 16)] = ((0x1u & (tmp_r >> 15)) << 14) | ((0x1u & (tmp_g >> 15)) << 13) | ((0x1u & (tmp_b >> 15)) << 12);
        cur_r <<= 1;
        cur_g <<= 1;
        cur_b <<= 1;
    }
}

/**
 * @brief Disable all LED Rows
 */
void MBI5042GP_disable_rows( void ) {

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
void MBI5042GP_disable_row( int row ) {
    switch (row) {
        case 0: // Row 0
            PC4 = PAL_LOW;
            break;
        case 1: // Row 1
            PC5 = PAL_LOW;
            break;
        case 2: // Row 2
            PB3 = PAL_LOW;
            break;
        case 3: // Row 3
            PB2 = PAL_LOW;
            break;
        case 4: // Row 4
            PD9 = PAL_LOW;
            break;
    }
}

/**
 * @brief Enable specific LED row
 */
void MBI5042GP_enable_row( int row ) {
    switch (row) {
        case 0: // Row 0
            PC4 = PAL_HIGH;
            break;
        case 1: // Row 1
            PC5 = PAL_HIGH;
            break;
        case 2: // Row 2
            PB3 = PAL_HIGH;
            break;
        case 3: // Row 3
            PB2 = PAL_HIGH;
            break;
        case 4: // Row 4
            PD9 = PAL_HIGH;
            break;
    }
}



OSAL_IRQ_HANDLER(NUC123_PWMA_HANDLER) {
    OSAL_IRQ_PROLOGUE();

    /* Check for PWM1 underflow IRQ */
    if (PWM_GetPeriodIntFlag(PWMA, PWM_CH1) == 1) {
        PWM_ClearPeriodIntFlag(PWMA, PWM_CH1);
        MBI5042GP_update_pwm_buffers();
    }

    OSAL_IRQ_EPILOGUE();
}
