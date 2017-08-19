#ifndef ERGODOX_ERGODONE_H
#define ERGODOX_ERGODONE_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

void init_ergodox(void);

inline void ergodox_right_led_1_off(void)               {}
inline void ergodox_right_led_1_on(void)                {}
inline void ergodox_right_led_2_off(void)               {}
inline void ergodox_right_led_2_on(void)                {}
inline void ergodox_right_led_3_off(void)               {}
inline void ergodox_right_led_3_on(void)                {}
inline void ergodox_right_led_on(uint8_t l)             {}
inline void ergodox_right_led_off(uint8_t l)            {}
inline void ergodox_board_led_off(void)                 {}
inline void ergodox_board_led_on(void)                  {}
inline void ergodox_led_all_on(void)                    {}
inline void ergodox_led_all_off(void)                   {}
inline void ergodox_right_led_1_set(uint8_t n)          {}
inline void ergodox_right_led_2_set(uint8_t n)          {}
inline void ergodox_right_led_3_set(uint8_t n)          {}
inline void ergodox_right_led_set(uint8_t l, uint8_t n) {}
inline void ergodox_led_all_set(uint8_t n)              {}

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
    { k00,   k01, k02, k03, k04, k05,   k06,      k07,   k08,   k09, k0A, k0B, k0C, k0D    }, \
    { k10,   k11, k12, k13, k14, k15,   k16,      k17,   k18,   k19, k1A, k1B, k1C, k1D    }, \
    { k20,   k21, k22, k23, k24, k25,   KC_NO,    KC_NO, k28,   k29, k2A, k2B, k2C, k2D    }, \
    { k30,   k31, k32, k33, k34, k35,   k36,      k37,   k38,   k39, k3A, k3B, k3C, k3D    }, \
    { k40,   k41, k42, k43, k44, KC_NO, KC_NO,    KC_NO, KC_NO, k49, k4A, k4B, k4C, k4D    }, \
    { KC_NO, k51, k52, k53, k54, k55,   k56,      k57,   k58,   k59, k5A, k5B, k5C, KC_NO  } \
   }

#define LAYOUT_ergodox KEYMAP

#endif
