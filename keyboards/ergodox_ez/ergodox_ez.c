/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

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

#include "ergodox_ez.h"

extern inline void ergodox_board_led_on(void);
extern inline void ergodox_right_led_1_on(void);
extern inline void ergodox_right_led_2_on(void);
extern inline void ergodox_right_led_3_on(void);
extern inline void ergodox_right_led_on(uint8_t led);

extern inline void ergodox_board_led_off(void);
extern inline void ergodox_right_led_1_off(void);
extern inline void ergodox_right_led_2_off(void);
extern inline void ergodox_right_led_3_off(void);
extern inline void ergodox_right_led_off(uint8_t led);

extern inline void ergodox_led_all_on(void);
extern inline void ergodox_led_all_off(void);

extern inline void ergodox_right_led_1_set(uint8_t n);
extern inline void ergodox_right_led_2_set(uint8_t n);
extern inline void ergodox_right_led_3_set(uint8_t n);
extern inline void ergodox_right_led_set(uint8_t led, uint8_t n);

extern inline void ergodox_led_all_set(uint8_t n);

keyboard_config_t keyboard_config;

bool         i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
    // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    // (tied to Vcc for hardware convenience)
    DDRB &= ~(1 << 4);   // set B(4) as input
    PORTB &= ~(1 << 4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-up enabled
    DDRC &= ~(1 << 7);
    DDRD &= ~(1 << 5 | 1 << 4);
    DDRE &= ~(1 << 6);
    PORTC |= (1 << 7);
    PORTD |= (1 << 5 | 1 << 4);
    PORTE |= (1 << 6);

    keyboard_config.raw = eeconfig_read_kb();
    ergodox_led_all_set((uint8_t)keyboard_config.led_level * 255 / 4);
#ifdef RGB_MATRIX_ENABLE
    if (keyboard_config.rgb_matrix_enable) {
        rgb_matrix_set_flags(LED_FLAG_ALL);
    } else {
        rgb_matrix_set_flags(LED_FLAG_NONE);
    }
#endif

    ergodox_blink_all_leds();

    matrix_init_user();
}

void ergodox_blink_all_leds(void) {
    ergodox_led_all_off();
    ergodox_led_all_set(LED_BRIGHTNESS_DEFAULT);
    ergodox_right_led_1_on();
    _delay_ms(50);
    ergodox_right_led_2_on();
    _delay_ms(50);
    ergodox_right_led_3_on();
    _delay_ms(50);
#ifdef LEFT_LEDS
    ergodox_left_led_1_on();
    _delay_ms(50);
    if (!mcp23018_status) {
        mcp23018_status = ergodox_left_leds_update();
    }
    ergodox_left_led_2_on();
    _delay_ms(50);
    if (!mcp23018_status) {
        mcp23018_status = ergodox_left_leds_update();
    }
    ergodox_left_led_3_on();
    _delay_ms(50);
    if (!mcp23018_status) {
        mcp23018_status = ergodox_left_leds_update();
    }
#endif
    ergodox_right_led_1_off();
    _delay_ms(50);
    ergodox_right_led_2_off();
    _delay_ms(50);
    ergodox_right_led_3_off();
#ifdef LEFT_LEDS
    _delay_ms(50);
    ergodox_left_led_1_off();
    if (!mcp23018_status) {
        mcp23018_status = ergodox_left_leds_update();
    }
    _delay_ms(50);
    ergodox_left_led_2_off();
    if (!mcp23018_status) {
        mcp23018_status = ergodox_left_leds_update();
    }
    _delay_ms(50);
    ergodox_left_led_3_off();
    if (!mcp23018_status) {
        mcp23018_status = ergodox_left_leds_update();
    }
#endif

    // ergodox_led_all_on();
    //_delay_ms(333);
    ergodox_led_all_off();
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
        _delay_ms(1000);
    }
    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;

out:
    i2c_stop();

#ifdef LEFT_LEDS
    if (!mcp23018_status) mcp23018_status = ergodox_left_leds_update();
#endif  // LEFT_LEDS

    // SREG=sreg_prev;

    return mcp23018_status;
}

#ifdef LEFT_LEDS
uint8_t ergodox_left_leds_update(void) {
    if (mcp23018_status) {  // if there was an error
        return mcp23018_status;
    }
#    define LEFT_LED_1_SHIFT 7  // in MCP23018 port B
#    define LEFT_LED_2_SHIFT 6  // in MCP23018 port B
#    define LEFT_LED_3_SHIFT 7  // in MCP23018 port A

    // set logical value (doesn't matter on inputs)
    // - unused  : hi-Z : 1
    // - input   : hi-Z : 1
    // - driving : hi-Z : 1
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(OLATA, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111 & ~(ergodox_left_led_3 << LEFT_LED_3_SHIFT), ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111 & ~(ergodox_left_led_2 << LEFT_LED_2_SHIFT) & ~(ergodox_left_led_1 << LEFT_LED_1_SHIFT), ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;

out:
    i2c_stop();
    return mcp23018_status;
}
#endif

#ifdef SWAP_HANDS_ENABLE
__attribute__((weak))
// swap-hands action needs a matrix to define the swap
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0, 13}, {1, 13}, {2, 13}, {3, 13}, {4, 13}, {5, 13}},
    {{0, 12}, {1, 12}, {2, 12}, {3, 12}, {4, 12}, {5, 12}},
    {{0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}, {5, 11}},
    {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}},
    {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}},
    {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
    /* Right hand, matrix positions */
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
};
#endif

#ifdef RGB_MATRIX_ENABLE
// clang-format off
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[RGB_MATRIX_LED_COUNT] = {
/*   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C3_1,  C2_1,  C4_1}, // LED1 on right
    {0, C6_1,  C5_1,  C7_1}, // LED2
    {0, C4_2,  C3_2,  C5_2}, // LED3
    {0, C7_2,  C6_2,  C8_2}, // LED4
    {0, C2_3,  C1_3,  C3_3}, // LED5
    {0, C5_3,  C4_3,  C6_3}, // LED6
    {0, C8_3,  C7_3,  C9_3}, // LED7
    {0, C2_4,  C1_4,  C3_4}, // LED8
    {0, C6_4,  C5_4,  C7_4}, // LED9
    {0, C2_5,  C1_5,  C3_5}, // LED10
    {0, C7_5,  C6_5,  C8_5}, // LED11
    {0, C2_6,  C1_6,  C3_6}, // LED12
    {0, C5_6,  C4_6,  C6_6}, // LED13
    {0, C8_6,  C7_6,  C9_6}, // LED14
    {0, C2_7,  C1_7,  C3_7}, // LED15
    {0, C5_7,  C4_7,  C6_7}, // LED16
    {0, C2_8,  C1_8,  C3_8}, // LED17
    {0, C5_8,  C4_8,  C6_8}, // LED18

    {0, C3_9,  C2_9,  C4_9}, // LED19
    {0, C6_9,  C5_9,  C7_9}, // LED20
    {0, C4_10, C3_10, C5_10}, // LED21
    {0, C7_10, C6_10, C8_10}, // LED22
    {0, C2_11, C1_11, C3_11}, // LED23
    {0, C5_11, C4_11, C6_11}, // LED24

    {1, C3_1,  C2_1,  C4_1}, // LED1 on left
    {1, C6_1,  C5_1,  C7_1}, // LED2
    {1, C4_2,  C3_2,  C5_2}, // LED3
    {1, C7_2,  C6_2,  C8_2}, // LED4
    {1, C2_3,  C1_3,  C3_3}, // LED5
    {1, C5_3,  C4_3,  C6_3}, // LED6
    {1, C8_3,  C7_3,  C9_3}, // LED7
    {1, C2_4,  C1_4,  C3_4}, // LED8
    {1, C6_4,  C5_4,  C7_4}, // LED9
    {1, C2_5,  C1_5,  C3_5}, // LED10
    {1, C7_5,  C6_5,  C8_5}, // LED11
    {1, C2_6,  C1_6,  C3_6}, // LED12
    {1, C5_6,  C4_6,  C6_6}, // LED13
    {1, C8_6,  C7_6,  C9_6}, // LED14
    {1, C2_7,  C1_7,  C3_7}, // LED15
    {1, C5_7,  C4_7,  C6_7}, // LED16
    {1, C2_8,  C1_8,  C3_8}, // LED17
    {1, C5_8,  C4_8,  C6_8}, // LED18

    {1, C3_9,  C2_9,  C4_9}, // LED19
    {1, C6_9,  C5_9,  C7_9}, // LED20
    {1, C4_10, C3_10, C5_10}, // LED21
    {1, C7_10, C6_10, C8_10}, // LED22
    {1, C2_11, C1_11, C3_11}, // LED23
    {1, C5_11, C4_11, C6_11} // LED24
};


led_config_t g_led_config = { {
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    {  28,  33,  38,  43,  47, NO_LED },
    {  27,  32,  37,  42,  46, NO_LED },
    {  26,  31,  36,  41,  45, NO_LED },
    {  25,  30,  35,  40,  44, NO_LED },
    {  24,  29,  34,  39, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    {   0,   5,  10,  15, NO_LED, NO_LED },
    {   1,   6,  11,  16,  20, NO_LED },
    {   2,   7,  12,  17,  21, NO_LED },
    {   3,   8,  13,  18,  22, NO_LED },
    {   4,   9,  14,  19,  23, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
    { 137,   0 }, { 154,   0 }, { 172,   0 }, { 189,   0 }, { 206,   0 }, { 137,  12 },
    { 154,  12 }, { 172,  12 }, { 189,  12 }, { 206,  12 }, { 137,  25 }, { 154,  25 },
    { 172,  25 }, { 189,  25 }, { 206,  25 }, { 137,  38 }, { 154,  38 }, { 172,  38 },
    { 189,  38 }, { 206,  38 }, { 154,  51 }, { 172,  51 }, { 189,  51 }, { 206,  51 },
    {  86,   0 }, {  68,   0 }, {  51,   0 }, {  34,   0 }, {  17,   0 }, {  86,  12 },
    {  68,  12 }, {  51,  12 }, {  34,  12 }, {  17,  12 }, {  86,  25 }, {  68,  25 },
    {  51,  25 }, {  34,  25 }, {  17,  25 }, {  86,  38 }, {  68,  38 }, {  51,  38 },
    {  34,  38 }, {  17,  38 }, {  68,  51 }, {  51,  51 }, {  34,  51 }, {  17,  51 }
}, {
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1
} };
// clang-format on

#    ifdef ORYX_CONFIGURATOR
void keyboard_post_init_kb(void) {
    rgb_matrix_enable_noeeprom();
    keyboard_post_init_user();
}
#    endif
#endif

#ifdef ORYX_CONFIGURATOR
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_LEVEL:
            if (record->event.pressed) {
                keyboard_config.led_level++;
                if (keyboard_config.led_level > 4) {
                    keyboard_config.led_level = 0;
                }
                ergodox_led_all_set((uint8_t)keyboard_config.led_level * 255 / 4);
                eeconfig_update_kb(keyboard_config.raw);
                layer_state_set_kb(layer_state);
            }
            break;
#    ifdef RGB_MATRIX_ENABLE
        case TOGGLE_LAYER_COLOR:
            if (record->event.pressed) {
                keyboard_config.disable_layer_led ^= 1;
                if (keyboard_config.disable_layer_led) rgb_matrix_set_color_all(0, 0, 0);
                eeconfig_update_kb(keyboard_config.raw);
            }
            break;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        keyboard_config.rgb_matrix_enable = false;
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        keyboard_config.rgb_matrix_enable = true;
                    } break;
                }
                eeconfig_update_kb(keyboard_config.raw);
            }
            return false;
#    endif
    }
    return process_record_user(keycode, record);
}
#endif

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    keyboard_config.raw               = 0;
    keyboard_config.led_level         = 4;
    keyboard_config.rgb_matrix_enable = true;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

#ifdef ORYX_ENABLE
static uint16_t loops = 0;
static bool is_on = false;
#endif

#ifdef DYNAMIC_MACRO_ENABLE
static bool is_dynamic_recording = false;
static uint16_t dynamic_loop_timer;

void dynamic_macro_record_start_user(int8_t direction) {
    is_dynamic_recording = true;
    dynamic_loop_timer = timer_read();
    ergodox_right_led_1_on();
}

void dynamic_macro_record_end_user(int8_t direction) {
    is_dynamic_recording = false;
    layer_state_set_user(layer_state);
}
#endif

void matrix_scan_kb(void) {
#ifdef DYNAMIC_MACRO_ENABLE
    if (is_dynamic_recording) {
        ergodox_right_led_1_off();
        // if (timer_elapsed(dynamic_loop_timer) > 5)
        {
            static uint8_t counter;
            counter++;
            if (counter > 100) ergodox_right_led_1_on();
            dynamic_loop_timer = timer_read();
        }
    }
#endif

#ifdef CAPS_LOCK_STATUS
    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock) {
        ergodox_right_led_3_on();
    }
    else {
        uint8_t layer = get_highest_layer(layer_state);
        if(layer != 1) {
        ergodox_right_led_3_off();
        }
    }
#endif

    matrix_scan_user();
}
