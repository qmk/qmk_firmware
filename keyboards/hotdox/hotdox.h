#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

void init_ergodox(void);

inline void ergodox_board_led_on(void)    { DDRB |= (1<<PB7); PORTB |= (1<<PB7);  }
inline void ergodox_right_led_1_on(void)  { DDRB |= (1<<PB5); PORTB &= ~(1<<PB5); }
inline void ergodox_right_led_2_on(void)  { DDRB |= (1<<PB6); PORTB &= ~(1<<PB6); }
inline void ergodox_right_led_3_on(void)  { DDRB |= (1<<PB4); PORTB &= ~(1<<PB4); }

inline void ergodox_board_led_off(void)   { DDRB |= (1<<PB7); PORTB &= ~(1<<PB7); }
inline void ergodox_right_led_1_off(void) { DDRB |= (1<<PB5); PORTB |= (1<<PB5);  }
inline void ergodox_right_led_2_off(void) { DDRB |= (1<<PB6); PORTB |= (1<<PB6);  }
inline void ergodox_right_led_3_off(void) { DDRB |= (1<<PB4); PORTB |= (1<<PB4);  }

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

inline void ergodox_led_all_on(void) {
    ergodox_board_led_on();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
}

inline void ergodox_led_all_off(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

inline void ergodox_right_led_1_set(uint8_t n)          {}
inline void ergodox_right_led_2_set(uint8_t n)          {}
inline void ergodox_right_led_3_set(uint8_t n)          {}
inline void ergodox_right_led_set(uint8_t l, uint8_t n) {}
inline void ergodox_led_all_set(uint8_t n)              {}

void ergodox_blink_all_leds(void);

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
                        k51,k52,k53,                            \
                                                                \
        k07,k08,k09,k0A,k0B,k0C,k0D,                            \
        k17,k18,k19,k1A,k1B,k1C,k1D,                            \
            k28,k29,k2A,k2B,k2C,k2D,                            \
        k37,k38,k39,k3A,k3B,k3C,k3D,                            \
                k49,k4A,k4B,k4C,k4D,                            \
    k57,k58,                                                    \
    k59,                                                        \
    k5A,k5B,k5C )                                               \
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
    k5A,k5B,k5C )                                               \
                                                                \
   /* matrix positions */                                       \
   {                                                            \
    { k00,   k01, k02, k03, k04, k05, k06,      k07,   k08, k09, k0A, k0B, k0C, k0D    }, \
    { k10,   k11, k12, k13, k14, k15, k16,      k17,   k18, k19, k1A, k1B, k1C, k1D    }, \
    { k20,   k21, k22, k23, k24, k25, KC_NO,    KC_NO, k28, k29, k2A, k2B, k2C, k2D    }, \
    { k30,   k31, k32, k33, k34, k35, k36,      k37,   k38, k39, k3A, k3B, k3C, k3D    }, \
    { k40,   k41, k42, k43, k44, k45, k45,      k47,   k48, k49, k4A, k4B, k4C, k4D    }, \
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
                        L51,L52,L53,       R53,R54,R55 )                        \
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
                        L51,L52,L53,       R53,R54,R55 )                       \
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

// Hotdox layout without needing KC_ prefix on all keys
#define LAYOUT_ergodox_kc(                                      \
                                                                \
                                                                \
    k00,k01,k02,k03,k04,k05,k06,                                \
    k10,k11,k12,k13,k14,k15,k16,                                \
    k20,k21,k22,k23,k24,k25,                                    \
    k30,k31,k32,k33,k34,k35,k36,                                \
    k40,k41,k42,k43,k44,                                        \
                            k55,k56,                            \
                                k54,                            \
                        k51,k52,k53,                            \
                                                                \
        k07,k08,k09,k0A,k0B,k0C,k0D,                            \
        k17,k18,k19,k1A,k1B,k1C,k1D,                            \
            k28,k29,k2A,k2B,k2C,k2D,                            \
        k37,k38,k39,k3A,k3B,k3C,k3D,                            \
                k49,k4A,k4B,k4C,k4D,                            \
    k57,k58,                                                    \
    k59,                                                        \
    k5A,k5B,k5C )                                               \
    LAYOUT_ergodox( \
        KC_##k00,   KC_##k01,   KC_##k02,   KC_##k03,   KC_##k04,   KC_##k05,   KC_##k06,               \
        KC_##k10,   KC_##k11,   KC_##k12,   KC_##k13,   KC_##k14,   KC_##k15,   KC_##k16,               \
        KC_##k20,   KC_##k21,   KC_##k22,   KC_##k23,   KC_##k24,   KC_##k25,                           \
        KC_##k30,   KC_##k31,   KC_##k32,   KC_##k33,   KC_##k34,   KC_##k35,   KC_##k36,               \
        KC_##k40,   KC_##k41,   KC_##k42,   KC_##k43,   KC_##k44,                                       \
                                                                                KC_##k55,   KC_##k56,   \
                                                                                            KC_##k54,   \
                                                                    KC_##k51,   KC_##k52,   KC_##k53,   \
                    KC_##k07,   KC_##k08,   KC_##k09,   KC_##k0A,   KC_##k0B,   KC_##k0C,   KC_##k0D,   \
                    KC_##k17,   KC_##k18,   KC_##k19,   KC_##k1A,   KC_##k1B,   KC_##k1C,   KC_##k1D,   \
                                KC_##k28,   KC_##k29,   KC_##k2A,   KC_##k2B,   KC_##k2C,   KC_##k2D,   \
                    KC_##k37,   KC_##k38,   KC_##k39,   KC_##k3A,   KC_##k3B,   KC_##k3C,   KC_##k3D,   \
                                            KC_##k49,   KC_##k4A,   KC_##k4B,   KC_##k4C,   KC_##k4D,   \
        KC_##k57,   KC_##k58,                                                                           \
        KC_##k59,                                                                                       \
        KC_##k5A,   KC_##k5B,   KC_##k5C                                                                \
    )


#define LAYOUT_ergodox_pretty_kc(                                                  \
                                                                                \
    L00,L01,L02,L03,L04,L05,L06,               R00,R01,R02,R03,R04,R05,R06,     \
    L10,L11,L12,L13,L14,L15,L16,               R10,R11,R12,R13,R14,R15,R16,     \
    L20,L21,L22,L23,L24,L25,                       R21,R22,R23,R24,R25,R26,     \
    L30,L31,L32,L33,L34,L35,L36,               R30,R31,R32,R33,R34,R35,R36,     \
    L40,L41,L42,L43,L44,                               R42,R43,R44,R45,R46,     \
                            L55,L56,       R50,R51,                             \
                                L54,       R52,                                 \
                        L51,L52,L53,       R53,R54,R55 )                        \
LAYOUT_ergodox_pretty( \
    KC_##L00,KC_##L01,KC_##L02,KC_##L03,KC_##L04,KC_##L05,KC_##L06,                      KC_##R00,KC_##R01,KC_##R02,KC_##R03,KC_##R04,KC_##R05,KC_##R06,    \
    KC_##L10,KC_##L11,KC_##L12,KC_##L13,KC_##L14,KC_##L15,KC_##L16,                      KC_##R10,KC_##R11,KC_##R12,KC_##R13,KC_##R14,KC_##R15,KC_##R16,    \
    KC_##L20,KC_##L21,KC_##L22,KC_##L23,KC_##L24,KC_##L25,                                        KC_##R21,KC_##R22,KC_##R23,KC_##R24,KC_##R25,KC_##R26,    \
    KC_##L30,KC_##L31,KC_##L32,KC_##L33,KC_##L34,KC_##L35,KC_##L36,                      KC_##R30,KC_##R31,KC_##R32,KC_##R33,KC_##R34,KC_##R34,KC_##R36,    \
    KC_##L40,KC_##L41,KC_##L42,KC_##L43,KC_##L44,                                                          KC_##R42,KC_##R43,KC_##R44,KC_##R45,KC_##R46,    \
                                                          KC_##L55,KC_##L56,    KC_##R50,KC_##R51,                                                          \
                                                                   KC_##L54,    KC_##R52,                                                                   \
                                                 KC_##L51,KC_##L52,KC_##L53,    KC_##R53,KC_##R54,KC_##R55)
