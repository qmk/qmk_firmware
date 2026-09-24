/*
Copyright 2023 @ Nuphy <https://nuphy.com/>
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

/* Caps Word */
#define CAPS_WORD_IDLE_TIMEOUT 5000
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

/* Debounce */
#define DEBOUNCE_TYPE sym_eager_pk

/* NuPhy settings */
#define TAP_CODE_DELAY              8
#define DYNAMIC_KEYMAP_MACRO_DELAY  8
#define EECONFIG_USER_DATA_SIZE     8

#define DEV_MODE_PIN                C0
#define SYS_MODE_PIN                C1
#define DC_BOOST_PIN                C2
#define NRF_RESET_PIN               B4
#define NRF_BOOT_PIN                B5
#define NRF_WAKEUP_PIN              C4
#define RGB_DRIVER_SDB1             C6
#define RGB_DRIVER_SDB2             C7

#define SERIAL_DRIVER               SD1
#define SD1_TX_PIN                  B6
#define SD1_TX_PAL_MODE             0
#define SD1_RX_PIN                  B7
#define SD1_RX_PAL_MODE             0

// I2C addresses for IS31FL3733 drivers
// 0x50 = AD <-> GND, 0x53 = AD <-> VCC
#define IS31FL3733_I2C_ADDRESS_1   IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2   IS31FL3733_I2C_ADDRESS_GND_VCC

#define IS31FL3733_I2C_TIMEOUT     1
#define I2C_DRIVER                 I2CD1
#define I2C1_SCL_PIN               B8
#define I2C1_SDA_PIN               B9
#define I2C1_CLOCK_SPEED           1000000
#define I2C1_SCL_PAL_MODE          1
#define I2C1_SDA_PAL_MODE          1
#define I2C1_TIMINGR_PRESC         0U
#define I2C1_TIMINGR_SCLDEL        0U
#define I2C1_TIMINGR_SDADEL        0U
#define I2C1_TIMINGR_SCLH          0U
#define I2C1_TIMINGR_SCLL          0U
#define I2C1_DUTY_CYCLE            FAST_DUTY_CYCLE_16_9

#define DRIVER_COUNT               2
#define DRIVER_1_LED_TOTAL         48
#define DRIVER_2_LED_TOTAL         (16 + 10)
#define RGB_MATRIX_LED_COUNT       (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define RGB_MATRIX_DEFAULT_MODE    RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES

