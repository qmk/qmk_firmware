#pragma once

/* --------------------------------------------------------------------------
 * I2C (SSD1306 128x32 OLED)
 *
 * XIAO RP2040
 * D4 (SDA) = RP2040 GPIO6
 * D5 (SCL) = RP2040 GPIO7
 * -------------------------------------------------------------------------- */

#define I2C_DRIVER I2CD1

#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#define I2C1_SDA_PAL_MODE 3
#define I2C1_SCL_PAL_MODE 3

#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_UPDATE_INTERVAL 20
// #define OLED_TIMEOUT 60000

/* --------------------------------------------------------------------------
 * WS2812 RGB LED
 *
 * Data  = GP12
 * Enable = GP11 (enabled in keyboard_pre_init_user())
 * -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
 * Direct Matrix
 *
 * SW1 = GP3
 * SW2 = GP4
 * SW3 = GP2
 * -------------------------------------------------------------------------- */

/* Vial-specific settings belong in:
 * keymaps/vial/config.h
 */