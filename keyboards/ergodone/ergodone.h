#ifndef ERGODOX_ERGODONE_H
#define ERGODOX_ERGODONE_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

void init_ergodox(void);

inline void ergodox_right_led_1_off(void) { DDRB &= ~(1<<PB5); PORTB &= ~(1<<PB5); }
inline void ergodox_right_led_1_on(void) { DDRB |= (1<<PB5); PORTB |= (1<<PB5); }
inline void ergodox_right_led_2_off(void) { DDRB &= ~(1<<PB6); PORTB &= ~(1<<PB6); }
inline void ergodox_right_led_2_on(void) { DDRB |= (1<<PB6); PORTB |= (1<<PB6); }
inline void ergodox_right_led_3_off(void) { DDRB &= ~(1<<PB3); PORTB &= ~(1<<PB3); }
inline void ergodox_right_led_3_on(void) { DDRB |= (1<<PB3); PORTB |= (1<<PB3); }
inline void ergodox_right_led_on(uint8_t l) {
    switch (l) {
         case 1:
             ergodox_right_led_1_on();
             break;
         case 2:
             ergodox_right_led_2_on();
             break;
         case 3:
             ergodox_right_led_3_on();
             break;
         default:
             break;
        }
}

inline void ergodox_right_led_off(uint8_t l) {
    switch (l) {
         case 1:
             ergodox_right_led_1_off();
             break;
         case 2:
             ergodox_right_led_2_off();
             break;
         case 3:
             ergodox_right_led_3_off();
             break;
         default:
             break;
        }
}
inline void ergodox_board_led_off(void) { DDRB &= ~(1<<PB0); PORTB |= (1<<PB0); }
inline void ergodox_board_led_on(void) { DDRB |= (1<<PB0); PORTB &= ~(1<<PB0); }
inline void ergodox_led_all_on(void) {
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
    ergodox_board_led_on();
}
inline void ergodox_led_all_off(void) {
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    ergodox_board_led_off();
}
inline void ergodox_right_led_1_set(uint8_t n)          {}
inline void ergodox_right_led_2_set(uint8_t n)          {}
inline void ergodox_right_led_3_set(uint8_t n)          {}
inline void ergodox_right_led_set(uint8_t l, uint8_t n) {}
inline void ergodox_led_all_set(uint8_t n)              {}

/*
 *   LEFT HAND: LINES 76-83
 *  RIGHT HAND: LINES 85-92
 */
#define LAYOUT_ergodox(                                         \
                                                                \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                                k54,                            \
                        k53,k52,k51,                            \
                                                                \
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
    { k00,   k01, k02, k03, k04, k05,   k06,      k07,   k08,   k09, k0A, k0B, k0C, k0D    }, \
    { k10,   k11, k12, k13, k14, k15,   k16,      k17,   k18,   k19, k1A, k1B, k1C, k1D    }, \
    { k20,   k21, k22, k23, k24, k25,   KC_NO,    KC_NO, k28,   k29, k2A, k2B, k2C, k2D    }, \
    { k30,   k31, k32, k33, k34, k35,   k36,      k37,   k38,   k39, k3A, k3B, k3C, k3D    }, \
    { k40,   k41, k42, k43, k44, KC_NO, KC_NO,    KC_NO, KC_NO, k49, k4A, k4B, k4C, k4D    }, \
    { KC_NO, k51, k52, k53, k54, k55,   k56,      k57,   k58,   k59, k5A, k5B, k5C, KC_NO  }  \
   }

/*
 *   LEFT HAND: LINES 110-117
 *  RIGHT HAND: LINES 119-126
 */
#define LAYOUT_ergodox_80(                                      \
                                                                \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                        k45,k46,k54,                            \
                        k53,k52,k51,                            \
                                                                \
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
    { k00,   k01, k02, k03, k04, k05, k06,      k07,   k08, k09, k0A, k0B, k0C, k0D    }, \
    { k10,   k11, k12, k13, k14, k15, k16,      k17,   k18, k19, k1A, k1B, k1C, k1D    }, \
    { k20,   k21, k22, k23, k24, k25, KC_NO,    KC_NO, k28, k29, k2A, k2B, k2C, k2D    }, \
    { k30,   k31, k32, k33, k34, k35, k36,      k37,   k38, k39, k3A, k3B, k3C, k3D    }, \
    { k40,   k41, k42, k43, k44, k45, k46,      k47,   k48, k49, k4A, k4B, k4C, k4D    }, \
    { KC_NO, k51, k52, k53, k54, k55, k56,      k57,   k58, k59, k5A, k5B, k5C, KC_NO  }  \
   }

/*  ---------- LEFT HAND -----------       ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodox_pretty(                                                  \
                                                                                \
    L00,L01,L02,L03,L04,L05,L06,               R00,R01,R02,R03,R04,R05,R06,     \
    L10,L11,L12,L13,L14,L15,L16,               R10,R11,R12,R13,R14,R15,R16,     \
    L20,L21,L22,L23,L24,L25,                       R21,R22,R23,R24,R25,R26,     \
    L30,L31,L32,L33,L34,L35,L36,               R30,R31,R32,R33,R34,R35,R36,     \
    L40,L41,L42,L43,L44,                               R42,R43,R44,R45,R46,     \
                            L55,L56,       R50,R51,                             \
                                L54,       R52,                                 \
                        L53,L52,L51,       R55,R54,R53 )                        \
                                                                                \
   /* matrix positions */                                                       \
   {                                                                            \
    {   L00,L01,L02,L03,L04,L05,L06,            R00,R01,R02,R03,R04,R05,R06  }, \
    {   L10,L11,L12,L13,L14,L15,L16,            R10,R11,R12,R13,R14,R15,R16  }, \
    {   L20,L21,L22,L23,L24,L25,KC_NO,        KC_NO,R21,R22,R23,R24,R25,R26  }, \
    {   L30,L31,L32,L33,L34,L35,L36,            R30,R31,R32,R33,R34,R35,R36  }, \
    { L40,L41,L42,L43,L44,KC_NO,KC_NO,    KC_NO,KC_NO,R42,R43,R44,R45,R46    }, \
    { KC_NO,L51,L52,L53,L54,L55,L56,          R50,R51,R52,R53,R54,R55,KC_NO  }  \
   }

/*  ---------- LEFT HAND -----------       ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodox_pretty_80(                                              \
                                                                               \
    L00,L01,L02,L03,L04,L05,L06,               R00,R01,R02,R03,R04,R05,R06,    \
    L10,L11,L12,L13,L14,L15,L16,               R10,R11,R12,R13,R14,R15,R16,    \
    L20,L21,L22,L23,L24,L25,                       R21,R22,R23,R24,R25,R26,    \
    L30,L31,L32,L33,L34,L35,L36,               R30,R31,R32,R33,R34,R35,R36,    \
    L40,L41,L42,L43,L44,                               R42,R43,R44,R45,R46,    \
                            L55,L56,       R50,R51,                            \
                        L45,L46,L54,       R52,R40,R41,                        \
                        L53,L52,L51,       R55,R54,R53 )                       \
                                                                               \
   /* matrix positions */                                                      \
   {                                                                           \
    {   L00,L01,L02,L03,L04,L05,L06,          R00,R01,R02,R03,R04,R05,R06   }, \
    {   L10,L11,L12,L13,L14,L15,L16,          R10,R11,R12,R13,R14,R15,R16   }, \
    {   L20,L21,L22,L23,L24,L25,KC_NO,      KC_NO,R21,R22,R23,R24,R25,R26   }, \
    {   L30,L31,L32,L33,L34,L35,L36,          R30,R31,R32,R33,R34,R35,R36   }, \
    {   L40,L41,L42,L43,L44,L45,L46,          R40,R41,R42,R43,R44,R45,R46   }, \
    { KC_NO,L51,L52,L53,L54,L55,L56,          R50,R51,R52,R53,R54,R55,KC_NO }  \
   }

#endif
