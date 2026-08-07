#pragma once

#include "quantum.h"
#include "action_layer.h"
#include <stdint.h>
#include <stdbool.h>
#include <hal.h>

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
