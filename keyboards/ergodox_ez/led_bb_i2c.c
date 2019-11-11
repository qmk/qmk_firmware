/*
 * light weight WS2812 lib V2.0b
 *
 * Controls WS2811/WS2812/WS2812B RGB-LEDs
 * Author: Tim (cpldcpu@gmail.com)
 *
 * Jan 18th, 2014  v2.0b Initial Version
 * Nov 29th, 2015  v2.3  Added SK6812RGBW support
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
#ifdef RGBLIGHT_ENABLE

#    include "ws2812.h"
#    include <avr/interrupt.h>
#    include <avr/io.h>
#    include <util/delay.h>
#    include "rgblight.h"

extern rgblight_config_t rgblight_config;

/*
 * Forward declare internal functions
 *
 * The functions take a byte-array and send to the data output as WS2812 bitstream.
 * The length is the number of bytes to send - three per LED.
 */

void ws2812_sendarray(uint8_t *array, uint16_t length);
void ws2812_sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask);

// Port for the I2C
#    define I2C_DDR DDRD
#    define I2C_PIN PIND
#    define I2C_PORT PORTD

// Pins to be used in the bit banging
#    define I2C_CLK 0
#    define I2C_DAT 1

#    define I2C_DATA_HI()           \
        I2C_DDR &= ~(1 << I2C_DAT); \
        I2C_PORT |= (1 << I2C_DAT);
#    define I2C_DATA_LO()          \
        I2C_DDR |= (1 << I2C_DAT); \
        I2C_PORT &= ~(1 << I2C_DAT);

#    define I2C_CLOCK_HI()          \
        I2C_DDR &= ~(1 << I2C_CLK); \
        I2C_PORT |= (1 << I2C_CLK);
#    define I2C_CLOCK_LO()         \
        I2C_DDR |= (1 << I2C_CLK); \
        I2C_PORT &= ~(1 << I2C_CLK);

#    define I2C_DELAY 1

void I2C_WriteBit(unsigned char c) {
    if (c > 0) {
        I2C_DATA_HI();
    } else {
        I2C_DATA_LO();
    }

    I2C_CLOCK_HI();
    _delay_us(I2C_DELAY);

    I2C_CLOCK_LO();
    _delay_us(I2C_DELAY);

    if (c > 0) {
        I2C_DATA_LO();
    }

    _delay_us(I2C_DELAY);
}

// Inits bitbanging port, must be called before using the functions below
//
void I2C_Init(void) {
    I2C_PORT &= ~((1 << I2C_DAT) | (1 << I2C_CLK));

    I2C_CLOCK_HI();
    I2C_DATA_HI();

    _delay_us(I2C_DELAY);
}

// Send a START Condition
//
void I2C_Start(void) {
    // set both to high at the same time
    I2C_DDR &= ~((1 << I2C_DAT) | (1 << I2C_CLK));
    _delay_us(I2C_DELAY);

    I2C_DATA_LO();
    _delay_us(I2C_DELAY);

    I2C_CLOCK_LO();
    _delay_us(I2C_DELAY);
}

// Send a STOP Condition
//
void I2C_Stop(void) {
    I2C_CLOCK_HI();
    _delay_us(I2C_DELAY);

    I2C_DATA_HI();
    _delay_us(I2C_DELAY);
}

// write a byte to the I2C slave device
//
unsigned char I2C_Write(unsigned char c) {
    for (char i = 0; i < 8; i++) {
        I2C_WriteBit(c & 128);

        c <<= 1;
    }

    I2C_WriteBit(0);
    _delay_us(I2C_DELAY);
    _delay_us(I2C_DELAY);

    // _delay_us(I2C_DELAY);
    // return I2C_ReadBit();
    return 0;
}



void rgblight_set(void) {
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
#ifdef RGBW
            led[i].w = 0;
#endif
        }
    }


    uint8_t sreg_prev, twcr_prev;
    uint8_t led_num = RGBLED_NUM;
    sreg_prev = SREG;
    twcr_prev = TWCR;
    cli();
    TWCR &= ~(1 << TWEN);
    I2C_Init();
    I2C_Start();
    I2C_Write(0x84);
    int i = 0;
#    if defined(ERGODOX_LED_30)
    // prevent right-half code from trying to bitbang all 30
    // so with 30 LEDs, we count from 29 to 15 here, and the
    // other half does 0 to 14.
    led_num = RGBLED_NUM / 2;
    for (i = led_num + led_num - 1; i >= led_num; --i)
#    elif defined(ERGODOX_LED_15_MIRROR)
    for (i = 0; i < led_num; ++i)
#    else  // ERGDOX_LED_15 non-mirrored
    for (i = led_num - 1; i >= 0; --i)
#    endif
    {
        uint8_t *data = (uint8_t *)(led + i);
        I2C_Write(*data++);
        I2C_Write(*data++);
        I2C_Write(*data++);
#ifdef RGBW
        I2C_Write(*data++);
#endif
    }
    I2C_Stop();
    SREG = sreg_prev;
    TWCR = twcr_prev;

    ws2812_setleds(led, RGBLED_NUM);
}


#endif  // RGBLIGHT_ENABLE
