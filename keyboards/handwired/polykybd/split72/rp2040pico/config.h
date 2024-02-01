/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define RP2040

#define MATRIX_COL_PINS \
    { GP10, GP11, GP12, GP13, GP14, GP15, GP16, GP3 }
#define MATRIX_ROW_PINS \
    { GP18, GP19, GP20, GP21, GP22 }

#define I2C_DRIVER I2CD0
#define I2C1_SCL_PIN GP0
#define I2C1_SDA_PIN GP1
#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 400000
//#define OLED_UPDATE_INTERVAL 1
//#define I2C1_DUTY_CYCLE STD_DUTY_CYCLE

#define OLED_INIT

#define WS2812_DI_PIN GP2

#define NOP_FUDGE 0.4

// SPI interface to write to the selected display
#define SPI_DRIVER SPID0
#define SPI_SS_PIN GP17
#define SPI_DC_PIN GP8
#define HW_RST_PIN GP9
#define SPI_SCK_PIN GP6
#define SPI_MOSI_PIN GP7
#define SPI_MISO_PIN GP4

//This number can be calculated by dividing the MCU’s clock speed
//by the desired SPI clock speed. For example, an MCU running at 8 MHz
//wanting to talk to an SPI device at 4 MHz would set the divisor to 2
#define SPI_DIVISOR (CPU_CLOCK / 10000000) //rp1040 runs at 133Mhz, SPI at 10Mhz

// Shift register to select the display
//#define SR_NMR_PIN //NO_PIN if possible
#define SR_CLK_PIN GP27
#define SR_DATA_PIN GP26
#define SR_LATCH_PIN GP28

//only for v3 and later
//#define USB_VBUS_PIN GP24


// KEY_DISPLAYS_VBAT_PIN
//#define KEY_DISPLAYS_VBAT_PIN NO_PIN
//#define KEY_DISPLAYS_VDD_PIN NO_PIN

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
//#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define ENCODERS_PAD_A { GP25 }
#define ENCODERS_PAD_B { GP29 }
#define ENCODER_RESOLUTION 2

//see also https://docs.qmk.fm/#/feature_pointing_device?id=split-keyboard-configuration


// Setup Cirque
#define CIRQUE_PINNACLE_DIAMETER_MM 35
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE

// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE

// Pointing device is on the right split.
#define POINTING_DEVICE_COMBINED

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

#define POINTING_DEVICE_ROTATION_90_RIGHT
//#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE

//#define POINTING_DEVICE_DEBUG
//#define PIMORONI_TRACKBALL_SCALE 5
//#define TRACKBALL_LED_TIMEOUT 5000

