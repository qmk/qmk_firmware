/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed_assert.h"
#include "device.h"

#if DEVICE_RTC

#include "rtc_api.h"
#include "rtc_iodefine.h"


#define RCR1_VAL_ON      (0x08u) // AIE = 1
#define RCR1_VAL_OFF     (0x00u)
#define RCR2_VAL_ALLSTOP (0x00u)
#define RCR2_VAL_START   (0x01u) // START = 1
#define RCR2_VAL_RESET   (0x02u) // RESET = 1
#define RCR3_VAL         (0x00u)
#define RCR5_VAL_EXTAL   (0x01u) // RCKSEL = connect EXTAL
#define RCR5_VAL_RTCX1   (0x00u) // RCKSEL = disconnect EXTAL
#define RFRH_VAL_13333   (0x8003u) // 13.3333MHz (= 64Hz * 0x32DCD) 
#define RFRL_VAL_13333   (0x2DCDu) //
#define RFRH_VAL_MAX     (0x0007u) // MAX value (= 128Hz * 0x7FFFF)
#define RFRL_VAL_MAX     (0xFFFFu) //

#define MASK_00_03_POS   (0x000Fu)
#define MASK_04_07_POS   (0x00F0u)
#define MASK_08_11_POS   (0x0F00u)
#define MASK_12_15_POS   (0xF000u)
#define MASK_16_20_POS   (0x000F0000u)
#define SHIFT_1_HBYTE    (4u)
#define SHIFT_2_HBYTE    (8u)
#define SHIFT_3_HBYTE    (12u)
#define SHIFT_1BYTE      (8u)
#define SHIFT_2BYTE      (16u)

#define TIME_ERROR_VAL   (0xFFFFFFFFu)

static int rtc_dec8_to_hex(uint8_t dec_val, uint8_t offset, int *hex_val);
static int rtc_dec16_to_hex(uint16_t dec_val, uint16_t offset, int *hex_val);
static uint8_t rtc_hex8_to_dec(uint8_t hex_val);
static uint16_t rtc_hex16_to_dec(uint16_t hex_val);


/*
 * Setup the RTC based on a time structure.
 * The rtc_init function should be executed first.
 * [in]
 * None.
 * [out]
 * None.
 */
void rtc_init(void) {
    volatile uint8_t dummy_read;

    // Set control register
    RTC.RCR2 = RCR2_VAL_ALLSTOP;
    RTC.RCR1 = RCR1_VAL_ON;
    RTC.RCR3 = RCR3_VAL;
    RTC.RCR5 = RCR5_VAL_EXTAL;
    RTC.RFRH = RFRH_VAL_13333;
    RTC.RFRL = RFRL_VAL_13333;

    // Dummy read
    dummy_read = RTC.RCR2;
    dummy_read = RTC.RCR2;

    RTC.RCR2 = RCR2_VAL_RESET; // RESET = 1

    // Dummy read
    dummy_read = RTC.RCR2;
    dummy_read = RTC.RCR2;

    // Set timer and alarm. Default value :01-01-1970 00:00:00
    RTC.RSECCNT = 0;
    RTC.RMINCNT = 0;
    RTC.RHRCNT  = 0;
    RTC.RWKCNT  = 0;
    RTC.RDAYCNT = 1;
    RTC.RMONCNT = 1;
    RTC.RYRCNT  = 0x1970;
    RTC.RSECAR  = 0;
    RTC.RMINAR  = 0;
    RTC.RHRAR   = 0;
    RTC.RWKAR   = 0;
    RTC.RDAYAR  = 1;
    RTC.RMONAR  = 1;
    RTC.RYRAR   = 0x1970;

    // Dummy read
    dummy_read = RTC.RYRCNT;
    dummy_read = RTC.RYRCNT;

}


/*
 * Release the RTC based on a time structure.
 * [in]
 * None.
 * [out]
 * None.
 */
void rtc_free(void) {
    volatile uint8_t dummy_read;

    // Set control register
    RTC.RCR2 = RCR2_VAL_ALLSTOP;
    RTC.RCR1 = RCR1_VAL_OFF;
    RTC.RCR3 = RCR3_VAL;
    RTC.RCR5 = RCR5_VAL_RTCX1;
    RTC.RFRH = RFRH_VAL_MAX;
    RTC.RFRL = RFRL_VAL_MAX;

    // Dummy read
    dummy_read = RTC.RCR2;
    dummy_read = RTC.RCR2;
    RTC.RCR2 = RCR2_VAL_RESET; // RESET = 1

    // Dummy read
    dummy_read = RTC.RCR2;
    dummy_read = RTC.RCR2;

    // Set timer and alarm. Default value :01-01-1970 00:00:00
    RTC.RSECCNT = 0;
    RTC.RMINCNT = 0;
    RTC.RHRCNT  = 0;
    RTC.RWKCNT  = 0;
    RTC.RDAYCNT = 1;
    RTC.RMONCNT = 1;
    RTC.RYRCNT  = 0x1970;
    RTC.RSECAR  = 0;
    RTC.RMINAR  = 0;
    RTC.RHRAR   = 0;
    RTC.RWKAR   = 0;
    RTC.RDAYAR  = 1;
    RTC.RMONAR  = 1;
    RTC.RYRAR   = 0x1970;

    // Dummy read
    dummy_read = RTC.RYRCNT;
    dummy_read = RTC.RYRCNT;

}


/*
 * Check the RTC has been enabled.
 * Clock Control Register RTC.RCR1(bit3): 0 = Disabled, 1 = Enabled.
 * [in]
 * None.
 * [out]
 * 0:Disabled, 1:Enabled.
 */
int rtc_isenabled(void) {
    int ret_val = 0;

    if ((RTC.RCR1 & RCR1_VAL_ON) != 0) { // RTC ON ?
        ret_val = 1;
    }

    return ret_val;
}


/*
 * RTC read function.
 * [in]
 * None.
 * [out]
 * UNIX timestamp value.
 */
time_t rtc_read(void) {

    struct tm timeinfo;
    int    err = 0;
    uint8_t tmp_regdata;
    time_t t;

    if (rtc_isenabled() != 0) {
        RTC.RCR1 &= ~0x10u; // CIE = 0
        do {
            // before reading process
            tmp_regdata  = RTC.RCR1;
            tmp_regdata &= ~0x80u; // CF = 0
            tmp_regdata |= 0x01u;  // AF = 1
            RTC.RCR1 = tmp_regdata;

            // Read RTC register
            err  = rtc_dec8_to_hex(RTC.RSECCNT , 0    , &timeinfo.tm_sec);
            err += rtc_dec8_to_hex(RTC.RMINCNT , 0    , &timeinfo.tm_min);
            err += rtc_dec8_to_hex(RTC.RHRCNT  , 0    , &timeinfo.tm_hour);
            err += rtc_dec8_to_hex(RTC.RDAYCNT , 0    , &timeinfo.tm_mday);
            err += rtc_dec8_to_hex(RTC.RMONCNT , 1    , &timeinfo.tm_mon);
            err += rtc_dec16_to_hex(RTC.RYRCNT , 1900 , &timeinfo.tm_year);
        } while ((RTC.RCR1 & 0x80u) != 0);
    } else {
        err = 1;
    }

    if (err == 0) {
        // Convert to timestamp
        t = mktime(&timeinfo);
    } else {
        // Error
        t = TIME_ERROR_VAL;
    }

    return t;
}

/*
 * Dec(8bit) to Hex function for RTC.
 * [in]
 * dec_val:Decimal value (from 0x00 to 0x99).
 * offset:Subtract offset from dec_val.
 * hex_val:Pointer of output hexadecimal value.
 * [out]
 * 0:Success
 * 1:Error
 */
static int rtc_dec8_to_hex(uint8_t dec_val, uint8_t offset, int *hex_val) {
    int err = 0;
    uint8_t ret_val;

    if (hex_val != NULL) {
        if (((dec_val & MASK_04_07_POS) >= (0x0A << SHIFT_1_HBYTE)) ||
            ((dec_val & MASK_00_03_POS) >=  0x0A)) {
            err = 1;
        } else {
            ret_val = ((dec_val & MASK_04_07_POS) >> SHIFT_1_HBYTE) * 10 +
                       (dec_val & MASK_00_03_POS);
            if (ret_val < offset) {
                err = 1;
            } else {
                *hex_val = ret_val - offset;
            }
        }
    } else {
        err = 1;
    }

    return err;
}

/*
 * Dec(16bit) to Hex function for RTC
 * [in]
 * dec_val:Decimal value (from 0x0000 to 0x9999).
 * offset:Subtract offset from dec_val.
 * hex_val:Pointer of output hexadecimal value.
 * [out]
 * 0:Success
 * 1:Error
 */
static int rtc_dec16_to_hex(uint16_t dec_val, uint16_t offset, int *hex_val) {
    int err = 0;
    uint16_t ret_val;

    if (hex_val != NULL) {
        if (((dec_val & MASK_12_15_POS) >= (0x0A << SHIFT_3_HBYTE)) ||
            ((dec_val & MASK_08_11_POS) >= (0x0A << SHIFT_2_HBYTE)) ||
            ((dec_val & MASK_04_07_POS) >= (0x0A << SHIFT_1_HBYTE)) ||
            ((dec_val & MASK_00_03_POS) >=  0x0A)) {
            err = 1;
            *hex_val = 0;
        } else {
            ret_val = (((dec_val & MASK_12_15_POS)) >> SHIFT_3_HBYTE) * 1000 +
                      (((dec_val & MASK_08_11_POS)) >> SHIFT_2_HBYTE) * 100 +
                      (((dec_val & MASK_04_07_POS)) >> SHIFT_1_HBYTE) * 10 +
                        (dec_val & MASK_00_03_POS);
            if (ret_val < offset) {
                err = 1;
            } else {
                *hex_val = ret_val - offset;
            }
        }
    } else {
        err = 1;
    }
    return err;
}

/*
 * RTC write function
 * [in]
 * t:UNIX timestamp value
 * [out]
 * None.
 */
void rtc_write(time_t t) {

    struct tm *timeinfo = localtime(&t);
    volatile uint16_t dummy_read;

    if (rtc_isenabled() != 0) {
        RTC.RCR2    = RCR2_VAL_ALLSTOP;
        dummy_read  = (uint16_t)RTC.RCR2;
        dummy_read  = (uint16_t)RTC.RCR2;
        RTC.RCR2    = RCR2_VAL_RESET; // RESET = 1
        dummy_read  = (uint16_t)RTC.RCR2;
        dummy_read  = (uint16_t)RTC.RCR2;

        RTC.RSECCNT = rtc_hex8_to_dec(timeinfo->tm_sec);
        RTC.RMINCNT = rtc_hex8_to_dec(timeinfo->tm_min);
        RTC.RHRCNT  = rtc_hex8_to_dec(timeinfo->tm_hour);
        RTC.RDAYCNT = rtc_hex8_to_dec(timeinfo->tm_mday);
        RTC.RMONCNT = rtc_hex8_to_dec(timeinfo->tm_mon + 1);
        RTC.RYRCNT  = rtc_hex16_to_dec(timeinfo->tm_year + 1900);
        dummy_read  = (uint16_t)RTC.RYRCNT;
        dummy_read  = (uint16_t)RTC.RYRCNT;

        RTC.RCR2    = RCR2_VAL_START; // START = 1

        dummy_read  = (uint16_t)RTC.RCR2;
        dummy_read  = (uint16_t)RTC.RCR2;
    }
}

/*
 * HEX to Dec(8bit) function for RTC.
 * [in]
 * hex_val:Hexadecimal value.
 * [out]
 * decimal value:From 0x00 to 0x99.
 */
static uint8_t rtc_hex8_to_dec(uint8_t hex_val) {
    uint32_t calc_data;

    calc_data  = hex_val / 10 * 0x10;
    calc_data += hex_val % 10;

    if (calc_data > 0x99) {
        calc_data = 0;
    }

    return (uint8_t)calc_data;
}

/*
 * HEX to Dec(16bit) function for RTC.
 * [in]
 * hex_val:Hexadecimal value.
 * [out]
 * decimal value:From 0x0000 to 0x9999.
 */
static uint16_t rtc_hex16_to_dec(uint16_t hex_val) {
    uint32_t calc_data;
    calc_data  =   hex_val / 1000       * 0x1000;
    calc_data += ((hex_val / 100) % 10) * 0x100;
    calc_data += ((hex_val / 10)  % 10) * 0x10;
    calc_data +=   hex_val        % 10;

    if (calc_data > 0x9999) {
        calc_data = 0;
    }
    return (uint16_t)calc_data;

}

#endif /* DEVICE_RTC */
