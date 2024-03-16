/* Copyright 2023 ArthurCyy <https://github.com/ArthurCyy>
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

#define POWER_SWITCH_PIN B0

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
