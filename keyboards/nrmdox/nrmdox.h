#ifndef ERGODOX_EZ_H
#define ERGODOX_EZ_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern uint8_t mcp23018_status;

void init_nrmdox(void);
void nrmdox_blink_all_leds(void);
uint8_t init_mcp23018(void);
uint8_t nrmdox_left_leds_update(void);

#define LED_BRIGHTNESS_LO       15
#define LED_BRIGHTNESS_HI       255


inline void nrmdox_board_led_on(void)      { DDRD |=  (1<<6); PORTD |=  (1<<6); }
inline void nrmdox_right_led_1_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void nrmdox_right_led_2_on(void)    { DDRB |=  (1<<6); PORTB |=  (1<<6); }
inline void nrmdox_right_led_3_on(void)    { DDRB |=  (1<<7); PORTB |=  (1<<7); }
inline void nrmdox_right_led_on(uint8_t led) { DDRB |= (1<<(led+4)); PORTB |= (1<<(led+4)); }

inline void nrmdox_board_led_off(void)     { DDRD &= ~(1<<6); PORTD &= ~(1<<6); }
inline void nrmdox_right_led_1_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void nrmdox_right_led_2_off(void)   { DDRB &= ~(1<<6); PORTB &= ~(1<<6); }
inline void nrmdox_right_led_3_off(void)   { DDRB &= ~(1<<7); PORTB &= ~(1<<7); }
inline void nrmdox_right_led_off(uint8_t led) { DDRB &= ~(1<<(led+4)); PORTB &= ~(1<<(led+4)); }

inline void nrmdox_led_all_on(void)
{
    nrmdox_board_led_on();
    nrmdox_right_led_1_on();
    nrmdox_right_led_2_on();
    nrmdox_right_led_3_on();
}

inline void nrmdox_led_all_off(void)
{
    nrmdox_board_led_off();
    nrmdox_right_led_1_off();
    nrmdox_right_led_2_off();
    nrmdox_right_led_3_off();
}

inline void nrmdox_right_led_1_set(uint8_t n)    { OCR1A = n; }
inline void nrmdox_right_led_2_set(uint8_t n)    { OCR1B = n; }
inline void nrmdox_right_led_3_set(uint8_t n)    { OCR1C = n; }
inline void nrmdox_right_led_set(uint8_t led, uint8_t n)  {
    (led == 1) ? (OCR1A = n) :
    (led == 2) ? (OCR1B = n) :
                 (OCR1C = n);
}

inline void nrmdox_led_all_set(uint8_t n)
{
    nrmdox_right_led_1_set(n);
    nrmdox_right_led_2_set(n);
    nrmdox_right_led_3_set(n);
}

#define KEYMAP(                                                 \
                                                                \
    /* left hand, spatial positions */                          \
    k00,k01,k02,k03,k04,k05,                                    \
    k10,k11,k12,k13,k14,k15,                                    \
    k20,k21,k22,k23,k24,k25,k26,                                \
                k33,k34,k35,k36,                                \
                                                                \
    /* right hand, spatial positions */                         \
        k41,k42,k43,k44,k45,k46,                                \
        k51,k52,k53,k54,k55,k56,                                \
    k60,k61,k62,k63,k64,k65,k66,                                \
    k70,k71,k72,k73                                             \
                )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
       { k00   , k01   , k02   , k03 , k04   , k05   , KC_NO }, \
       { k10   , k11   , k12   , k13 , k14   , k15   , KC_NO }, \
       { k20   , k21   , k22   , k23 , k24   , k25   , k26 }  , \
       { KC_NO , KC_NO , KC_NO , k33 , k34   , k35   , k36 }  , \
                                                                \
       { KC_NO , k41   , k42   , k43 , k44   , k45   , k46 }  , \
       { KC_NO , k51   , k52   , k53 , k54   , k55   , k56 }  , \
       { k60   , k61   , k62   , k63 , k64   , k65   , k66 }  , \
       { k70   , k71   , k72   , k73 , KC_NO , KC_NO , KC_NO } \
   }

#endif
