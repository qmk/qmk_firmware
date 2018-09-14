/*
Copyright 2018 Massdrop Inc.

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

#ifndef _CLKS_H_
#define _CLKS_H_

#ifndef MD_BOOTLOADER

//From keyboard
#include "config_led.h"
#include "config.h"

#endif //MD_BOOTLOADER

#define PLL_RATIO                   47  //mcu frequency ((X+1)MHz)
#define FREQ_DFLL_DEFAULT     48000000  //DFLL frequency / usb clock
#define FREQ_SPI_DEFAULT       1000000  //spi to 595 shift regs
#define FREQ_I2C0_DEFAULT       100000  //i2c to hub
#define FREQ_I2C1_DEFAULT       I2C_HZ  //i2c to LED drivers
#define FREQ_TC45_DEFAULT      1000000  //1 usec resolution

//I2C1 Set      ~Result     PWM Time (2x Drivers)
//     1000000  1090000
//     900000   1000000     3.82ms
//     800000   860000
//     700000   750000
//     600000   630000
//     580000   615000      6.08ms
//     500000   522000

#define FREQ_XOSC0            16000000

#define CHAN_SERCOM_SPI   2 //shift regs
#define CHAN_SERCOM_I2C0  0 //hub
#define CHAN_SERCOM_I2C1  1 //led drivers
#define CHAN_SERCOM_UART  3 //debug util

//Generator clock channels
#define GEN_DPLL0   0
#define GEN_OSC0    1
#define GEN_TC45    2

#define SERCOM_COUNT 5
#define GCLK_COUNT  12

typedef struct clk_s {
    uint32_t freq_dfll;
    uint32_t freq_dpll[2];
    uint32_t freq_sercom[SERCOM_COUNT];
    uint32_t freq_gclk[GCLK_COUNT];
    uint32_t freq_xosc0;
    uint32_t freq_spi;
    uint32_t freq_i2c0;
    uint32_t freq_i2c1;
    uint32_t freq_uart;
    uint32_t freq_adc0;
} clk_t;

extern volatile clk_t system_clks;
extern volatile uint64_t ms_clk;

void CLK_oscctrl_init(void);
void CLK_reset_time(void);
uint32_t CLK_set_gclk_freq(uint8_t gclkn, uint32_t freq);
uint32_t CLK_enable_timebase(void);
uint32_t CLK_get_ms(void);
uint64_t CLK_get_us(void);
void CLK_delay_us(uint16_t usec);
void CLK_delay_ms(uint64_t msec);

uint32_t CLK_set_spi_freq(uint8_t sercomn, uint32_t freq);
uint32_t CLK_set_i2c0_freq(uint8_t sercomn, uint32_t freq);
uint32_t CLK_set_i2c1_freq(uint8_t sercomn, uint32_t freq);
void CLK_init(void);

#endif // _CLKS_H_
