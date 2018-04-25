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

void init_ergodox(void);
void ergodox_blink_all_leds(void);
uint8_t init_mcp23018(void);
uint8_t ergodox_left_leds_update(void);

#ifndef LED_BRIGHTNESS_LO
#define LED_BRIGHTNESS_LO       15
#endif
#ifndef LED_BRIGHTNESS_LO
#define LED_BRIGHTNESS_HI       255
#endif


inline void ergodox_board_led_on(void)      { DDRD |=  (1<<6); PORTD |=  (1<<6); }
inline void ergodox_right_led_1_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void ergodox_right_led_2_on(void)    { DDRB |=  (1<<6); PORTB |=  (1<<6); }
inline void ergodox_right_led_3_on(void)    { DDRB |=  (1<<7); PORTB |=  (1<<7); }
inline void ergodox_right_led_on(uint8_t led) { DDRB |= (1<<(led+4)); PORTB |= (1<<(led+4)); }

inline void ergodox_board_led_off(void)     { DDRD &= ~(1<<6); PORTD &= ~(1<<6); }
inline void ergodox_right_led_1_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void ergodox_right_led_2_off(void)   { DDRB &= ~(1<<6); PORTB &= ~(1<<6); }
inline void ergodox_right_led_3_off(void)   { DDRB &= ~(1<<7); PORTB &= ~(1<<7); }
inline void ergodox_right_led_off(uint8_t led) { DDRB &= ~(1<<(led+4)); PORTB &= ~(1<<(led+4)); }

#ifdef LEFT_LEDS
bool ergodox_left_led_1;
bool ergodox_left_led_2;
bool ergodox_left_led_3;

inline void ergodox_left_led_1_on(void)    { ergodox_left_led_1 = 1; }
inline void ergodox_left_led_2_on(void)    { ergodox_left_led_2 = 1; }
inline void ergodox_left_led_3_on(void)    { ergodox_left_led_3 = 1; }

inline void ergodox_left_led_1_off(void)    { ergodox_left_led_1 = 0; }
inline void ergodox_left_led_2_off(void)    { ergodox_left_led_2 = 0; }
inline void ergodox_left_led_3_off(void)    { ergodox_left_led_3 = 0; }
#endif // LEFT_LEDS

inline void ergodox_led_all_on(void)
{
    ergodox_board_led_on();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
#ifdef LEFT_LEDS
    ergodox_left_led_1_on();
    ergodox_left_led_2_on();
    ergodox_left_led_3_on();
#endif // LEFT_LEDS
}

inline void ergodox_led_all_off(void)
{
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
#ifdef LEFT_LEDS
    ergodox_left_led_1_off();
    ergodox_left_led_2_off();
    ergodox_left_led_3_off();
#endif // LEFT_LEDS
}

inline void ergodox_right_led_1_set(uint8_t n)    { OCR1A = n; }
inline void ergodox_right_led_2_set(uint8_t n)    { OCR1B = n; }
inline void ergodox_right_led_3_set(uint8_t n)    { OCR1C = n; }
inline void ergodox_right_led_set(uint8_t led, uint8_t n)  {
    (led == 1) ? (OCR1A = n) :
    (led == 2) ? (OCR1B = n) :
                 (OCR1C = n);
}

inline void ergodox_led_all_set(uint8_t n)
{
    ergodox_right_led_1_set(n);
    ergodox_right_led_2_set(n);
    ergodox_right_led_3_set(n);
}

#define KEYMAP(                                                 \
                                                                \
    /* left hand, spatial positions */                          \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                                k54,                            \
                        k53,k52,k51,                            \
                                                                \
    /* right hand, spatial positions */                         \
        k07,k08,k09,k0A,k0B,k0C,k0D,                            \
        k17,k18,k19,k1A,k1B,k1C,k1D,                            \
            k28,k29,k2A,k2B,k2C,k2D,                            \
        k37,k38,k39,k3A,k3B,k3C,k3D,                            \
                k49,k4A,k4B,k4C,k4D,                            \
    k57,k58,                                                    \
    k59,                                                        \
    k5C,k5B,k5A )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { k00, k10, k20, k30, k40, KC_NO },   \
    { k01, k11, k21, k31, k41, k51 },   \
    { k02, k12, k22, k32, k42, k52 },   \
    { k03, k13, k23, k33, k43, k53 },   \
    { k04, k14, k24, k34, k44, k54 },   \
    { k05, k15, k25, k35, KC_NO, k55 },   \
    { k06, k16, KC_NO, k36, KC_NO, k56 },   \
                                                                 \
    { k07, k17, KC_NO, k37,KC_NO, k57 },   \
    { k08, k18, k28, k38,KC_NO, k58 },   \
    { k09, k19, k29, k39, k49, k59 },   \
    { k0A, k1A, k2A, k3A, k4A, k5A },   \
    { k0B, k1B, k2B, k3B, k4B, k5B },   \
    { k0C, k1C, k2C, k3C, k4C, k5C },   \
    { k0D, k1D, k2D, k3D, k4D, KC_NO }    \
   }

#define KEYMAP_80(                                              \
                                                                \
    /* left hand, spatial positions */                          \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                        k45,k46,k54,                            \
                        k53,k52,k51,                            \
                                                                \
    /* right hand, spatial positions */                         \
        k07,k08,k09,k0A,k0B,k0C,k0D,                            \
        k17,k18,k19,k1A,k1B,k1C,k1D,                            \
            k28,k29,k2A,k2B,k2C,k2D,                            \
        k37,k38,k39,k3A,k3B,k3C,k3D,                            \
                k49,k4A,k4B,k4C,k4D,                            \
    k57,k58,                                                    \
    k59,k47,k48,                                                \
    k5C,k5B,k5A )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { k00, k10, k20, k30, k40, KC_NO },   \
    { k01, k11, k21, k31, k41, k51 },   \
    { k02, k12, k22, k32, k42, k52 },   \
    { k03, k13, k23, k33, k43, k53 },   \
    { k04, k14, k24, k34, k44, k54 },   \
    { k05, k15, k25, k35, k45, k55 },   \
    { k06, k16, KC_NO, k36, k46, k56 },   \
                                                                 \
    { k07, k17, KC_NO, k37, k47, k57 },   \
    { k08, k18, k28, k38, k48, k58 },   \
    { k09, k19, k29, k39, k49, k59 },   \
    { k0A, k1A, k2A, k3A, k4A, k5A },   \
    { k0B, k1B, k2B, k3B, k4B, k5B },   \
    { k0C, k1C, k2C, k3C, k4C, k5C },   \
    { k0D, k1D, k2D, k3D, k4D, KC_NO }    \
   }

#define KEYMAP_PRETTY(                                                                                        \
    /* left hand, spatial positions */     /* right hand, spatial positions */                         \
    L00,L01,L02,L03,L04,L05,L06,               R00,R01,R02,R03,R04,R05,R06,                            \
    L10,L11,L12,L13,L14,L15,L16,               R10,R11,R12,R13,R14,R15,R16,                            \
    L20,L21,L22,L23,L24,L25,                       R21,R22,R23,R24,R25,R26,                            \
    L30,L31,L32,L33,L34,L35,L36,               R30,R31,R32,R33,R34,R35,R36,                            \
    L40,L41,L42,L43,L44,                               R42,R43,R44,R45,R46,                            \
                            L55,L56,       R50,R51,                                                    \
                                L54,       R52,                                                        \
                        L53,L52,L51,       R55,R54,R53 )                                               \
                                          \
   /* matrix positions */                 \
    {                                     \
    { L00, L10, L20, L30, L40, KC_NO },   \
    { L01, L11, L21, L31, L41, L51 },     \
    { L02, L12, L22, L32, L42, L52 },     \
    { L03, L13, L23, L33, L43, L53 },     \
    { L04, L14, L24, L34, L44, L54 },     \
    { L05, L15, L25, L35, KC_NO, L55 },   \
    { L06, L16, KC_NO, L36, KC_NO, L56 }, \
                                          \
    { R00, R10, KC_NO, R30,KC_NO, R50 },  \
    { R01, R11, R21, R31,KC_NO, R51 },    \
    { R02, R12, R22, R32, R42, R52 },     \
    { R03, R13, R23, R33, R43, R53 },     \
    { R04, R14, R24, R34, R44, R54 },     \
    { R05, R15, R25, R35, R45, R55 },     \
    { R06, R16, R26, R36, R46, KC_NO }    \
    }

#define KEYMAP_PRETTY_80(                                                                              \
    /* left hand, spatial positions */     /* right hand, spatial positions */                         \
    L00,L01,L02,L03,L04,L05,L06,               R00,R01,R02,R03,R04,R05,R06,                            \
    L10,L11,L12,L13,L14,L15,L16,               R10,R11,R12,R13,R14,R15,R16,                            \
    L20,L21,L22,L23,L24,L25,                       R21,R22,R23,R24,R25,R26,                            \
    L30,L31,L32,L33,L34,L35,L36,               R30,R31,R32,R33,R34,R35,R36,                            \
    L40,L41,L42,L43,L44,                               R42,R43,R44,R45,R46,                            \
                            L55,L56,       R50,R51,                                                    \
                        L45,L46,L54,       R52,R40,R41,                                                \
                        L53,L52,L51,       R55,R54,R53 )                                               \
                                          \
      /* matrix positions */              \
    {                                     \
    { L00, L10, L20, L30, L40, KC_NO },   \
    { L01, L11, L21, L31, L41, L51 },     \
    { L02, L12, L22, L32, L42, L52 },     \
    { L03, L13, L23, L33, L43, L53 },     \
    { L04, L14, L24, L34, L44, L54 },     \
    { L05, L15, L25, L35, L45, L55 },     \
    { L06, L16, KC_NO, L36, L46, L56 },   \
                                          \
    { R00, R10, KC_NO, R30, R40, R50 },   \
    { R01, R11, R21, R31, R41, R51 },     \
    { R02, R12, R22, R32, R42, R52 },     \
    { R03, R13, R23, R33, R43, R53 },     \
    { R04, R14, R24, R34, R44, R54 },     \
    { R05, R15, R25, R35, R45, R55 },     \
    { R06, R16, R26, R36, R46, KC_NO }    \
    }

#define LAYOUT_ergodox KEYMAP
#define LAYOUT_ergodox_pretty KEYMAP_PRETTY
#define LAYOUT_ergodox_80 KEYMAP_80
#define LAYOUT_ergodox_pretty_80 KEYMAP_PRETTY_80

#endif
