/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "i2c_master.h"

/**
 * @brief I2C definition
 */
#define DS3231_I2C_ADDRESS          0x68 /**< iic device address */
#define DS3231_I2C_TIMEOUT           100 /**< iic timeout */

/**
 * @brief Chip register definition
 */
#define DS3231_TIME_REG             0x00
#define DS3231_ALARM1_REG           0x07
#define DS3231_ALARM2_REG           0x0B
#define DS3231_CONTROL_REG          0x0E
#define DS3231_STATUS_REG           0x0F
#define DS3231_AGING_OFFSET_REG     0x10
#define DS3231_TEMPERATURE_REG      0x11

/**
 * @brief ds3231 am pm enumeration definition
 */
typedef enum
{
    DS3231_AM = 0x00,        /**< am */
    DS3231_PM = 0x01,        /**< pm */
} ds3231_am_pm_t;

/**
 * @brief ds3231 format enumeration definition
 */
typedef enum
{
    DS3231_FORMAT_12H = 0x01,        /**< 12h format */
    DS3231_FORMAT_24H = 0x00,        /**< 24h format */
} ds3231_format_t;

/**
 * @brief Time Struct
 */
typedef struct ds3231_time_s
{
    uint16_t year;          /**< year */
    uint8_t month;          /**< month */
    uint8_t week;           /**< week */
    uint8_t date;           /**< date */
    uint8_t hour;           /**< hour */
    uint8_t minute;         /**< minute */
    uint8_t second;         /**< second */
    ds3231_format_t format; /**< data format */
    ds3231_am_pm_t am_pm;   /**< am pm */
    uint32_t unixtime;      /**< Unix Time */
} ds3231_time_t;

/**
 * @brief Helpers
 */
#define SECONDS_FROM_1970_TO_2000 946684800
#define TIME_OFFSET 6
#define xpgm_read_byte(addr) (*(const uint8_t *)(addr))
uint32_t get_unixtime(ds3231_time_t t);

/**
 * @brief Functions Prototypes
 */
i2c_status_t ds3231_init(void);

i2c_status_t ds3231_set_time(ds3231_time_t t);
i2c_status_t ds3231_get_time(ds3231_time_t *t);

