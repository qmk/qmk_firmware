#include "frenchdev.h"

extern inline void frenchdev_board_led_on(void);
extern inline void frenchdev_led_1_on(void);
extern inline void frenchdev_led_2_on(void);
extern inline void frenchdev_led_3_on(void);
extern inline void frenchdev_led_on(uint8_t led);

extern inline void frenchdev_board_led_off(void);
extern inline void frenchdev_led_1_off(void);
extern inline void frenchdev_led_2_off(void);
extern inline void frenchdev_led_3_off(void);
extern inline void frenchdev_led_off(uint8_t led);

extern inline void frenchdev_led_all_on(void);
extern inline void frenchdev_led_all_off(void);

extern inline void frenchdev_led_1_set(uint8_t n);
extern inline void frenchdev_led_2_set(uint8_t n);
extern inline void frenchdev_led_3_set(uint8_t n);
extern inline void frenchdev_led_set(uint8_t led, uint8_t n);

extern inline void frenchdev_led_all_set(uint8_t n);

bool i2c_initialized = 0;
uint8_t mcp23018_status = 0x20;

void matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM



    // unused pins - D4, D5, D7, E6
    // set as input with internal pull-ip enabled
    DDRD  &= ~(1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTD |=  (1<<5 | 1<<4);
    PORTE |=  (1<<6);

    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();

    matrix_init_user();
}

void frenchdev_blink_all_leds(void)
{
    frenchdev_led_all_off();
    frenchdev_led_all_set(LED_BRIGHTNESS_HI);
    frenchdev_led_1_on();
    wait_ms(50);
    frenchdev_led_2_on();
    wait_ms(50);
    frenchdev_led_3_on();
    wait_ms(50);
    frenchdev_led_1_off();
    wait_ms(50);
    frenchdev_led_2_off();
    wait_ms(50);
    frenchdev_led_3_off();
    frenchdev_led_all_off();
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;;
        wait_ms(1000);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    uint8_t data[] = {0b00000000, 0b00111111};
    mcp23018_status = i2c_writeReg(I2C_ADDR, IODIRA, data, sizeof(data), I2C_TIMEOUT);

    if (!mcp23018_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        mcp23018_status = i2c_writeReg(I2C_ADDR, GPPUA, data, sizeof(data), I2C_TIMEOUT);
    }

    // SREG=sreg_prev;

    return mcp23018_status;
}
