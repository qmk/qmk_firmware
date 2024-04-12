/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
Copyright 2021 Gary Kong <kongkm88@gmail.com> (@garykong)

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

#include "bajjak.h"

extern inline void bajjak_board_led_on(void);
extern inline void bajjak_right_led_1_on(void);
extern inline void bajjak_right_led_2_on(void);
extern inline void bajjak_right_led_3_on(void);
extern inline void bajjak_right_led_on(uint8_t led);

extern inline void bajjak_board_led_off(void);
extern inline void bajjak_right_led_1_off(void);
extern inline void bajjak_right_led_2_off(void);
extern inline void bajjak_right_led_3_off(void);
extern inline void bajjak_right_led_off(uint8_t led);

extern inline void bajjak_led_all_on(void);
extern inline void bajjak_led_all_off(void);

extern inline void bajjak_right_led_1_set(uint8_t n);
extern inline void bajjak_right_led_2_set(uint8_t n);
extern inline void bajjak_right_led_3_set(uint8_t n);
extern inline void bajjak_right_led_set(uint8_t led, uint8_t n);

extern inline void bajjak_led_all_set(uint8_t n);

keyboard_config_t keyboard_config;

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    // (tied to Vcc for hardware convenience)
    DDRB  &= ~(1<<4);  // set B(4) as input
    PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins - D4, D5, E6
    // set as input with internal pull-up enabled
    DDRD  &= ~(1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTD |=  (1<<5 | 1<<4);
    PORTE |=  (1<<6);

    keyboard_config.raw = eeconfig_read_kb();
    bajjak_led_all_set((uint8_t)keyboard_config.led_level * 255 / 4 );
    bajjak_blink_all_leds();

    matrix_init_user();
}

void bajjak_blink_all_leds(void)
{
    bajjak_led_all_off();
    bajjak_led_all_set(LED_BRIGHTNESS_DEFAULT);
    bajjak_right_led_1_on();
    wait_ms(50);
    bajjak_right_led_2_on();
    wait_ms(50);
    bajjak_right_led_3_on();
    wait_ms(50);
#ifdef LEFT_LEDS
    bajjak_left_led_1_on();
    wait_ms(50);
    if (!mcp23018_status) {
      mcp23018_status = bajjak_left_leds_update();
    }
    bajjak_left_led_2_on();
    wait_ms(50);
    if (!mcp23018_status) {
      mcp23018_status = bajjak_left_leds_update();
    }
#endif
    bajjak_right_led_1_off();
    wait_ms(50);
    bajjak_right_led_2_off();
    wait_ms(50);
    bajjak_right_led_3_off();
#ifdef LEFT_LEDS
    wait_ms(50);
    bajjak_left_led_1_off();
    if (!mcp23018_status) {
      mcp23018_status = bajjak_left_leds_update();
    }
    wait_ms(50);
    bajjak_left_led_2_off();
    if (!mcp23018_status) {
      mcp23018_status = bajjak_left_leds_update();
    }
#endif

    //bajjak_led_all_on();
    //wait_ms(333);
    bajjak_led_all_off();
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        wait_ms(1000);
    }
    // i2c_init(); // on pins D(1,0)
    // wait_ms(1000);

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    uint8_t data[] = {0b00000000, 0b00111111};
    mcp23018_status = i2c_write_register(I2C_ADDR, IODIRA, data, 2, BAJJAK_EZ_I2C_TIMEOUT);

    if (!mcp23018_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        mcp23018_status = i2c_write_register(I2C_ADDR, IODIRA, data, 2, BAJJAK_EZ_I2C_TIMEOUT);
    }

#ifdef LEFT_LEDS
    if (!mcp23018_status) mcp23018_status = bajjak_left_leds_update();
#endif // LEFT_LEDS

    // SREG=sreg_prev;

    return mcp23018_status;
}

#ifdef LEFT_LEDS
uint8_t bajjak_left_leds_update(void) {
    if (mcp23018_status) { // if there was an error
        return mcp23018_status;
    }
#define LEFT_LED_1_SHIFT        7       // in MCP23018 port A
#define LEFT_LED_2_SHIFT        7       // in MCP23018 port B

    // set logical value (doesn't matter on inputs)
    // - unused  : hi-Z : 1
    // - input   : hi-Z : 1
    // - driving : hi-Z : 1
    uint8_t data[2];
    data[0] = 0b11111111 & ~(bajjak_left_led_1<<LEFT_LED_1_SHIFT);
    data[1] = 0b11111111 & ~(bajjak_left_led_2<<LEFT_LED_2_SHIFT);
    mcp23018_status = i2c_write_register(I2C_ADDR, OLATA, data, 2, BAJJAK_EZ_I2C_TIMEOUT);

    return mcp23018_status;
}
#endif


#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
// swap-hands action needs a matrix to define the swap
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0, 13}, {1, 13}, {2, 13}, {3, 13}, {4, 13}, {5, 13}, {6, 13}},
    {{0, 12}, {1, 12}, {2, 12}, {3, 12}, {4, 12}, {5, 12}, {6, 12}},
    {{0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 11}},
    {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10}},
    {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 9}},
    {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}},
    /* Right hand, matrix positions */
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}},
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}},
};
#endif

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    keyboard_config.raw = 0;
    keyboard_config.led_level = 4;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}
