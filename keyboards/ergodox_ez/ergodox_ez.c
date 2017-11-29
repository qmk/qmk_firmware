#include QMK_KEYBOARD_H
#include "i2cmaster.h"


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
uint8_t mcp23018_status = 0x20;

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

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA);            if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111);        if (mcp23018_status) goto out;

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
    mcp23018_status = i2c_start(I2C_ADDR_WRITE);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(OLATA);
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111
                                & ~(ergodox_left_led_3<<LEFT_LED_3_SHIFT)
                                );
    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b11111111
                                & ~(ergodox_left_led_2<<LEFT_LED_2_SHIFT)
                                & ~(ergodox_left_led_1<<LEFT_LED_1_SHIFT)
                                );
    if (mcp23018_status) goto out;

 out:
    i2c_stop();
    return mcp23018_status;
}
#endif


#ifdef ONEHAND_ENABLE
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
