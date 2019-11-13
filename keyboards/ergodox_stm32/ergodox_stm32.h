#pragma once

#include "quantum.h"
#include "action_layer.h"
#include <stdint.h>
#include <stdbool.h>
#include "hal.h"

// #define I2C_ADDR 0b01000000
#define I2C_ADDR 0b01000000
#define I2C_IODIRA 0x0
#define I2C_IODIRB 0x1
#define I2C_GPIOA 0x12
#define I2C_GPIOB 0x13
#define I2C_OLATA 0x14
#define I2C_OLATB 0x15
#define I2C_GPPUA 0x0C
#define I2C_GPPUB 0x0D

inline void ergodox_board_led_1_on(void) { palSetPad(GPIOA, 10); }
inline void ergodox_board_led_2_on(void) { palSetPad(GPIOA, 9); }
inline void ergodox_board_led_3_on(void) { palSetPad(GPIOA, 8); }
inline void ergodox_board_led_1_off(void) { palClearPad(GPIOA, 10); }
inline void ergodox_board_led_2_off(void) { palClearPad(GPIOA, 9); }
inline void ergodox_board_led_3_off(void) { palClearPad(GPIOA, 8); }
inline void ergodox_led_all_off(void)
{
  palClearPad(GPIOA, 10);
  palClearPad(GPIOA, 9);
  palClearPad(GPIOA, 8);
}

extern volatile int mcp23017_status;

uint8_t init_mcp23017(void);

void ergodox_blink_all_leds(void);

/*
 *   LEFT HAND: LINES 115-122
 *  RIGHT HAND: LINES 124-131
 */
#define LAYOUT_ergodox(                     \
                                            \
    k00, k01, k02, k03, k04, k05, k06,      \
    k10, k11, k12, k13, k14, k15, k16,      \
    k20, k21, k22, k23, k24, k25,           \
    k30, k31, k32, k33, k34, k35, k36,      \
    k40, k41, k42, k43, k44,                \
    k55, k56,                               \
    k54,                                    \
    k53, k52, k51,                          \
                                            \
    k07, k08, k09, k0A, k0B, k0C, k0D,      \
    k17, k18, k19, k1A, k1B, k1C, k1D,      \
    k28, k29, k2A, k2B, k2C, k2D,           \
    k37, k38, k39, k3A, k3B, k3C, k3D,      \
    k49, k4A, k4B, k4C, k4D,                \
    k57, k58,                               \
    k59,                                    \
    k5C, k5B, k5A)                          \
                                            \
  /* matrix positions */                    \
  {                                         \
    {k00, k10, k20, k30, k40, KC_NO},       \
        {k01, k11, k21, k31, k41, k51},     \
        {k02, k12, k22, k32, k42, k52},     \
        {k03, k13, k23, k33, k43, k53},     \
        {k04, k14, k24, k34, k44, k54},     \
        {k05, k15, k25, k35, KC_NO, k55},   \
        {k06, k16, KC_NO, k36, KC_NO, k56}, \
                                            \
        {k07, k17, KC_NO, k37, KC_NO, k57}, \
        {k08, k18, k28, k38, KC_NO, k58},   \
        {k09, k19, k29, k39, k49, k59},     \
        {k0A, k1A, k2A, k3A, k4A, k5A},     \
        {k0B, k1B, k2B, k3B, k4B, k5B},     \
        {k0C, k1C, k2C, k3C, k4C, k5C},     \
    {                                       \
      k0D, k1D, k2D, k3D, k4D, KC_NO        \
    }                                       \
  }

/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodox_pretty(                                            \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16, R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, R21, R22, R23, R24, R25, R26,           \
    L30, L31, L32, L33, L34, L35, L36, R30, R31, R32, R33, R34, R35, R36, \
    L40, L41, L42, L43, L44, R42, R43, R44, R45, R46,                     \
    L55, L56, R50, R51,                                                   \
    L54, R52,                                                             \
    L53, L52, L51, R55, R54, R53)                                         \
                                                                          \
  /* matrix positions */                                                  \
  {                                                                       \
    {L00, L10, L20, L30, L40, KC_NO},                                     \
        {L01, L11, L21, L31, L41, L51},                                   \
        {L02, L12, L22, L32, L42, L52},                                   \
        {L03, L13, L23, L33, L43, L53},                                   \
        {L04, L14, L24, L34, L44, L54},                                   \
        {L05, L15, L25, L35, KC_NO, L55},                                 \
        {L06, L16, KC_NO, L36, KC_NO, L56},                               \
                                                                          \
        {R00, R10, KC_NO, R30, KC_NO, R50},                               \
        {R01, R11, R21, R31, KC_NO, R51},                                 \
        {R02, R12, R22, R32, R42, R52},                                   \
        {R03, R13, R23, R33, R43, R53},                                   \
        {R04, R14, R24, R34, R44, R54},                                   \
        {R05, R15, R25, R35, R45, R55},                                   \
    {                                                                     \
      R06, R16, R26, R36, R46, KC_NO                                      \
    }                                                                     \
  }
