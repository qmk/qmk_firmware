/* Copyright 2022 MIIIW <www.miiiw.com>
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

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { A7, A6, A5, A4, A3, A2 }
#define MATRIX_COL_PINS { H0, H1, H2, H3, H4, H5, H6, H7, H8, H9, H10, H11, H12, H13, H14, H15, B3, B4 }

/* Dip Switch */
#define POWER_SWITCH_PIN B0
#define DIP_SWITCH_PINS { POWER_SWITCH_PIN, B1, B8, B12 }

/* LED indicator lights */
#define LED_CAPS_LOCK_PIN B2
#define LED_NUM_LOCK_PIN B14

/* 16 with dummy columns for shift registers */
#define SHR_SERIES_NUM 2
#define SHR_CLOCK_PIN A0
#define SHR_DATA_PIN A1
#define SHR_LATCH_PIN C15

/* MIIIW Protocol Driver */
#define MWPROTO_BITRATE 256000
#define MWPROTO_DRIVER SD1
#define MWPROTO_TX_PIN A9
#define MWPROTO_TX_PAL_MODE 1
#define MWPROTO_RX_PIN A10
#define MWPROTO_RX_PAL_MODE 1
#define MWPROTO_WAKEUP_PIN A15
#define MWPROTO_STATUS_PIN C13

/* RGB Matrix config */
#define RGB_EN_PIN A8
#define RGB_DI_PIN B15
#define RGBLED_NUM 98
#define RGB_MATRIX_LED_COUNT RGBLED_NUM
#define RGB_MATRIX_CENTER { 74, 42 }

// PWM RGB Underglow Defines
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB
#define WS2812_TRST_US 200

// I2C config
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1
#define I2C1_TIMINGR_PRESC 0x00U
#define I2C1_TIMINGR_SCLDEL 0x03U
#define I2C1_TIMINGR_SDADEL 0x01U
#define I2C1_TIMINGR_SCLH 0x03U
#define I2C1_TIMINGR_SCLL 0x09U

