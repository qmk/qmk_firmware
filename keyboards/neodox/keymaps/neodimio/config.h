/*
Copyright 2022 Matteo Dal Molin <matteodalmo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

//One pin serial
// #define SERIAL_USART_DRIVER	SIOD0
// // #define SERIAL_USART_TX_PIN	GP0
// #define SERIAL_USART_RX_PIN	GP1
// #undef SOFT_SERIAL_PIN
// #define SOFT_SERIAL_PIN GP1


#undef SOFT_SERIAL_PIN
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

// wiring of each half
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { GP4, GP5, GP6, GP7, GP8 }  // B5 B4 B2 has some problem with right side
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { GP9, GP10, GP11, GP12, GP13, GP14, GP15 }


#undef RGB_DI_PIN


#undef DEBOUNCE
#define DEBOUNCE 5


// Set USB polling rate to 1000 Hz
#define USB_POLLING_INTERVAL_MS 1

// Lets you roll mod-tap keys
// #define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 200
// #define HOLD_ON_OTHER_KEY_PRESS
// #define PERMISSIVE_HOLD
#define TAPPING_TERM_PER_KEY
// #define IGNORE_MOD_TAP_INTERRUPT
// - Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// #define TAPPING_FORCE_HOLD
// - enable TAPPING_FORCE_HOLD only on single keys (home row mods) in order to allow auto-repeat on all other keys (like backspace or space).
// #define TAPPING_FORCE_HOLD_PER_KEY
// - Recommended for heavy chording
// #define QMK_KEYS_PER_SCAN 6


#ifdef OLED_ENABLE
    #define OLED_DISPLAY_128X64
    #define SPLIT_OLED_ENABLE
    #define OLED_DISPLAY_ADDRESS     0x3C //0x78
    #define OLED_BRIGHTNESS 128
    #define I2C_DRIVER        I2CD3
    #define I2C1_SCL_PIN     A8  //B10 I2C2 ok // B6 B8 I2C1 has some problems in some aliexpress f401 try to use weact f411 genuine( only boards with bootloaders problem?)
    #define I2C1_SDA_PIN     B4   //B3  I2C2 ok // B7 B9 I2C1 has some problems in some aliexpress f401 try to use weact f411 genuine( only boards with bootloaders problem?)
    #define I2C1_SCL_PAL_MODE 4
    #define I2C1_SDA_PAL_MODE 9
    #define I2C1_CLOCK_SPEED  400000
    #define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#endif 




#undef SPLIT_HAND_MATRIX_GRID
#define SPLIT_HAND_MATRIX_GRID GP5, GP15  // row first because the board is col2row

#undef  SPI_DRIVER
#define SPI_DRIVER   SPID0
#undef  SPI_SCK_PIN
#define SPI_SCK_PIN	 GP18
#undef  SPI_MISO_PIN
#define SPI_MISO_PIN GP20
#undef  SPI_MOSI_PIN
#define SPI_MOSI_PIN GP19
// LCD Configuration
#define LCD_RST_PIN GP16

#define LCD_CS_PIN GP17
#define LCD_DC_PIN GP21




// #define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_WPM_ENABLE

// // Master to slave:
// #define RPC_M2S_BUFFER_SIZE 48
// // // Slave to master:
// #define RPC_S2M_BUFFER_SIZE 48


#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PIN GP28
// #define BACKLIGHT_ON_STATE 1
#define BACKLIGHT_PWM_DRIVER PWMD6
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A

#undef RGB_DI_PIN
#define RGB_DI_PIN GP23

#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral

#ifdef RGBLIGHT_ENABLE
// #    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_LAYERS
#endif

/* RGB matrix support */
#ifdef RGB_MATRIX_ENABLE
    #ifndef SPLIT_LAYER_STATE_ENABLE
        #define SPLIT_LAYER_STATE_ENABLE
    #endif
#endif


// #define SPLIT_USB_TIMEOUT 2000

// #define SPLIT_USB_TIMEOUT_POLL 10

// #define SPLIT_WATCHDOG_ENABLE

// #define SPLIT_WATCHDOG_TIMEOUT 3000
// #define SPLIT_USB_TIMEOUT 1000
// #define SPLIT_USB_TIMEOUT_POLL 25
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 15000

// - Mouse tuning
// #undef MOUSEKEY_DELAY
// #define MOUSEKEY_DELAY          0
// #undef MOUSEKEY_SCROLL_DELAY
// #define MOUSEKEY_SCROLL_DELAY   100
// #undef MOUSEKEY_INTERVAL
// #define MOUSEKEY_INTERVAL       16
// #undef MOUSEKEY_WHEEL_DELAY
// #define MOUSEKEY_WHEEL_DELAY    0
// #undef MOUSEKEY_MAX_SPEED
// #define MOUSEKEY_MAX_SPEED      12
// #undef MOUSEKEY_TIME_TO_MAX
// #define MOUSEKEY_TIME_TO_MAX    64
