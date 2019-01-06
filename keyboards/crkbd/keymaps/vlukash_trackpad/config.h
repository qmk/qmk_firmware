#pragma once

/* Select hand configuration */
#define MASTER_RIGHT

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* Redefine TX/RX LEDs as they are not used in Elite-C. */
#undef TX_RX_LED_INIT
#undef TXLED0
#undef TXLED1
#undef RXLED0
#undef RXLED1
// #define TX_RX_LED_INIT DDRD |= (1<<2), DDRD |= (1<<3)
// #define TXLED0
// #define TXLED1
// #define RXLED0
#define RXLED1

/* key matrix size */
// Rows are doubled-up
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { F4, F5, F6, F7, B7, D5 }

/* ws2812 RGB LED */
#undef RGB_DI_PIN
#define RGB_DI_PIN B5
