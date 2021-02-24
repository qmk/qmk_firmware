#pragma once
#define PRODUCT_ID  0x8710
#define DEVICE_VER  0x0001
#define MANUFACTURER  Team.Mechlovin
#define PRODUCT       Infinity 87 RGB rev1

#define MATRIX_ROW_PINS { A10, A13, A14, C13, A4, A3 }
#define MATRIX_COL_PINS { B12, B13, B14, B15, A8, A9, B11, B10, B2, B1, B0, A7, A6, A5, A2, A1, A0 }


//rgb matrix setting
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b0110000 AD <-> GND
// 0b0110011 AD <-> VCC
// 0b0110001 AD <-> SCL
// 0b0110010 AD <-> SDA
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MATRIX_KEYPRESSES
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
//#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
//#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DRIVER_ADDR_1 0b0110010
#define DRIVER_ADDR_2 0b0110010 // this is here for compliancy reasons.
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 91
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#define DRIVER_INDICATOR_LED_TOTAL 0
