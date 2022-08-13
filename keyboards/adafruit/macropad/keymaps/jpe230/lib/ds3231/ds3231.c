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

#include "ds3231.h"
#include "print.h"

i2c_status_t ds3231_set_byte_reg(uint8_t reg, uint8_t data) {
    uint8_t d[1] = {data};
    return i2c_writeReg(DS3231_I2C_ADDRESS << 1, reg, d, 1, DS3231_I2C_TIMEOUT);
}

i2c_status_t ds3231_get_byte_reg(uint8_t reg, uint8_t *data) {
    return i2c_readReg(DS3231_I2C_ADDRESS << 1, reg, data, 1, DS3231_I2C_TIMEOUT);;
}

i2c_status_t ds3231_set_reg(uint8_t reg, uint8_t *data, uint16_t len) {
    return i2c_writeReg(DS3231_I2C_ADDRESS << 1, reg, data, len, DS3231_I2C_TIMEOUT);
}

i2c_status_t ds3231_get_reg(uint8_t reg, uint8_t *data, uint16_t len) {
    return i2c_readReg(DS3231_I2C_ADDRESS << 1, reg, data, len, DS3231_I2C_TIMEOUT);
}

i2c_status_t ds3231_init() {
    return i2c_start(DS3231_I2C_ADDRESS << 1);
}

static uint8_t ds3231_bcd2hex(uint8_t val)
{
    uint8_t temp;
    
    temp = val & 0x0F;              /* get ones place */
    val = (val >> 4) & 0x0F;        /* get tens place */
    val = val * 10;                 /* set tens place */
    temp = temp + val;              /* get hex */
    
    return temp;                    /* return hex */
}

i2c_status_t ds3231_set_time(ds3231_time_t t) {
    uint8_t data[7] = {0};

    if(ds3231_set_reg(DS3231_TIME_REG, data, 7) != I2C_STATUS_SUCCESS) {
        uprintf("Error while sending time to RTC!\n");
        return I2C_STATUS_ERROR;
    }

    uint8_t status[1] = {0};
    
    if(ds3231_get_byte_reg(DS3231_STATUS_REG, status)!= I2C_STATUS_SUCCESS) {
        uprintf("Error while reading status!\n");
        return I2C_STATUS_ERROR;
    }

    status[0] &= ~0x80;

    return ds3231_set_byte_reg(DS3231_STATUS_REG, status[0]);
}

i2c_status_t ds3231_get_time(ds3231_time_t *t) {
    uint8_t buf[7] = {0,0,0,0,0,0,0};

    if(ds3231_get_reg(DS3231_TIME_REG, buf, 7) != I2C_STATUS_SUCCESS) {
        uprintf("Error while reading status!\n");
        return I2C_STATUS_ERROR;
    }

    t->year   = ds3231_bcd2hex(buf[6]) + 2000 + ((buf[5] >> 7) & 0x01) * 100;  /* get year */
    t->month  = ds3231_bcd2hex(buf[5]&0x1F);                                   /* get month */
    t->week   = ds3231_bcd2hex(buf[3]);                                        /* get week */
    t->date   = ds3231_bcd2hex(buf[4]);                                        /* get date */
    t->am_pm  = (ds3231_am_pm_t)((buf[2] >> 5) & 0x01);                        /* get am pm */
    t->format = (ds3231_format_t)((buf[2] >> 6) & 0x01);                       /* get format */
    t->minute = ds3231_bcd2hex(buf[1]);                                        /* get minute */
    t->second = ds3231_bcd2hex(buf[0]);                                        /* get second */

    if (t->format == DS3231_FORMAT_12H)                                        /* if 12H */
    {
        t->hour = ds3231_bcd2hex(buf[2] & 0x1F);                               /* get hour */
    }
    else
    {
        t->hour = ds3231_bcd2hex(buf[2] & 0x3F);                               /* get hour */
    }

    t->unixtime = get_unixtime(*t);

    return I2C_STATUS_SUCCESS;
}

const uint8_t days_in_month [12] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };
uint32_t get_unixtime(ds3231_time_t t)
{
    uint16_t days;
    int16_t years;
    uint32_t unixtime;

    if (t.year >= 2000) {
        years = t.year - 2000;
    } else {
        return 0;
    }

    days = t.date - 1;
    for (uint8_t i = 1; i < t.month; i++) {
        days += xpgm_read_byte(days_in_month + i - 1);
    }
    if (t.month > 2 && years % 4 == 0) {
        days++;
    }

    // count leap days
    days += (365 * years + (years + 3) / 4);
    unixtime = ((days * 24UL + t.hour) * 60 + t.minute) * 60 + t.second + SECONDS_FROM_1970_TO_2000 + (TIME_OFFSET * 3000);
    return unixtime;
}