#ifndef ALBATROSS_H
#define ALBATROSS_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2cmaster.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

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

extern uint8_t expander_status;
extern uint8_t expander_input_pin_mask;
extern bool i2c_initialized;

void init_albatross(void);
void init_expander(void);

/*
 *   LEFT HAND: LINES 38-46
 *  RIGHT HAND: LINES 48-55
 */
#define LAYOUT_albatross(                                                  \
                                                                        \
    k00,k01,k02,k03,k04,k05,k06,k07,                                            \
    k10,k11,k12,k13,k14,k15,k16,k17,                                            \
    k20,k21,k22,k23,k24,k25,k26,k27,                                            \
    k30,k31,k32,k33,k34,k35,k36,k37,                                            \
    k40,k41,k42,k43,k44,k45,k46,                                                \
    k50,k51,k52,k53,k54,k55,                                                \
                            k56,k47,                                    \
                                k57,                                    \
                        k65,k66,k67,                                    \
                                                                        \
            k08,k09,k0A,k0B,k0C,k0D,k0E,k0F,                                    \
            k18,k19,k1A,k1B,k1C,k1D,k1E,k1F,                                    \
            k28,k29,k2A,k2B,k2C,k2D,k2E,k2F,                                    \
            k38,k39,k3A,k3B,k3C,k3D,k3E,k3F,                                    \
                k49,k4A,k4B,k4C,k4D,k4E,k4F,                                    \
                    k5A,k5B,k5C,k5D,k5E,k5F,                                    \
    k48,k59,                                                            \
    k58,                                                                \
    k68,k69,k6A )                                                       \
                                                                        \
   /* matrix positions */                                               \
   {                                                                    \
    {           k00, k01, k02, k03, k04, k05, k06, k07, \
                        k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    {           k10, k11, k12, k13, k14, k15, k16, k17, \
                        k18, k19, k1A, k1B, k0C, k0D, k0E, k0F }, \
    {           k20, k21, k22, k23, k24, k25, k26, k27, \
                        k28, k29, k2A, k2B, k0C, k0D, k0E, k0F }, \
    {           k30, k31, k32, k33, k34, k35, k36, k37, \
                        k38, k39, k3A, k3B, k0C, k0D, k0E, k0F }, \
    {           k40, k41, k42, k43, k44, k45, k46, k47, \
                        k48, k49, k4A, k4B, k4C, k4D, k4E, k4F }, \
    {           k50, k51, k52, k53, k54, k55, k56, k57, \
                        k58, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k65, k66, k67, 
            k68, k69, k6A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
   }

const led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {           58, 57, 56, 55, 54, 53, 52, 51, \
                         0,  1,  2,  3,  4,  5,  6,  7 }, \
    {           66, 65, 64, 63, 62, 61, 60, 59, \
                         8,  9, 10, 11, 12, 13, 14, 15 }, \
    {           74, 73, 72, 71, 70, 69, 68, 67, \
                        16, 17, 18, 19, 20, 21, 22, 23 }, \
    {           82, 81, 80, 79, 78, 77, 76, 75, \
                        24, 25, 26, 27, 28, 29, 30, 31 }, \
    {           91, 90, 89, 88, 87, 86, 85, 83, \
                        32, 34, 35, 36, 37, 38, 39, 40, }, \
    {           101, 100, 99, 98, 97, 96, 84, 92, \
                        41, 33, 45, 46, 47, 48, 49, 50 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 95, 94, 93, 
                        42, 43, 44, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }
}, {\
    { 119,  0 }, { 134,  0 }, { 149,  0 }, { 164,  0 }, { 179,  0 }, { 194,  0 }, { 209,  0 }, { 224,  0 }, 
    { 119, 11 }, { 134, 11 }, { 149, 11 }, { 164, 11 }, { 179, 11 }, { 194, 11 }, { 209, 11 }, { 224, 11 }, 
    { 119, 21 }, { 134, 21 }, { 149, 21 }, { 164, 21 }, { 179, 21 }, { 194, 21 }, { 209, 21 }, { 224, 21 }, 
    { 119, 32 }, { 134, 32 }, { 149, 32 }, { 164, 32 }, { 179, 32 }, { 194, 32 }, { 209, 32 }, { 224, 32 }, 
    { 119, 43 }, { 134, 53 }, { 134, 43 }, { 149, 43 }, { 164, 43 }, { 179, 43 }, { 194, 43 }, { 209, 43 }, { 224, 43 }, 
    { 119, 53 }, { 119, 64 }, { 134, 64 }, { 149, 64 }, { 149, 53 }, { 164, 53 }, { 179, 53 }, { 194, 53 }, { 209, 53 }, { 224, 53 },

                              { 105,  0 }, {  90,  0 }, {  75,  0 }, {  60,  0 }, {  45,  0 }, {  30,  0 }, {  15,  0 }, {   0,  0 }, 
                              { 105, 11 }, {  90, 11 }, {  75, 11 }, {  60, 11 }, {  45, 11 }, {  30, 11 }, {  15, 11 }, {   0, 11 }, 
                              { 105, 21 }, {  90, 21 }, {  75, 21 }, {  60, 21 }, {  45, 21 }, {  30, 21 }, {  15, 21 }, {   0, 21 }, 
                              { 105, 32 }, {  90, 32 }, {  75, 32 }, {  60, 32 }, {  45, 32 }, {  30, 32 }, {  15, 32 }, {   0, 32 }, 
                 { 105, 43 }, {  90, 43 }, {  90, 53 }, {  75, 43 }, {  60, 43 }, {  45, 43 }, {  30, 43 }, {  15, 43 }, {   0, 43 }, 
    { 105, 53 }, { 105, 64 }, {  90, 64 }, {  75, 64 }, {  75, 53 }, {  60, 53 }, {  45, 53 }, {  30, 53 }, {  15, 53 }, {   0, 53 }, 

}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4
} }


#endif
