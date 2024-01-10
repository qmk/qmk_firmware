/**
 * Copyright 2023 astro
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

#include <string.h>

#include "is31fl3729.h"
#include "i2c_master.h"
#include "wait.h"

// addr in gnd: 0x68
// addr in vcc: 0x6E

#define PWM_BUFFER_SIZE     0x90
#define SCALE_BUFFER_SIZE   0x10

// registers
#define PWM_BASE_REG        0x01    // 0x01-0x8F
#define SCALE_BASE_REG      0x90    // 0x90-0x9F

#define CONFIG_REG          0xA0
#define GLOBAL_CURRENT_REG  0xA1
#define PD_PU_REG           0xB0
#define SS_REG              0xB1
#define PWM_FREQ_REG        0xB2
// open short register B3~C4
#define RESET_REG           0xCF

// pullup and pulldown register for SWx and CSy
#define PD_OFFSET           0x04
#define PD_NO               0x00
#define PD_0_5K_SW_OFF      0x01
#define PD_1K_SW_OFF        0x02
#define PD_2K_SW_OFF        0x03
#define PD_1K_ALL           0x04
#define PD_2K_ALL           0x05
#define PD_4K_ALL           0x06
#define PD_8K_ALL           0x07

#ifndef IS31FL3729_PD_DEFAULT
    #define IS31FL3729_PD_DEFAULT PD_NO
#endif

#define PU_OFFSET           0x00
#define PU_NO               0x00
#define PU_0_5K_CS_OFF      0x01
#define PU_1K_CS_OFF        0x02
#define PU_2K_CS_OFF        0x03
#define PU_1K_ALL           0x04
#define PU_2K_ALL           0x05
#define PU_4K_ALL           0x06
#define PU_8K_ALL           0x07

#ifndef IS31FL3729_PU_DEFAULT
    #define IS31FL3729_PU_DEFAULT PU_NO
#endif

// reset command
#define RESET_COMMAND       0xAE

#ifndef IS31FL3729_NUM
    #define IS31FL3729_NUM  2
#endif

#ifndef IS31FL3729_GLOBAL_CURRENT
    #define IS31FL3729_GLOBAL_CURRENT 0xFF
#endif

#ifndef IS31FL3729_SCALE_DEFAULT
    #define IS31FL3729_SCALE_DEFAULT    0xFF
#endif

#define ISSI_TIMEOUT             100

static uint8_t s_pwm_buffer[IS31FL3729_NUM][PWM_BUFFER_SIZE] = {0};
static bool    s_pwm_buffer_update_required[IS31FL3729_NUM] = {false};

void IS31FL3729_init(uint8_t addr, uint8_t index)
{
    // Reset 3729 to default state
    uint8_t data = RESET_COMMAND;
    i2c_writeReg(addr, RESET_REG, &data, 1, ISSI_TIMEOUT);

    wait_ms(10);

    // enable chip
    data = 0x01; // 9x15, lgc 1.4v/0v, disalbe osde
    i2c_writeReg(addr, CONFIG_REG, &data, 1, ISSI_TIMEOUT);

    // set global current
    data = IS31FL3729_GLOBAL_CURRENT;
    i2c_writeReg(addr, GLOBAL_CURRENT_REG, &data, 1, ISSI_TIMEOUT);

    // set pulldown and pullup
    // AS default
    //data = ((IS31FL3729_PD_DEFAULT<<PD_OFFSET) | (IS31FL3729_PU_DEFAULT<<PU_OFFSET));
    //i2c_writeReg(addr, PD_PU_REG, &data, 1, ISSI_TIMEOUT);

    // set scale buffer
    data = IS31FL3729_SCALE_DEFAULT;
    for (int i = 0;i < 0x0F; i++) {
        i2c_writeReg(addr, SCALE_BASE_REG+i, &data, 1, ISSI_TIMEOUT);
    }

    // reset pwm
    memset(s_pwm_buffer[index], 0, PWM_BUFFER_SIZE);
    // set swx first reg address
    for (int i = 0; i < 9; i++) {
        s_pwm_buffer[index][i*0x10] = i*0x10+1;
    }
}

void IS31FL3729_set_color(int index, uint8_t red, uint8_t green, uint8_t blue)
{
    is31_led led = g_is31_leds[index];

    uint8_t driver = led.driver;

    s_pwm_buffer[driver][led.r]   = red;
    s_pwm_buffer[driver][led.g]   = green;
    s_pwm_buffer[driver][led.b]   = blue;
    s_pwm_buffer_update_required[driver] = true;
}

void IS31FL3729_set_color_all(uint8_t red, uint8_t green, uint8_t blue)
{
    for (int i = IS31FL3729_LED_BEGIN; i < IS31FL3729_LED_BEGIN+IS31FL3729_LED_TOTAL; i++) {
        IS31FL3729_set_color(i, red, green, blue);
    }
}

void IS31FL3729_update_pwm_buffers(uint8_t addr, uint8_t index)
{
    if (s_pwm_buffer_update_required[index]) {
        for (int i = 0; i < 9; i++) {
            i2c_transmit(addr, &s_pwm_buffer[index][i*0x10], 0x10, ISSI_TIMEOUT);
        }
        s_pwm_buffer_update_required[index] = false;
    }
}
