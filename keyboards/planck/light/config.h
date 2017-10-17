#ifndef LIGHT_CONFIG_H
#define LIGHT_CONFIG_H

#include "config_common.h"

#undef PRODUCT
#define PRODUCT Planck Light
#undef PRODUCT_ID
#define PRODUCT_ID 0x6065
#define DEVICE_VER 0x0001

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

#define MATRIX_ROW_PINS { B0, E7, F0, F1 }
#define MATRIX_COL_PINS { E6, E3, E4, D3, D4, D5, C0, A7, A6, E1, E0, D7 }

#define C6_AUDIO
#define B5_AUDIO

#undef BACKLIGHT_PIN

#define BACKLIGHT_PIN A5

/* Size of Bootloaders in bytes:
 *   Atmel DFU loader(ATmega32U4)   4096
 *   Atmel DFU loader(AT90USB128)   8192
 *   LUFA bootloader(ATmega32U4)    4096
 *   Arduino Caterina(ATmega32U4)   4096
 *   USBaspLoader(ATmega***)        2048
 *   Teensy   halfKay(ATmega32U4)   512
 *   Teensy++ halfKay(AT90USB128)   1024
 */
#define BOOTLOADER_SIZE 8192 

#define NO_USB_STARTUP_CHECK

#define PLANCK_MIT_LAYOUT

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b1110100 AD <-> GND
// 0b1110111 AD <-> VCC
// 0b1110101 AD <-> SCL
// 0b1110110 AD <-> SDA
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110110

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 25
#define DRIVER_2_LED_TOTAL 24
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL


#endif