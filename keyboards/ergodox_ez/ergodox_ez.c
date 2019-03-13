#include QMK_KEYBOARD_H

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

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    // (tied to Vcc for hardware convenience)
    DDRB  &= ~(1<<4);  // set B(4) as input
    PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-up enabled
    DDRC  &= ~(1<<7);
    DDRD  &= ~(1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTC |=  (1<<7);
    PORTD |=  (1<<5 | 1<<4);
    PORTE |=  (1<<6);

    ergodox_blink_all_leds();

    matrix_init_user();
}

void ergodox_blink_all_leds(void)
{
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

    //ergodox_led_all_on();
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
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, ERGODOX_EZ_I2C_TIMEOUT);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, ERGODOX_EZ_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;

out:
    i2c_stop();

#ifdef LEFT_LEDS
    if (!mcp23018_status) mcp23018_status = ergodox_left_leds_update();
#endif // LEFT_LEDS

    // SREG=sreg_prev;

    return mcp23018_status;
}

#ifdef LEFT_LEDS
uint8_t ergodox_left_leds_update(void) {
    if (mcp23018_status) { // if there was an error
        return mcp23018_status;
    }
#define LEFT_LED_1_SHIFT        7       // in MCP23018 port B
#define LEFT_LED_2_SHIFT        6       // in MCP23018 port B
#define LEFT_LED_3_SHIFT        7       // in MCP23018 port A

    // set logical value (doesn't matter on inputs)
    // - unused  : hi-Z : 1
    // - input   : hi-Z : 1
    // - driving : hi-Z : 1
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(OLATA, ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111
                                & ~(ergodox_left_led_3<<LEFT_LED_3_SHIFT),
                                ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111
                                & ~(ergodox_left_led_2<<LEFT_LED_2_SHIFT)
                                & ~(ergodox_left_led_1<<LEFT_LED_1_SHIFT),
                                ERGODOX_EZ_I2C_TIMEOUT);
    if (mcp23018_status) goto out;

 out:
    i2c_stop();
    return mcp23018_status;
}
#endif


#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
// swap-hands action needs a matrix to define the swap
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0,13}, {1,13}, {2,13}, {3,13}, {4,13}, {5,13}},
    {{0,12}, {1,12}, {2,12}, {3,12}, {4,12}, {5,12}},
    {{0,11}, {1,11}, {2,11}, {3,11}, {4,11}, {5,11}},
    {{0,10}, {1,10}, {2,10}, {3,10}, {4,10}, {5,10}},
    {{0,9}, {1,9}, {2,9}, {3,9}, {4,9}, {5,9}},
    {{0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8}},
    {{0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7}},
    /* Right hand, matrix positions */
    {{0,6}, {1,6}, {2,6}, {3,6}, {4,6}, {5,6}},
    {{0,5}, {1,5}, {2,5}, {3,5}, {4,5}, {5,5}},
    {{0,4}, {1,4}, {2,4}, {3,4}, {4,4}, {5,4}},
    {{0,3}, {1,3}, {2,3}, {3,3}, {4,3}, {5,3}},
    {{0,2}, {1,2}, {2,2}, {3,2}, {4,2}, {5,2}},
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}},
    {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}},
};
#endif

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
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


__attribute__ ((weak))
const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {

    /*{row | col << 4}
      |             {x=0..224, y=0..64}
      |              |                    modifier
      |              |                    | */
    {{0|(0<<4)},   {24.9*5, 16*0}, 0}, // LED 1 on right
    {{0|(1<<4)},   {24.9*6, 16*0}, 0}, // LED 2
    {{0|(2<<4)},   {24.9*7, 16*0}, 0}, // LED 3
    {{0|(3<<4)},   {24.9*8, 16*0}, 0}, // LED 4
    {{0|(4<<4)},   {24.9*9, 16*0}, 0}, // LED 5

    {{1|(5<<4)},   {24.9*5, 16*1}, 0}, // LED 6
    {{1|(6<<4)},   {24.9*6, 16*1}, 0}, // LED 7
    {{1|(7<<4)},   {24.9*7, 16*1}, 0}, // LED 8
    {{1|(8<<4)},   {24.9*8, 16*1}, 0}, // LED 9
    {{1|(9<<4)},   {24.9*9, 16*1}, 0}, // LED 10

    {{2|(5<<4)},   {24.9*5, 16*2}, 0}, // LED 11
    {{2|(6<<4)},   {24.9*6, 16*2}, 0}, // LED 12
    {{2|(7<<4)},   {24.9*7, 16*2}, 0}, // LED 13
    {{2|(8<<4)},   {24.9*8, 16*2}, 0}, // LED 14
    {{2|(9<<4)},   {24.9*9, 16*2}, 0}, // LED 15

    {{3|(5<<4)},   {24.9*5, 16*2}, 0}, // LED 16
    {{3|(6<<4)},   {24.9*6, 16*2}, 0}, // LED 17
    {{3|(7<<4)},   {24.9*7, 16*2}, 0}, // LED 18
    {{3|(8<<4)},   {24.9*8, 16*2}, 0}, // LED 19
    {{3|(9<<4)},   {24.9*9, 16*2}, 0}, // LED 20

    {{4|(6<<4)},   {24.9*6, 16*2}, 0}, // LED 21
    {{4|(7<<4)},   {24.9*7, 16*2}, 0}, // LED 22
    {{4|(8<<4)},   {24.9*8, 16*2}, 0}, // LED 23
    {{4|(9<<4)},   {24.9*9, 16*2}, 0}, // LED 24

    {{0|(0<<4)},   {24.9*4, 16*0}, 0}, // LED 1 on left
    {{0|(1<<4)},   {24.9*3, 16*0}, 0}, // LED 2
    {{0|(2<<4)},   {24.9*2, 16*0}, 0}, // LED 3
    {{0|(3<<4)},   {24.9*1, 16*0}, 0}, // LED 4
    {{0|(4<<4)},   {24.9*0, 16*0}, 0}, // LED 5

    {{1|(5<<4)},   {24.9*4, 16*1}, 0}, // LED 6
    {{1|(6<<4)},   {24.9*3, 16*1}, 0}, // LED 7
    {{1|(7<<4)},   {24.9*2, 16*1}, 0}, // LED 8
    {{1|(8<<4)},   {24.9*1, 16*1}, 0}, // LED 9
    {{1|(9<<4)},   {24.9*0, 16*1}, 0}, // LED 10

    {{2|(5<<4)},   {24.9*4, 16*2}, 0}, // LED 11
    {{2|(6<<4)},   {24.9*3, 16*2}, 0}, // LED 12
    {{2|(7<<4)},   {24.9*2, 16*2}, 0}, // LED 13
    {{2|(8<<4)},   {24.9*1, 16*2}, 0}, // LED 14
    {{2|(9<<4)},   {24.9*0, 16*2}, 0}, // LED 15

    {{3|(5<<4)},   {24.9*4, 16*2}, 0}, // LED 16
    {{3|(6<<4)},   {24.9*3, 16*2}, 0}, // LED 17
    {{3|(7<<4)},   {24.9*2, 16*2}, 0}, // LED 18
    {{3|(8<<4)},   {24.9*1, 16*2}, 0}, // LED 19
    {{3|(9<<4)},   {24.9*0, 16*2}, 0}, // LED 20

    {{4|(6<<4)},   {24.9*3, 16*2}, 0}, // LED 21
    {{4|(7<<4)},   {24.9*2, 16*2}, 0}, // LED 22
    {{4|(8<<4)},   {24.9*1, 16*2}, 0}, // LED 23
    {{4|(9<<4)},   {24.9*0, 16*2}, 0}, // LED 24
};
#endif
