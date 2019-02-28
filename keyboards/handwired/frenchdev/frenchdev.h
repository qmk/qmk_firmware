#ifndef FRENCHDEV_V1_H
#define FRENCHDEV_V1_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

// I2C aliases and register addresses (see "mcp23018.md" on tmk repository)
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

void init_frenchdev(void);
void frenchdev_blink_all_leds(void);
uint8_t init_mcp23018(void);

#define LED_BRIGHTNESS_LO       15
#define LED_BRIGHTNESS_HI       255


inline void frenchdev_board_led_on(void)      { DDRD |=  (1<<6); PORTD |=  (1<<6); }
inline void frenchdev_led_1_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void frenchdev_led_2_on(void)    { DDRB |=  (1<<6); PORTB |=  (1<<6); }
inline void frenchdev_led_3_on(void)    { DDRB |=  (1<<7); PORTB |=  (1<<7); }
inline void frenchdev_led_on(uint8_t led) { DDRB |= (1<<(led+4)); PORTB |= (1<<(led+4)); }

inline void frenchdev_board_led_off(void)     { DDRD &= ~(1<<6); PORTD &= ~(1<<6); }
inline void frenchdev_led_1_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void frenchdev_led_2_off(void)   { DDRB &= ~(1<<6); PORTB &= ~(1<<6); }
inline void frenchdev_led_3_off(void)   { DDRB &= ~(1<<7); PORTB &= ~(1<<7); }
inline void frenchdev_led_off(uint8_t led) { DDRB &= ~(1<<(led+4)); PORTB &= ~(1<<(led+4)); }

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

#define LAYOUT(                                                 \
                                                                \
         k01, k02, k03, k04, k05, k06,                        k09, k0a, k0b, k0c, k0d, k0e,      \
    k10, k11, k12, k13, k14, k15, k16,                        k19, k1a, k1b, k1c, k1d, k1e, k1f, \
    k20, k21, k22, k23, k24, k25, k26,                        k29, k2a, k2b, k2c, k2d, k2e, k2f, \
    k30, k31, k32, k33, k34, k35, k36,                        k39, k3a, k3b, k3c, k3d, k3e, k3f, \
    k40, k41, k42, k43, k44, k45, k46, k47, k37,    k38, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, \
    k50, k51, k52, k53, k54, k55, k56,   k57,          k58,   k59, k5a, k5b, k5c, k5d, k5e, k5f, \
    \
    PL1, PL2, PL3, \
    PR1, PR2, PR3 \
    )                                             \
                                                  \
   /* matrix positions, inverted left and right for I2C to be on row 0-7 */\
   {                                              \
                                                  \
    { k5f,   k4f,   k3f,  k2f,   k1f,   KC_NO},   \
    { k5e,   k4e,   k3e,  k2e,   k1e,   k0e  },   \
    { k5d,   k4d,   k3d,  k2d,   k1d,   k0d  },   \
    { k5c,   k4c,   k3c,  k2c,   k1c,   k0c  },   \
    { k5b,   k4b,   k3b,  k2b,   k1b,   k0b  },   \
    { k5a,   k4a,   k3a,  k2a,   k1a,   k0a  },   \
    { k59,   k49,   k39,  k29,   k19,   k09  },   \
    { k58,   k48,   k38,  PR1,   PR2,   PR3   },   \
    \
    { k57,   k47,  k37,   PL1,   PL2,   PL3   },   \
    { k56,   k46,  k36,   k26,   k16,   k06   },   \
    { k55,   k45,  k35,   k25,   k15,   k05   },   \
    { k54,   k44,  k34,   k24,   k14,   k04   },   \
    { k53,   k43,  k33,   k23,   k13,   k03   },   \
    { k52,   k42,  k32,   k22,   k12,   k02   },   \
    { k51,   k41,  k31,   k21,   k11,   k01   },   \
    { k50,   k40,  k30,   k20,   k10,   KC_NO }   \
   }

#endif
