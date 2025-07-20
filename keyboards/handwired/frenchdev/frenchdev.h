#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>

// I2C aliases and register addresses (see "mcp23018.md" on tmk repository)
#define I2C_ADDR        (0b0100000<<1)
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern uint8_t mcp23018_status;
#define I2C_TIMEOUT 100

void init_frenchdev(void);
void frenchdev_blink_all_leds(void);
uint8_t init_mcp23018(void);

#define LED_BRIGHTNESS_LO       15
#define LED_BRIGHTNESS_HI       255

#define FRENCHDEV_BOARD_LED_PIN D6
#define FRENCHDEV_LED_1_PIN B5
#define FRENCHDEV_LED_2_PIN B6
#define FRENCHDEV_LED_3_PIN B7

inline void frenchdev_board_led_on(void) {
    gpio_set_pin_output(FRENCHDEV_BOARD_LED_PIN);
    gpio_write_pin_high(FRENCHDEV_BOARD_LED_PIN);
}
inline void frenchdev_led_1_on(void) {
    gpio_set_pin_output(FRENCHDEV_LED_1_PIN);
    gpio_write_pin_high(FRENCHDEV_LED_1_PIN);
}
inline void frenchdev_led_2_on(void) {
    gpio_set_pin_output(FRENCHDEV_LED_2_PIN);
    gpio_write_pin_high(FRENCHDEV_LED_2_PIN);
}
inline void frenchdev_led_3_on(void) {
    gpio_set_pin_output(FRENCHDEV_LED_3_PIN);
    gpio_write_pin_high(FRENCHDEV_LED_3_PIN);
}

inline void frenchdev_board_led_off(void) {
    gpio_set_pin_input(FRENCHDEV_BOARD_LED_PIN);
}
inline void frenchdev_led_1_off(void) {
    gpio_set_pin_input(FRENCHDEV_LED_1_PIN);
}
inline void frenchdev_led_2_off(void) {
    gpio_set_pin_input(FRENCHDEV_LED_2_PIN);
}
inline void frenchdev_led_3_off(void) {
    gpio_set_pin_input(FRENCHDEV_LED_3_PIN);
}

inline void frenchdev_led_all_on(void)
{
    frenchdev_board_led_on();
    frenchdev_led_1_on();
    frenchdev_led_2_on();
    frenchdev_led_3_on();
}

inline void frenchdev_led_all_off(void)
{
    frenchdev_board_led_off();
    frenchdev_led_1_off();
    frenchdev_led_2_off();
    frenchdev_led_3_off();
}

inline void frenchdev_led_1_set(uint8_t n)    { OCR1A = n; }
inline void frenchdev_led_2_set(uint8_t n)    { OCR1B = n; }
inline void frenchdev_led_3_set(uint8_t n)    { OCR1C = n; }
inline void frenchdev_led_set(uint8_t led, uint8_t n)  {
    (led == 1) ? (OCR1A = n) :
    (led == 2) ? (OCR1B = n) :
                 (OCR1C = n);
}

inline void frenchdev_led_all_set(uint8_t n)
{
    frenchdev_led_1_set(n);
    frenchdev_led_2_set(n);
    frenchdev_led_3_set(n);
}
