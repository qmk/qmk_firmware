/*
Copyright 2016 Fred Sundvik <fsundvik@gmail.com>

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

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

static const I2CConfig i2ccfg = {
  400000 // clock speed (Hz); 400kHz max for IS31
};

static const uint8_t led_mask[] = {
	0xFF, 0x00, /* C1-1 -> C1-16 */
	0xFF, 0x00, /* C2-1 -> C2-16 */
	0xFF, 0x00, /* C3-1 -> C3-16 */
	0xFF, 0x00, /* C4-1 -> C4-16 */
	0x3F, 0x00, /* C5-1 -> C5-16 */
	0x00, 0x00, /* C6-1 -> C6-16 */
	0x00, 0x00, /* C7-1 -> C7-16 */
	0x00, 0x00, /* C8-1 -> C8-16 */
	0x00, 0x00, /* C9-1 -> C9-16 */
};

// The address of the LED
#define LA(c, r) (c + r * 16 )
// Need to be an address that is not mapped, but inside the range of the controller matrix
#define NA LA(8, 8)

// The numbers in the comments are the led numbers DXX on the PCB
// The mapping is taken from the schematic of left hand side
static const uint8_t led_mapping[GDISP_SCREEN_HEIGHT][GDISP_SCREEN_WIDTH] = {
//   45        44        43        42        41        40        39
   { LA(1, 1), LA(1, 0), LA(0, 4), LA(0, 3), LA(0, 2), LA(0, 1), LA(0, 0)},
//   52        51        50        49        48        47        46
   { LA(2, 3), LA(2, 2), LA(2, 1), LA(2, 0), LA(1, 4), LA(1, 3), LA(1, 2) },
//   58        57        56        55        54        53        N/A
   { LA(3, 4), LA(3, 3), LA(3, 2), LA(3, 1), LA(3, 0), LA(2, 4), NA },
//   67        66        65        64        63        62        61
   { LA(5, 3), LA(5, 2), LA(5, 1), LA(5, 0), LA(4, 4), LA(4, 3), LA(4, 2) },
//   76        75        74        73        72        60        59
   { LA(7, 3), LA(7, 2), LA(7, 1), LA(7, 0), LA(6, 3), LA(4, 1), LA(4, 0) },
//   N/A       N/A       N/A       N/A       N/A       N/A       68
   { NA,       NA,       NA,       NA,       NA,       NA,       LA(5, 4) },
//   N/A       N/A       N/A       N/A       71        70        69
   { NA,       NA,       NA,       NA,       LA(6, 2), LA(6, 1), LA(6, 0) },
};


#define IS31_ADDR_DEFAULT 0x74 // AD connected to GND
#define IS31_TIMEOUT 5000

static GFXINLINE void init_board(GDisplay *g) {
    (void) g;
    /* I2C pins */
    palSetPadMode(GPIOB, 0, PAL_MODE_ALTERNATIVE_2); // PTB0/I2C0/SCL
    palSetPadMode(GPIOB, 1, PAL_MODE_ALTERNATIVE_2); // PTB1/I2C0/SDA
    palSetPadMode(GPIOB, 16, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOB, 16);
    /* start I2C */
    i2cStart(&I2CD1, &i2ccfg);
    // try high drive (from kiibohd)
    I2CD1.i2c->C2 |= I2Cx_C2_HDRS;
    // try glitch fixing (from kiibohd)
    I2CD1.i2c->FLT = 4;
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE const uint8_t* get_led_mask(GDisplay* g) {
    (void) g;
    return led_mask;
}

static GFXINLINE uint8_t get_led_address(GDisplay* g, uint16_t x, uint16_t y)
{
    (void) g;
    return led_mapping[y][x];
}

static GFXINLINE void set_hardware_shutdown(GDisplay* g, bool shutdown) {
    (void) g;
    if(!shutdown) {
        palSetPad(GPIOB, 16);
    }
    else {
        palClearPad(GPIOB, 16);
    }
}

static GFXINLINE void write_data(GDisplay *g, uint8_t* data, uint16_t length) {
	(void) g;
	i2cMasterTransmitTimeout(&I2CD1, IS31_ADDR_DEFAULT, data, length, 0, 0, US2ST(IS31_TIMEOUT));
}

#endif /* _GDISP_LLD_BOARD_H */
