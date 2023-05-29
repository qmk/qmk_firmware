/* Copyright 2023 Dimitris Mantzouranis <d3xter93@gmail.com>
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

#include "sled1734x.h"
#include "i2c_master.h"
#include "wait.h"

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b1110100 (0x74) AD <-> GND
// 0b1110111 (0x77) AD <-> VCC
// 0b1110101 (0x75) AD <-> SCL
// 0b1110110 (0x76) AD <-> SDA
#define SLED_ADDR_DEFAULT 0x74

/* Function Registers Declarations */
#define SLED_REG_CONFIG 0x00 // Configuration register
// Sync Mode
// 00 - High Impedance, 01 Master, 10 Slave
#define SLED_REG_CONFIG_SYNC 0x00

#define SLED_REG_PICTUREDISPLAY 0x01 // Picture Display register
// Matrix Type
// 00 - Type-1, 01 Type-2, 10 Type-3, 11 Type-4
#define SLED_REG_PICTUREDISPLAY_MATRIXTYPE 0x10

#define SLED_REG_DISPLAYOPTION 0x05 // Display Option register
// Blink Frame and Enable. Default to Disabled
#define SLED_REG_DISPLAYOPTION_BLINKFRAME 0x00

#define SLED_REG_AUDIOSYNC 0x06 // Audio Sync register
// Audio Sync Enable. Default to Disabled
#define SLED_REG_AUDIOSYNC_ENABLE 0x00

#define SLED_REG_BREATHCONTROL1 0x08 // Breath Control 1 register
// Fade Out and Fade In Time setting. Default to 0
#define SLED_REG_BREATHCONTROL_FADE 0x00

#define SLED_REG_BREATHCONTROL2 0x09 // Breath Control 2 register
// Breathe and Continuous Breathe Enable. Default to Disabled
#define SLED_REG_BREATHCONTROL_BREATHE 0x00

#define SLED_REG_SHUTDOWN 0x0A // Shutdown register
// 0 - SW Shutdown Mode, 1 Normal Mode
#define SLED_REG_SHUTDOWN_MODE 0x00
#define SLED_REG_NORMAL_MODE 0x01

#define SLED_REG_AGC 0x0B // AGC Control register
// Audio Gain Control. Mode, Gain and Enable setting. Default to Disabled
#define SLED_REG_AGC_MODE 0x00

#define SLED_REG_STAGGEREDDELAY 0x0D // Staggered Delay register
// Staggered Delay Timing setting. Default to 0
#define SLED_REG_STAGGEREDDELAY_TIMING 0x00

#define SLED_REG_SLEWRATECONTROL 0x0E // Slew Rate Control register
// Slew Rate Control Enable. Default to Enabled
#define SLED_REG_SLEWRATECONTROL_ENABLE 0x01

#define SLED_REG_CURRENTCONTROL 0x0F // Current Control register
// Current Control Enable. Default to Disabled
#define SLED_REG_CURRENTCONTROL_ENABLE 0xB0

#define SLED_REG_OPENSHORT1 0x10 // Open Short Test 1 register
// Open Short Detection Mode. Default to Disabled
#define SLED_REG_OPENSHORT1_MODE 0x00

#define SLED_REG_OPENSHORT2 0x11 // Open Short Test 2 register
// Open Short Detection Interrupt. Default to Disabled
#define SLED_REG_OPENSHORT2_MODE 0x00

#define SLED_REG_VAF1 0x14 // VAF 1 register
// VAF fine tune setting. Default to 0x44
#define SLED_REG_VAF1_TUNE 0x44

#define SLED_REG_VAF2 0x15 // VAF 2 register
// VAF control setting. Default to 0x04
#define SLED_REG_VAF2_MODE 0x04

/* Configure Command Registers Declarations */
#define SLED_COMMANDREGISTER 0xFD
#define SLED_PAGE_FRAME_1 0x00
#define SLED_PAGE_FRAME_2 0x01
#define SLED_PAGE_FUNCTION 0x0B
#define SLED_PAGE_DETECTION 0x0C
#define SLED_PAGE_LEDVAF 0x0D

#ifndef SLED_TIMEOUT
#    define SLED_TIMEOUT 100
#endif

#ifndef SLED_PERSISTENCE
#    define SLED_PERSISTENCE 0
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[17];

// These buffers match the SLED1734X PWM registers 0x20-0x9F.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in SLED1734X_write_pwm_buffer() but it's
// probably not worth the extra complexity.
uint8_t g_pwm_buffer[DRIVER_COUNT][256];
bool    g_pwm_buffer_update_required[DRIVER_COUNT] = {false};

uint8_t g_led_control_registers[DRIVER_COUNT][32]             = {{0}};
bool    g_led_control_registers_update_required[DRIVER_COUNT] = {false};

// This is the bit pattern in the LED control registers
// (for matrix type 3, using split frames)
//
//  CHA - reg  - b15  b14  b13  b12  b11  b10  b09  b08  b07  b06  b05  b04  b03  b02  b01  b00
// --------------------------------------------------------------------------------------------
//  CA1 - 0x00 | R13, R12, R11, R10, R09, R08, R07, R06, R05, R04, R03, R02, R01, R00,  - ,  -
//  CA2 - 0x02 | G13, G12, G11, G10, G09, G08, G07, G06, G05, G04, G03, G02, G01, G00,  - ,  -
//  CA3 - 0x04 | B13, B12, B11, B10, B09, B08, B07, B06, B05, B04, B03, B02, B01, B00,  - ,  -
//  CA4 - 0x06 | R27, R26, R25, R24, R23, R22, R21, R20, R19, R18, R17,  - ,  - , R16, R15, R14
//  CA5 - 0x08 | G27, G26, G25, G24, G23, G22, G21, G20, G19, G18, G17,  - ,  - , G16, G15, G14
//  CA6 - 0x0A | B27, B26, B25, B24, B23, B22, B21, B20, B19, B18, B17,  - ,  - , B16, B15, B14
//  CA7 - 0x0C | R41, R40, R39, R38, R37, R36, R35, R34,  - ,  - , R33, R32, R31, R30, R29, R28
//  CA8 - 0x0E | G41, G40, G39, G38, G37, G36, G35, G34,  - ,  - , G33, G32, G31, G30, G29, G28
// --------------------------------------------------------------------------------------
//  CA9 - 0x00 | B41, B40, B39, B38, B37, B36, B35, B34,  - ,  - , B33, B32, B31, B30, B29, B28
//  CB1 - 0x02 | R55, R54, R53, R52, R51,  - ,  - , R50, R49, R48, R47, R46, R45, R44, R43, R42
//  CB2 - 0x04 | G55, G54, G53, G52, G51,  - ,  - , G50, G49, G48, G47, G46, G45, G44, G43, G42
//  CB3 - 0x06 | B55, B54, B53, B52, B51,  - ,  - , B50, B49, B48, B47, B46, B45, B44, B43, B42
//  CB4 - 0x08 | R69, R68,  - ,  - , R67, R66, R65, R64, R64, R62, R61, R60, R59, R58, R57, R56
//  CB5 - 0x0A | G69, G68,  - ,  - , G67, G66, G65, G64, G64, G62, G61, G60, G59, G58, G57, G56
//  CB6 - 0x0C | B69, B68,  - ,  - , B67, B66, B65, B64, B64, B62, B61, B60, B59, B58, B57, B56
//  CB7 - 0x0E |  - ,  - ,  - ,  - ,  - ,  - ,  - ,  - ,  - ,  - ,  - ,  - ,  - ,  - ,  - ,  -
// --------------------------------------------------------------------------------------

void SLED1734X_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;

#if SLED_PERSISTENCE > 0
    for (uint8_t i = 0; i < SLED_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, SLED_TIMEOUT) == 0) break;
    }
#else
    i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, SLED_TIMEOUT);
#endif
}

bool SLED1734X_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer) {
    uint8_t page_frame_select[2];
    page_frame_select[0] = SLED_COMMANDREGISTER;
    // select the first frame
    page_frame_select[1] = SLED_PAGE_FRAME_1;
    i2c_transmit(addr << 1, page_frame_select, 2, SLED_TIMEOUT);
    // transmit PWM registers in 8 transfers of 16 bytes
    // g_twi_transfer_buffer[] is 17 bytes

    // iterate over the pwm_buffer contents at 16 byte intervals
    for (int i = 0; i < SLED_FRAME_OFFSET; i += 16) {
        // set the first register, e.g. 0x20, 0x30, 0x40, etc.
        g_twi_transfer_buffer[0] = SLED_OFFSET + i;
        // copy the data from i to i+15
        // device will auto-increment register for data after the first byte
        // thus this sets registers 0x20-0x2F, 0x30-0x3F, etc. in one transfer
        for (int j = 0; j < 16; j++) {
            g_twi_transfer_buffer[1 + j] = pwm_buffer[i + j];
        }

#if SLED_PERSISTENCE > 0
        for (uint8_t i = 0; i < SLED_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, SLED_TIMEOUT) != 0) return false;
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, SLED_TIMEOUT) != 0) return false;
#endif
    }
    // select the second frame
    page_frame_select[1] = SLED_PAGE_FRAME_2;
    i2c_transmit(addr << 1, page_frame_select, 2, SLED_TIMEOUT);
    // transmit PWM registers in 8 transfers of 16 bytes
    // g_twi_transfer_buffer[] is 17 bytes

    // iterate over the pwm_buffer contents at 16 byte intervals
    for (int i = 0; i < SLED_FRAME_OFFSET; i += 16) {
        // set the first register, e.g. 0x20, 0x30, 0x40, etc.
        g_twi_transfer_buffer[0] = SLED_OFFSET + i;
        // copy the data from i to i+15
        // device will auto-increment register for data after the first byte
        // thus this sets registers 0x20-0x2f, 0x30-0x3f, etc. in one transfer
        for (int j = 0; j < 16; j++) {
            g_twi_transfer_buffer[1 + j] = pwm_buffer[SLED_FRAME_OFFSET + i + j];
        }

#if SLED_PERSISTENCE > 0
        for (uint8_t i = 0; i < SLED_PERSISTENCE; i++) {
            if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, SLED_TIMEOUT) != 0) return false;
        }
#else
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 17, SLED_TIMEOUT) != 0) return false;
#endif
    }
    return true;
}

void SLED1734X_init(uint8_t addr) {
    // Toggle the SDB pin HIGH to disable the hardware power down state
    // Not always connected to the MCU, hence optional here.
#ifdef SLED_SDB_PIN
    setPinOutput(SLED_SDB_PIN);
    writePinHigh(SLED_SDB_PIN);
#endif
    // Hardware powerup requires 180us.
    wait_us(180);
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, first enable software shutdown,
    // then set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // select "function register" bank
    SLED1734X_write_register(addr, SLED_COMMANDREGISTER, SLED_PAGE_FUNCTION);

    // enable software shutdown
    SLED1734X_write_register(addr, SLED_REG_SHUTDOWN, SLED_REG_SHUTDOWN_MODE);

    // sync mode
    SLED1734X_write_register(addr, SLED_REG_CONFIG, SLED_REG_CONFIG_SYNC);
    // matrix type
    SLED1734X_write_register(addr, SLED_REG_PICTUREDISPLAY, SLED_REG_PICTUREDISPLAY_MATRIXTYPE);
    // blink frame
    SLED1734X_write_register(addr, SLED_REG_DISPLAYOPTION, SLED_REG_DISPLAYOPTION_BLINKFRAME);
    // audio sync off
    SLED1734X_write_register(addr, SLED_REG_AUDIOSYNC, SLED_REG_AUDIOSYNC_ENABLE);
    // breathe control
    SLED1734X_write_register(addr, SLED_REG_BREATHCONTROL1, SLED_REG_BREATHCONTROL_FADE);
    SLED1734X_write_register(addr, SLED_REG_BREATHCONTROL2, SLED_REG_BREATHCONTROL_BREATHE);
    // audio gain off
    SLED1734X_write_register(addr, SLED_REG_AGC, SLED_REG_AGC_MODE);
    // staggered delay off
    SLED1734X_write_register(addr, SLED_REG_STAGGEREDDELAY, SLED_REG_STAGGEREDDELAY_TIMING);
    // slew rate control enable
    SLED1734X_write_register(addr, SLED_REG_SLEWRATECONTROL, SLED_REG_SLEWRATECONTROL_ENABLE);
    // VAF fine tuning
    SLED1734X_write_register(addr, SLED_REG_VAF1, SLED_REG_VAF1_TUNE);
    SLED1734X_write_register(addr, SLED_REG_VAF2, SLED_REG_VAF2_MODE);
    // current control
    SLED1734X_write_register(addr, SLED_REG_CURRENTCONTROL, SLED_REG_CURRENTCONTROL_ENABLE);

    // select page frame 1
    SLED1734X_write_register(addr, SLED_COMMANDREGISTER, SLED_PAGE_FRAME_1);

    // turn off all LEDs in the LED control register
    for (int i = 0x00; i <= 0x0F; i++) {
        SLED1734X_write_register(addr, i, 0x00);
    }

    // turn off all LEDs in the blink control register (not really needed)
    for (int i = 0x10; i <= 0x1F; i++) {
        SLED1734X_write_register(addr, i, 0x00);
    }

    // set PWM on all LEDs to 0
    for (int i = 0x20; i <= 0x9F; i++) {
        SLED1734X_write_register(addr, i, 0x00);
    }

    // select page frame 2
    SLED1734X_write_register(addr, SLED_COMMANDREGISTER, SLED_PAGE_FRAME_2);

    // turn off all LEDs in the LED control register
    for (int i = 0x00; i <= 0x0F; i++) {
        SLED1734X_write_register(addr, i, 0x00);
    }

    // turn off all LEDs in the blink control register (not really needed)
    for (int i = 0x10; i <= 0x1F; i++) {
        SLED1734X_write_register(addr, i, 0x00);
    }

    // set PWM on all LEDs to 0
    for (int i = 0x20; i <= 0x9F; i++) {
        SLED1734X_write_register(addr, i, 0x00);
    }

    // select "function register" bank
    SLED1734X_write_register(addr, SLED_COMMANDREGISTER, SLED_PAGE_FUNCTION);

    // disable software shutdown
    SLED1734X_write_register(addr, SLED_REG_SHUTDOWN, SLED_REG_NORMAL_MODE);
}

void SLED1734X_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    sled1734x_led led;
    if (index >= 0 && index < RGB_MATRIX_LED_COUNT) {
        memcpy_P(&led, (&g_sled1734x_leds[index]), sizeof(led));

        g_pwm_buffer[led.driver][led.r]          = red;
        g_pwm_buffer[led.driver][led.g]          = green;
        g_pwm_buffer[led.driver][led.b]          = blue;
        g_pwm_buffer_update_required[led.driver] = true;
    }
}

void SLED1734X_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        SLED1734X_set_color(i, red, green, blue);
    }
}

void SLED1734X_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    sled1734x_led led;
    memcpy_P(&led, (&g_sled1734x_leds[index]), sizeof(led));

    uint8_t control_register_r = (led.r) / 8;
    uint8_t control_register_g = (led.g) / 8;
    uint8_t control_register_b = (led.b) / 8;

    uint8_t bit_r = (led.r) % 8;
    uint8_t bit_g = (led.g) % 8;
    uint8_t bit_b = (led.b) % 8;

    if (red) {
        g_led_control_registers[led.driver][control_register_r] |= (1 << bit_r);
    } else {
        g_led_control_registers[led.driver][control_register_r] &= ~(1 << bit_r);
    }
    if (green) {
        g_led_control_registers[led.driver][control_register_g] |= (1 << bit_g);
    } else {
        g_led_control_registers[led.driver][control_register_g] &= ~(1 << bit_g);
    }
    if (blue) {
        g_led_control_registers[led.driver][control_register_b] |= (1 << bit_b);
    } else {
        g_led_control_registers[led.driver][control_register_b] &= ~(1 << bit_b);
    }

    g_led_control_registers_update_required[led.driver] = true;
}

void SLED1734X_update_pwm_buffers(uint8_t addr, uint8_t index) {
    if (g_pwm_buffer_update_required[index]) {
        if (!SLED1734X_write_pwm_buffer(addr, g_pwm_buffer[index])) {
            g_led_control_registers_update_required[index] = true;
        }
    }
    g_pwm_buffer_update_required[index] = false;
}

void SLED1734X_update_led_control_registers(uint8_t addr, uint8_t index) {
    if (g_led_control_registers_update_required[index]) {
        // select the first frame
        SLED1734X_write_register(addr, SLED_COMMANDREGISTER, SLED_PAGE_FRAME_1);
        for (int i = 0; i < 16; i++) {
            SLED1734X_write_register(addr, i, g_led_control_registers[index][i]);
        }
        // select the second frame
        SLED1734X_write_register(addr, SLED_COMMANDREGISTER, SLED_PAGE_FRAME_2);
        for (int i = 0; i < 16; i++) {
            SLED1734X_write_register(addr, i, g_led_control_registers[index][i + 16]);
        }
    }
    g_led_control_registers_update_required[index] = false;
}

void SLED1734X_sw_return_normal(uint8_t addr) {
    // Select to function page
    SLED1734X_write_register(addr, SLED_COMMANDREGISTER, SLED_PAGE_FUNCTION);
    // Setting LED driver to normal mode
    SLED1734X_write_register(addr, SLED_REG_SHUTDOWN, SLED_REG_NORMAL_MODE);
}

void SLED1734X_sw_shutdown(uint8_t addr) {
    // Select to function page
    SLED1734X_write_register(addr, SLED_COMMANDREGISTER, SLED_PAGE_FUNCTION);
    // Setting LED driver to shutdown mode
    SLED1734X_write_register(addr, SLED_REG_SHUTDOWN, SLED_REG_SHUTDOWN_MODE);
}
